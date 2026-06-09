# AI Ingestion Guide

Use this guide when connecting a new AI model or agent.

## Required Context Packet

Give the AI these files first:

- `ai-system/AI-PORTAL.md`
- `ai-system/manifests/system-manifest.json`
- `ai-system/manifests/generated-ai-index.json`
- `ai-system/identity/constitution.md`
- `ai-system/projects/project-registry.yml`
- `ai-system/organization/hierarchy.yml`
- `ai-system/agents/agent-registry.yml`
- `ai-system/orchestration/model-router.yml`
- `ai-system/research/model-archaeology/source-ledger.yml`
- `ai-system/research/model-archaeology/deconstruction-protocol.md`
- `ai-system/model-ops/target-ai/target-ai-architecture.md`
- `ai-system/model-ops/target-ai/capability-roadmap.yml`
- `ai-system/memory/context-iq/contextual-work-iq.md`
- `ai-system/governance/absolutes.md`
- `ai-system/handoff/CURRENT_STATE.md`
- `ai-system/work/TODO.md`
- `ai-system/sensory/scans/latest-scan.json`
- `ai-system/engine/order-of-operations.md`
- `ai-system/engine/routine-catalog.yml`
- `ai-system/forensics/evidence-register.csv`
- `ai-system/forensics/claim-catalog.csv`
- `ai-system/forensics/evidence-claim-map.csv`

## Required First Response From Agent

The agent should state:

- active layer,
- understood restrictions,
- current known risks,
- intended next action,
- verification method.

## Agent Must Not Assume

- Docker is installed or running.
- The server is live.
- The venv works.
- The game client payload is committed.
- GitHub server push is allowed.
- Generated scans or reports are current if the operation cycle has not been run.

## Agent Output Contract

After meaningful work, the agent must leave:

- changed files,
- verification evidence,
- work/risk/handoff update if needed,
- local commit if appropriate.

## Preferred Full-Cycle Command

```powershell
powershell -NoProfile -ExecutionPolicy Bypass -File .\ai-system\tools\Invoke-AIOperationCycle.ps1 -SkipLiveProbe
```
