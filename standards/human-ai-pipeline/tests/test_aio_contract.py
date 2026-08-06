import importlib.util
import json
import unittest
from pathlib import Path

from jsonschema import Draft202012Validator

ROOT = Path(__file__).resolve().parents[3]
spec = importlib.util.spec_from_file_location("aio", ROOT / "tools" / "aio_contract.py")
aio = importlib.util.module_from_spec(spec)
spec.loader.exec_module(aio)


class AIOTests(unittest.TestCase):
    @classmethod
    def setUpClass(cls):
        cls.master = aio.load(ROOT / "contracts" / "AIO-MASTER-CONTRACT.yml")
        cls.master_schema = json.loads(
            (ROOT / "contracts" / "aio-master-contract.schema.json").read_text(encoding="utf-8")
        )
        cls.instance_schema = json.loads(
            (ROOT / "contracts" / "aio-contract-instance.schema.json").read_text(encoding="utf-8")
        )
        cls.source = json.loads(
            (ROOT / "standards" / "human-ai-pipeline" / "examples" / "aio-input.example.json").read_text(encoding="utf-8")
        )

    def test_master(self):
        aio.validate_master(self.master)
        self.assertEqual(len(self.master["pipeline"]), 21)
        self.assertTrue(
            {"athena", "aesir", "forge", "aegis", "nexus_v"}
            <= set(self.master["participants"])
        )

    def test_master_json_schema(self):
        Draft202012Validator.check_schema(self.master_schema)
        Draft202012Validator(self.master_schema).validate(self.master)

    def test_one_input_runs_all_phases(self):
        instance = aio.instantiate(self.master, self.source)
        self.assertEqual(
            [phase["id"] for phase in instance["pipeline_state"]["phases"]],
            [f"P{i:02d}" for i in range(21)],
        )
        self.assertTrue(
            all(phase["effective_depth"] > 0 for phase in instance["pipeline_state"]["phases"])
        )
        aio.validate_instance(instance, self.master)

    def test_instance_json_schema(self):
        instance = aio.instantiate(self.master, self.source)
        Draft202012Validator.check_schema(self.instance_schema)
        Draft202012Validator(self.instance_schema).validate(instance)

    def test_parent_hash_enforced(self):
        instance = aio.instantiate(self.master, self.source)
        with self.assertRaises(aio.AIOError):
            aio.append_event(instance, "athena", "test", {}, "wrong")

    def test_views_not_authoritative(self):
        instance = aio.instantiate(self.master, self.source)
        view = aio.project(instance, "aesir")
        self.assertTrue(view["non_authoritative"])
        self.assertEqual(view["instance_id"], instance["identity"]["instance_id"])
        self.assertEqual(view["current_sha256"], instance["provenance"]["current_sha256"])


if __name__ == "__main__":
    unittest.main()
