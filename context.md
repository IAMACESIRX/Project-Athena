# Project Athena Context

Generated: 2026-07-10

This file is the practical orientation map for this repository. It explains what
the project is, how it functions, which files matter, and what future agents or
humans need to know before editing it.

Latest foundation update: 2026-07-10. Athena task intake, memory map, cycle
report template, cycle runner, filled Plan planning files, root-relative tool
paths, generated reports, and operation-cycle verification were added or
refreshed. The latest full operation cycle is recorded in
`engine/cycle-reports/latest-cycle-report.md`; the live probe is intentionally
skipped when no live target is part of the task.

## Athena Operating Definition

Athena is an AI prosthetic external brain: a file-native memory, database, and
processor that extends a human operator by preserving context, organizing
knowledge, routing instructions, processing goals, and returning auditable next
actions.

In practical terms:

- The memory is the durable file tree: context docs, Plan specs, registries,
  ledgers, handoff notes, reports, source artifacts, and generated indexes.
- The database is the organized structure around that memory: folders,
  manifests, schemas, work queues, evidence maps, capability matrices, and
  canonical context files.
- The processor is the operating loop: human intent enters through `AI-PORTAL.md`
  and current context, then moves through governance, cognition, routing,
  execution, verification, audit, and continuity updates.
- The external-brain function is the combination of all three: Athena does not
  merely store notes; it turns stored project state into structured reasoning,
  decisions, tasks, and recoverable outputs.

Using Athena means using the repository itself as the thinking substrate. A
model should read the portal, respect `Plan/` as the highest-priority
architecture intent, ground claims in observed files, process the task through
the order-of-operations loop, then write back context, evidence, reports, or
work items when it learns something important.

## OASIS And Local Athena Adapters

The human-provided OASIS/Athena diagram is now captured as Plan intent in
`Plan/OASIS_ATHENA_AGENT_MODEL.md`.

Interpret it this way:

- OASIS is the outer operating environment: the full ecosystem that can contain
  Athena, tools, files, agents, project state, human direction, and future
  runtime services.
- Central Athena is the canonical external brain: memory, database, processor,
  router, evidence trail, and current project truth.
- Codex, Jarvis, GPT, and future AI surfaces each carry a local Athena adapter.
  They are not separate brains; they are agent surfaces that load Athena
  context, act through Athena rules, and write back to Athena memory.

The operating invariant is:

```text
Many agents, one Athena memory.
Many interfaces, one operating truth.
Many task surfaces, one evidence trail.
```

## Short Answer

Project Athena is a local-first AI operating-system control plane plus a
hardware/execution architecture research package.

It has two major identities:

1. A file-native AI-OS control plane for project memory, governance, agents,
   handoff, audit, diagnostics, work tracking, model routing, and long-running
   context preservation.
2. A Nexus-V / NVISC hardware and ISA project that explores versioned,
   branchable, reversible state computation, Aegis security/audit gates,
   tensor/NPU paths, topology routing, and quantum-domain scaffolding.

The repo is not a conventional app. There is no package manager root, no single
server entry point, and no normal build manifest. It is primarily a structured
knowledge and operations repository, with one substantial hardware/source
subsystem under `Nexus V`.

## Current Checkout Reality

Current root:

`D:\Projects\Project Athena`

Observed current state:

- Git branch: `main`
- Tracked files: 1,067
- Approximate size excluding `.git`: 8.19 MB
- Top-level source of truth entry: `AI-PORTAL.md`
- Main context folders: `identity`, `governance`, `agents`, `orchestration`,
  `memory`, `engine`, `forensics`, `work`, `tools`, `Plan`, `Nexus V`
- Current extra visual artifact: `Circuit design/ChatGPT Image Jul 9, 2026, 03_27_29 PM.png`

Resolved layout note:

- The current checkout is the standalone Project Athena root.
- First-read manifests and PowerShell tools were updated on 2026-07-10 to use
  root-relative paths instead of the old nested `ai-system/` prefix.
- Some generated archives and mirrored historical docs may still contain old
  `ai-system/` paths because they preserve earlier state.

Treat this checkout as the current Athena root unless the human explicitly
reactivates the old parent-stack layout.

## Declared Original System

The original declared system in the root docs is:

- Mega backup stack root:
  `C:\Users\aesir\OneDrive\Desktop\WoW-Backups\2026-05-30_2035`
- AI control plane: `ai-system/`
- Game client layer: `GameClient-ChromieCraft-3.3.5a`
- Server live-state layer: `Server-Live-State`
- Server project layer: `WoW-Server-Project`
- Local bare remotes:
  `C:\Users\aesir\OneDrive\Desktop\WoW-Backups\local-git-host\2026-05-30_2035`

That original stack is still represented in:

- `START-HERE.md`
- `manifests/system-manifest.json`
- `registries/layers.yml`
- `navigation/project-map.md`
- `handoff/CURRENT_STATE.md`
- `sensory/scans/latest-scan.json`

This repo currently does not include the original game-client, live-state, or
server-project child layers at root.

## What The Project Is

The project is an institutional memory and execution-control layer for AI work.
Its core idea is that an AI system should not be a stateless chatbot. It should
have:

- identity,
- constitution,
- project brains,
- governance,
- authority levels,
- agents,
- model routing,
- memory,
- evidence ledgers,
- work queues,
- diagnostic tools,
- operation cycles,
- handoff packets,
- audit trails,
- restore awareness,
- cognition protocols,
- and future runtime APIs.

The AI-OS side turns work into a governed loop:

1. Read the human goal.
2. Anchor to authority and current state.
3. Select the active project brain.
4. Gather evidence.
5. Route the task to the right agent/model/tool.
6. Reason with uncertainty labels.
7. Execute only within the correct layer.
8. Verify the result.
9. Record audit, handoff, and lessons.

The Nexus-V side is the hardware/execution substrate research direction:

- versioned state compute,
- Git-like commit/branch/merge/rollback primitives,
- reversible/checkpointable execution,
- topology routing,
- multi-domain memory,
- Aegis safety and attestation,
- tensor/NPU execution,
- quantum-domain bridge scaffolding,
- NVASM/NVIR/NVOBJ compiler bridge,
- eventual AI-OS integration into a semantic execution machine.

## What It Is Not

This repository is not currently:

- a finished application,
- a production AI runtime,
- a web dashboard,
- a complete CPU implementation,
- a verified hardware design,
- a package-manager project,
- a complete WoW stack checkout,
- or a source of live runtime truth without refreshing reports.

Many capabilities are intentionally specified as future contracts rather than
implemented systems.

## How It Functions

The current implementation is file-native. Files are the database, API,
message bus, governance layer, evidence layer, and memory layer.

The functional pieces are:

- Markdown files define human-readable policies, protocols, context, and
  plans.
- YAML files define registries, routers, capabilities, resources, tasks, and
  state.
- JSON files define schemas, generated reports, scans, indexes, and tool
  outputs.
