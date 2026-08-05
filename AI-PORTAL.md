# AI Portal

This is the universal entry point for any AI model, team member, program, script or software agent that needs to understand or operate Project Athena.

## Identity

Project name: Project Athena

Primary goal: create a local-first institutional-intelligence and prosthetic external-brain system that preserves context, organizes knowledge, routes instructions, processes goals, coordinates AI and human work, audits evidence and safely expands capability over time.

Project Athena is part of a wider system-of-systems. Do not collapse the independent entities into one brain.

```text
ATHENA = independent institutional intelligence
JARVIS = independent personal/executive intelligence
JANUS  = independent operative metacognitive intelligence
OASIS  = persistent digital reality, simulation and creation substrate; not an AI
```

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
4. `Plan/CHAT_DERIVED_CONCEPT_REGISTER.md`
5. `Plan/ATHENA_DISTRIBUTED_COGNITIVE_FABRIC.md`
6. `Plan/CHAT_REPOSITORY_CONTINUITY_PIPELINE.md`
7. `context-file-index.md`
8. `manifests/system-manifest.json`
9. `manifests/ingestion-order.yml`
10. `memory/athena-memory-map.md`
11. `work/ATHENA-FIRST-STEPS.md`
12. `identity/README.md`
13. `identity/constitution.md`
14. `projects/project-registry.yml`
15. `organization/hierarchy.yml`
16. `agents/agent-registry.yml`
17. `orchestration/model-router.yml`
18. `START-HERE.md`
19. `governance/absolutes.md`
20. `registries/layers.yml`
21. `registries/modules.yml`
22. `navigation/project-map.md`
23. `sensory/health-model.md`
24. `work/TODO.md`
25. `engine/README.md`
26. `engine/order-of-operations.md`
27. `cognition/README.md`
28. `cognition/anti-hallucination/anti-hallucination-protocol.md`
29. `cognition/cognition-workflow.md`
30. `council/roles.yml`
31. `schemas/athena-task-intake.schema.json`
32. `templates/athena-task-intake.md`
33. `forensics/evidence-register.csv`
34. `forensics/claim-catalog.csv`
35. `forensics/evidence-claim-map.csv`

## First run

```powershell
powershell -NoProfile -ExecutionPolicy Bypass -File .\tools\Invoke-AIProjectScan.ps1
powershell -NoProfile -ExecutionPolicy Bypass -File .\tools\Export-AISystemManifest.ps1
powershell -NoProfile -ExecutionPolicy Bypass -File .\tools\Invoke-AIOperationCycle.ps1 -SkipLiveProbe
```

For a structured ATHENA task cycle:

```powershell
powershell -NoProfile -ExecutionPolicy Bypass -File .\tools\Invoke-AthenaCycle.ps1 -Goal "Describe the task here"
```

## How to think about this system

### ATHENA and this repository

- The repository is ATHENA's durable project/institutional substrate and the source of truth for this project.
- ATHENA handles institutional memory, evidence, governance, project brains, ontology, cognitive routing and long-horizon coordination.
- The repository also contains file-native precursors for distributed docking, the Athena Highway, project capsules, chat/repository continuity, the OASIS Reality Compiler and Lightcore research.
- `Plan/` is the design authority.
- `Nexus V/` is the semantic execution/toolchain implementation branch.
- Identity, constitution, governance, memory and evidence are durable; models and tool surfaces are replaceable.
- GPT, Codex, local models and other workers may use ATHENA adapters. An adapter does not make every independent intelligence an ATHENA subsystem.

Current Athena foundations include task intake, memory map, cycle report templates, operation-cycle tooling, Plan roadmaps, context indexes, an audited five-chat source archive, and bounded specifications for distributed docking, JANUS/Operative Duplex, Lightcore, and the OASIS Reality Compiler.

### JANUS

- JANUS is the independent operative metacognitive AI.
- Its Interior Face monitors reasoning, confidence, permissions and predicted state transitions.
- Its Exterior Face perceives and operates programs/OASIS, maps unfamiliar applications and validates actual state changes.
- It can use native UI semantics, application adapters, visual-semantic understanding and virtual input without depending primarily on a shell.
- It compiles validated workflows into Skill Capsules.

### JARVIS

- JARVIS is the independent personal/executive AI.
- It handles immediate dialogue, personal context, preferences, scheduling, devices and executive orchestration.
- It can collaborate with ATHENA, JANUS and OASIS through explicit contracts.

### OASIS

- OASIS is not an AI.
- It is a persistent programmable digital reality for engineering, science, simulation, games, virtual living/workspaces, R&D think tanks, digital twins, production and schematic workshops.
- Humans and independent AIs can inhabit or operate through it.

### Execution and physical layers

- Nexus-V provides branchable/reversible state semantics.
- Aegis provides trust, attestation and commit gates.
- Lightcore is a future physical execution profile and remains staged R&D.
- L.O.D.E TV is a display/telemetry/sensing endpoint.
- RoomSense and BodyRig provide local-first room and embodied tracking.
- Reality-to-Simulation and Known Behavioral Map work provide evidence-linked geometry, material, condition and behavior models.

## Capability posture

Some capabilities are implemented, some are scaffolded, some are specified, and some are speculative. Never treat a specification, rendered blueprint, simulation result or inferred application skill as a proven implementation without evidence.

Required labels:

- implemented;
- scaffolded;
- specified;
- conceptual;
- speculative;
- blocked;
- validated for a named use.

## Cross-system request rule

Every request between ATHENA, JARVIS, JANUS, OASIS runtime services or external tools should carry:

- requester identity;
- objective;
- context/evidence references;
- authority requested;
- privacy class;
- expected state diff;
- validation criteria;
- rollback or escalation requirements.

## Non-negotiable

The human is the ultimate authority.

Cloud/GitHub publication requires explicit human authorization and sanitization. The bounded 2026-08-01 GitHub planning exception covers workflow files and planning metadata after preview; it does not authorize raw account exports, unrelated private chats, credentials, unreviewed personal data or blanket future pushes. The 2026-08-05 local reconciliation request treats `origin/main` as the source for local repair; it does not publish local additions by itself.
