import importlib.util
import unittest
from pathlib import Path

ROOT = Path(__file__).resolve().parents[4]
spec = importlib.util.spec_from_file_location("omega", ROOT / "tools" / "aio_omega_validate.py")
omega = importlib.util.module_from_spec(spec)
spec.loader.exec_module(omega)


class OmegaDefinitionTests(unittest.TestCase):
    @classmethod
    def setUpClass(cls):
        base = ROOT / "benchmarks" / "aio" / "omega" / "yggdrasil-habitat"
        cls.challenge = omega.load_json(base / "challenge.json")
        cls.scoring = omega.load_json(base / "scoring.json")
        cls.schema = omega.load_json(base / "submission.schema.json")

    def test_definition(self):
        omega.validate_definition(self.challenge, self.scoring, self.schema)

    def test_all_rounds_required(self):
        self.assertEqual(
            [round_def["id"] for round_def in self.challenge["rounds"]],
            [f"R{i}" for i in range(9)],
        )
        self.assertTrue(all(round_def["required"] for round_def in self.challenge["rounds"]))

    def test_score_totals_100(self):
        self.assertEqual(sum(domain["points"] for domain in self.scoring["domains"]), 100)

    def test_hidden_truth_forbidden(self):
        self.assertEqual(self.challenge["hidden_generation"]["solver_access"], "forbidden")
        self.assertTrue(self.scoring["anti_gaming"]["solver_cannot_read_hidden_pack"])


if __name__ == "__main__":
    unittest.main()