- CSV files define evidence registers, claim maps, timelines, ledgers, and
  baselines.
- PowerShell scripts under `tools/` implement scan, export, verification,
  audit, work-item, handoff, and operation-cycle commands.
- Python scripts under `Nexus V/scripts` and `Nexus V/toolchain` implement
  static hardware audits, regression scaffolding, and the NVISC compiler bridge.
- SystemVerilog files under `Nexus V/rtl` and `Nexus V/tb` define Nexus-V RTL
  modules and testbench assets.

The intended full operation cycle is:

1. `Invoke-AIIntegrityCheck.ps1`
2. `Invoke-AIProjectScan.ps1`
3. `Export-ProjectMap.ps1`
4. `Export-AISystemManifest.ps1`
5. `Invoke-AIForensicVerification.ps1`
6. `Invoke-AILogIntelligence.ps1`
7. `Invoke-AIWatchedState.ps1`
8. optional `Invoke-LiveServerProbe.ps1`
9. `Invoke-AIOperationCycle.ps1` report output

Because the checkout is now root-level instead of nested under `ai-system/`,
run these tools cautiously and inspect script defaults before write-mode use.

## Prime Directives And Invariants

The controlling rules appear in `README.md`, `identity/constitution.md`, and
`governance/absolutes.md`.

Core invariants:

- Human authority is highest.
- Evidence beats assumption.
- Do not falsify evidence.
- Do not present uncertainty as certainty.
- Do not destroy knowledge, SQL dumps, live state, client state, audit records,
  Docker volumes, or Git history casually.
- Do not push to cloud remotes when a project is marked local-only unless the
  human explicitly changes the rule.
- Identify rollback paths before live-state or runtime changes.
- Generated reports are not current truth unless refreshed.
- Handoff and audit are part of the work.

Important contradiction:

- Project policy says local-only and no GitHub server push by default.
- This checkout currently has a GitHub origin remote.
- Treat that as a governance mismatch unless the human explicitly confirms the
  cloud remote is now allowed.

## Root File Map

`AI-PORTAL.md`
: Universal entry point for any AI, human, program, or tool. Defines the
  project name, first-read list, first-run commands, conceptual map, capability
  posture, and local-only warning.

`README.md`
: High-level explanation of the AI system layer, read order, role of the
  folder, and prime directive.

`START-HERE.md`
: Practical first-actions guide for a new AI session. Still reflects the old
  WoW backup-stack parent layout.

`.gitattributes`
: Enables automatic text normalization.

`context.md`
: This generated orientation file.

`Circuit design/ChatGPT Image Jul 9, 2026, 03_27_29 PM.png`
: Visual architecture diagram titled "ATHENA + NEXUS-V + LIGHTCORE". It shows
  Athena as institutional cognition/orchestration, Nexus-V as semantic
  execution/verification state machine, and Lightcore as physical execution
  fabric. It also shows Athena-to-Nexus and Nexus-to-Lightcore interfaces,
  memory layers, routing/interconnects, technologies, and end-to-end flow.

## Directory Map

`agents/`
: Agent registry, object model, lifecycle, and team formation. Defines the
  human owner, Codex-style local engineer, GPT-style reasoner, research agent,
  observer agent, and governance agent.

`audit/`
: Decision, causality, rollback, audit ledgers, audit schema, and event files.
  Used to make major changes traceable.

`cognition/`
: Advanced reasoning protocol library. Includes anti-hallucination, conceptual
  leaps, algorithmic inversion, fuzzy logic, superposition, non-monotonic
  reasoning, contextual anchoring, hypergraph processing, group dynamics, and
  other structured cognition systems.

`continuity/`
: Long-session and cross-agent continuity layer. Contains chat logs, handoff
  packets, distilled context, transcript inbox, and interaction ledger.

`council/`
: Reasoning council protocols and roles. Supports structured debate and
  multi-perspective review.

`counterfactuals/`
: Counterfactual analysis protocols and ledgers.

`diagnostics/`
: Risk register, issue ledger, correction queue, integrity reports, restore
  readiness, and resolvable issue tracking.

`drift/`
: Drift detection and drift ledgers. Used to identify stale assumptions,
  semantic drift, and mismatch between declared and actual state.

`engine/`
: Operation-cycle engine. This is the deterministic work spine: integrity,
  scan, map, manifest export, forensic verification, log intelligence,
  watched-state baseline, optional live probe, cognition checklist, and cycle
  report.

`forensics/`
: Evidence discipline layer. Contains evidence IDs, claim catalog,
  evidence-to-claim links, event timeline, known unknowns, verification
  reports, role packets, and evidence labeling rules.

`governance/`
: Absolutes, policy matrix, change control, review gates, error correction,
  and self-correction. Controls what actions are safe, blocked, cautious, or
  human-only.

`handoff/`
: Current state, next actions, changelog, session template, and per-session
  handoffs.

`identity/`
: System identity, constitution, mission, values, scope, and human authority.

`integration/`
: Adapter contracts, ingestion guide, adapter registry, and programmatic API
  documentation.

`learning/`
: Meta-learning, lesson extraction, and lesson ledger.

`manifests/`
: System manifest, ingestion order, capability matrix, tool index, and
  generated AI index. These are the closest thing to a machine-readable API.

`memory/`
: Contextual work IQ, contextual anchors, semantic memory, procedural memory,
  and memory maintenance. There is no root `memory/README.md` in this checkout.

`model-ops/`
: Model registry, provider policy, evaluation rubric, and target AI
  architecture contracts.

`modules/`
: Human-readable module cards for major functional areas such as game client,
  server live state, command hub, playerbots, AI operation engine, and local Git
  host. Some cards describe original WoW stack layers that are absent in this
  standalone checkout.

`navigation/`
: Project map and generated map. Still reflects the old parent-stack topology.

`Nexus V/`
: Main source-heavy subsystem. Contains SystemVerilog RTL/testbenches, NVISC
  toolchain code, generated compiler outputs, reports, source archives,
  mirrored docs, and Verilator-generated artifacts.

`observability/`
: Live server observability contracts, probes, log signatures, log index, event
  model, reports, and report JSON.

`operating-model/`
: Agent protocol, roles, mission, security/permissions, editing contracts, and
  Git layer protocol.

`orchestration/`
: Model router, message protocol, task routing, MCP tool layer, and event bus.
  Defines how Codex-style local engineering, GPT-style reasoning, research,
  diagnostics, governance, and future models should be routed.

`organization/`
: Organization hierarchy, authority levels, consensus protocol, and executive
  operating model.

`physics/`
: System physics model, entities, state vectors, interaction contracts, and
  failure modes. This is a conceptual model for how state moves and fails.

`Plan/`
: Planning/specification vault. Contains AI-OS v1-v13, Project Athena
  cognitive orchestrator spec, Odysseus Nexus ontology migration blueprint,
  Nexus-V/NVISC/NVVM Word specs, hardware notes, source zips, filled roadmap
  files, and the implementation matrix.

