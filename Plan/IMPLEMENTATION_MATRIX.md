# IMPLEMENTATION MATRIX

This matrix connects Plan intent to current Project Athena implementation.

## Status Legend

- done: implemented and usable.
- active: currently being built.
- partial: scaffold exists but needs more implementation or verification.
- planned: design intent exists but implementation has not started.
- specified: documented architecture/spec exists; implementation not yet proven.
- conceptual: user/project concept captured; needs formal spec and validation.
- speculative: future R&D hypothesis; requires research, modelling, prototype, and validation.
- blocked: requires human decision or external setup.

## Core Athena

| Plan Concept | Current Files | Status | Evidence | Next Step |
|---|---|---|---|---|
| AI prosthetic external brain | `context.md`, `AI-PORTAL.md`, `identity/README.md` | active | Definition written into root context and identity. | Keep first-read files aligned. |
| OASIS/Athena local-agent model | `Plan/OASIS_ATHENA_AGENT_MODEL.md`, `context.md`, `AI-PORTAL.md` | planned | Human diagram converted into Plan-level model. | Build adapter contracts for Codex, Jarvis, GPT, and future local agents. |
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
| Athena/Nexus-V bridge spec | `docs/athena-master-expansion/NEXUSV_ATHENA_BRIDGE_SPEC.md` | specified | Bridge contract exists in master expansion. | Connect intake/evidence records to branch/commit records. |

## Applied Spatial / Physical Concept Tracks

| Concept | Current Files | Status | Evidence | Next Step |
|---|---|---|---|---|
| GPT project concept sync | `docs/athena-master-expansion/CHATGPT_PROJECT_SYNC_2026-08-05.md` | active | Consolidates chat concepts into repo-accessible terminology and status classes. | Update after major conceptual corrections. |
| Lightcore physical execution profile | `docs/athena-master-expansion/LIGHTCORE_PHYSICAL_EXECUTION_PROFILE.md` | specified / speculative | Lightcore is documented as Nexus-V physical execution profile, not Nexus-V replacement. | Create formal signal schema, device risk register, and simulation roadmap. |
| L.O.D.E TV completion | `docs/athena-master-expansion/LODE_TV_COMPLETION_SPEC.md` | specified | Display endpoint, photonic pipeline, telemetry, RoomSense/BodyRig integration, privacy, and roadmap are documented. | Generate controlled vector engineering sheets and measured assembly pack. |
| L.O.D.E engineering completion map | `docs/athena-master-expansion/LODE_TV_ENGINEERING_COMPLETION_MAP.md` | active | Reference dimensions, subassemblies, telemetry schema, assembly sequence, drawing sheet list, and validation roadmap added. | Convert sheet list into SVG/PDF blueprint sources. |
| RoomSense / BodyRig interface | `docs/athena-master-expansion/LODE_ROOMSENSE_BODYRIG_INTERFACE_SPEC.md` | specified | Interface spec exists for L.O.D.E, RoomSense, BodyRig, XR outputs, and privacy modes. | Add coordinate-frame schema and pose-confidence metrics. |
| Athena feed/benefit matrix | `docs/athena-master-expansion/ATHENA_SYSTEM_FEED_BENEFIT_MATRIX.md` | active | Source-to-target benefits and validation paths documented. | Use as dependency map for Asana/GitHub issues. |
| OASIS architecture | `docs/athena-master-expansion/OASIS_ARCHITECTURE_SPEC.md` | planned / specified | Formal environment/runtime/interface spec exists. | Define simulation object model, material import schema, and provenance requirements. |
| Operative Duplex AI | `docs/athena-master-expansion/OPERATIVE_DUPLEX_AI_SPEC.md` | planned / specified | Action-layer boundary exists. | Build permission model, action trace schema, and local sandbox requirements. |
| Plugin workspace sync | `docs/athena-master-expansion/PLUGIN_WORKSPACE_SYNC_LOG_2026-08-05.md`, `PLUGIN_MIRROR_INDEX.md` | active | Plugin roles, labels, canonicality, and mirror status documented. | Mirror updated repo state into Notion/Asana/Gamma/Drive where tools allow. |

## Research / Sanity Anchors

| Domain | Current Evidence | Status | Next Step |
|---|---|---|---|
| Agentic AI governance | Consensus/SciSpace searches for multi-agent governance, auditability, provenance, HITL, and policy gates. | research-supported primitive | Keep anchors in `RESEARCH_ANCHORS.md` and avoid claiming full Athena implementation. |
| Silicon nitride photonics | Research anchors support SiN as a low-loss integrated photonics platform. | research-supported primitive | Connect to Lightcore photonic routing assumptions. |
| CNT silicon-waveguide photonics | Research anchors support CNT photodetectors and CNT/silicon-waveguide integration. | research-supported primitive | Keep CNT compute/memory claims marked speculative beyond demonstrated detector/optoelectronic pieces. |
| Multi-sensor SLAM / human pose | Research anchors support LiDAR/camera/IMU fusion and LiDAR-based human pose without wearables. | research-supported primitive | Use to constrain RoomSense/BodyRig claims and tests. |
| 100-inch 16:9 display geometry | Wolfram calculation gives 2213.7 mm × 1245.3 mm active area. | checked reference value | Use rounded 2214 mm × 1245 mm in L.O.D.E drawing sheets. |

## Immediate Work Items

1. Validate `schemas/athena-task-intake.schema.json`.
2. Run one task through intake, decision, implementation, verification, and memory writeback.
3. Fill Nexus-V implementation matrix.
4. Extract AI-OS v13 into modules, invariants, and work items.
5. Keep the local-only governance rule scoped correctly: local repo/code pushes remain human-controlled; explicit plugin documentation syncs may be written to GitHub/cloud mirrors when authorized.
6. Convert L.O.D.E drawing-sheet register into controlled vector/PDF engineering sheets.
7. Create RoomSense/BodyRig coordinate-frame schema and pose-confidence metrics.
8. Create Lightcore signal schema and physical execution risk register.
9. Mirror this documentation pass into Notion, Asana, Gamma, and Drive where connector permissions allow.
10. Keep all speculative hardware marked as R&D until supported by simulation, bench testing, part selection, and compliance analysis.
