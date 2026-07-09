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
3. `context-file-index.md`
4. `manifests/system-manifest.json`
5. `manifests/ingestion-order.yml`
6. `memory/athena-memory-map.md`
7. `work/ATHENA-FIRST-STEPS.md`
8. `identity/README.md`
9. `identity/constitution.md`
10. `projects/project-registry.yml`
11. `organization/hierarchy.yml`
12. `agents/agent-registry.yml`
13. `orchestration/model-router.yml`
14. `START-HERE.md`
15. `governance/absolutes.md`
16. `registries/layers.yml`
17. `registries/modules.yml`
18. `navigation/project-map.md`
19. `sensory/health-model.md`
20. `work/TODO.md`
21. `engine/README.md`
22. `engine/order-of-operations.md`
23. `cognition/README.md`
24. `cognition/anti-hallucination/anti-hallucination-protocol.md`
25. `cognition/cognition-workflow.md`
26. `council/roles.yml`
27. `schemas/athena-task-intake.schema.json`
28. `templates/athena-task-intake.md`
29. `forensics/evidence-register.csv`
30. `forensics/claim-catalog.csv`
31. `forensics/evidence-claim-map.csv`

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