`playbooks/`
: Operational playbooks for first contact, adding features, diagnosing server
  state, snapshotting live state, and updating the game client.

`projects/`
: Project registry and project brains. Current primary project is
  `project-athena`; `nexus-v` is an active subsystem, `general-ai-os` is the
  foundation, and `wow-backup-stack` is retained as legacy history.

`registries/`
: Layer, module, interface, and file-ownership registries.

`reputation/`
: Trust model and reputation ledger for agents or systems.

`research/`
: Experiments, R&D backlog, model archaeology, source ledgers, deconstruction
  protocol, and open-model capability matrix.

`resources/`
: Resource budget and resource documentation.

`restore/`
: Backup policy, restore playbook, restore points, restore reports, and drills.

`reverse-engineering/`
: Reverse-engineering protocols and target inventory.

`runtime/`
: Future executable runtime contracts, service map, API contracts, runtime
  state machine, and Windows agent platform.

`schemas/`
: JSON schemas for agents, capability, claim, cognition output, cycle report,
  evidence, fuzzy claim, hyperedge, message, observation, open-model source,
  project, system manifest, task, and work item.

`sensory/`
: Health model, signal definitions, scans, baselines, latest watched changes,
  and latest scan.

`templates/`
: Templates for experiment cards, handoffs, issue cards, and module cards.

`tools/`
: PowerShell implementation scripts for project scan, manifest export, map
  export, integrity check, operation cycle, forensic verification, log
  intelligence, watched state, handoff snapshots, chat handoffs, work items,
  audit events, restore points, live server probes, and layer pointer updates.

`training/`
: Curriculum, feedback loop, and training data policy.

`truth/`
: Source priority, evidence ledger, and cross-check pipeline.

`work/`
: TODO, backlog, bugs, features, milestones, decisions needed, README, and
  individual work items.

## Important File Groups

### Manifests

`manifests/system-manifest.json`
: Full machine-readable map of the intended AI-system.

`manifests/ingestion-order.yml`
: Stable read order for humans, agents, and programs.

`manifests/capability-matrix.yml`
: Implemented/scaffolded/specified/blocked capability list.

`manifests/tool-index.yml`
: Tool registry with mutation behavior and purpose.

`manifests/generated-ai-index.json`
: Generated index of the AI-system. Treat as stale if not refreshed.

### Registries

`registries/layers.yml`
: Original multi-layer stack topology and hosting policy.

`registries/modules.yml`
: Functional modules and risk levels.

`registries/interfaces.yml`
: Allowed and blocked interfaces for Git, filesystem, server runtime, and AI
  backend.

`registries/file-ownership.yml`
: Ownership and edit policy for major paths.

### Governance

`governance/absolutes.md`
: Rules that override convenience.

`governance/policy-matrix.yml`
: Action risk matrix and confirmation requirements.

`governance/change-control.md`
: Change classes and fields required for significant changes.

`identity/constitution.md`
: Non-negotiable principles, human authority, and evolution rule.

### Operation Engine

`engine/README.md`
: Explains the operation engine.

`engine/operation-cycle.md`
: Defines the cycle contract and generated outputs.

`engine/routine-catalog.yml`
: Machine-readable routine order.

`engine/order-of-operations.md`
: Full long-form checklist for serious work.

`engine/checklists/*.md`
: Specific diagnostic, engineering, and reasoning checklists.

`engine/cycle-reports/latest-cycle-report.*`
: Most recent generated cycle report. Treat as generated state.

### Tools

`tools/Invoke-AIProjectScan.ps1`
: Scans Project Athena root, Plan, Nexus V, engine, memory, work, and tools
  state from the standalone checkout.

`tools/Invoke-AIIntegrityCheck.ps1`
: Checks required files, JSON validity, manifest path resolution, and
  local-only governance from the standalone checkout.

`tools/Invoke-AIOperationCycle.ps1`
: Runs the full integrated operation cycle.

`tools/Export-AISystemManifest.ps1`
: Generates `manifests/generated-ai-index.json`.

`tools/Export-ProjectMap.ps1`
: Generates the project map.

`tools/Invoke-AIForensicVerification.ps1`
: Checks evidence IDs, claims, links, timeline, and known unknowns.

`tools/Invoke-AILogIntelligence.ps1`
: Scans logs against signatures and queues findings.

`tools/Invoke-AIWatchedState.ps1`
: Tracks watched file hashes and drift.

`tools/Invoke-LiveServerProbe.ps1`
: Read-only live server probe scaffold.

`tools/New-HandoffSnapshot.ps1`
: Creates dated session handoffs.

`tools/New-ChatHandoff.ps1`
: Creates chat log plus handoff packet.

`tools/New-AuditEvent.ps1`
: Creates audit events.

`tools/New-WorkItem.ps1`
: Creates work items.

`tools/New-RestorePoint.ps1`
: Creates restore point manifests and optionally Git tags/bundles.

`tools/Update-LayerPointers.ps1`
: Stages/commits child repo pointer changes in the original mega-repo layout.

### Forensics

`forensics/evidence-register.csv`
: Stable evidence IDs and paths.

`forensics/claim-catalog.csv`
: Claims separated from observations.

`forensics/evidence-claim-map.csv`
: Evidence-to-claim grounding.

`forensics/event-timeline.csv`
: Timeline of relevant events.

`forensics/known-unknowns.csv`
: Explicit uncertainties.

`forensics/verification-reports/latest-forensic-verification.*`
: Generated verification result.

### Work And Risk

`work/TODO.md`
: Current declared work queue.

`work/backlog.yml`, `work/bugs.yml`, `work/features.yml`
: Structured backlog, bugs, and features.

`work/work-items/`
: Individual work item records.

`diagnostics/risk-register.md`
: Known project risks.

`diagnostics/correction-queue.md`
: Queue for resolvable integrity/correction items.

`diagnostics/reports/latest-integrity-report.*`
: Generated integrity report.

### Continuity

`handoff/CURRENT_STATE.md`
: Older state snapshot for the original WoW backup stack.

`handoff/NEXT_ACTIONS.md`
: Older next-action list for the original stack.

`continuity/chat-logs/`
: Stored chat logs.

`continuity/handoff-packets/`
: Structured handoff packets.

`continuity/distilled-context/project-continuity.md`
: Compressed continuity memory.

`continuity/interaction-ledger/interaction-ledger.yml`
: Interaction ledger.

## Plan Folder

The `Plan/` folder is the concept and specification vault.

Observed contents:

- 61 files total
- 24 `.docx`
- 22 `.md`
- 13 `.zip`
- 2 `.txt`
- All `.docx` files structurally open.
- All `.zip` files structurally open.
- 53 of 61 files are exact duplicates of `Nexus V/docs/Plan`.
- 8 files exist only in root `Plan`: AI-OS v9-v13, Athena Memory Architecture,
  Project Athena Cognitive Orchestrator, and Odysseus Nexus.

Key Plan files:

