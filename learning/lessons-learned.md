# Lessons Learned

## 2026-06-03: Direct Script Execution May Be Blocked

PowerShell execution policy blocked direct `.ps1` execution. Use:

```powershell
powershell -NoProfile -ExecutionPolicy Bypass -File .\path\to\script.ps1
```

## 2026-06-03: Docker CLI Is Not Available In Current Shell

The live server probe reported `docker command not found`. Future runtime diagnostics need Docker CLI availability.

## 2026-06-03: Full Client Git Snapshot Needs Storage Plan

The game client payload is too large to casually commit on the current drive.
