#!/usr/bin/env python3
"""Transparent blind baseline for the runnable AIO-OMEGA habitat."""
from __future__ import annotations
import argparse, importlib.util, json, sys
from copy import deepcopy
from pathlib import Path
from typing import Any

def load_runtime(path:Path):
    spec=importlib.util.spec_from_file_location("aio_omega_runtime",path)
    if spec is None or spec.loader is None: raise RuntimeError(f"Cannot load runtime: {path}")
    module=importlib.util.module_from_spec(spec); sys.modules[spec.name]=module; spec.loader.exec_module(module); return module

def aio_instance(runtime,objective:str)->dict[str,Any]:
    names=["single_input_capture","authority_privacy_safety_gate","context_state_temporal_map","epistemic_partition_and_evidence_map","full_scientific_method","intra_and_cross_scientific_integration","multiscale_full_stack_sweep","aesir_polymath_expansion","systems_hypergraph_dependencies","forge_candidate_lattice_and_symmetric_challenge","weighted_tournament_and_mechanism_mining","native_reverse_reconstruction","full_engineering_method","compile_time_complexity_runtime_simplification","simulation_prototype_reality_closure","mitigation_and_offset","governance_memory_and_promotion","aegis_trust_attestation_commit_gate","nexus_versioned_execution_and_state_commit","unified_outputs_and_generated_views","method_repass_and_future_revalidation"]
    owners=["human_owner","athena","athena","aesir","aesir","aesir","aesir","aesir","athena","forge","forge","forge","implementation_toolchain","forge","oasis","athena","athena","aegis","nexus_v","athena","forge"]
    phases=[{"id":f"P{i:02d}","name":name,"owner":owners[i],"status":"completed","effective_depth":1.0,"contracts":[],"result":{"summary":f"Completed {name}."},"evidence":[]} for i,name in enumerate(names)]
    value={"schema":"project-athena.aio.contract_instance.v0.1","identity":{"instance_id":"AIO-OMEGA-REFERENCE","master_contract_id":"AIO-MASTER-CONTRACT","master_version":"0.1.0","mode":"ai_assisted","status":"completed"},"input":{"title":"Yggdrasil Habitat","objective":objective},"pipeline_state":{"current_phase":"P20","phases":phases},"shared_state":{},"events":[{"event_id":"EVT-000001","actor":"reference_solver","type":"complete","payload":{"phases":21}}],"interventions":[],"attestations":[],"outputs":{},"provenance":{"parent_sha256":None,"lineage":[],"current_sha256":""}}
    value["provenance"]["current_sha256"]=runtime.digest({k:v for k,v in value.items() if k!="provenance"}); return value

def probability(signal:float)->float:
    if signal>=0.72:return min(0.98,0.72+(signal-0.72)*1.1)
    if signal<=0.22:return max(0.02,signal*0.35)
    return 0.35+(signal-0.22)*0.72

def solve(runtime,session,template_path:Path)->dict[str,Any]:
    brief=session.public_snapshot()["brief"]
    plan=["independent_power_calibration","battery_capacity_test","gas_tracer_test","co2_bypass_inspection","water_mass_balance","radiator_thermal_test","control_loop_replay","biofilter_assay","log_chain_integrity","inventory_barcode_audit"]
    experiments=[]; posterior={}; evidence_for={}; evidence_against={}
    for test_id in plan:
        result=session.execute_diagnostic(test_id); updates={}
        for finding in result["findings"]:
            fault_id=finding["fault_id"]; p=probability(float(finding["signal"])); posterior[fault_id]=p; updates[fault_id]=p
            (evidence_for if p>=0.5 else evidence_against).setdefault(fault_id,[]).append(finding["observation"])
        experiments.append({"id":test_id,"cost":result["cost"],"risk":result["risk"],"target_hypotheses":[f["fault_id"] for f in result["findings"]],"expected_information_gain":"high discriminatory value per budget unit","result":result,"posterior_updates":updates})
    for fault_id in session.world.faults: posterior.setdefault(fault_id,0.08)
    hypotheses=[]; repairs=[]
    for fault_id,p in sorted(posterior.items(),key=lambda item:item[1],reverse=True):
        if p>=0.55: repairs.append(fault_id)
        hypotheses.append({"id":fault_id,"fault_id":fault_id,"statement":f"The habitat has the failure mode {fault_id}.","probability":round(p,4),"evidence_for":evidence_for.get(fault_id,[]),"evidence_against":evidence_against.get(fault_id,[]),"falsifiers":[f"Independent repeat test for {fault_id} remains negative under controlled conditions."],"status":"provisionally_supported" if p>=0.55 else "currently_unsupported"})
    submission=deepcopy(json.loads(template_path.read_text(encoding="utf-8")))
    submission.update({"schema":"project-athena.aio.omega.submission.v0.1","benchmark_id":"AIO-OMEGA-001","aio_instance":aio_instance(runtime,brief["objective"]),"hypotheses":hypotheses,"experiments":experiments})
    submission["architecture"]["repairs"]=repairs; architecture_sha=runtime.digest(submission["architecture"]); session.freeze_architecture(architecture_sha)
    crisis=session.reveal("R4"); upgrade=session.reveal("R5"); intervention=session.reveal("R6")
    submission["crisis_adaptation"]={"detected_change":crisis,"new_branch":"branch/crisis-r4","actions":["enter conservative resource mode","isolate affected path","activate matching contingency","verify independent measurements"],"verification":["state diff","resource-margin trend","two-person confirmation"],"rollback":"checkout frozen pre-crisis configuration after tests pass"}
    submission["technology_adoption"]={"comparison":{"offer":upgrade,"current_baseline":architecture_sha},"decision":"shadow-test before partial adoption","coexistence":"operate one isolated pilot segment while retaining the proven system","migration":"promote only after fault injection, serviceability, and manual-mode tests","rollback":"remove pilot and restore signed baseline configuration","archived_path":architecture_sha}
    submission["human_intervention"]={"instruction":intervention["instruction"],"state_before":"automation-centred optimiser with manual fallback under development","state_after":"bounded manual safety layer is mandatory and independently testable","rejected_branch_preserved":True}
    submission["machine_configuration"]["architecture_sha256"]=architecture_sha; return submission

def main()->int:
    parser=argparse.ArgumentParser(description="Run the transparent OMEGA reference solver")
    parser.add_argument("--runtime",type=Path,default=Path("tools/aio_omega_runtime.py")); parser.add_argument("--model",type=Path,default=Path("benchmarks/aio/omega/yggdrasil-habitat/scenario-model.json")); parser.add_argument("--template",type=Path,default=Path("benchmarks/aio/omega/yggdrasil-habitat/reference-design.json")); parser.add_argument("--session",type=Path,required=True); parser.add_argument("--seed",default="reference-seed-001"); parser.add_argument("--submission-out",type=Path,required=True); parser.add_argument("--score-out",type=Path,required=True)
    args=parser.parse_args(); runtime=load_runtime(args.runtime); world=runtime.OmegaWorld.load(args.model); session=runtime.OmegaSession.create(args.session,world,args.seed); submission=solve(runtime,session,args.template); runtime.write_json(args.submission_out,submission); score=session.score_submission(submission); runtime.write_json(args.score_out,score); print(json.dumps(score,indent=2)); return 0 if score["passed"] else 3
if __name__=="__main__": raise SystemExit(main())