`Plan/system plan.md`
: AI-OS v1.0. Defines AI-OS as an artificial organization with human authority,
  board/executive/reasoning/governance/coordination/management/operative/
  observation/adaptive/meta layers, memory, knowledge graph, decision ledger,
  anti-hallucination, and learning loop.

`Plan/AI-OS-v2.0-Artificial-Organization-Specification.md`
: Expands the organization and cognitive civilization structure.

`Plan/AI-OS-v3.0-Institution-Expansion-and-Action-Plan.md`
: Adds institution, civilization, long-term sustainability, and phased action.

`Plan/AI-OS-v4.0-Technical-Architecture-Specification.md`
: Technical architecture, kernel, agent object model, messages, tasks,
  consensus, reputation, memory, knowledge, governance, identity, and
  observability.

`Plan/AI-OS-v5.0-Runtime-Implementation-Blueprint.md`
: Runtime implementation blueprint with gateway, services, event bus, memory,
  routing, simulation, observability, audit, deployment, scaling, and disaster
  recovery.

`Plan/AI-OS-v6.0-Source-Code-and-Infrastructure-Architecture.md`
: Source and infrastructure architecture, microservices, schemas, databases,
  model routing, MCP layer, agent teams, consensus, observability, security,
  Kubernetes, and recovery.

`Plan/AI-OS-v7.0-Master-Specification.md`
: Master AI-OS specification.

`Plan/AI-OS-v8.0-Constitution-and-Identity-Charter.md`
: Constitution and identity charter.

`Plan/AI-OS-v9.0-Governance-Manual-and-Operating-Procedures.md`
: Governance manual and operating procedures.

`Plan/AI-OS-v10.0-Knowledge-and-Memory-Constitution.md`
: Knowledge classes, memory layers, lifecycle, and project brain standard.

`Plan/AI-OS-v11.0-Agent-Species-Catalog.md`
: Organizational, reasoning, capability, and specialist agent species.

`Plan/AI-OS-v12.0-Federation-and-Civilization-Framework.md`
: Evolution path from agent to federation/civilization.

`Plan/AI-OS-v13.0-Unified-Encyclopedia.md`
: Merges AI-OS v2-v12 and integrates Nexus-V into the canonical objective.

`Plan/Project-Athena-Cognitive-Orchestrator-Specification-v1.0.md`
: Defines the cognitive orchestrator and cognitive senate.

`Plan/Odysseus-Nexus-Ontology-Extraction-and-Unification-Specification.md`
: AI-OS v14 migration blueprint for extracting and unifying all concepts into a
  canonical ontology.

`Plan/Hardware plan.md`
: Raw conceptual hardware notes for 3D state/tensor CPUs, Git-like states,
  branch/merge/rollback execution, multi-valued logic, Aegis safeguard
  auditing, anti-cheat/anti-hack attestation, and polyhedral processor shapes.

`Plan/define.txt`
: Checklist-like definition of Nexus-V core completeness and Phase 7 CPU core
  completion.

`Plan/NVISC.txt`
: Large opcode vocabulary for the N-dimensional versioned ISA.

`Plan/ROADMAP.md`, `Plan/TODO.md`, `Plan/TODO_STATUS.md`,
`Plan/QUALITY_PLAN.md`, `Plan/FEATURE_ROADMAP.md`
: Filled planning files as of 2026-07-10. They define the roadmap, actionable
  TODOs, subsystem status, quality gates, and feature tracks.

### Plan Priority File-By-File Appendix

The `Plan/` folder is top priority. Every file in it is accounted for below.
Text and Markdown files were read directly. Word documents were opened as
OOXML packages and text was extracted/validated. Zip archives were opened and
their entry counts and dominant source types were checked. This is not a full
semantic review of every line inside every `.docx` or every archived source
file; it is a file-by-file project-context pass.

#### AI-OS Planning Files

`Plan/system plan.md`
: AI-OS v1.0 source concept. Defines the system as an artificial organization,
  not a chatbot. It lays out the human, board AI, executive AI, reasoning
  council, governance AI, instructional AI, coordination AI, management AI,
  operative network, observation AI, adaptive AI, meta AI, memory architecture,
  knowledge graph, decision ledger, anti-hallucination framework, internal
  debate framework, and continuous learning loop. This is the conceptual seed
  for the root AI-system folders.

`Plan/AI-OS-v2.0-Artificial-Organization-Specification.md`
: Expands AI-OS into an artificial organization and cognitive civilization
  model. It formalizes hierarchy layers, capability agents, expertise agents,
  operative workforce, observation, adaptive/meta systems, memory, knowledge,
  project brains, relationship model, temporary teams, swarm layer, and
  continuous feedback.

`Plan/AI-OS-v3.0-Institution-Expansion-and-Action-Plan.md`
: Moves from organization to institution/civilization. Defines constitution,
  identity, economic, reputation, and civilization layers plus a phased action
  plan from foundation through civilization.

`Plan/AI-OS-v4.0-Technical-Architecture-Specification.md`
: Converts the organization idea into a technical architecture: AI-OS kernel,
  agent object model, message protocol, task lifecycle, consensus, voting,
  reputation, trust, memory, knowledge graph, decision ledger, constitution,
  governance, identity, economic engine, resources, capability/expertise
  networks, project team formation, observation, adaptive learning, meta
  evolution, federation, and success metrics.

`Plan/AI-OS-v5.0-Runtime-Implementation-Blueprint.md`
: Runtime implementation blueprint. Defines high-level stack, API gateway,
  kernel services, agent runtime/orchestrator, event bus, memory architecture,
  project brain, task routing, reputation/trust/consensus/simulation systems,
  observability, audit, security, economics, learning, meta evolution,
  deployment, scaling, disaster recovery, and success criteria.

`Plan/AI-OS-v6.0-Source-Code-and-Infrastructure-Architecture.md`
: Source-code and infrastructure architecture. Describes reference services,
  identity/constitution/governance/agent/reputation/trust/project-brain
  services, agent state machine, message/task/decision/knowledge schemas,
  vector/relational/graph/object storage, model routing, MCP layer, team
  generation, consensus, observability, security, Kubernetes deployment,
  disaster recovery, and future v7 targets.

`Plan/AI-OS-v7.0-Master-Specification.md`
: Master specification for artificial organization, institution, federation,
  and civilization. This is a consolidation layer for v1-v6 concepts.

`Plan/AI-OS-v8.0-Constitution-and-Identity-Charter.md`
: Constitution and identity charter. Defines the durable identity layer, core
  values, non-negotiable principles, human authority, knowledge, memory,
  governance, auditability, learning, reputation, resources, evolution,
  federation, civilization, and success criteria.

`Plan/AI-OS-v9.0-Governance-Manual-and-Operating-Procedures.md`
: Short governance manual and operating procedure layer. This file exists only
  in root `Plan`, not the `Nexus V/docs/Plan` mirror.

