# Work System

This folder is the local project management layer.

## Files

- `TODO.md`: active short list.
- `backlog.yml`: structured backlog.
- `bugs.yml`: bug tracker.
- `features.yml`: feature tracker.
- `milestones.md`: milestone plan.
- `decisions-needed.md`: questions requiring human or engineering decision.
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
powershell -NoProfile -ExecutionPolicy Bypass -File .\ai-system\tools\New-WorkItem.ps1 -Type bug -Title "Example bug" -Layer server-project
```
