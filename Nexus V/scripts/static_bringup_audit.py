#!/usr/bin/env python3
import re, json, shutil, subprocess, sys
from pathlib import Path
root = Path(__file__).resolve().parents[1]
filelist = root/'filelist.f'
entries=[]; incdirs=[]
for line in filelist.read_text().splitlines():
    s=line.strip()
    if not s or s.startswith('//'): continue
    if s.startswith('+incdir+'):
        incdirs.append(s.split('+incdir+',1)[1])
    else:
        entries.append(s)
files=[root/e for e in entries]
issues=[]; warnings=[]
for f in files:
    if not f.exists(): issues.append({'severity':'error','file':str(f.relative_to(root)),'issue':'filelisted file missing'})
packages={}; modules={}; imports=[]; insts=[]
mod_decl_re=re.compile(r'\bmodule\s+(\w+)\b')
pkg_decl_re=re.compile(r'\bpackage\s+(\w+)\s*;')
import_re=re.compile(r'\bimport\s+(\w+)::')
# heuristic: lines like module_name #(...)? instance_name (
inst_re=re.compile(r'^\s*(\w+)\s*(?:#\s*\(|\s+)\s*(\w+)\s*\(')
for f in files:
    if not f.exists(): continue
    txt=f.read_text(errors='ignore')
    rel=str(f.relative_to(root))
    for p in pkg_decl_re.findall(txt):
        packages.setdefault(p,[]).append(rel)
    for m in mod_decl_re.findall(txt):
        modules.setdefault(m,[]).append(rel)
    for p in import_re.findall(txt): imports.append((rel,p))
    for line in txt.splitlines():
        line=line.split('//')[0]
        if 'module ' in line or 'endmodule' in line or 'function ' in line or 'task ' in line or 'typedef ' in line or 'always_' in line or 'if ' in line or 'case ' in line or 'assign ' in line or 'for ' in line or 'return ' in line or 'begin' in line: continue
        m=inst_re.match(line)
        if m:
            name, inst=m.group(1), m.group(2)
            if name not in ('logic','wire','reg','input','output','parameter','localparam','assign','always_comb','always_ff','if','else','for','case','unique','import'):
                insts.append((rel,name,inst))
# duplicate package/module names
for p, locs in packages.items():
    if len(locs)>1: issues.append({'severity':'error','symbol':p,'issue':'duplicate package definition in filelist','locations':locs})
for m, locs in modules.items():
    if len(locs)>1: issues.append({'severity':'error','symbol':m,'issue':'duplicate module definition in filelist','locations':locs})
# imports missing
for rel,p in imports:
    if p not in packages:
        issues.append({'severity':'error','file':rel,'issue':f'imported package {p} not defined in canonical filelist'})
# instantiations missing, heuristic only
for rel,name,inst in insts:
    if name not in modules and name not in packages:
        # ignore common SV/interface constructs / typed variable declarations
        if name.startswith('nvisc_') or name.startswith('nexus_'):
            warnings.append({'severity':'warning','file':rel,'issue':f'possible instantiation of unknown module {name} as {inst}'})
# simulator availability
simulators={tool: bool(shutil.which(tool)) for tool in ['verilator','iverilog','vcs','vsim','xsim']}
# try verilator if available
verilator_result=None
if simulators['verilator']:
    cmd=['verilator','--lint-only','-sv','-f',str(filelist)]
    proc=subprocess.run(cmd,cwd=root,stdout=subprocess.PIPE,stderr=subprocess.STDOUT,text=True,timeout=60)
    verilator_result={'returncode':proc.returncode,'output':proc.stdout[-20000:]}
else:
    warnings.append({'severity':'warning','issue':'No SystemVerilog simulator/linter found in container; Verilator/Icarus/Questa/VCS/XSIM execution skipped.'})
# basic hardware plan capability files presence
cap_files={
'phase0_core':'rtl/phase0/nexus_v_phase0_core.sv',
'rsm_controller':'rtl/rsm_phase1/nvisc_rsm_controller_phase1.sv',
'rsm_rollback':'rtl/rsm_rollback/nvisc_rsm_rollback_fsm.sv',
'aegis_enclave':'rtl/aegis_phase1/nvisc_aegis_enclave.sv',
'topology_fabric':'rtl/topology_phase3/nvisc_rhombic_dodeca_fabric_v0.sv',
'tensor_npu':'rtl/tensor_phase4/nvisc_tensor_npu_engine.sv',
'quantum_domain':'rtl/quantum_phase5/nvisc_quantum_domain_engine.sv',
'soc_top':'rtl/integration/nexus_v_soc.sv',
'soc_tb':'tb/tb_nexus_v_soc.sv',
'full_program':'programs/06_full_system_ai_versioned_secure.nvasm',
}
capability_status={k:(root/v).exists() for k,v in cap_files.items()}
# token string scans
required_terms=['branch_id','state_id','commit_id','topology_epoch','thermal_epoch','audit','rollback','route','tensor','quantum','minrep','attest']
term_hits={term:[] for term in required_terms}
for f in files:
    if not f.exists(): continue
    txt=f.read_text(errors='ignore').lower()
    rel=str(f.relative_to(root))
    for term in required_terms:
        if term.lower() in txt:
            term_hits[term].append(rel)
report={
'root':str(root),
'file_count':len(files),
'package_count':len(packages),
'module_count':len(modules),
'packages':packages,
'modules':modules,
'simulators_available':simulators,
'verilator_result':verilator_result,
'capability_status':capability_status,
'required_term_coverage':{k:len(v) for k,v in term_hits.items()},
'issues':issues,
'warnings':warnings,
'status':'blocked' if issues else 'static_audit_passed_lint_not_executed' if not any(simulators.values()) else 'see_verilator_result'
}
out=root/'reports'/'phase6_static_bringup_audit.json'
out.parent.mkdir(exist_ok=True)
out.write_text(json.dumps(report,indent=2))
# markdown summary
md=root/'reports'/'phase6_static_bringup_audit.md'
md.write_text('\n'.join([
'# Nexus-V Phase 6 Static Bring-Up Audit',
'',f'- Canonical root: `{root}`',f'- Filelist entries: {len(files)}',f'- Packages detected: {len(packages)}',f'- Modules detected: {len(modules)}',f'- Simulator availability: `{simulators}`',f'- Status: **{report["status"]}**','',
'## Capability presence',
]+[f'- {k}: {"present" if v else "missing"}' for k,v in capability_status.items()]+[
'', '## Issues',
]+([f'- {i}' for i in issues] if issues else ['- No blocking static issues detected by the lightweight audit.'])+[
'', '## Warnings',
]+([f'- {w}' for w in warnings] if warnings else ['- None.'])+[
'', '## Required term coverage',
]+[f'- {k}: {v} files' for k,v in report['required_term_coverage'].items()]))
print(json.dumps({'status':report['status'],'issues':len(issues),'warnings':len(warnings),'out':str(out)},indent=2))