`Plan/AI-OS-v10.0-Knowledge-and-Memory-Constitution.md`
: Short knowledge and memory constitution. Defines knowledge classes, memory
  layers, memory lifecycle, and the project brain standard. Exists only in root
  `Plan`.

`Plan/AI-OS-v11.0-Agent-Species-Catalog.md`
: Catalog of organizational, reasoning, capability, and specialist agent
  types. Defines the fields each agent definition should carry. Exists only in
  root `Plan`.

`Plan/AI-OS-v12.0-Federation-and-Civilization-Framework.md`
: Short framework for evolution from agent to multi-agent system, organization,
  institution, federation, and civilization. Exists only in root `Plan`.

`Plan/AI-OS-v13.0-Unified-Encyclopedia.md`
: Integrated master blueprint that merges AI-OS v2-v12 and incorporates
  Nexus-V. Defines AI-OS as agent, multi-agent system, artificial organization,
  persistent institution, and future federation/civilization. This is a major
  canonical bridge between AI-OS and Nexus-V.

`Plan/Project-Athena-Cognitive-Orchestrator-Specification-v1.0.md`
: Defines the cognitive orchestrator and cognitive senate. It explains task
  classification, cognitive selection/scheduling, consensus, confidence
  aggregation, learning integration, knowledge preservation, and maps future
  cognitive functions to Nexus-V/NPU/GPU/CPU/DPU/FPGA/ASIC domains. Exists only
  in root `Plan`.

`Plan/Odysseus-Nexus-Ontology-Extraction-and-Unification-Specification.md`
: AI-OS v14 migration blueprint. Its root axiom is that the system is an
  institutional intelligence rather than a model, agent, or runtime. Defines
  domain map, cognitive senate mapping, execution unification, ontology
  extraction tasks, duplication detection, gap analysis, and Nexus-V
  integration. Exists only in root `Plan`.

#### Hardware And ISA Notes

`Plan/Hardware plan.md`
: Raw hardware architecture dialogue and design notes. Captures the core Nexus-V
  thesis: 3D/depth-parallel state compute, more-than-binary logic, Git-like
  commit/branch/merge/rollback state, reversible state history, branch
  explosion controls, Aegis safeguard attestation, AI policy integrity, local
  privacy-preserving anti-cheat/anti-hack attestation, and alternate processor
  shapes such as dodecahedron, rhombic dodecahedron, octahedron, triangular
  bipyramid, isohedral polyhedra, and tetrahedron.

`Plan/Hardware specifics.md`
: Dense raw component inventory: instruction/data/execution/live memory,
  caches, media engine, accelerators, efficiency/performance cores, secure
  enclaves, PCIe/I/O, registers, ALUs, branch prediction, SIMD, GPU/tensor/CUDA
  ideas, 3D memory stacking, DRAM/VRAM/hot trusted memory, TPU/DPU/QPU/NPU/IPU,
  and smart tasking. This is concept capture rather than a formal spec.

`Plan/define.txt`
: Nexus-V core completeness and Phase 7 conventional CPU completion checklist.
  Lists instruction fetch, decoder, PC/branch, CSR, LSU, MMU/TLB, L1/L2/L3,
  memory controller, interrupt/timer, vector/SIMD, multi-core instances,
  per-thread state, RSM coherence, Aegis contexts, schedulers, reorder buffer,
  issue queues, branch prediction, speculation, retirement, rollback,
  cache/state ownership, bus tags, memory controllers, ECC, DMA, and 8-core
  shared-service targets.

`Plan/NVISC.txt`
: Opcode vocabulary for the N-dimensional versioned ISA. Includes conventional
  scalar ops, floating/approximate ops, versioned state ops, RSM/COW/delta ops,
  merge/conflict ops, reversible execution ops, multi-valued logic ops,
  tensor/NPU ops, dataflow ops, topology/geometric routing ops, Aegis/security
  ops, AI-policy audit ops, anti-cheat/anti-hack attestation ops, proof/signing
  ops, I/O/GPU/HID provenance ops, ECC/repair ops, thermal/power ops, memory
  ops, micro-op pipeline ops, privilege/VM/isolation ops, fault/debug ops, and
  quantum/hybrid ops.

#### Nexus-V Word Specifications

`Plan/Athena Memory Architecture v1.0.docx`
: Word spec for Athena memory architecture. Extracted text begins with
  "Athena Memory Architecture v1.0 Institutional..." and the document has 187
  text runs. Exists only in root `Plan`.

`Plan/Nexus_V_RTL_Microarchitecture_Specification_v0_1.docx`
: RTL microarchitecture specification for Nexus-V v0.1. Extracted text begins
  with "Nexus-V RTL Microarchitecture Specification..." and has 644 text runs.

`Plan/Nexus_V_Phase0_SystemVerilog_RTL_and_Routing_Modules_v0_1.docx`
: Phase 0 SystemVerilog RTL and routing modules. Extracted text begins with
  "Nexus-V Phase 0 SystemVerilog RTL..." and has 726 text runs.

`Plan/Nexus_V_Phase0_Closeout_Topology_Fabric_and_Two_Path_Routing_v0_1.docx`
: Phase 0 closeout for topology fabric integration and two-path routing.
  Extracted text begins with "Nexus-V Phase 0 Closeout: Topology..." and has
  789 text runs.

`Plan/Nexus_V_RSM_Phase1_Physical_Memory_Allocator_and_Metadata_Triad_v0_1.docx`
: RSM Phase 1 physical memory allocator and metadata triad. Extracted text
  begins with "Nexus-V RSM Phase 1 Physical Memory Allocator..." and has 304
  text runs.

`Plan/Nexus_V_RSM_Phase1_Rollback_FSM_and_Delta_Log_Engine_v0_1.docx`
: RSM rollback FSM and delta log engine. Extracted text begins with
  "Nexus-V RSM Phase 1 Rollback FSM..." and has 800 text runs.

`Plan/Nexus_V_Aegis_Phase1_Enclave_Commit_Gate_and_MINREP_v0_1.docx`
: Aegis enclave, commit gate, attestation, and MINREP spec. Extracted text
  begins with "Nexus-V Aegis Phase 1 Enclave, Commit Gate..." and has 740 text
  runs.

`Plan/Nexus_V_Phase3_Topology_Fabric_Multi_Node_Polyhedral_Network_v0_1.docx`
: Phase 3 topology fabric, multi-node polyhedral network. Extracted text begins
  with "Nexus-V Phase 3 Topology Fabric Multi-Node..." and has 692 text runs.

`Plan/Nexus_V_Phase4_Tensor_NPU_Engine_Spatial_Execution_v0_1.docx`
: Phase 4 tensor/NPU spatial execution engine. Extracted text begins with
  "Nexus-V Phase 4 Tensor/NPU Engine Spatial..." and has 805 text runs.

`Plan/Nexus_V_Phase5_Hybrid_Quantum_Domain_QSIM_QHW_Bridge_v0_1.docx`
: Phase 5 hybrid quantum domain QSIM/QHW bridge. Extracted text begins with
  "Nexus-V Phase 5 Hybrid Quantum Domain QSIM..." and has 226 text runs.

