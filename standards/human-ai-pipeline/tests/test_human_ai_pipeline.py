from __future__ import annotations
import importlib.util, json, tempfile, unittest
from pathlib import Path
ROOT=Path(__file__).resolve().parents[3]
TOOL=ROOT/"tools"/"human_ai_pipeline.py"
spec=importlib.util.spec_from_file_location("human_ai_pipeline",TOOL)
module=importlib.util.module_from_spec(spec); assert spec and spec.loader; spec.loader.exec_module(module)
class HumanAIPipelineTests(unittest.TestCase):
    def test_all_profiles_validate(self):
        for name in ("athena.yml","aesir.yml","forge.yml"):
            module.validate_profile(module.load_data(ROOT/"standards"/"human-ai-pipeline"/"profiles"/name))
    def test_new_run_contains_dual_notes(self):
        path=ROOT/"standards"/"human-ai-pipeline"/"profiles"/"aesir.yml"; p=module.load_data(path)
        run=module.new_run(p,path.as_posix(),"Research test","hybrid",None)
        self.assertIn("manual_notes",run["stages"][0]); self.assertIn("machine_notes",run["stages"][0])
    def test_example_run_validates(self):
        run=module.load_data(ROOT/"standards"/"human-ai-pipeline"/"examples"/"run-packet.example.json")
        self.assertEqual(module.validate_run(run),[])
    def test_weakness_requires_mitigation(self):
        run=module.load_data(ROOT/"standards"/"human-ai-pipeline"/"examples"/"run-packet.example.json"); run["mitigations"]=[]
        with self.assertRaises(module.PipelineError): module.validate_run(run)
    def test_mitigation_preserves_named_benefit(self):
        run=module.load_data(ROOT/"standards"/"human-ai-pipeline"/"examples"/"run-packet.example.json"); run["mitigations"][0]["preserves_benefits"]=["unrelated"]
        with self.assertRaises(module.PipelineError): module.validate_run(run)
    def test_render_is_readable(self):
        text=module.render_run(module.load_data(ROOT/"standards"/"human-ai-pipeline"/"examples"/"run-packet.example.json"))
        self.assertIn("## Weaknesses",text); self.assertIn("## Mitigations and offsets",text); self.assertIn("Manual notes",text)
    def test_new_packet_can_be_written(self):
        path=ROOT/"standards"/"human-ai-pipeline"/"profiles"/"athena.yml"; p=module.load_data(path)
        with tempfile.TemporaryDirectory() as d:
            out=Path(d)/"run.json"; module.write_json(out,module.new_run(p,path.as_posix(),"Goal","manual","Title"))
            self.assertEqual(json.loads(out.read_text())["mode"],"manual")
if __name__=="__main__": unittest.main()
