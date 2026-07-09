# NEXUS-V IMPLEMENTATION MATRIX

This matrix connects Project Athena Plan intent to the current Nexus-V source
tree.

## Status Legend

- active: source exists and is being developed.
- partial: scaffold exists but needs verification or completion.
- planned: design intent exists but source coverage is incomplete.
- blocked: needs external toolchain, human decision, or missing evidence.

## Subsystem Status

| Subsystem | Current Files | Status | Evidence | Next Test |
|---|---|---|---|---|
| Phase 0 core and topology interface | `rtl/phase0/` | partial | RTL folder exists. | Add or run phase-specific simulation. |
| Conventional CPU core v0.2 | `rtl/core_v02/` | partial | Core, decoder, CSR, LSU, memory/cache stubs exist. | Run lint/sim with available SV toolchain. |
| RSM state and rollback | `rtl/rsm_phase1/`, `rtl/rsm_rollback/` | partial | Branch metadata, copy-on-write, rollback modules exist. | Map to Plan reversible-state requirements. |
| Aegis trust/security | `rtl/aegis_phase1/` | partial | Attestation, commit gate, enclave, telemetry modules exist. | Create security requirement checklist. |
| Topology routing | `rtl/topology_phase3/` | partial | Fabric, routing, token table, compute modules exist. | Add route correctness tests. |
| Tensor/NPU path | `rtl/tensor_phase4/` | partial | Dispatch, compute, scratchpad, scheduler, integrity modules exist. | Add tensor vector tests. |
| Quantum-domain scaffold | `rtl/quantum_phase5/` | planned | QSIM/QHW bridge and quantum domain modules exist as scaffold. | Keep labeled as scaffold until tested. |
| SoC integration | `rtl/integration/`, `tb/` | partial | SoC top, verification package, driver, monitor, scoreboard exist. | Run integration smoke test. |
| NVISC toolchain | `toolchain/` | partial | Parser, lowering, NVOBJ, RTL-vector export exist. | Add parser/lowering regression corpus. |
| Generated outputs | `generated/` | active | NVIR, NVOBJ, RTL-vector outputs exist. | Regenerate after toolchain changes. |
| Reports | `reports/` | active | Static bring-up reports exist. | Re-run after source edits. |

## Plan Links To Build

| Plan Source | Nexus-V Mapping Needed |
|---|---|
| `Plan/Hardware plan.md` | CPU/SoC feature checklist. |
| `Plan/Hardware specifics.md` | Concrete hardware parameter extraction. |
| `Plan/NVISC.txt` | Instruction taxonomy and coverage matrix. |
| `Plan/define.txt` | Core completeness checklist. |
| `Plan/AI-OS-v13.0-Unified-Encyclopedia.md` | AI-OS to Nexus-V semantic execution bridge. |
| `Plan/Odysseus-Nexus-Ontology-Extraction-and-Unification-Specification.md` | Ontology and semantic object mapping. |

## Immediate Nexus-V Work

1. Re-run static bring-up audit after documentation/path changes.
2. Add expected traces for regression.
3. Decide simulator/lint toolchain and document installation.
4. Map each RTL subsystem to a Plan requirement.
5. Separate generated artifacts from source authority in future commits.