`Plan/Nexus_V_Unified_Interface_Contract_and_Bring_Up_Plan_v0_1.docx`
: Unified interface contract and bring-up plan. Extracted text begins with
  "Nexus-V Unified Interface Contract and Bring..." and has 267 text runs.

`Plan/Nexus_V_Phase6_Bringup_Run_001_Report.docx`
: Phase 6 bring-up run report. Extracted text begins with "Nexus-V Phase 6
  Bring-Up Run 001..." and has 97 text runs.

`Plan/Nexus_V_SoC_Top_Level_Integration_and_Hardware_Plan_Pre_Audit_v0_1.docx`
: SoC top-level integration and hardware-plan pre-audit. Extracted text begins
  with "Nexus-V SoC Top-Level Integration..." and has 237 text runs.

`Plan/Nexus_V_SoC_Verification_and_Regression_Suite_v0_1.docx`
: SoC verification and regression suite spec. Extracted text begins with
  "Nexus-V SoC Verification & Regression..." and has 397 text runs.

`Plan/Nexus_V_Core_Completeness_Specification_v0_2.docx`
: Core completeness specification v0.2. Extracted text begins with "Nexus-V
  Core Completeness Specification v0.2..." and has 527 text runs.

`Plan/Nexus_V_Four_Domain_Memory_and_Harvard_Bus_Model_v0_1.docx`
: Four-domain memory and Harvard-lane bus model. Extracted text begins with
  "Nexus-V Four-Domain Memory and Harvard-Lane..." and has 311 text runs.

`Plan/Nexus_V_Advanced_Execution_Architecture_Addendum_v0_3.docx`
: Advanced execution architecture addendum. Extracted text begins with
  "Nexus-V Advanced Execution Architecture Addendum..." and has 433 text runs.

`Plan/Nexus_V_Adaptive_Physical_Execution_Fabric_v0_1.docx`
: Adaptive physical execution fabric spec. Extracted text begins with
  "Nexus-V Adaptive Physical Execution Fabric..." and has 362 text runs.

`Plan/NVISC_Architecture_Reference_v2_Complete.docx`
: NVISC architecture reference for the N-dimensional versioned ISA. Extracted
  text begins with "NVISC Architecture Reference N-Dimensional..." and has 1418
  text runs.

`Plan/NVASM_Specification_v0_2_Extended.docx`
: NVASM v0.2 extended assembly specification. Extracted text begins with
  "NVASM Specification v0.2 Extended..." and has 2014 text runs.

`Plan/NVASM_Specification_v0_3_Semantic_Parser_Extended.docx`
: NVASM v0.3 semantic parser extension. Extracted text begins with
  "NVASM Specification v0.3 Semantic Parser..." and has 2409 text runs.

`Plan/NVIR_Semantic_Lowering_and_Versioned_Dataflow_Specification_v0_1.docx`
: NVIR semantic lowering and versioned dataflow specification. Extracted text
  begins with "NVIR Semantic Lowering and Versioned Dataflow..." and has 532
  text runs.

`Plan/NVISC_NVVM_Compiler_Bridge_Toolchain_v0_1.docx`
: NVISC/NVVM compiler bridge and toolchain specification. Extracted text begins
  with "NVISC / NVVM Compiler Bridge Toolchain..." and has 193 text runs.

`Plan/NVVM_Virtual_Machine_Architecture_and_3D_Routing_Specification_v0_1.docx`
: NVVM virtual machine architecture and 3D routing specification. Extracted
  text begins with "NVVM Virtual Machine Architecture..." and has 622 text runs.

#### Nexus-V Source Archives In Plan

`Plan/nexus_v_phase0_sv_sources.zip`
: Valid archive with 8 SystemVerilog entries. Contains early phase0 package,
  regfile, ALU slice, state token interface, route mux, rhombic dodeca router,
  phase0 core, and testbench.

`Plan/nexus_v_phase0_closeout_sv_sources.zip`
: Valid archive with 11 SystemVerilog entries. Adds route request arbiter,
  routing unit, topology fabric interface, and expanded phase0 closeout source.

`Plan/nexus_v_rsm_phase1_sources.zip`
: Valid archive with 7 SystemVerilog entries. Contains RSM branch meta table,
  controller, COW map, physical allocator, package, state meta table, and
  allocator testbench.

`Plan/nexus_v_rsm_phase1_rollback_delta_sources.zip`
: Valid archive with 5 SystemVerilog entries. Contains RSM package, delta log,
  rollback FSM, rollback-aware controller, and rollback testbench.

`Plan/nexus_v_aegis_phase1_sources.zip`
: Valid archive with 7 SystemVerilog entries. Contains Aegis package, trust
  telemetry aggregator, commit gate, attest token unit, MINREP generator,
  enclave, and enclave testbench.

`Plan/nexus_v_phase3_topology_sources.zip`
: Valid archive with 7 SystemVerilog entries. Contains topology package,
  poly crossbar, route compute unit, router node, topology token table,
  rhombic dodeca fabric, and fabric testbench.

`Plan/nexus_v_phase4_tensor_sources.zip`
: Valid archive with 12 SystemVerilog entries. Contains tensor package,
  descriptor table, scratchpad, scheduler, compute unit, node array, route
  adapter, reduce/fold, dispatch, numeric integrity, tensor NPU engine, and
  engine testbench.

`Plan/nexus_v_phase5_quantum_sources.zip`
: Valid archive with 11 SystemVerilog entries. Contains quantum package, qreg
  file, QSIM state bank, gate/measure/token/collapse units, QHW bridge stub,
  control FSM, quantum domain engine, and testbench.

`Plan/nexus_v_phase6_unified_interface_sources.zip`
: Valid archive with 8 entries: 3 SystemVerilog, 2 Python, 1 Markdown, plus
  schema/program assets. Contains README, SoC smoke testbench, golden trace
  schema, lint/regression scripts, full-system NVASM program, common package,
  and SoC wrapper.

`Plan/nexus_v_soc_integration_sources.zip`
: Valid archive with 74 entries: 63 SystemVerilog and 1 Markdown. Contains
  integration, phase0, RSM, rollback, Aegis, topology, tensor, and quantum
  source groups.

`Plan/nexus_v_soc_verification_sources.zip`
: Valid archive with 14 entries: 8 SystemVerilog and 3 Python. Contains SoC
  testbench, driver, monitor, scoreboard, trace checker, assertions, fault
  injector, verification package, and helper scripts.

`Plan/nexus_v_canonical_repo_v0_1_bringup_run_001.zip`
: Valid canonical repo snapshot with 126 entries: 71 SystemVerilog, 10 Python,
  and 4 Markdown. This is the broadest source archive in Plan and appears to
  correspond to the current `Nexus V` working tree lineage.

