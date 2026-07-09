# Start Here

This is the orientation page for any human, AI agent, model, tool, or program
entering Project Athena.

## Current Shape

Project Athena is a standalone local repository at:

`D:\Projects\Project Athena`

It is an AI prosthetic external brain built from:

- file-native memory,
- organized context and schemas,
- Athena cognition and council methods,
- governance and evidence rules,
- a repeatable operation cycle,
- Plan architecture authority,
- Nexus-V hardware/toolchain implementation research.

The older WoW Backup Stack remains represented in legacy docs and project-brain
records, but it is no longer the root identity of this checkout.

No GitHub server push is allowed unless the human explicitly reverses that rule.

## First Actions For An AI Session

1. Read `AI-PORTAL.md`.
2. Read `context.md`.
3. Read `Plan/context.md`.
4. Read `memory/athena-memory-map.md`.
5. Read `work/ATHENA-FIRST-STEPS.md`.
6. Read `manifests/system-manifest.json`.
7. Read `manifests/ingestion-order.yml`.
8. Read `governance/absolutes.md`.
9. Read `engine/order-of-operations.md`.
10. Read `cognition/cognition-workflow.md`.
11. If the task is non-trivial, create or update an intake packet in
    `work/intake/`.
12. Identify the active layer before editing.
13. Verify results and write back memory before ending the session.

## Windows Script Commands

Use the process-local execution-policy bypass form:

```powershell
powershell -NoProfile -ExecutionPolicy Bypass -File .\tools\Invoke-AIProjectScan.ps1
powershell -NoProfile -ExecutionPolicy Bypass -File .\tools\Export-AISystemManifest.ps1
powershell -NoProfile -ExecutionPolicy Bypass -File .\tools\Export-ProjectMap.ps1
powershell -NoProfile -ExecutionPolicy Bypass -File .\tools\Invoke-AIOperationCycle.ps1 -SkipLiveProbe
```

To bootstrap a structured Athena cycle:

```powershell
powershell -NoProfile -ExecutionPolicy Bypass -File .\tools\Invoke-AthenaCycle.ps1 -Goal "Describe the task here"
```

## Operating Bias

- Prefer local-only changes.
- Treat `Plan/` as design authority.
- Treat implementation state as observed only after reading files or reports.
- Label assumptions and unknowns.
- Use the smallest reversible action that moves the work forward.
- Do not mutate runtime state without explicit human intent.
- Keep generated outputs in report/generated locations.

## Definition Of Good Work

Good work leaves behind:

- a clear working-tree state,
- an updated context or work artifact when new facts were learned,
- a cycle report for meaningful reasoning or implementation,
- verification output or a clear statement of what was not verified,
- and no mystery about what changed.
