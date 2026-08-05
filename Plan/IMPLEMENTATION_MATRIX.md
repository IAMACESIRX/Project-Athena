# IMPLEMENTATION MATRIX

Updated: 2026-08-05 independent-system correction

This matrix connects Plan intent to current Project Athena implementation and distinguishes independent AIs from shared infrastructure.

## Status legend

- **done**: implemented and usable.
- **active**: currently being built.
- **partial**: scaffold exists but needs implementation or verification.
- **planned**: design intent exists but implementation has not started.
- **specified**: documented architecture/spec exists; implementation not yet proven.
- **conceptual**: user/project concept captured; needs formal implementation detail and validation.
- **speculative**: future R&D hypothesis; requires research, modelling, prototype and validation.
- **blocked**: requires human decision, unavailable local tooling or external setup.
- **superseded**: retained only for provenance; newer canonical authority exists.

## Canonical identity matrix

| Entity | Type | Canonical role | Status | Authority file |
|---|---|---|---|---|
| ATHENA | independent institutional intelligence | governance, evidence, memory, ontology, councils, project coordination | active / specified | `README.md`, `AI-PORTAL.md`, `context.md`, `Plan/` |
| JARVIS | independent personal/executive intelligence | immediate human interaction, personal context, device and daily-work orchestration | conceptual | `Plan/OASIS_ATHENA_AGENT_MODEL.md`, system correction |
| JANUS | independent operative metacognitive intelligence | program discovery, direct software/OASIS operation, Skill Capsules, state verification | specified / planned | `docs/athena-master-expansion/JANUS_OPERATIVE_METACOGNITIVE_AI_MASTER_SPEC.md` |
| OASIS | non-AI persistent digital-reality substrate | engineering, science, games, living/work, R&D, digital twins and production workshops | specified / conceptual | `docs/athena-master-expansion/OASIS_ARCHITECTURE_SPEC.md` |
| Nexus-V | semantic/versioned execution architecture | branchable state, rollback, merge, provenance, execution semantics | partial / specified | `Nexus V/`, `Plan/NVISC*`, `Plan/NVASM*`, `Plan/NVIR*` |
| Aegis | trust/attestation/commit-gate architecture | policy enforcement, trust telemetry, commit/rollback authority | partial / specified | `Nexus V/`, Aegis Plan specs |
| Lightcore | future physical execution profile | optoelectronic/CNT/photonic compute and transport | specified / speculative | `docs/athena-master-expansion/LIGHTCORE_PHYSICAL_EXECUTION_PROFILE.md` |

## Repository implementation areas

| Area | Current files | Status | Evidence | Next step |
|---|---|---|---|---|
| AI prosthetic external brain | `context.md`, `AI-PORTAL.md`, `identity/README.md` | active | Definition written into root context and identity. | Keep first-read files aligned. |
| Distributed docking and hot-swap fabric | `Plan/ATHENA_DISTRIBUTED_COGNITIVE_FABRIC.md`, `integration/`, `orchestration/` | planned | Model-local node, highway, external core, project capsule and skill ownership contracts are captured. | Define adapter, capsule and skill-package schemas; test read-only docking. |
| Metacognitive orchestration | `Plan/Project-Athena-Cognitive-Orchestrator-Specification-v1.0.md`, `cognition/`, `orchestration/model-router.yml` | partial | Cognitive selection, senate, confidence and workflow specifications exist. | Add machine-readable cognition profiles and activation evidence. |
| Chat knowledge reconciliation | `athena_context/`, `Plan/CHAT_DERIVED_CONCEPT_REGISTER.md` | active | Five-chat linear text archive passed repeat retrieval; gaps are labelled. | Reconcile recovered images and missing generated documents. |
| Two-way chat/repository continuity | `Plan/CHAT_REPOSITORY_CONTINUITY_PIPELINE.md`, `continuity/chat-repository-sync/`, `tools/Import-AthenaChatExport.ps1`, `tools/Export-AthenaChatContext.ps1` | active | Source, promotion, bounded export, privacy and completeness contracts are implemented. | Add fixtures and complete official export reconciliation. |
| GitHub planning and integrity | `.github/`, `work/github-plan.json`, `tools/Sync-AthenaGitHub.ps1` | active | Read-only CI plus preview-first desired state for 25 labels, 9 milestones and 27 issues. | Apply the bounded remote reconciliation and configure Project fields/views. |

