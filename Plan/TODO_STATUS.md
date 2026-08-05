# TODO_STATUS

## Status Legend

- done: implemented and verified enough for current use.
- active: currently being built.
- partial: structure exists but needs more work.
- planned: design intent exists.
- blocked: requires human decision or external setup.

## Athena Status

| Area | Status | Evidence | Next Step |
|---|---|---|---|
| Root context | active | `context.md` | Keep current after major changes. |
| Plan context | active | `Plan/context.md` | Update after Plan extraction. |
| File index | active | `context-file-index.md` | Refresh after new files. |
| Task intake | active | `schemas/athena-task-intake.schema.json`, `templates/athena-task-intake.md`, `work/intake/` | Run a full task through intake to closure. |
| Memory map | active | `memory/athena-memory-map.md` | Add examples after more cycles. |
| Cycle reports | active | `engine/cycle-reports/` | Standardize report template use. |
| Operation tools | partial | `tools/` | Verify all scripts from standalone root. |
| Plan extraction | planned | `Plan/IMPLEMENTATION_MATRIX.md` | Fill detailed rows from key specs. |
| Nexus-V matrix | planned | `Nexus V/docs/NEXUS-V-IMPLEMENTATION-MATRIX.md` | Map RTL/toolchain to Plan. |
| Operator console | planned | `runtime/`, `tools/` | Design after intake is stable. |
| Two-way chat continuity | active | `continuity/chat-repository-sync/`, `tools/Import-AthenaChatExport.ps1`, `tools/Export-AthenaChatContext.ps1` | Add fixtures and reconcile an official export. |
| Storyboard recovery | active | `athena_context/assets/generated-storyboards-2026-08-01/` | Complete all-image semantic review; hashes already pass. |
| GitHub planning | active | `work/github-plan.json`, `.github/` | Apply bounded labels, milestones, issues, and Project configuration after preview. |

## Human Decisions Needed

| Decision | Status | Notes |
|---|---|---|
| GitHub remote versus local-only rule | decided for current task | Local-only remains default; 2026-08-01 exception covers reviewed workflow files and planning metadata only. |
| How aggressively to update Nexus V generated files | planned | Source and reports should be separated from generated build artifacts. |
| Whether WoW legacy records stay first-class | planned | Current identity treats them as retained history, not root identity. |
