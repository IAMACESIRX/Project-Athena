# AI Portal

This is the universal entry point for any AI model, team member, program, script, or software agent that needs to understand or operate this project.

## Identity

Project name: Project Athena

Primary goal: create a local-first AI prosthetic external brain that preserves
context, organizes knowledge, routes instructions, processes goals, coordinates
AI and human work, audits evidence, and safely expands capability over time.

Current primary managed project: Project Athena.

Legacy retained project: WoW Backup Stack.

## First Read

1. `context.md`
2. `Plan/context.md`
3. `Plan/OASIS_ATHENA_AGENT_MODEL.md`
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

## First Run

```powershell
powershell -NoProfile -ExecutionPolicy Bypass -File .\tools\Invoke-AIProjectScan.ps1
powershell -NoProfile -ExecutionPolicy Bypass -File .\tools\Export-AISystemManifest.ps1
powershell -NoProfile -ExecutionPolicy Bypass -File .\tools\Invoke-AIOperationCycle.ps1 -SkipLiveProbe
```

For a structured Athena task cycle:

```powershell
powershell -NoProfile -ExecutionPolicy Bypass -File .\tools\Invoke-AthenaCycle.ps1 -Goal "Describe the task here"
```

## How To Think About This System

- The repository is the external-brain substrate.
- OASIS is the larger operating environment around Athena.
- Central Athena is the canonical memory, database, processor, router, and
  evidence trail.
- Codex, Jarvis, GPT, and future AI surfaces each operate through a local Athena
  adapter rather than becoming separate project brains.
- `Plan/` is the design authority.
- `Nexus V/` is the semantic execution implementation branch.
- Identity and constitution are the durable AI-OS core.
- Project brains are managed organs; WoW is retained as legacy project history,
  not the current root identity.
- Organization, agents, and orchestration are the executive nervous system.
- Child repos are major organs.
- Registries are the skeleton.
- Playbooks are muscle memory.
- Sensory scans are nerves.
- Handoff and memory are continuity.
- Governance is the immune system.
- Work trackers are project metabolism.
- The physics model defines how state moves and how failures propagate.
- Continuity is long-term nervous system memory across agents.
- Audit and causality are the black box flight recorder.
- Restore points are the recovery spine.
- Cognition systems are the advanced reasoning laboratory.
- Anti-hallucination is the evidence brake.
- Liquid-state dynamics are the transient signal reservoir.
- Fuzzy/superposition systems prevent premature binary conclusions.
- Contextual anchors keep long sessions and many agents from drifting.
- Hypergraph processing maps many-way project dependencies.
- The operation engine turns scans, maps, verification, logs, cognition, audit, and handoff into one ordered cycle.
- The forensics layer keeps evidence IDs, claims, timelines, and known unknowns separate so reasoning does not smear facts into guesses.
- Model operations and training define how Codex-like, GPT-like, local, and future AI workers can be evaluated and routed.
- Model archaeology studies open-weight/open-source model families and self-hosted AI workspaces, then converts legal public lessons into our own target AI architecture.
- Contextual Work IQ decides which memory, files, tools, models, risks, and verification paths are relevant for the current work.

## Capability Posture

Some capabilities are implemented now. Some are specified as contracts for future build-out. A future AI or engineer should treat unimplemented capability specs as build targets, not as current promises.

Current Athena foundations include task intake, memory map, cycle report
templates, operation-cycle tooling, Plan roadmaps, and context indexes.

## Non-Negotiable

No GitHub server push. This stack is local-only unless the human explicitly changes that rule.

