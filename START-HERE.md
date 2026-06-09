# Start Here

This is the orientation page for any human, AI agent, model, tool, or program entering the local AI-OS workspace.

## Current Shape

The system is now a general local AI-OS control plane with project brains. The current primary managed project is a local-only layered WoW Git stack:

- Mega layer: `C:\Users\aesir\OneDrive\Desktop\WoW-Backups\2026-05-30_2035`
- Game client layer: `GameClient-ChromieCraft-3.3.5a`
- Server live-state layer: `Server-Live-State`
- Server project layer: `WoW-Server-Project`
- Local bare host: `C:\Users\aesir\OneDrive\Desktop\WoW-Backups\local-git-host\2026-05-30_2035`

No GitHub server push is allowed unless the human explicitly reverses that rule.

## First Actions For An AI Session

1. Read `AI-PORTAL.md`.
2. Read `manifests/system-manifest.json`.
3. Read `identity/constitution.md`.
4. Read `projects/project-registry.yml`.
5. Read `organization/hierarchy.yml`.
6. Read `agents/agent-registry.yml`.
7. Read `governance/absolutes.md`.
8. Read `research/model-archaeology/source-ledger.yml`.
9. Read `model-ops/target-ai/target-ai-architecture.md`.
10. Read `memory/context-iq/contextual-work-iq.md`.
11. Read `handoff/CURRENT_STATE.md`.
12. Read `handoff/NEXT_ACTIONS.md`.
13. Read `engine/order-of-operations.md`.
14. Read `forensics/role-packets/ai-ingestion-brief.md`.
15. Run `tools/Invoke-AIOperationCycle.ps1 -SkipLiveProbe` from the mega repo for a full local control-plane pass.
16. Check `work/TODO.md` and `diagnostics/risk-register.md`.
17. Identify the project and layer being changed before editing.
18. Update handoff notes before ending the session.

## Operating Bias

- Prefer local-only changes and local-only pushes.
- Commit inside child repos before committing child pointers in the mega repo.
- Treat SQL dumps, account names, IPs, client WTF files, and restore scripts as private.
- Do not duplicate the full game client payload in the mega repo.
- Avoid re-scanning huge binary payloads unless the task requires it.
- Treat open-model research as architecture extraction, not weight copying or license bypassing.

## Windows Script Command

If PowerShell blocks direct script execution, use the process-local bypass form:

```powershell
powershell -NoProfile -ExecutionPolicy Bypass -File .\ai-system\tools\Invoke-AIProjectScan.ps1
powershell -NoProfile -ExecutionPolicy Bypass -File .\ai-system\tools\Export-AISystemManifest.ps1
powershell -NoProfile -ExecutionPolicy Bypass -File .\ai-system\tools\Export-ProjectMap.ps1
powershell -NoProfile -ExecutionPolicy Bypass -File .\ai-system\tools\Invoke-AIOperationCycle.ps1 -SkipLiveProbe
```

## Definition Of Good Work

Good work leaves behind:

- a clear git state,
- an updated handoff,
- a record of decisions or risks discovered,
- a reproducible command or script when the action will recur,
- and no mystery about what changed.