## Core ATHENA

| Plan concept | Current files | Status | Evidence | Next step |
|---|---|---|---|---|
| AI prosthetic / institutional external brain | `context.md`, `README.md`, `AI-PORTAL.md`, `identity/README.md` | active | repository, context and identity structure exist | keep first-read files aligned |
| Independent-system boundary | `SYSTEM_IDENTITY_AND_AUTHORITY_CORRECTION_2026-08-05.md`, `ATHENA_FULL_SYSTEM_MAP.md` | specified | canonical correction committed on controlled branch | merge and propagate to every stale diagram/schema |
| Task intake | `schemas/athena-task-intake.schema.json`, `templates/athena-task-intake.md`, `work/intake/` | active | schema, template and sample intake exist | run a task to closure through intake |
| Memory architecture | `memory/athena-memory-map.md`, `memory/`, Plan DOCX | active | memory map defines layers/writeback | extract remaining DOCX detail into contracts/schemas |
| Decision processor loop | `engine/order-of-operations.md`, cycle template, `Invoke-AthenaCycle.ps1` | active | cycle template and runner exist | validate runner output and closure workflow locally |
| Evidence discipline | `forensics/`, `truth/`, `cognition/anti-hallucination/` | partial | evidence/truth protocols exist | connect intake claims to evidence IDs |
| Council reasoning | `council/`, `council/reasoning-rounds/` | active | council round exists | create role-specific review packets for high-risk tasks |
| Docking/hot-swap fabric | `ATHENA_DOCKING_FABRIC_HOTSWAP_SPEC.md`, adapters and highway work | specified | architecture and diagrams exist | convert into runtime contracts and conformance tests |

## JANUS implementation track

| Capability | Current files | Status | Evidence | Next step |
|---|---|---|---|---|
| Independent JANUS identity | `JANUS_OPERATIVE_METACOGNITIVE_AI_MASTER_SPEC.md` | specified | role, boundaries and maturity defined | add manifest and runtime package skeleton |
| Interior/Exterior duplex | JANUS master spec | specified | metacognitive and operative responsibilities separated | implement independently testable planner/verifier services |
| Native semantic UI control | JANUS master spec | planned | platform mechanisms exist; no JANUS runtime yet | Windows UIA/Win32 read-only mapper prototype |
| Visual-semantic fallback | JANUS master spec, research validation notes | specified / research-supported primitive | GUI-agent literature supports direction but professional accuracy remains weak | benchmark grounding and focus/modal state |
| Application Cartographer | JANUS master spec | specified / planned | controlled discovery protocol defined | sandbox explorer and state-transition recorder |
| Skill Capsules | JANUS master spec | specified / planned | schema and validation lifecycle defined | implement registry, versioning and replay |
| Independent pre-action verifier | JANUS master spec, research validation notes | specified / required | GUI confused-deputy research supports external verification | implement target/focus/fresh-state gate |
| Permission/commit model | JANUS master spec | specified | O0-O4 authority classes defined | formal policy schema and human approval UI |
| OASIS embodiment | JANUS/OASIS specs | conceptual / planned | interface described | conventional engine avatar/tool runtime |
| Nexus-V/Aegis native integration | JANUS/Nexus specs | future | no end-to-end implementation | defer until conventional JANUS runtime passes tests |
| Universal undocumented-program competence | JANUS spec | research target | not established by current evidence | staged professional-software benchmark programme |

## OASIS implementation track

