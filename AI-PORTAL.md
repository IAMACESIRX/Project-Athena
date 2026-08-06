# AI Portal

This is the universal entry point for any AI model, team member, program, script, software agent or future hardware reader that needs to understand or operate Project Athena.

## Identity

Project name: Project Athena

Primary goal: create a local-first institutional-intelligence and prosthetic external-brain system that preserves context, organizes knowledge, routes instructions, processes goals, coordinates AI and human work, audits evidence and safely expands capability over time.

GitHub Wiki companion index: `https://github.com/IAMACESIRX/Project-Athena/wiki`

Project Athena is part of a wider system-of-systems. Do not collapse the independent entities into one brain.

```text
ATHENA = independent institutional intelligence
JARVIS = independent personal/executive intelligence
JANUS  = independent operative metacognitive intelligence
F.O.R.G.E. = independent cognitive-synthesis and native-reconstruction system
A.E.S.I.R. = Adaptive Evolutionary System for Intelligent Research
OASIS  = persistent digital reality, simulation and creation substrate; not an AI
AIO    = All-In-One Interoperability and Orchestration master contract shared by every participant
```

A.E.S.I.R. expands evidence and candidate space; F.O.R.G.E. challenges, mines mechanisms and reverse-reconstructs; ATHENA governs and preserves lineage; Aegis attests consequential commits; Nexus‑V materialises versioned state. They do not exchange separate circular contracts. Every participant reads and writes one shared logical contract defined by `contracts/AIO-MASTER-CONTRACT.yml`.

The AIO contract is manually operable and machine readable. AI is favoured for throughput but is never mandatory. Manual, AI-assisted, automated and hybrid operation all update the same versioned state with interventions and history preserved.

## Mandatory identity correction

Read before using the older OASIS/agent material:

1. `docs/athena-master-expansion/SYSTEM_IDENTITY_AND_AUTHORITY_CORRECTION_2026-08-05.md`
2. `docs/athena-master-expansion/ATHENA_FULL_SYSTEM_MAP.md`
3. `docs/athena-master-expansion/JANUS_OPERATIVE_METACOGNITIVE_AI_MASTER_SPEC.md`
4. `docs/athena-master-expansion/OASIS_ARCHITECTURE_SPEC.md`
5. `Plan/OASIS_ATHENA_AGENT_MODEL.md`

Any statement that JANUS/Operative Duplex AI is an ATHENA subsystem, that JARVIS is only an ATHENA adapter, or that OASIS contains/owns ATHENA is superseded.

## First read

1. `context.md`
2. `Plan/context.md`
3. the mandatory identity-correction files above
4. `context-file-index.md`
5. `manifests/system-manifest.json`
6. `manifests/ingestion-order.yml`
7. `identity/README.md`
8. `identity/constitution.md`
9. `projects/project-registry.yml`
10. `contracts/AIO-MASTER-CONTRACT.yml`
11. `contracts/README.md`
12. `standards/human-ai-pipeline/AIO-UNIFIED-PIPELINE.md`
13. `standards/human-ai-pipeline/STANDARD-v0.1.md`
14. `standards/human-ai-pipeline/ONBOARDING.md`
15. `aesir/AESIR-PORTAL.md`
16. `aesir/manifest.yml`
17. `forge/FORGE-PORTAL.md`
18. `forge/manifest.yml`
19. `memory/athena-memory-map.md`
20. `work/ATHENA-FIRST-STEPS.md`
21. `organization/hierarchy.yml`
22. `agents/agent-registry.yml`
23. `orchestration/model-router.yml`
24. `START-HERE.md`
25. `governance/absolutes.md`
26. `registries/layers.yml`
27. `registries/modules.yml`
28. `navigation/project-map.md`
29. `sensory/health-model.md`
30. `work/TODO.md`
31. `engine/README.md`
32. `engine/order-of-operations.md`
33. `engine/HAIPS-ATHENA-ADAPTER.md`
34. `cognition/README.md`
35. `cognition/anti-hallucination/anti-hallucination-protocol.md`
36. `cognition/cognition-workflow.md`
37. `council/roles.yml`
38. `schemas/athena-task-intake.schema.json`
39. `templates/athena-task-intake.md`
40. `forensics/evidence-register.csv`
41. `forensics/claim-catalog.csv`
42. `forensics/evidence-claim-map.csv`

## First run

```powershell
powershell -NoProfile -ExecutionPolicy Bypass -File .\tools\Invoke-AIProjectScan.ps1
powershell -NoProfile -ExecutionPolicy Bypass -File .\tools\Export-AISystemManifest.ps1
powershell -NoProfile -ExecutionPolicy Bypass -File .\tools\Invoke-AIOperationCycle.ps1 -SkipLiveProbe
```

Create one input and compile the shared AIO instance:

```powershell
python .\tools\aio_contract.py validate-master .\contracts\AIO-MASTER-CONTRACT.yml
python .\tools\aio_contract.py instantiate --master .\contracts\AIO-MASTER-CONTRACT.yml --input .\standards\human-ai-pipeline\examples\aio-input.example.json --out .\work\aio-run.json
python .\tools\aio_contract.py validate-instance .\work\aio-run.json --master .\contracts\AIO-MASTER-CONTRACT.yml
python .\tools\aio_contract.py render .\work\aio-run.json --out .\work\aio-run.md
```

For a structured ATHENA intake cycle:

