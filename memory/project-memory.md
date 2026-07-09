# Project Memory

This file stores stable project facts that should survive across sessions.

## Core Goal

Build Project Athena as a private, local-first AI prosthetic external brain that
preserves context, organizes knowledge, processes tasks, coordinates agents,
audits evidence, and converts Plan architecture intent into working systems.

## Current Project Layers

- Project Athena root: first-read docs, manifests, registries, context, tools,
  schemas, templates, memory, work, and operation engine.
- Plan: highest-priority architecture-intent vault for AI-OS, Athena, Nexus-V,
  NVISC, NVASM, NVIR, NVVM, Odysseus, and Lightcore direction.
- Nexus V: source-heavy hardware/toolchain implementation branch.
- Work and intake: task state, roadmaps, sample intake packets, and next actions.
- Engine and forensics: processor loop, cycle reports, evidence, claims, and
  audit records.
- Legacy WoW Backup Stack: retained project-brain history, not current root
  identity.

## Durable Constraints

- Local-only hosting unless explicitly changed by the human.
- Preserve recoverability before experimenting.
- Treat private paths, account data, SQL dumps, and local state as sensitive.
- Do not treat Plan intent as implemented until mapped to source and evidence.
- Do not treat generated artifacts as design authority.
- Label assumptions and unknowns before writing durable memory.

## Useful Commands

```powershell
git status --ignore-submodules=untracked
powershell -NoProfile -ExecutionPolicy Bypass -File .\tools\Invoke-AIProjectScan.ps1
powershell -NoProfile -ExecutionPolicy Bypass -File .\tools\Invoke-AIOperationCycle.ps1 -SkipLiveProbe
powershell -NoProfile -ExecutionPolicy Bypass -File .\tools\Invoke-AthenaCycle.ps1 -Goal "Describe the task here"
```
