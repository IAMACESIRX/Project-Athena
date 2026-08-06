import importlib.util
import json
import shutil
import sys
import tempfile
import threading
import urllib.request
import unittest
from pathlib import Path

ROOT = Path(__file__).resolve().parents[4]


def load_module(name: str, path: Path):
    spec = importlib.util.spec_from_file_location(name, path)
    module = importlib.util.module_from_spec(spec)
    sys.modules[name] = module
    spec.loader.exec_module(module)
    return module


runtime = load_module("aio_omega_runtime", ROOT / "tools" / "aio_omega_runtime.py")
solver = load_module("aio_omega_reference_solver", ROOT / "tools" / "aio_omega_reference_solver.py")
MODEL = ROOT / "benchmarks" / "aio" / "omega" / "yggdrasil-habitat" / "scenario-model.json"


class OmegaRuntimeTests(unittest.TestCase):
    def setUp(self):
        self.tmp = Path(tempfile.mkdtemp(prefix="aio-omega-test-"))
        self.world = runtime.OmegaWorld.load(MODEL)

    def tearDown(self):
        shutil.rmtree(self.tmp, ignore_errors=True)

    def create(self, name="session", seed="unit-seed"):
        return runtime.OmegaSession.create(self.tmp / name, self.world, seed)

    def test_hidden_truth_is_not_in_public_snapshot(self):
        session = self.create()
        public = session.public_snapshot()
        serialized = json.dumps(public)
        self.assertNotIn("causal_faults", serialized)
        self.assertNotIn("seed_hash", serialized)
        self.assertTrue(session.paths.hidden.exists())
        self.assertFalse(session.paths.hidden.is_relative_to(session.paths.public))

    def test_generation_is_deterministic_but_public_session_is_separated(self):
        first = self.create("one", "same-seed")
        second = self.create("two", "same-seed")
        self.assertEqual(first.hidden()["generated_sha256"], second.hidden()["generated_sha256"])
        self.assertEqual(first.public_snapshot()["evidence"], second.public_snapshot()["evidence"])

    def test_diagnostic_budget_and_event_order_are_enforced(self):
        session = self.create()
        for test_id in [
            "independent_power_calibration", "battery_capacity_test", "gas_tracer_test",
            "co2_bypass_inspection", "water_mass_balance", "radiator_thermal_test",
            "control_loop_replay", "biofilter_assay", "log_chain_integrity",
            "inventory_barcode_audit",
        ]:
            session.execute_diagnostic(test_id)
        with self.assertRaises(runtime.OmegaRuntimeError):
            session.execute_diagnostic("battery_capacity_test")
        with self.assertRaises(runtime.OmegaRuntimeError):
            session.reveal("R4")
        session.freeze_architecture("a" * 64)
        self.assertEqual(session.reveal("R4")["round"], "R4")
        with self.assertRaises(runtime.OmegaRuntimeError):
            session.reveal("R6")
        self.assertEqual(session.reveal("R5")["round"], "R5")
        self.assertEqual(session.reveal("R6")["round"], "R6")

    def test_unreconstructed_baseline_is_not_robust(self):
        session = self.create(seed="fragile-seed")
        hidden = session.hidden()
        architecture = {
            "capacities": dict(self.world.model["baseline"]),
            "components": ["baseline"],
            "interfaces": {"baseline": "coupled"},
            "failure_modes": ["unknown"],
            "verification": ["none"],
            "fallbacks": ["shutdown"],
            "repairs": [],
            "contingencies": [],
            "control": {"load_shed": False, "bounded_manual_mode": False},
        }
        outcomes = [self.world.simulate(hidden, architecture, replay) for replay in hidden["evaluation_replays"]]
        self.assertLess(sum(outcome["survived"] for outcome in outcomes) / len(outcomes), 0.95)

    def test_reference_solver_passes_blind_across_seeds(self):
        scores = []
        for index in range(3):
            session = runtime.OmegaSession.create(self.tmp / f"seed-{index}", self.world, f"ci-seed-{index}")
            submission = solver.solve(runtime, session, ROOT / "benchmarks" / "aio" / "omega" / "yggdrasil-habitat" / "reference-design.json")
            score = session.score_submission(submission)
            scores.append(score["score"])
            self.assertTrue(score["passed"], score)
            self.assertEqual(score["hard_failures"], [])
        self.assertGreater(min(scores), 90)

    def test_http_service_exposes_public_state_not_hidden_truth(self):
        session = self.create(seed="http-seed")
        handler = type(
            "TestOmegaHTTPHandler",
            (runtime.OmegaHTTPHandler,),
            {"session": session, "token": "test-token"},
        )
        server = runtime.ThreadingHTTPServer(("127.0.0.1", 0), handler)
        thread = threading.Thread(target=server.serve_forever, daemon=True)
        thread.start()
        try:
            request = urllib.request.Request(
                f"http://127.0.0.1:{server.server_port}/snapshot",
                headers={"Authorization": "Bearer test-token"},
            )
            with urllib.request.urlopen(request, timeout=5) as response:
                payload = json.loads(response.read())
            self.assertNotIn("causal_faults", json.dumps(payload))
            diagnostic = urllib.request.Request(
                f"http://127.0.0.1:{server.server_port}/diagnostics/water_mass_balance",
                data=b"{}",
                method="POST",
                headers={"Authorization": "Bearer test-token", "Content-Type": "application/json"},
            )
            with urllib.request.urlopen(diagnostic, timeout=5) as response:
                result = json.loads(response.read())
            self.assertEqual(result["id"], "water_mass_balance")
        finally:
            server.shutdown()
            server.server_close()
            thread.join(timeout=5)

    def test_reference_solver_has_no_hidden_truth_calls(self):
        import ast
        source = (ROOT / "tools" / "aio_omega_reference_solver.py").read_text(encoding="utf-8")
        tree = ast.parse(source)
        called_attributes = {
            node.func.attr
            for node in ast.walk(tree)
            if isinstance(node, ast.Call) and isinstance(node.func, ast.Attribute)
        }
        self.assertNotIn("hidden", called_attributes)
        self.assertNotIn("read_json", called_attributes)

    def test_evidence_fabrication_is_a_hard_failure(self):
        session = self.create(seed="fabrication-seed")
        submission = solver.solve(runtime, session, ROOT / "benchmarks" / "aio" / "omega" / "yggdrasil-habitat" / "reference-design.json")
        submission["experiments"][0]["result"]["findings"][0]["signal"] = 1.0
        score = session.score_submission(submission)
        self.assertFalse(score["passed"])
        self.assertTrue(any(item.startswith("modified_evidence") for item in score["hard_failures"]))


if __name__ == "__main__":
    unittest.main()
