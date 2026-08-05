# AI Portal

This is the universal entry point for any AI model, team member, program, script or software agent that needs to understand or operate Project Athena.

## Identity

Project name: Project Athena

Primary goal: create a local-first institutional-intelligence and prosthetic external-brain system that preserves context, organizes knowledge, routes instructions, processes goals, coordinates AI and human work, audits evidence and safely expands capability over time.

GitHub Wiki companion index: `https://github.com/IAMACESIRX/Project-Athena/wiki`

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
4. `context-file-index.md`
5. `manifests/system-manifest.json`
6. `manifests/ingestion-order.yml`
7. `memory/athena-memory-map.md`
8. `work/ATHENA-FIRST-STEPS.md`
9. `identity/README.md`
10. `identity/constitution.md`
11. `projects/project-registry.yml`
12. `organization/hierarchy.yml`
13. `agents/agent-registry.yml`
14. `orchestration/model-router.yml`
15. `START-HERE.md`
16. `governance/absolutes.md`
17. `registries/layers.yml`
18. `registries/modules.yml`
19. `navigation/project-map.md`
20. `sensory/health-model.md`
21. `work/TODO.md`
22. `engine/README.md`
23. `engine/order-of-operations.md`
24. `cognition/README.md`
25. `cognition/anti-hallucination/anti-hallucination-protocol.md`
26. `cognition/cognition-workflow.md`
27. `council/roles.yml`
28. `schemas/athena-task-intake.schema.json`
29. `templates/athena-task-intake.md`
30. `forensics/evidence-register.csv`
31. `forensics/claim-catalog.csv`
32. `forensics/evidence-claim-map.csv`

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
- `Plan/` is the design authority.
- `Nexus V/` is the semantic execution/toolchain implementation branch.
- Identity, constitution, governance, memory and evidence are durable; models and tool surfaces are replaceable.
- GPT, Codex, local models and other workers may use ATHENA adapters. An adapter does not make every independent intelligence an ATHENA subsystem.

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

Cloud/GitHub publication requires explicit human authorization and sanitization. This consolidation pass is authorized by the user's direct instruction to update and push the Project Athena repository and plugin mirrors. That authorization does not create a permanent unrestricted push rule.
