# Restore Point System

The restore system records reversible project states.

## Restore Point Classes

### Class A: Git Restore Point

Tags the committed state of each Git layer and writes a manifest.

Good for:

- AI system,
- project code,
- live-state committed dumps,
- child repo pointers.

Limitation:

- Does not protect untracked game client payload.

### Class B: Git Bundle Backup

Creates local `.bundle` files for committed Git histories.

Good for:

- local copy of committed repo history.

Limitation:

- Still does not include untracked client payload.

### Class C: Full Filesystem Backup

Copies payload files to a separate target.

Good for:

- full game client backup,
- untracked large binary payload.

Limitation:

- Requires enough target storage.

## Tool

```powershell
powershell -NoProfile -ExecutionPolicy Bypass -File .\ai-system\tools\New-RestorePoint.ps1 -Name "before-major-change"
```
