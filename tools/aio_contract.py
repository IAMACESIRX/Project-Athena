#!/usr/bin/env python3
"""AIO master-contract CLI: validate, instantiate, mutate, project and render."""
from __future__ import annotations
import argparse, hashlib, json, sys
from datetime import datetime, timezone
from pathlib import Path
from typing import Any
try:
    import yaml
except ImportError as exc:
    raise SystemExit("PyYAML is required: pip install pyyaml") from exc

MASTER_SCHEMA="project-athena.aio.master_contract.v0.1"
INSTANCE_SCHEMA="project-athena.aio.contract_instance.v0.1"
MODES={"manual","ai_assisted","automated","hybrid"}

class AIOError(ValueError): pass

def now()->str: return datetime.now(timezone.utc).isoformat()
def canonical(v:Any)->bytes: return json.dumps(v,sort_keys=True,separators=(",",":"),ensure_ascii=False).encode()
def digest(v:Any)->str: return hashlib.sha256(canonical(v)).hexdigest()
def load(path:Path)->dict[str,Any]:
    try: text=path.read_text(encoding="utf-8-sig")
    except FileNotFoundError as e: raise AIOError(f"Missing file: {path}") from e
    try: value=json.loads(text) if path.suffix.lower()==".json" else yaml.safe_load(text)
    except Exception as e: raise AIOError(f"Cannot parse {path}: {e}") from e
    if not isinstance(value,dict): raise AIOError(f"Root must be an object: {path}")
    return value

def dump(path:Path,v:dict[str,Any])->None:
    path.parent.mkdir(parents=True,exist_ok=True)
    if path.suffix.lower() in {".yml",".yaml"}: path.write_text(yaml.safe_dump(v,sort_keys=False,allow_unicode=True),encoding="utf-8")
    else: path.write_text(json.dumps(v,indent=2,ensure_ascii=False)+"\n",encoding="utf-8")

def req(v:dict[str,Any],fields:list[str],ctx:str)->None:
    missing=[x for x in fields if x not in v]
    if missing: raise AIOError(f"{ctx} missing: {', '.join(missing)}")

def validate_master(m:dict[str,Any])->None:
    req(m,["schema","metadata","architecture","hard_gates","weights","participants","contracts","pipeline","scale_ladder","instance"],"master")
    if m["schema"]!=MASTER_SCHEMA: raise AIOError(f"Unsupported master schema: {m['schema']}")
    if m["architecture"].get("pairwise_contracts")!="generated_views_only": raise AIOError("Pairwise contracts must be generated views only")
    participants=set(m["participants"])
    required={"human_owner","athena","aesir","forge","aegis","nexus_v"}
    if not required<=participants: raise AIOError(f"Missing core participants: {sorted(required-participants)}")
    phases=m["pipeline"]
    if len(phases)!=21: raise AIOError("AIO v0.1 requires exactly 21 full-stack phases")
    ids=[p.get("id") for p in phases]
    expected=[f"P{i:02d}" for i in range(21)]
    if ids!=expected: raise AIOError(f"Phase sequence must be {expected}")
    contract_ids={c["id"] for c in m["contracts"]}
    for p in phases:
        req(p,["id","name","owner","depth","contracts"],f"phase {p.get('id')}")
        if p["owner"] not in participants: raise AIOError(f"Unknown phase owner {p['owner']}")
        if not 0<float(p["depth"])<=1: raise AIOError(f"Invalid depth for {p['id']}")
        if any(c not in contract_ids for c in p["contracts"]): raise AIOError(f"Unknown contract in {p['id']}")
    if float(m["architecture"].get("minimum_phase_depth",0))<=0: raise AIOError("Coverage floor must be non-zero")