| Capability | Current files | Status | Evidence | Next step |
|---|---|---|---|---|
| Correct non-AI identity and broad scope | `OASIS_ARCHITECTURE_SPEC.md` | specified | engineering/science/game/living/work/R&D/production scope formalized | propagate to ontology and diagrams |
| Universal object model | OASIS spec | specified | schema defined | JSON Schema and example objects |
| Reality/validation classes | OASIS spec | specified | fictional to production-qualified classes defined | enforce in import/export tools |
| Scene graph and persistent world state | OASIS spec | planned | data contracts drafted | conventional runtime prototype |
| Modular simulation fidelity | OASIS spec | conceptual / specified | solver/profile boundary defined | select initial physics/simulation engines |
| Engineering export/import | OASIS spec | planned | export package schema defined | CAD/mesh/code adapter prototype |
| R&D think-tank environments | OASIS spec | conceptual | spatial project model described | build one Project Athena demonstrator space |
| JANUS integration | OASIS/JANUS specs | planned | operation/export contracts described | simulation-to-external-tool comparison test |

## Plan sources

| Source | Meaning | Status | Next extraction |
|---|---|---|---|
| `AI-OS-v13.0-Unified-Encyclopedia.md` | integrated AI-OS plus Nexus-V master blueprint | planned | extract top-level modules/invariants |
| `Project-Athena-Cognitive-Orchestrator-Specification-v1.0.md` | cognitive orchestration model | planned | map attention, memory, agents and reasoning to root folders |
| `Athena Memory Architecture v1.0.docx` | institutional memory architecture | planned | convert to memory contracts/schemas |
| `Odysseus-Nexus-Ontology-Extraction-and-Unification-Specification.md` | ontology migration blueprint | planned | create ontology extraction backlog |
| `NVISC.txt` | ISA taxonomy | planned | map instructions to toolchain and RTL state |
| `define.txt` | Nexus-V completeness notes | planned | convert to checklist |
| Plan DOCX corpus | detailed Nexus-V/Aegis/SoC/RTL specifications | inventoried / partially summarized | OOXML and archive structure previously validated; current GitHub connector cannot semantically re-extract every binary | local extraction and content-hash review |
| `CHAT_DERIVED_CONCEPT_REGISTER.md` | evidence-bounded register for recovered ATHENA conversation intent | active | keep source pointers, status and artifact gaps current |
| `ATHENA_DISTRIBUTED_COGNITIVE_FABRIC.md` | model docking, highway, capsules, skill ownership and hot swapping | planned | convert contracts into schemas and fixtures |
| `OPERATIVE_DUPLEX_AI_MODEL.md` | independent operative metacognitive AI and computer/world embodiment | planned | confirm naming and build a read-only Cartographer slice |
| `OASIS_REALITY_COMPILER.md` | multidomain sensing, Material Behavioral Atlas, environment compilation and inverse design | planned | define schemas and a bounded capture experiment |
| `LIGHTCORE_PHYSICAL_EXECUTION_PROFILE.md` | experimental physical execution profile beneath Nexus-V | planned | build evidence ledger, emulator profile and one link experiment |

## Nexus-V bridge

| Plan concept | Current files | Status | Evidence | Next step |
|---|---|---|---|---|
| RTL implementation branch | `Nexus V/rtl/` | partial | multiple subsystem folders exist | link each subsystem to Plan requirements |
| NVASM/NVIR/NVOBJ toolchain | `Nexus V/toolchain/`, `Nexus V/generated/` | partial | Python bridge and generated outputs exist | add regression expectations |
| Static bring-up reports | `Nexus V/reports/` | active | reports exist | rerun locally after source changes |
| Full simulation/lint | scripts under `Nexus V/` | blocked | local simulator/toolchain required | decide simulator install path |
| ATHENA/Nexus-V bridge | `NEXUSV_ATHENA_BRIDGE_SPEC.md` | specified | bridge contract exists | connect intake/evidence to branch/commit records |
| JANUS/Nexus-V bridge | JANUS master spec | specified / future | operation state maps to branch/diff/commit semantics | define conventional reference adapter first |
| OASIS versioned state | OASIS spec | specified / future | world-state contract exists | implement engine-neutral snapshots before hardware path |
| Lightcore physical execution profile | `Plan/LIGHTCORE_PHYSICAL_EXECUTION_PROFILE.md` | planned | architecture and validation gates are captured with explicit research boundaries | preserve Nexus-V invariants in a software profile before hardware claims |

## Applied spatial and physical concepts

