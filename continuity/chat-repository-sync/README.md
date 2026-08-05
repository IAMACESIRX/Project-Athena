# Chat Repository Sync

This directory is the control surface for Project Athena's bidirectional chat
and repository lifecycle.

## Tracked Files

- `sync-policy.json`: machine-readable authority, privacy, and promotion rules.
- `promotion-ledger.jsonl`: append-only decisions about chat-derived changes.
- `latest-context-capsule.json`: manifest for the latest bounded repo export.
- `latest-context-capsule.md`: content supplied to a future chat session.

## Local-Only Generated Files

Unreviewed imports are written under
`continuity/transcript-inbox/imports/`. That directory is ignored by Git. It can
contain account data and must not be published merely because it was parsed.

## Normal Cycle

```powershell
powershell -NoProfile -ExecutionPolicy Bypass -File .\tools\Import-AthenaChatExport.ps1 -SourcePath <path>
powershell -NoProfile -ExecutionPolicy Bypass -File .\tools\Export-AthenaChatContext.ps1
powershell -NoProfile -ExecutionPolicy Bypass -File .\tools\Test-AthenaRepository.ps1
```

Use `-Full` with the context exporter when an independent completeness pass is
needed. Full output is chunked under the ignored generated directory and is not
intended for routine Git publication.
