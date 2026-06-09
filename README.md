# AI System Layer

This folder is the coordination layer for humans, AI agents, tools, and programs working through a local AI-OS control plane.

Its job is to preserve context, reduce repeated discovery, expose risks early, coordinate multiple AIs, and give every future session a clear operating model for every managed project.

## Read Order

1. `AI-PORTAL.md`
2. `manifests/system-manifest.json`
3. `identity/README.md`
4. `identity/constitution.md`
5. `projects/project-registry.yml`
6. `organization/hierarchy.yml`
7. `agents/agent-registry.yml`
8. `START-HERE.md`
9. `governance/absolutes.md`
10. `handoff/CURRENT_STATE.md`
11. `handoff/NEXT_ACTIONS.md`
12. `registries/layers.yml`
13. `registries/modules.yml`
14. `navigation/project-map.md`
15. `sensory/health-model.md`
16. `engine/order-of-operations.md`
17. `forensics/role-packets/ai-ingestion-brief.md`

## What This Layer Does

- Tracks the project across the mega repo, child repos, and nested server repos.
- Manages multiple project brains, with WoW as the first primary project.
- Defines identity, constitution, organization hierarchy, agents, model routing, runtime contracts, and training loops.
- Gives AI agents a shared memory and handoff protocol.
- Defines module boundaries, ownership, risks, and edit contracts.
- Provides local diagnostics scripts for git state, disk pressure, remotes, and restore readiness.
- Keeps research, experiments, issues, and decisions in stable places.
- Exposes machine-readable manifests and schemas for outside tools.
- Defines governance, drift handling, reverse-engineering protocols, observability contracts, and a system physics model.
- Adds cognition systems for advanced inference, creativity, collaboration, disruption, anti-hallucination, and liquid-state signal dynamics.
- Runs a Redwire-inspired native operation engine for repeatable scan, map, verify, diagnose, reason, audit, and handoff cycles.
- Runs a Xavier-inspired native forensics layer for evidence IDs, claim maps, timelines, known unknowns, and verification reports.

## Prime Directive

Preserve recoverability first. Improve automation second. Add features third.

Every action should answer:

- What layer am I touching?
- What state do I need to preserve before changing it?
- What will prove the change worked?
- What should the next human or AI know?
