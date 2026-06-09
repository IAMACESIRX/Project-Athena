# Project Memory

This file stores stable project facts that should survive across sessions.

## Core Goal

Maintain a private local WoW server/client backup stack with enough structure that humans and AI agents can restore, inspect, modify, and evolve it safely.

## Current Project Layers

- Game client: full ChromieCraft 3.3.5a client backup with account-local state and ReShade files.
- Live state: SQL dumps and restore helpers for the active AzerothCore Playerbots server.
- Server project: FastAPI assistant scaffold, WoW setup docs, helper scripts, and nested AzerothCore source checkouts.
- Mega layer: top-level orchestration and child repo pointer tracking.

## Durable Constraints

- Local-only hosting unless explicitly changed by the human.
- Preserve recoverability before experimenting.
- Treat live-state and client account files as sensitive.
- Do not assume the copied `.venv` is valid after moving machines.
- Avoid full binary Git snapshots when disk free space is tight.

## Useful Commands

```powershell
git status --ignore-submodules=untracked
powershell -NoProfile -ExecutionPolicy Bypass -File .\ai-system\tools\Invoke-AIProjectScan.ps1
powershell -NoProfile -ExecutionPolicy Bypass -File .\ai-system\tools\Update-LayerPointers.ps1
```
