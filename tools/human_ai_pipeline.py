#!/usr/bin/env python3
"""Create, validate and render project-wide human/AI pipeline run packets."""
from __future__ import annotations
import argparse, json, sys
from datetime import datetime, timezone
from pathlib import Path
from typing import Any
try:
    import yaml
except ImportError:
    yaml = None

MODES={"manual","ai_assisted","automated","hybrid"}
ACTIONS={"pause","edit","override","branch","reject","resume","rollback","change_mode","change_mitigation","request_evidence","request_review"}
class PipelineError(ValueError): pass

def now(): return datetime.now(timezone.utc).isoformat()
def load_data(path:Path)->dict[str,Any]:
    try: text=path.read_text(encoding="utf-8-sig")
    except OSError as exc: raise PipelineError(f"Cannot read {path}: {exc}") from exc
    try:
        value=yaml.safe_load(text) if path.suffix.lower() in {".yml",".yaml"} and yaml else json.loads(text)
    except Exception as exc: raise PipelineError(f"Cannot parse {path}: {exc}") from exc
    if not isinstance(value,dict): raise PipelineError(f"{path} must contain an object/mapping.")
    return value

def write_json(path:Path,value:Any):
    path.parent.mkdir(parents=True,exist_ok=True); path.write_text(json.dumps(value,indent=2,ensure_ascii=False)+"\n",encoding="utf-8")
def require(value,fields,context):
    missing=sorted(set(fields)-set(value))
    if missing: raise PipelineError(f"{context} missing fields: {', '.join(missing)}")

def validate_profile(p):
    require(p,{"schema","profile_id","system_id","name","modes_supported","entrypoints","outputs","stages","intervention","mitigation","validation"},"Profile")
    if p["schema"]!="project-athena.haips.profile.v0.1": raise PipelineError("Unsupported profile schema.")
    if set(p["modes_supported"])!=MODES: raise PipelineError("Profile must support all four execution modes.")
    require(p["entrypoints"],{"human","ai","machine","pipeline","template"},"Profile entrypoints")
    seen=set()
    for s in p["stages"]:
        require(s,{"id","name","purpose","manual_procedure","machine_procedure","outputs","intervention_allowed"},"Profile stage")
        if s["id"] in seen: raise PipelineError(f"Duplicate stage ID: {s['id']}")
        seen.add(s["id"])
        if not s["manual_procedure"] or not s["machine_procedure"]: raise PipelineError(f"Stage {s['id']} requires manual and machine procedures.")
    if p["intervention"].get("allowed") is not True or p["intervention"].get("history_preserved") is not True: raise PipelineError("Intervention and history preservation are mandatory.")
    if set(p["intervention"].get("actions",[]))-ACTIONS: raise PipelineError("Profile contains unknown intervention actions.")
    for f in ("required","preserve_benefits","declare_tradeoffs","declare_new_risks","reviewable"):
        if p["mitigation"].get(f) is not True: raise PipelineError(f"Mitigation field {f} must be true.")

def new_run(p,source,goal,mode,title=None):
    validate_profile(p)
    if mode not in MODES: raise PipelineError(f"Unsupported mode: {mode}")
    stamp=datetime.now(timezone.utc).strftime("%Y%m%dT%H%M%SZ")
    return {"schema":"project-athena.haips.run_packet.v0.1","run_id":f"HAIPS-{p['system_id'].upper()}-{stamp}","parent_run_id":None,"profile_id":p["profile_id"],"system_id":p["system_id"],"title":title or goal,"created_at":now(),"updated_at":now(),"mode":mode,"operator":{"type":"human_or_system","id":"unassigned"},"objective":goal,"status":"created","benefits_to_preserve":list(p.get("default_benefits_to_preserve",["human authority","evidence traceability"])),"weaknesses":[],"mitigations":[],"interventions":[],"stages":[{"stage_id":s["id"],"name":s["name"],"status":"pending","manual_notes":"","machine_notes":"","inputs":[],"outputs":[],"evidence":[],"decision":"","intervention_required":False} for s in p["stages"]],"validation":{"manual_checks":list(p["validation"]["manual"]),"machine_checks":list(p["validation"]["machine"]),"status":"pending"},"provenance":{"created_by":"tools/human_ai_pipeline.py","source_profile":source,"history":[{"timestamp":now(),"event":"created","mode":mode}]}}