def phase_depth(master:dict[str,Any],phase:dict[str,Any],requested:float,weights:dict[str,float])->float:
    floor=float(master["architecture"]["minimum_phase_depth"])
    phase_weights=phase.get("weights",{})
    if phase_weights:
        vals=[float(weights.get(k,master["weights"]["default"].get(k,0.5)))*float(v) for k,v in phase_weights.items()]
        affinity=sum(vals)/max(sum(abs(float(v)) for v in phase_weights.values()),1e-9)
    else: affinity=sum(weights.values())/max(len(weights),1)
    return round(max(floor,min(1,0.45*requested+0.35*float(phase["depth"])+0.20*affinity)),4)

def instantiate(master:dict[str,Any],source:dict[str,Any])->dict[str,Any]:
    validate_master(master)
    req(source,["title","objective"],"input")
    mode=source.get("mode","hybrid")
    if mode not in MODES: raise AIOError(f"mode must be one of {sorted(MODES)}")
    requested=float(source.get("requested_depth",1.0))
    if not 0<requested<=1: raise AIOError("requested_depth must be >0 and <=1")
    weights=dict(master["weights"]["default"]); weights.update(source.get("weights",{}))
    seed={"title":source["title"],"objective":source["objective"],"created_at":now()}
    instance_id="AIO-"+digest(seed)[:16].upper()
    phases=[]
    for p in master["pipeline"]:
        phases.append({"id":p["id"],"name":p["name"],"owner":p["owner"],"status":"pending","effective_depth":phase_depth(master,p,requested,weights),"contracts":list(p["contracts"]),"result":{},"evidence":[],"review":None})
    instance={
      "schema":INSTANCE_SCHEMA,"identity":{"instance_id":instance_id,"master_contract_id":master["metadata"]["id"],"master_version":master["metadata"]["version"],"created_at":now(),"mode":mode,"status":"active"},
      "input":source,"weights":weights,"pipeline_state":{"current_phase":"P00","phases":phases},
      "shared_state":{"claims":[],"evidence":[],"unknowns":[],"candidates":[],"mechanisms":[],"requirements":[],"risks":[],"mitigations":[],"decisions":[],"state_graph":{}},
      "events":[],"interventions":[],"attestations":[],"outputs":{},"provenance":{"parent_sha256":None,"current_sha256":None,"lineage":[]}}
    append_event(instance,"system","instantiate",{"source_sha256":digest(source)},None)
    return instance

def append_event(inst:dict[str,Any],actor:str,event_type:str,payload:dict[str,Any],expected_parent:str|None)->None:
    current=inst.get("provenance",{}).get("current_sha256")
    if current and expected_parent!=current: raise AIOError(f"Parent hash mismatch: expected {expected_parent}, current {current}")
    event={"event_id":f"EVT-{len(inst.get('events',[]))+1:06d}","timestamp":now(),"actor":actor,"type":event_type,"expected_parent_sha256":expected_parent,"payload":payload}
    inst.setdefault("events",[]).append(event)
    new_hash=digest({k:v for k,v in inst.items() if k!="provenance"})
    prov=inst.setdefault("provenance",{})
    if current: prov.setdefault("lineage",[]).append(current)
    prov["parent_sha256"]=current; prov["current_sha256"]=new_hash

def validate_instance(inst:dict[str,Any],master:dict[str,Any])->None:
    validate_master(master)
    req(inst,["schema","identity","input","weights","pipeline_state","shared_state","events","interventions","attestations","outputs","provenance"],"instance")
    if inst["schema"]!=INSTANCE_SCHEMA: raise AIOError("Unsupported instance schema")
    phases=inst["pipeline_state"].get("phases",[])
    if [p.get("id") for p in phases]!=[f"P{i:02d}" for i in range(21)]: raise AIOError("Instance must retain every ordered phase")
    if any(float(p.get("effective_depth",0))<=0 for p in phases): raise AIOError("No phase may have zero depth")
    if inst["identity"].get("mode") not in MODES: raise AIOError("Invalid execution mode")
    if not inst["events"]: raise AIOError("Instance requires event history")
    expected=digest({k:v for k,v in inst.items() if k!="provenance"})
    if inst["provenance"].get("current_sha256")!=expected: raise AIOError("Current hash does not match materialized state")

