# Tools

Local tools for AI and human operators.

## Invoke-AIProjectScan.ps1

Creates a project scan report under `sensory/scans/latest-scan.json` and appends a short line to `SCAN-LOG.md`.

```powershell
powershell -NoProfile -ExecutionPolicy Bypass -File .\tools\Invoke-AIProjectScan.ps1
```

## New-HandoffSnapshot.ps1

Creates a dated session handoff under `handoff/sessions/`.

```powershell
powershell -NoProfile -ExecutionPolicy Bypass -File .\tools\New-HandoffSnapshot.ps1 -Title "After live-state snapshot"
```

## Update-LayerPointers.ps1

Compatibility shim for the old layered WoW checkout. In standalone Project
Athena it reports that there are no child repo pointers to stage, and refuses
legacy `-Commit` or `-Push` requests.

```powershell
powershell -NoProfile -ExecutionPolicy Bypass -File .\tools\Update-LayerPointers.ps1
```

No tool in this folder pushes to GitHub servers.

## Export-AISystemManifest.ps1

Writes `manifests/generated-ai-index.json`.

```powershell
powershell -NoProfile -ExecutionPolicy Bypass -File .\tools\Export-AISystemManifest.ps1
```

## Export-ProjectMap.ps1

Writes `navigation/generated/project-map.json`.

```powershell
powershell -NoProfile -ExecutionPolicy Bypass -File .\tools\Export-ProjectMap.ps1
```

## Update-ContextFileIndex.ps1

Regenerates `context-file-index.md` by indexing text files, Word documents,
zip archives, images, binaries, roles, sizes, and short hashes while excluding
`.git` internals.

```powershell
powershell -NoProfile -ExecutionPolicy Bypass -File .\tools\Update-ContextFileIndex.ps1
```

## New-WorkItem.ps1

Creates an individual work item under `work/work-items/`.

```powershell
powershell -NoProfile -ExecutionPolicy Bypass -File .\tools\New-WorkItem.ps1 -Type feature -Title "Add SQL dump inventory" -Layer live-state
```

## Invoke-LiveServerProbe.ps1

Creates a non-destructive live server report under `observability/reports/`.

```powershell
powershell -NoProfile -ExecutionPolicy Bypass -File .\tools\Invoke-LiveServerProbe.ps1
```

## New-ChatHandoff.ps1

Creates a chat log and handoff packet for continuity across AIs/tools.

```powershell
powershell -NoProfile -ExecutionPolicy Bypass -File .\tools\New-ChatHandoff.ps1 -Title "Session title" -Summary "What changed"
```

## New-AuditEvent.ps1

Creates an individual audit event record.

```powershell
powershell -NoProfile -ExecutionPolicy Bypass -File .\tools\New-AuditEvent.ps1 -Summary "Changed restore workflow" -EventType change -Layer live-state
```

## New-RestorePoint.ps1

Creates a restore point manifest and optionally Git tags/bundles for committed repo state.

```powershell
powershell -NoProfile -ExecutionPolicy Bypass -File .\tools\New-RestorePoint.ps1 -Name "before-major-change"
```

## Invoke-AIOperationCycle.ps1

Runs the integrated operation cycle: integrity, scan, map, manifest, forensic verification, log intelligence, watched-state baseline, optional live probe, and cognition checklist presence.

```powershell
powershell -NoProfile -ExecutionPolicy Bypass -File .\tools\Invoke-AIOperationCycle.ps1 -SkipLiveProbe
```

## Invoke-AIIntegrityCheck.ps1

Verifies required AI-system files, JSON validity, manifest path references, and local-only governance.

```powershell
powershell -NoProfile -ExecutionPolicy Bypass -File .\tools\Invoke-AIIntegrityCheck.ps1
```

## Invoke-AIForensicVerification.ps1

Validates the project forensics layer: evidence IDs, evidence paths, claim IDs, evidence-claim links, timeline evidence links, and known unknowns.

```powershell
powershell -NoProfile -ExecutionPolicy Bypass -File .\tools\Invoke-AIForensicVerification.ps1
```

## Invoke-AILogIntelligence.ps1

Scans local client/server logs against `observability/log-signatures.json` and writes log intelligence reports.

```powershell
powershell -NoProfile -ExecutionPolicy Bypass -File .\tools\Invoke-AILogIntelligence.ps1
```

## Invoke-AIWatchedState.ps1

Tracks a rolling hash baseline for selected AI-system, live-state, and server-project files.

```powershell
powershell -NoProfile -ExecutionPolicy Bypass -File .\tools\Invoke-AIWatchedState.ps1
```

