# IMPLEMENTATION MATRIX

This matrix connects Plan intent to current Project Athena implementation.

## Status Legend

- done: implemented and usable.
- active: currently being built.
- partial: scaffold exists but needs more implementation or verification.
- planned: design intent exists but implementation has not started.
- blocked: requires human decision or external setup.

## Core Athena

| Plan Concept | Current Files | Status | Evidence | Next Step |
|---|---|---|---|---|
| AI prosthetic external brain | `context.md`, `AI-PORTAL.md`, `identity/README.md` | active | Definition written into root context and identity. | Keep first-read files aligned. |
| Task intake | `schemas/athena-task-intake.schema.json`, `templates/athena-task-intake.md`, `work/intake/` | active | Schema, template, and sample intake exist. | Run a task to closure through intake. |
| Memory architecture | `memory/athena-memory-map.md`, `memory/` | active | Memory map defines layers and writeback rules. | Extract details from Athena Memory Architecture docx. |
| Decision processor loop | `engine/order-of-operations.md`, `templates/athena-cycle-report.md`, `tools/Invoke-AthenaCycle.ps1` | active | Cycle template and runner exist. | Validate runner output and closure workflow. |
| Evidence discipline | `forensics/`, `truth/`, `cognition/anti-hallucination/` | partial | Existing evidence and truth protocols. | Connect intake claims to evidence IDs. |
| Council reasoning | `council/`, `council/reasoning-rounds/` | active | Brainstorm council round exists. | Create role-specific review packets for high-risk tasks. |

## Plan Sources

| Source | Meaning | Status | Next Extraction |
|---|---|---|---|
| `AI-OS-v13.0-Unified-Encyclopedia.md` | Integrated AI-OS plus Nexus-V master blueprint. | planned | Extract top-level modules and invariants. |
| `Project-Athena-Cognitive-Orchestrator-Specification-v1.0.md` | Cognitive orchestration model. | planned | Map attention, memory, agents, and reasoning to root folders. |
| `Athena Memory Architecture v1.0.docx` | Institutional memory architecture. | planned | Convert to memory contracts and schemas. |
| `Odysseus-Nexus-Ontology-Extraction-and-Unification-Specification.md` | Ontology migration blueprint. | planned | Create ontology extraction backlog. |
| `NVISC.txt` | ISA taxonomy. | planned | Map instructions to toolchain and RTL state. |
| `define.txt` | Nexus-V completeness notes. | planned | Convert to checklist. |

## Nexus-V Bridge

| Plan Concept | Current Files | Status | Evidence | Next Step |
|---|---|---|---|---|
| RTL implementation branch | `Nexus V/rtl/` | partial | Multiple RTL subsystem folders exist. | Link each subsystem to Plan requirements. |
| NVASM/NVIR/NVOBJ toolchain | `Nexus V/toolchain/`, `Nexus V/generated/` | partial | Python bridge and generated outputs exist. | Add regression expectations. |
| Static bring-up reports | `Nexus V/reports/` | active | Reports exist. | Re-run after source changes. |
| Full simulation/lint | `Nexus V/scripts/run_lint.py`, `Nexus V/scripts/run_regression.py` | blocked | Requires local simulator/toolchain setup. | Decide simulator install path. |

## Immediate Work Items

1. Validate `schemas/athena-task-intake.schema.json`.
2. Run one task through intake, decision, implementation, verification, and
   memory writeback.
3. Fill Nexus-V implementation matrix.
4. Extract AI-OS v13 into modules, invariants, and work items.
5. Resolve local-only governance versus configured remote.
