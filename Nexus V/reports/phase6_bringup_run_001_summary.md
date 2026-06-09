# Phase 6 Bring-Up Run 001 Summary

- Status: **partial_pass**
- Static source audit: **static_audit_passed_lint_not_executed**
- Blocking static issues: **0**
- Toolchain compile of `06_full_system_ai_versioned_secure.nvasm`: **pass**
- SystemVerilog simulator execution: **not_run_no_sv_simulator_available_in_container**

## Generated toolchain artifacts
- `06_full_system_ai_versioned_secure.nvir.json` — 22612 bytes
- `06_full_system_ai_versioned_secure.nvobj` — 2380 bytes
- `06_full_system_ai_versioned_secure.rtl_vectors.json` — 11574 bytes

## Important limitation
This container does not include Verilator, Icarus Verilog, Questa, VCS, or XSIM, so this run performed static/source bring-up and toolchain generation only. It did not perform real SystemVerilog compilation or waveform simulation.

## Next command on a machine with Verilator
```bash
cd nexus_v_canonical_repo_v0_1
verilator --lint-only -sv -f filelist.f --top-module tb_nexus_v_soc
```