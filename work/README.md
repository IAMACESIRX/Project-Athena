# Work System

This folder is Project Athena's local planning layer. GitHub planning is a
bounded external projection of this state, not a replacement for repository
memory.

## Files

- `TODO.md`: current short execution list.
- `backlog.yml`: structured current and legacy backlog.
- `bugs.yml`: observed defects and environment blockers.
- `features.yml`: capability tracker.
- `milestones.md`: nine-milestone outcome roadmap.
- `github-plan.json`: desired labels, milestones, issues, Project fields, and
  views.
- `decisions-needed.md`: questions requiring human or engineering authority.
- `intake/`: structured task-intake records.
- `work-items/`: individual item records.

## Work Item Types

- `todo`
- `bug`
- `feature`
- `research`
- `decision`
- `risk`

## Creation

```powershell
powershell -NoProfile -ExecutionPolicy Bypass -File .\tools\New-WorkItem.ps1 -Type feature -Title "Example" -Layer athena
```

## GitHub Reconciliation

Preview only:

```powershell
powershell -NoProfile -ExecutionPolicy Bypass -File .\tools\Sync-AthenaGitHub.ps1
```

Remote mutation requires a token, explicit authority, and `-Apply`. The normal
path remains preview-first.