def project(inst:dict[str,Any],participant:str)->dict[str,Any]:
    return {"schema":"project-athena.aio.generated_view.v0.1","participant":participant,"non_authoritative":True,"instance_id":inst["identity"]["instance_id"],"objective":inst["input"]["objective"],"current_phase":inst["pipeline_state"]["current_phase"],"phases":[p for p in inst["pipeline_state"]["phases"] if p["owner"]==participant or participant=="human_owner"],"shared_state":inst["shared_state"],"outputs":inst["outputs"],"current_sha256":inst["provenance"]["current_sha256"]}

def render(inst:dict[str,Any])->str:
    rows=[]
    for p in inst["pipeline_state"]["phases"]: rows.append(f"| {p['id']} | {p['name']} | {p['owner']} | {p['effective_depth']:.2f} | {p['status']} |")
    return f"# AIO Contract {inst['identity']['instance_id']}\n\n## Objective\n\n{inst['input']['objective']}\n\n- Mode: `{inst['identity']['mode']}`\n- Current phase: `{inst['pipeline_state']['current_phase']}`\n- State hash: `{inst['provenance']['current_sha256']}`\n\n## Pipeline\n\n| ID | Phase | Owner | Depth | Status |\n|---|---|---|---:|---|\n"+"\n".join(rows)+"\n\n## Unresolved state\n\n- Claims: "+str(len(inst['shared_state']['claims']))+"\n- Unknowns: "+str(len(inst['shared_state']['unknowns']))+"\n- Risks: "+str(len(inst['shared_state']['risks']))+"\n- Mitigations: "+str(len(inst['shared_state']['mitigations']))+"\n"

def main()->int:
    ap=argparse.ArgumentParser(description="AIO shared contract tool")
    sub=ap.add_subparsers(dest="cmd",required=True)
    p=sub.add_parser("validate-master"); p.add_argument("master",type=Path)
    p=sub.add_parser("instantiate"); p.add_argument("--master",type=Path,required=True); p.add_argument("--input",type=Path,required=True); p.add_argument("--out",type=Path,required=True)
    p=sub.add_parser("validate-instance"); p.add_argument("instance",type=Path); p.add_argument("--master",type=Path,required=True)
    p=sub.add_parser("event"); p.add_argument("instance",type=Path); p.add_argument("--actor",required=True); p.add_argument("--type",required=True); p.add_argument("--payload",default="{}"); p.add_argument("--expected-parent")
    p=sub.add_parser("view"); p.add_argument("instance",type=Path); p.add_argument("--participant",required=True); p.add_argument("--out",type=Path,required=True)
    p=sub.add_parser("render"); p.add_argument("instance",type=Path); p.add_argument("--out",type=Path,required=True)
    a=ap.parse_args()
    try:
        if a.cmd=="validate-master": validate_master(load(a.master)); print("PASS: AIO master contract valid")
        elif a.cmd=="instantiate":
            m=load(a.master); i=instantiate(m,load(a.input)); dump(a.out,i); print(i["identity"]["instance_id"])
        elif a.cmd=="validate-instance": validate_instance(load(a.instance),load(a.master)); print("PASS: AIO instance valid")
        elif a.cmd=="event":
            i=load(a.instance); append_event(i,a.actor,a.type,json.loads(a.payload),a.expected_parent); dump(a.instance,i); print(i["provenance"]["current_sha256"])
        elif a.cmd=="view": dump(a.out,project(load(a.instance),a.participant))
        elif a.cmd=="render": a.out.write_text(render(load(a.instance)),encoding="utf-8")
        return 0
    except (AIOError,json.JSONDecodeError) as e: print(f"FAIL: {e}",file=sys.stderr); return 2
if __name__=="__main__": raise SystemExit(main())
