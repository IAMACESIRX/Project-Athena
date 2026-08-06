from __future__ import annotations

import importlib.util
import json
import tempfile
import unittest
import sys
from pathlib import Path

ROOT = Path(__file__).resolve().parents[2]
MODULE_PATH = ROOT / "forge" / "compiler" / "forge_compiler.py"
SPEC = importlib.util.spec_from_file_location("forge_compiler", MODULE_PATH)
assert SPEC and SPEC.loader
forge_compiler = importlib.util.module_from_spec(SPEC)
sys.modules[SPEC.name] = forge_compiler
SPEC.loader.exec_module(forge_compiler)


class ForgeCompilerTests(unittest.TestCase):
    @classmethod
    def setUpClass(cls) -> None:
        cls.example_path = ROOT / "forge" / "examples" / "concept-packet.example.json"
        cls.packet = json.loads(cls.example_path.read_text(encoding="utf-8"))

    def test_example_validates(self) -> None:
        forge_compiler.validate_packet(self.packet)

    def test_ranking_is_deterministic(self) -> None:
        weights = forge_compiler.normalized_weights(self.packet)
        first = forge_compiler.rank_candidates(self.packet, weights)
        second = forge_compiler.rank_candidates(self.packet, weights)
        self.assertEqual(first, second)
        self.assertEqual(first[0].candidate_id, "CAND-003")

    def test_compile_preserves_semantic_invariants(self) -> None:
        snapshot, trace = forge_compiler.compile_packet(self.packet)
        self.assertEqual(snapshot["semantic_invariants"], self.packet["semantic_invariants"])
        self.assertEqual(trace["input_sha256"], forge_compiler.stable_hash(self.packet))
        self.assertEqual(snapshot["capability_state"], "scaffolded")

    def test_recurring_mechanisms_are_selected(self) -> None:
        snapshot, _ = forge_compiler.compile_packet(self.packet)
        selected = {item["mechanism_id"] for item in snapshot["selected_mechanisms"]}
        self.assertIn("MECH-MODEL-INDEPENDENCE", selected)
        self.assertIn("MECH-PROVENANCE", selected)
        self.assertIn("MECH-VERSIONED-STATE", selected)

    def test_declared_conflict_is_exposed(self) -> None:
        snapshot, _ = forge_compiler.compile_packet(self.packet)
        pairs = {
            tuple(sorted((item["mechanism_a"], item["mechanism_b"])))
            for item in snapshot["unresolved_conflicts"]
        }
        self.assertIn(tuple(sorted(("MECH-LOCAL-CONTEXT", "MECH-MODEL-INDEPENDENCE"))), pairs)

    def test_cli_writes_outputs(self) -> None:
        with tempfile.TemporaryDirectory() as directory:
            result = forge_compiler.main(["compile", str(self.example_path), "--out", directory])
            self.assertEqual(result, 0)
            self.assertTrue((Path(directory) / "functional-snapshot.json").exists())
            self.assertTrue((Path(directory) / "compile-trace.json").exists())


if __name__ == "__main__":
    unittest.main()