```powershell
powershell -NoProfile -ExecutionPolicy Bypass -File .\tools\Invoke-AthenaCycle.ps1 -Goal "Describe the task here"
```

The previous Human–AI Pipeline profiles and F.O.R.G.E. compiler remain specialised tools, but their outputs must be written into the same AIO contract lineage rather than becoming separate cross-system authorities.

## How to think about this system

### ATHENA and this repository

- The repository is ATHENA's durable project/institutional substrate and the source of truth for this project.
- ATHENA handles institutional memory, evidence, governance, project brains, ontology, cognitive routing and long-horizon coordination.
- `Plan/` is the design authority.
- `contracts/AIO-MASTER-CONTRACT.yml` is the cross-system contract authority.
- `Nexus V/` is the semantic execution/toolchain implementation branch.
- `aesir/` is the independent polymath research and discovery subsystem.
- `forge/` is the independent cognitive-synthesis and reconstruction subsystem.
- `standards/human-ai-pipeline/` supplies shared manual/AI/automation/hybrid interfaces.
- Identity, constitution, governance, memory and evidence are durable; models and tool surfaces are replaceable.

### AIO unified contract and pipeline

- One idea or task creates one shared contract instance.
- ATHENA, A.E.S.I.R., F.O.R.G.E., Aegis, Nexus‑V, humans, AI workers and tools append events and update only fields within their authority.
- Pairwise or subsystem-specific contracts are generated views and never independent sources of truth.
- Every input traverses all 21 required phases: authority, context, epistemics, full scientific method, intrascientific integration, multiscale analysis, polymath expansion, hypergraph mapping, candidate synthesis, engineering, simulation, mitigation, governance, attestation, execution and method repass.
- Weights adjust depth, priority, review intensity and resources. They cannot remove a required phase or defeat a hard gate.
- Human-readable Markdown and machine-readable JSON/YAML are generated from the same state.
- Atomic writes use the expected parent hash; competing writes branch or become explicit conflict events.
- Weakness controls must preserve named benefits, declare trade-offs and new risks, and remain reviewable and removable.

### F.O.R.G.E. and A.E.S.I.R.

- A.E.S.I.R. performs adaptive polymath research, source discovery, cross-domain exploration, the full scientific method, intra- and cross-scientific integration, hypothesis generation and evidence gathering.
- F.O.R.G.E. operationalises the owner's method: intent anchoring, epistemic partition, analogy, first-principles reduction, symmetric challenge, candidate tournaments, mechanism mining, reverse reconstruction, simplification and functional-snapshot compilation.
- F.O.R.G.E. preserves failed and superseded paths rather than flattening history into only the active result.
- Results remain provisional until evidence, simulation/prototypes, ATHENA governance, Aegis attestation and human approval support promotion.

### JANUS

- JANUS is the independent operative metacognitive AI.
- Its Interior Face monitors reasoning, confidence, permissions and predicted state transitions.
- Its Exterior Face perceives and operates programs/OASIS, maps unfamiliar applications and validates actual state changes.
- It can use native UI semantics, application adapters, visual-semantic understanding and virtual input without depending primarily on a shell.
- It compiles validated workflows into Skill Capsules and records actual state differences into the AIO instance.

### JARVIS

- JARVIS is the independent personal/executive AI.
- It handles immediate dialogue, personal context, preferences, scheduling, devices and executive orchestration.
- It participates through the AIO authority and privacy rules rather than maintaining separate bilateral contracts.

### OASIS

- OASIS is not an AI.
- It is a persistent programmable digital reality for engineering, science, simulation, games, virtual living/workspaces, R&D think tanks, digital twins, production and schematic workshops.
- Humans and independent AIs can inhabit or operate through it.
- Simulation and measurement outputs re-enter the same AIO contract as evidence-linked events.

### Execution and physical layers

- Nexus-V provides branchable/reversible state semantics and future AIO/NVIR object mapping.
- Aegis provides trust, attestation and commit gates using the same contract state.
- Lightcore is a future physical execution profile and remains staged R&D.
- L.O.D.E TV is a display/telemetry/sensing endpoint.
- RoomSense and BodyRig provide local-first room and embodied tracking.
- Reality-to-Simulation and Known Behavioral Map work provide evidence-linked geometry, material, condition and behavior models.

## Capability posture

Some capabilities are implemented, some are scaffolded, some are specified, and some are speculative. Never treat a specification, rendered blueprint, compiler scaffold, simulation result or inferred application skill as a proven implementation without evidence.

Required labels:

- implemented;
- scaffolded;
- specified;
- conceptual;
- speculative;
- blocked;
- validated for a named use.

## Cross-system request rule

Do not create another authoritative pairwise contract unless a future hard technical constraint proves it necessary. Create or update one AIO contract instance carrying:

- participant identity and authority scope;
- objective and semantic invariants;
- context and evidence references;
- claims, unknowns and falsifiers;
- privacy and publication class;
- expected state difference and rollback;
- execution mode and weights;
- benefits to preserve, active mitigations and intervention checkpoints;
- Aegis attestation and commit status where required;
- current parent hash and lineage.

## Non-negotiable

The human is the ultimate authority.

Cloud/GitHub publication requires explicit human authorization and sanitization. This consolidation pass is authorized by the user's direct instruction to update the Project Athena repository. That authorization does not create a permanent unrestricted push rule.
