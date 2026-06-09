# Project Brain: WoW Backup Stack

## Identity

Project ID: `wow-backup-stack`

Role: first managed project under the generalized AI-OS control plane.

Local-only: yes.

Evidence namespace: `EVD-WOW`.

## Mission

Preserve, understand, diagnose, and safely evolve the local WoW server/client/live-state stack.

## Managed Layers

- Mega repo.
- Game client repo.
- Server live-state repo.
- WoW server project repo.
- Nested AzerothCore and playerbots source repos.

## First Run

```powershell
powershell -NoProfile -ExecutionPolicy Bypass -File .\ai-system\tools\Invoke-AIOperationCycle.ps1 -SkipLiveProbe
```