def validate_run(r):
    require(r,{"schema","run_id","profile_id","system_id","created_at","mode","objective","status","benefits_to_preserve","weaknesses","mitigations","interventions","stages","validation","provenance"},"Run packet")
    if r["schema"]!="project-athena.haips.run_packet.v0.1" or r["mode"] not in MODES: raise PipelineError("Unsupported run schema or execution mode.")
    if not r["benefits_to_preserve"]: raise PipelineError("At least one benefit to preserve is required.")
    warnings=[]; weaknesses={}
    for w in r["weaknesses"]:
        require(w,{"weakness_id","description","triggers","harms","associated_benefits","status","disposition"},"Weakness")
        if w["weakness_id"] in weaknesses: raise PipelineError(f"Duplicate weakness ID: {w['weakness_id']}")
        if not w["associated_benefits"]: raise PipelineError(f"Weakness {w['weakness_id']} requires associated benefits.")
        if w["disposition"]=="accept" and not w.get("acceptance_reason"): raise PipelineError(f"Accepted weakness {w['weakness_id']} requires a reason.")
        weaknesses[w["weakness_id"]]=w
    covered=set()
    for m in r["mitigations"]:
        require(m,{"mitigation_id","weakness_ids","control","preserves_benefits","activation_trigger","execution_modes","tradeoffs","new_risks","verification","review_condition","removal_condition","status"},"Mitigation")
        unknown=set(m["weakness_ids"])-set(weaknesses)
        if unknown: raise PipelineError(f"Mitigation {m['mitigation_id']} references unknown weaknesses: {sorted(unknown)}")
        covered.update(m["weakness_ids"])
        known=set(r["benefits_to_preserve"])
        for wid in m["weakness_ids"]: known.update(weaknesses[wid]["associated_benefits"])
        if not set(m["preserves_benefits"]).intersection(known): raise PipelineError(f"Mitigation {m['mitigation_id']} does not preserve a declared benefit.")
        if not m["tradeoffs"] or not m["new_risks"]: raise PipelineError(f"Mitigation {m['mitigation_id']} must declare trade-offs and new risks.")
        require(m["verification"],{"manual","machine"},"Mitigation verification")
        if not m["verification"]["manual"] or not m["verification"]["machine"]: raise PipelineError(f"Mitigation {m['mitigation_id']} requires manual and machine verification.")
    for wid,w in weaknesses.items():
        if w["disposition"]=="mitigate" and wid not in covered: raise PipelineError(f"Weakness {wid} is marked mitigate but has no mitigation.")
        if w["status"]=="open" and w["disposition"]=="monitor": warnings.append(f"Weakness {wid} is open and monitoring-only.")
    for i in r["interventions"]:
        require(i,{"intervention_id","timestamp","actor","authority","stage_id","action","reason","changed_fields","validation_required"},"Intervention")
        if i["action"] not in ACTIONS: raise PipelineError(f"Invalid intervention action: {i['action']}")
    for s in r["stages"]:
        require(s,{"stage_id","name","status","manual_notes","machine_notes","inputs","outputs","evidence","decision","intervention_required"},"Run stage")
        if s["status"]=="skipped" and not s.get("skip_reason"): warnings.append(f"Stage {s['stage_id']} is skipped without reason.")
    return warnings