| Concept | Current files | Status | Evidence | Next step |
|---|---|---|---|---|
| GPT project concept sync | `CHATGPT_PROJECT_SYNC_2026-08-05.md` | active | chat concepts consolidated with status classes | update after identity correction |
| Lightcore physical execution profile | `LIGHTCORE_PHYSICAL_EXECUTION_PROFILE.md` | specified / speculative | Lightcore correctly beneath Nexus-V contracts | formal signal schema, device risk register and simulation roadmap |
| L.O.D.E TV completion | `LODE_TV_COMPLETION_SPEC.md`, engineering map, controlled SVGs, measured File Library PDF | specified / concept package | optical pipeline, telemetry, RoomSense/BodyRig and preliminary dimensions exist | ingest controlled PDF/index and run ray/thermal/structural modelling |
| RoomSense / BodyRig | interface spec and L.O.D.E package | specified / conceptual | coordinate-frame and sensor-fusion intent documented | schemas, confidence metrics and local testbed |
| Reality-to-Simulation multisensor | File Library engineering package | conceptual engineering baseline | modular sensor design, calibration/evidence policy and outputs documented | create canonical repo spec and choose first deployment use case |
| Known Behavioral Map | File Library package | conceptual campaign design | multidomain repeated-test matrix documented | statistical design, material schema, cost/throughput and pilot campaign |
| ATHENA feed/benefit map | system matrices and diagrams | active | source-to-target benefits documented | update for independent JANUS/JARVIS/OASIS identities |
| Plugin workspace sync | sync logs and connected workspaces | active | GitHub/Notion/Drive/Asana mirrors exist | correct stale Operative Duplex and OASIS pages |

## Research and sanity anchors

| Domain | Current evidence | Status | Architecture consequence |
|---|---|---|---|
| Professional GUI grounding | ScreenSpot-Pro and related benchmarks | research-supported limitation | require application-specific tests, narrowed search and state verification |
| GUI-agent security | Visual Confused Deputy | research-supported risk | independent pre-action verifier and fresh-state checks mandatory |
| Hierarchical computer use | Agent S/Surfer/related research | research-supported pattern | separate planning, specialist skills, execution and recovery |
| Silicon nitride photonics | existing research anchors | research-supported primitive | valid platform candidate; not proof of full Lightcore |
| CNT/silicon-waveguide devices | existing research anchors | research-supported primitive | detector/optoelectronic pieces plausible; compute/memory claims remain speculative |
| Multisensor SLAM/human pose | existing research anchors | research-supported primitive | constrain RoomSense/BodyRig tests and confidence handling |
| 100-inch 16:9 geometry | calculated 2213.7 x 1245.3 mm | checked reference | use rounded 2214 x 1245 mm active area |

## Immediate work items

1. Merge the independent JANUS/OASIS identity correction after review.
2. Add `janus.manifest.yml`, operation schema and Skill Capsule JSON Schema.
3. Prototype read-only Windows UIA/Win32 application mapping.
4. Build independent pre-action target/focus/fresh-state verification.
5. Add OASIS object/world/export schemas and conventional runtime proof.
6. Reconcile `ATHENA_MASTER_ONTOLOGY.yml` with the corrected independent nodes.
7. Extract and hash-review the Plan DOCX corpus locally.
8. Ingest the L.O.D.E and R2S/Known Behavioral Map controlled packages into the canonical repo or a referenced artifact registry.
9. Create RoomSense/BodyRig coordinate-frame and confidence schemas.
10. Create Lightcore signal schema and physical execution risk register.
11. Keep speculative hardware, performance and material claims labelled as R&D until simulation and bench evidence exist.
12. Maintain GitHub as canonical; Notion/Drive/Asana/Figma/Canva remain labelled mirrors or execution surfaces.
13. Validate `schemas/athena-task-intake.schema.json`.
14. Run one task through intake, decision, implementation, verification and memory writeback.
15. Define adapter, project-capsule and skill-package schemas.
16. Confirm or replace the provisional Operative Duplex/JANUS naming where older material still conflicts.
17. Finish semantic review of the verified 58-image package through `athena_context/ASSET_INVENTORY.md`.
18. Complete the bounded GitHub planning reconciliation without broadening the local-only default.