`Plan/nvisc_toolchain_bridge_v0_1_sources.zip`
: Valid toolchain archive with 14 entries: 7 Python and 1 Markdown. Contains
  README, example NVASM, `nvisc-bridge`, and the `nvisc_toolchain` Python
  package.

#### Planning Files

`Plan/FEATURE_ROADMAP.md`
: Filled feature-track roadmap for Athena core, Plan knowledge, Nexus-V, and
  operator capabilities.

`Plan/QUALITY_PLAN.md`
: Filled quality plan for context accuracy, intake discipline, tool safety,
  Plan traceability, and verification.

`Plan/ROADMAP.md`
: Filled phased roadmap from current baseline through Athena brain-stem,
  Plan extraction, Nexus-V alignment, repeatable processor, and operator
  experience.

`Plan/TODO.md`
: Filled near-term, next, later, and parking-lot tasks.

`Plan/TODO_STATUS.md`
: Filled subsystem status table and human decisions needed.

`Plan/IMPLEMENTATION_MATRIX.md`
: Added on 2026-07-10. Maps Plan concepts to current implementation state and
  next steps.

### Plan Canonical Priority

When there is a conflict between the root operational docs and Plan:

1. Treat root operational docs as the current working control-plane state.
2. Treat `Plan/` as the highest-priority architecture intent and design
   backlog.
3. Convert Plan intent into root docs/code through explicit updates rather than
   assuming old Plan text is already implemented.
4. Treat root-only Plan files, especially AI-OS v9-v13, Athena Memory
   Architecture, Cognitive Orchestrator, and Odysseus Nexus, as the newest
   architectural direction.

## Nexus V Subsystem

`Nexus V/` is the current source-heavy part of the repository.

Observed structure:

- `docs/`: 422 files. Includes mirrored AI-system docs and mirrored Plan docs.
- `rtl/`: 98 SystemVerilog files.
- `sim/`: 42 simulation-related files.
- `obj_dir/`: 27 generated Verilator/build artifacts.
- `toolchain/`: 17 Python/toolchain files.
- `tb/`: 8 testbench files.
- `reports/`: 5 generated reports/logs.
- `generated/`: 3 generated toolchain outputs.
- `scripts/`: 3 Python scripts.
- `schemas/`: 1 schema.
- `programs/`: 1 NVASM program.

RTL domains:

- `rtl/phase0`: Phase 0 core, routing, state token, topology fabric interface.
- `rtl/core_v02`: Conventional CPU core v0.2 scaffold with fetch, decoder,
  control, CSR, LSU, register file, memory domains, cache/controller stubs, and
  testbenches.
- `rtl/rsm_phase1`: RSM state/branch metadata, copy-on-write maps, physical
  allocator, and controller.
- `rtl/rsm_rollback`: Rollback FSM, delta log, and rollback-aware RSM.
- `rtl/aegis_phase1`: Aegis trust telemetry, attestation, commit gate, enclave,
  MINREP generator, and package.
- `rtl/topology_phase3`: Rhombic-dodeca fabric, routing nodes, poly crossbar,
  topology token table, and routing compute.
- `rtl/tensor_phase4`: Tensor/NPU descriptor, dispatch, compute, scratchpad,
  route adapter, numeric integrity, reduce/fold, scheduler, and testbench.
- `rtl/quantum_phase5`: QSIM/QHW bridge, qreg, state bank, control FSM, gates,
  measure/collapse, token table, and quantum domain engine.
- `rtl/integration`: Nexus-V SoC package/top and smoke testbench.

Testbench and verification:

- `tb/` contains SoC verification package, assertions, fault injector, driver,
  monitor, scoreboard, trace checker, and `tb_nexus_v_soc.sv`.
- `scripts/static_bringup_audit.py` does static filelist/module/package/capability
  checks and writes reports.
- `scripts/run_lint.py` requires Verilator on PATH.
- `scripts/run_regression.py` checks generated vector/expected trace presence.

Toolchain:

- `toolchain/README.md` describes the compiler bridge:
  `NVASM -> parser AST -> semantic lowering -> NVIR JSON -> NVOBJ container -> RTL vectors`.
- `toolchain/nvisc_toolchain/parser.py` parses NVASM.
- `toolchain/nvisc_toolchain/lowering.py` lowers parsed instructions to NVIR.
- `toolchain/nvisc_toolchain/nvobj.py` writes NVOBJ.
- `toolchain/nvisc_toolchain/rtl_vectors.py` exports RTL vectors.
- `toolchain/nvisc_toolchain/schema.py` defines internal schema.
- `toolchain/nvisc_toolchain/cli.py` is the command entry point.

Generated Nexus-V outputs:

- `generated/06_full_system_ai_versioned_secure.nvir.json`
- `generated/06_full_system_ai_versioned_secure.nvobj`
- `generated/06_full_system_ai_versioned_secure.rtl_vectors.json`

Reports:

- `reports/phase6_static_bringup_audit.md`
  says the static audit passed, no blocking static issues were found, but no
  SystemVerilog simulator/linter was available.
- `reports/phase6_bringup_run_001_summary.md`
  says the Phase 6 bring-up was a partial pass: toolchain compile passed, SV
  simulation did not run.

Known Nexus-V limitation:

- Real SystemVerilog lint/simulation has not been proven in this environment.
- Verilator/Icarus/Questa/VCS/XSIM were absent in prior checks.
- Regression is scaffold-only unless expected traces are added.

## Circuit Design Artifact

`Circuit design/ChatGPT Image Jul 9, 2026, 03_27_29 PM.png`
is a visual system architecture diagram for:

- Athena: institutional cognition and orchestration layer.
- Nexus-V: semantic execution and verification state machine.
- Lightcore: physical execution fabric.

The diagram shows:

- Athena core services,
- Athena memory and knowledge fabric,
- Athena I/O and integration,
- Nexus-V execution architecture,
- adaptive execution router,
- core services,
- memory domains,
- Lightcore compute fabric,
- Lightcore memory hierarchy,
- routing/interconnect,
- end-to-end information and feedback flow.

This image is a design communication artifact, not executable source.

## File Type Coverage

The project is covered by these tracked file classes:

- `.md`: 515 Markdown documents and protocols.
- `.yml`: 138 registries, ledgers, routing files, and structured specs.
- `.sv`: 105 SystemVerilog RTL/testbench files.
- `.json`: 67 schemas, generated reports, scans, and compiler outputs.
- `.cpp`: 50 generated/simulation C++ files.
- `.docx`: 47 Word specification documents.
- `.ps1`: 30 PowerShell tools.
- `.zip`: 26 archived source/spec packets.
- `.gitkeep`: 18 placeholder directory keepers.
- `.csv`: 14 evidence, claim, timeline, ledger, and baseline files.
- `.py`: 10 Python audit/toolchain scripts.
- `.pyc`: 7 tracked Python cache files.
- `.d`, `.o`, `.exe`, `.mk`, `.h`, `.hpp`: generated/build artifacts.
- `.txt`: 4 raw text plans/spec notes.
- `.nvasm`: 2 NVASM program examples.
- `.png`: 1 visual architecture artifact.