def render_run(r):
    warnings=validate_run(r); esc=lambda x:str(x).replace("|","\\|").replace("\n"," ")
    lines=[f"# {r.get('title') or r['run_id']}","",f"- **Run:** `{r['run_id']}`",f"- **System/profile:** `{r['system_id']}` / `{r['profile_id']}`",f"- **Mode:** `{r['mode']}`",f"- **Status:** `{r['status']}`","","## Objective","",r["objective"],"","## Benefits to preserve",""]+[f"- {x}" for x in r["benefits_to_preserve"]]
    lines += ["","## Pipeline stages","","| Stage | Status | Decision | Manual notes | Machine notes |","|---|---|---|---|---|"]
    for s in r["stages"]: lines.append(f"| {esc(s['stage_id']+' '+s['name'])} | {s['status']} | {esc(s['decision'])} | {esc(s['manual_notes'])} | {esc(s['machine_notes'])} |")
    lines += ["","## Weaknesses","","| ID | Description | Harms | Benefits associated | Disposition | Status |","|---|---|---|---|---|---|"]
    for w in r["weaknesses"]: lines.append(f"| {w['weakness_id']} | {w['description']} | {'; '.join(w['harms'])} | {'; '.join(w['associated_benefits'])} | {w['disposition']} | {w['status']} |")
    lines += ["","## Mitigations and offsets","","| ID | Weaknesses | Control | Benefits preserved | Trade-offs | New risks | Status |","|---|---|---|---|---|---|---|"]
    for m in r["mitigations"]: lines.append(f"| {m['mitigation_id']} | {', '.join(m['weakness_ids'])} | {m['control']} | {'; '.join(m['preserves_benefits'])} | {'; '.join(m['tradeoffs'])} | {'; '.join(m['new_risks'])} | {m['status']} |")
    lines += ["","## Interventions",""]
    if r["interventions"]:
        lines += ["| ID | Actor | Stage | Action | Reason |","|---|---|---|---|---|"]
        for i in r["interventions"]: lines.append(f"| {i['intervention_id']} | {i['actor']} | {i['stage_id']} | {i['action']} | {i['reason']} |")
    else: lines.append("No interventions recorded.")
    lines += ["","## Validation","",f"- Status: `{r['validation']['status']}`"]
    if warnings: lines += ["","## Warnings",""]+[f"- {w}" for w in warnings]
    lines += ["","## Provenance","",f"- Created by: `{r['provenance']['created_by']}`",f"- Source profile: `{r['provenance']['source_profile']}`",""]
    return "\n".join(lines)

def profile_paths(p,root):
    return [f"{p['profile_id']} missing {k} path: {v}" for k,v in p["entrypoints"].items() if not(k=="tool" and v is None) and not(root/v).exists()]

def main():
    ap=argparse.ArgumentParser(); sub=ap.add_subparsers(dest="cmd",required=True)
    n=sub.add_parser("new"); n.add_argument("--profile",type=Path,required=True); n.add_argument("--goal",required=True); n.add_argument("--mode",choices=sorted(MODES),default="hybrid"); n.add_argument("--title"); n.add_argument("--out",type=Path,required=True)
    v=sub.add_parser("validate"); v.add_argument("run",type=Path)
    r=sub.add_parser("render"); r.add_argument("run",type=Path); r.add_argument("--out",type=Path)
    p=sub.add_parser("validate-profile"); p.add_argument("profile",type=Path)
    c=sub.add_parser("compliance"); c.add_argument("--root",type=Path,default=Path(".")); c.add_argument("--profiles",type=Path,nargs="+",required=True)
    a=ap.parse_args()
    try:
        if a.cmd=="new":
            prof=load_data(a.profile); run=new_run(prof,a.profile.as_posix(),a.goal,a.mode,a.title); write_json(a.out,run); print(json.dumps({"status":"PASS","run_id":run["run_id"],"output":str(a.out)},indent=2))
        elif a.cmd=="validate": print(json.dumps({"status":"WARN" if (w:=validate_run(load_data(a.run))) else "PASS","warnings":w},indent=2))
        elif a.cmd=="render":
            text=render_run(load_data(a.run)); a.out.parent.mkdir(parents=True,exist_ok=True) if a.out else None; a.out.write_text(text+"\n",encoding="utf-8") if a.out else print(text)
        elif a.cmd=="validate-profile": validate_profile(load_data(a.profile)); print(f"PASS: {a.profile}")
        else:
            errors=[]
            for path in a.profiles:
                try: prof=load_data(path); validate_profile(prof); errors += profile_paths(prof,a.root)
                except PipelineError as exc: errors.append(f"{path}: {exc}")
            if errors:
                [print(f"ERROR: {e}",file=sys.stderr) for e in errors]; return 1
            print(json.dumps({"status":"PASS","profiles":[str(x) for x in a.profiles]},indent=2))
    except PipelineError as exc: print(f"ERROR: {exc}",file=sys.stderr); return 2
    return 0
if __name__=="__main__": raise SystemExit(main())
