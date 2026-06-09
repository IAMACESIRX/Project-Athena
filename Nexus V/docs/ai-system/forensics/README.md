# Project Forensics

This folder adapts the useful function of the Xavier forensic case system into the local AI-OS control plane.

The purpose is not medical-style content. The purpose is evidence discipline:

- stable IDs for important observations across projects,
- canonical paths for files and reports,
- claim maps,
- event timelines,
- known unknowns,
- verification passes,
- role-specific packets for AI, engineering, operations, and neutral review.

Project namespaces keep records portable: `EVD-WOW-*` for the WoW Backup Stack, `EVD-AIOS-*` for the general AI-OS, and future namespaces for future project brains.

## Primary Files

- `evidence-labeling-guide.md`
- `evidence-register.csv`
- `claim-catalog.csv`
- `evidence-claim-map.csv`
- `event-timeline.csv`
- `known-unknowns.csv`
- `verification-protocol.md`
- `role-packets/ai-ingestion-brief.md`

## Verification Command

```powershell
powershell -NoProfile -ExecutionPolicy Bypass -File .\ai-system\tools\Invoke-AIForensicVerification.ps1
```

## Rule

Claims about the project should point to evidence IDs where possible. Unsupported claims stay provisional.
