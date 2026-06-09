# Project Map

## Topology

```text
2026-05-30_2035/
  ai-system/                         project brain and operations layer
  GameClient-ChromieCraft-3.3.5a/    child repo: game client
  Server-Live-State/                 child repo: SQL/live-state backup
  WoW-Server-Project/                child repo: docs/scripts/backend/server source
    backend/                         FastAPI command hub
    scripts/wow/                     server/client helper scripts
    servers/wow/
      azerothcore-wotlk/             nested repo: clean baseline
      azerothcore-wotlk-playerbots/  nested repo: bot-enabled fork
        modules/mod-playerbots/      nested repo: playerbot module
```

## Navigation Rules

- Use `ai-system/AI-PORTAL.md` for universal entry.
- Use `registries/layers.yml` to know which repo owns a path.
- Use `registries/modules.yml` to know functional boundaries.
- Use `work/TODO.md` and `work/backlog.yml` for active work.
- Use `observability/` for live reading and diagnostics.
- Use `reverse-engineering/` when learning unknown internals.

## Source Of Truth By Question

- "Where is this file owned?" -> `registries/file-ownership.yml`
- "What modules exist?" -> `registries/modules.yml`
- "What can be automated?" -> `manifests/capability-matrix.yml`
- "What is safe?" -> `governance/policy-matrix.yml`
- "What is broken?" -> `work/bugs.yml` and `diagnostics/issue-ledger.md`
- "What did we learn?" -> `memory/` and `handoff/`