## Full Repository Read And Index Pass

On 2026-07-10, a full non-`.git` repository inventory/extraction pass was run
across `D:\Projects\Project Athena`.

Generated output:

- `context-file-index.md`

Coverage of files present at scan time:

- 1,069 files indexed.
- 978 text-like files opened directly.
- 47 Word `.docx` files opened as OOXML and text-indexed.
- 26 zip archives opened and entry-indexed.
- 17 opaque binary/generated files metadata-indexed.
- 1 image metadata-indexed; the visible architecture image was also visually
  inspected.

This pass reads/summarizes the whole tree in the only meaningful way available
for mixed source, documentation, archive, generated, image, and binary
artifacts. It does not pretend that compiled `.o`, `.exe`, `.pyc`, `.a`, image,
or zip payload bytes are human-readable prose. For those files, it records
metadata, archive entry structure, role, size, and short hash.

Use `context-file-index.md` as the complete file-by-file appendix for this
repository. Use this `context.md` as the human-oriented explanation of what the
indexed files mean.

Important hygiene note:

- There is no `.gitignore`.
- Generated artifacts such as `Nexus V/obj_dir`, `.o`, `.exe`, and `.pyc` files
  are tracked.
- This is workable at the current small size, but build outputs can quickly
  pollute future commits if in-place builds continue.

## Mirrors And Duplicates

`Nexus V/docs/ai-system`
: Historical mirror of the earlier AI-system control-plane docs at the time of
  Nexus V packaging. Its `README.md`, `AI-PORTAL.md`, and `START-HERE.md` now
  redirect to the active root, but the remaining tree intentionally preserves
  old path names, schemas, and WoW-era assumptions for lineage.

`Nexus V/docs/Plan`
: Mirror/archive of root `Plan/` material, including the now-filled planning
  files.

`Plan/`
: Root `Plan/` remains canonical when root and mirrored copies disagree.

Rule:

When root and mirror disagree in the future, assume the root file is canonical
for current project operation and the `Nexus V/docs/...` copy is archival unless
evidence says otherwise.

## Current Known Risks

From `diagnostics/risk-register.md` and current scan findings:

- Original game client payload not fully committed in the old stack.
- Live-state SQL is sensitive in the old stack.
- Broken Python venv in old `WoW-Server-Project`.
- Realmlist mismatch in old live-state auth dump.
- Local bare host is not off-machine backup.
- Nested repos can drift in the old stack.
- Current checkout has GitHub remote despite local-only policy.
- Some generated or mirrored historical files still preserve old `ai-system/...`
  paths, but first-read manifests and tools now use root-relative paths.
- Generated artifacts are tracked and no `.gitignore` exists.
- Nexus-V has static/source checks but no proven real SV simulator run here.

## What Is Implemented Now

Implemented or usable now:

- File-native identity, governance, memory, work, and audit structure.
- Project registry and project-brain documents.
- Agent registry and authority model.
- Model-router contract.
- Operation-cycle PowerShell scripts.
- Integrity/forensic/log/watched-state/report scaffolding.
- Evidence, claim, timeline, known-unknowns records.
- Nexus-V RTL/source tree.
- NVISC Python compiler bridge scaffold.
- Generated full-system NVISC outputs.
- Static Nexus-V audit reports.

## What Is Scaffolded Or Specified

Scaffolded or specified:

- Runtime API gateway.
- Persistent agent scheduler.
- External model router.
- Vector/graph/relational memory stores.
- Event bus implementation.
- UI dashboard.
- Training and evaluation harness.
- Full live-server command modules.
- Live log watcher.
- Server dashboard.
- Game-client inventory tools.
- SQL dump inventory tool.
- Hardware branch scheduler, VPHI merge hardware, full ECC arrays, crypto units,
  true CDC, thermal sensors/governor, and alternate topology generators.

## How To Work In This Repo

For orientation:

1. Read `AI-PORTAL.md`.
2. Read this `context.md`.
3. Read `README.md`.
4. Read `Plan/context.md`.
5. Read `memory/athena-memory-map.md`.
6. Read `manifests/system-manifest.json`.
7. Read `registries/modules.yml` and `registries/file-ownership.yml`.
8. Read `governance/absolutes.md`.
9. For active work, read `work/ATHENA-FIRST-STEPS.md`, `work/TODO.md`, and
   `diagnostics/risk-register.md`.
10. For Nexus-V work, read `Nexus V/docs/NEXUS-V-IMPLEMENTATION-MATRIX.md`,
   `Nexus V/docs/pre_audit_against_hardware_plan.md`,
   `Nexus V/reports/phase6_bringup_run_001_summary.md`, and the relevant
   `Nexus V/rtl` or `Nexus V/toolchain` files.
11. For Plan/architecture work, read `Plan/IMPLEMENTATION_MATRIX.md`,
   `Plan/AI-OS-v13.0-Unified-Encyclopedia.md`,
   `Plan/Project-Athena-Cognitive-Orchestrator-Specification-v1.0.md`, and
   `Plan/Odysseus-Nexus-Ontology-Extraction-and-Unification-Specification.md`.

For script execution:

- Inspect a tool before running it.
- Prefer `-NoWrite` if the script supports it and you are only scanning.
- Tools now default to the standalone Project Athena root.
- Pass explicit roots when operating outside this checkout.

For code/hardware work:

- Treat `Nexus V/rtl` and `Nexus V/toolchain` as current source.
- Treat `Nexus V/obj_dir` and root-level `.o/.d/.cpp` simulation artifacts as
  generated outputs unless intentionally preserved.
- Do not claim SV simulation is verified unless a simulator was installed and
  run successfully.

For documentation work:

- Root docs are current operational docs.
- `Nexus V/docs/ai-system` and `Nexus V/docs/Plan` are mirrors/archives.
- Avoid editing both root and mirrored docs unless intentionally updating an
  archival package.

## Suggested Next Maintenance Tasks

1. Decide whether GitHub remote use is allowed; update governance or remote
   config to match.
2. Add `.gitignore` for future generated artifacts.
3. Decide whether tracked `.pyc`, `.o`, `.d`, `.exe`, and Verilator `obj_dir`
   files should remain in history.
4. Run one full task through intake, decision, implementation, verification,
   and memory writeback.
5. Expand `Plan/IMPLEMENTATION_MATRIX.md` from the highest-priority Plan specs.
6. Add expected traces for Nexus-V regression.
7. Install or document Verilator/Icarus/other SV tooling and run a real lint or
   simulation pass.
8. Refresh generated reports after tool and manifest updates.

## One-Sentence Project Definition

Project Athena is a local, file-native institutional AI control plane combined
with a Nexus-V semantic execution hardware research stack, intended to preserve
context, govern AI work, coordinate agents, audit evidence, and eventually map
AI-OS cognition into a versioned, secure, branchable execution substrate.
