# Nexus-V Phase 6 Static Bring-Up Audit

- Canonical root: `/mnt/data/nexus_v_canonical_repo_v0_1`
- Filelist entries: 62
- Packages detected: 8
- Modules detected: 54
- Simulator availability: `{'verilator': False, 'iverilog': False, 'vcs': False, 'vsim': False, 'xsim': False}`
- Status: **static_audit_passed_lint_not_executed**

## Capability presence
- phase0_core: present
- rsm_controller: present
- rsm_rollback: present
- aegis_enclave: present
- topology_fabric: present
- tensor_npu: present
- quantum_domain: present
- soc_top: present
- soc_tb: present
- full_program: present

## Issues
- No blocking static issues detected by the lightweight audit.

## Warnings
- {'severity': 'warning', 'issue': 'No SystemVerilog simulator/linter found in container; Verilator/Icarus/Questa/VCS/XSIM execution skipped.'}

## Required term coverage
- branch_id: 27 files
- state_id: 27 files
- commit_id: 14 files
- topology_epoch: 14 files
- thermal_epoch: 14 files
- audit: 13 files
- rollback: 20 files
- route: 21 files
- tensor: 15 files
- quantum: 12 files
- minrep: 5 files
- attest: 5 files