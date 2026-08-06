import importlib.util, json, unittest
from pathlib import Path
ROOT=Path(__file__).resolve().parents[3]
spec=importlib.util.spec_from_file_location("aio",ROOT/"tools"/"aio_contract.py")
aio=importlib.util.module_from_spec(spec); spec.loader.exec_module(aio)
class AIOTests(unittest.TestCase):
    @classmethod
    def setUpClass(cls):
        cls.master=aio.load(ROOT/"contracts"/"AIO-MASTER-CONTRACT.yml")
        cls.source=json.loads((ROOT/"standards"/"human-ai-pipeline"/"examples"/"aio-input.example.json").read_text())
    def test_master(self):
        aio.validate_master(self.master)
        self.assertEqual(len(self.master["pipeline"]),21)
        self.assertTrue({"athena","aesir","forge","aegis","nexus_v"}<=set(self.master["participants"]))
    def test_one_input_runs_all_phases(self):
        inst=aio.instantiate(self.master,self.source)
        self.assertEqual([p["id"] for p in inst["pipeline_state"]["phases"]],[f"P{i:02d}" for i in range(21)])
        self.assertTrue(all(p["effective_depth"]>0 for p in inst["pipeline_state"]["phases"]))
        aio.validate_instance(inst,self.master)
    def test_parent_hash_enforced(self):
        inst=aio.instantiate(self.master,self.source)
        with self.assertRaises(aio.AIOError): aio.append_event(inst,"athena","test",{},"wrong")
    def test_views_not_authoritative(self):
        inst=aio.instantiate(self.master,self.source)
        self.assertTrue(aio.project(inst,"aesir")["non_authoritative"])
if __name__=="__main__": unittest.main()
