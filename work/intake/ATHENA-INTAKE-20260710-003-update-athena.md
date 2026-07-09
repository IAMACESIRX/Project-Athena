# Athena Task Intake: Update Athena Foundations

## Metadata

- schema: `ai-system.athena_task_intake.v1`
- intake_id: `ATHENA-INTAKE-20260710-003`
- created_at: `2026-07-10`
- status: `executing`
- active_layer: `root`
- priority_source: `human instruction plus Plan authority`

## Human Goal

Update all current Athena context and planning files, fill blank Plan template
files, and implement the recommended Athena improvements through Athena's own
decision-making process.

## Required Output

Current root-level Athena docs and tools should describe this checkout as
Project Athena, not the old nested `ai-system/` WoW layout. Blank Plan planning
files should become useful roadmaps. The recommended task-intake, memory-map,
and cycle-runner assets should exist.

## Files To Read

- `AI-PORTAL.md`
- `context.md`
- `Plan/context.md`
- `work/ATHENA-FIRST-STEPS.md`
- `council/reasoning-rounds/council-20260710-athena-improvement-brainstorm.md`
- `engine/order-of-operations.md`
- `tools/`
- `manifests/`
- `Plan/`

## Files Read

- `AI-PORTAL.md`
- `START-HERE.md`
- `context.md`
- `Plan/context.md`
- `work/ATHENA-FIRST-STEPS.md`
- `council/reasoning-rounds/council-20260710-athena-improvement-brainstorm.md`
- `engine/order-of-operations.md`
- `schemas/task.schema.json`
- `schemas/cycle-report.schema.json`
- `tools/*.ps1`
- `manifests/*.yml`
- `manifests/system-manifest.json`

## Known Facts

| Statement | Truth Value | Confidence | Evidence |
|---|---|---:|---|
| Current checkout is rooted at `D:\Projects\Project Athena`. | observed | 1.0 | environment and prior context scan |
| `Plan/` is the highest-priority architecture-intent vault. | observed | 1.0 | `Plan/context.md` |
| Previous docs and tools contained stale `ai-system/` path assumptions. | observed | 1.0 | `rg` results and tool reads |
| Plan placeholder files were headings only before this pass. | observed | 1.0 | `Get-ChildItem` and file reads |

## Assumptions

| Statement | Truth Value | Confidence | Evidence |
|---|---|---:|---|
| "All files to current" means canonical docs, tools, manifests, context, and Plan placeholders, not `.gitkeep`, empty logs, or generated build artifacts. | inferred | 0.8 | User asked to flesh out blanks and add recommended changes |

## Unknowns

| Statement | Truth Value | Confidence | Evidence |
|---|---|---:|---|
| Whether the GitHub remote should remain configured despite local-only governance. | unknown | 0.0 | Governance conflict remains a human decision |

## Risks

| Risk | Truth Value | Confidence | Mitigation |
|---|---|---:|---|
| Updating too many generated/mirrored files can add noise. | inferred | 0.7 | Limit changes to source-of-truth docs, tools, Plan mirror placeholders, and indexes |
| Running old write-mode scripts before path normalization could create wrong folders. | observed | 0.9 | Normalize paths before running checks |

## Athena Decision Pass

Problem frame:
: Athena needs its root identity, tools, and Plan planning files updated to
  match the current standalone Project Athena checkout.

Relevant cognition methods:
: Socratic deconstruction, algorithmic inversion, council review,
  anti-hallucination, and hypergraph dependency mapping.

Decision:
: Implement intake, memory map, cycle template/runner, path normalization, Plan
  planning files, and current context/index updates in one auditable pass.

Why this action:
: The previous brainstorm identified intake and memory contracts as the safest
  foundation before heavier automation.

Rollback or recovery:
: All edits are file-local. Git working tree can show the exact patch before
  commit.

## Verification Method

- Search for remaining stale root-level `ai-system/` path references.
- Parse JSON files touched or created.
- Run PowerShell syntax parsing for touched scripts.
- Run `tools/Invoke-AIIntegrityCheck.ps1 -NoWrite` after path normalization.
- Check ASCII on new/changed markdown/json/schema/tool files.
- Check `git status --short --branch`.

## Memory Writeback Targets

- `context.md`
- `Plan/context.md`
- `work/ATHENA-FIRST-STEPS.md`
- `engine/cycle-reports/`
- `context-file-index.md`

## End State

Completed.

- Athena task-intake schema, template, sample intake, memory map, cycle report
  template, and lightweight cycle runner were created.
- Plan blank planning files were filled and mirrored where appropriate.
- Root identity, manifests, registries, project map, and memory files were
  updated to current Project Athena framing.
- PowerShell tools were normalized to the standalone root and verified by the
  operation cycle.
- Latest operation-cycle result is recorded in `engine/cycle-reports/latest-cycle-report.md`; the live probe is skipped when no live target is part of the task.
