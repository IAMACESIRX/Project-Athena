# AI Portal

This is the universal entry point for any AI model, team member, program, script, or software agent that needs to understand or operate this project.

## Identity

Project name: Local AI-OS Control Plane

Primary goal: create a local-first, multi-purpose AI operating system that can preserve context, coordinate Codex-like and GPT-like agents, manage multiple project brains, diagnose issues, track work, reverse engineer behavior, and safely expand capabilities over time.

Current primary managed project: WoW Backup Stack.

## First Read

1. `manifests/system-manifest.json`
2. `manifests/ingestion-order.yml`
3. `identity/README.md`
4. `identity/constitution.md`
5. `projects/project-registry.yml`
6. `organization/hierarchy.yml`
7. `agents/agent-registry.yml`
8. `orchestration/model-router.yml`
9. `research/model-archaeology/source-ledger.yml`
10. `research/model-archaeology/deconstruction-protocol.md`
11. `model-ops/target-ai/target-ai-architecture.md`
12. `model-ops/target-ai/capability-roadmap.yml`
13. `memory/context-iq/contextual-work-iq.md`
14. `START-HERE.md`
15. `governance/absolutes.md`
16. `registries/layers.yml`
17. `registries/modules.yml`
18. `navigation/project-map.md`
19. `sensory/health-model.md`
20. `work/TODO.md`
21. `engine/README.md`
22. `engine/order-of-operations.md`
23. `forensics/evidence-register.csv`
24. `forensics/claim-catalog.csv`
25. `forensics/evidence-claim-map.csv`
26. `continuity/continuity-protocol.md`
27. `audit/decision-framework.md`
28. `truth/cross-check-pipeline.md`
29. `cognition/README.md`
30. `cognition/anti-hallucination/anti-hallucination-protocol.md`
31. `cognition/cognition-workflow.md`

## First Run

```powershell
powershell -NoProfile -ExecutionPolicy Bypass -File .\ai-system\tools\Invoke-AIProjectScan.ps1
powershell -NoProfile -ExecutionPolicy Bypass -File .\ai-system\tools\Export-AISystemManifest.ps1
powershell -NoProfile -ExecutionPolicy Bypass -File .\ai-system\tools\Invoke-AIOperationCycle.ps1 -SkipLiveProbe
```

## How To Think About This System

- The mega repo is the command deck.
- Identity and constitution are the durable AI-OS core.
- Project brains are managed organs; WoW is the first active organ, not the whole body.
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

## Non-Negotiable

No GitHub server push. This stack is local-only unless the human explicitly changes that rule.
