# Project Brain: WoW Backup Stack

## Identity

Project ID: `wow-backup-stack`

Role: retained legacy managed project under Project Athena.

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
powershell -NoProfile -ExecutionPolicy Bypass -File .\tools\Invoke-AIOperationCycle.ps1 -SkipLiveProbe
```

Note: this project brain is retained history; Project Athena is now the active
root identity.
