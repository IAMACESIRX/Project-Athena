# Tools

Local tools for AI and human operators.

## Invoke-AIProjectScan.ps1

Creates a project scan report under `ai-system/sensory/scans/latest-scan.json` and appends a short line to `SCAN-LOG.md`.

```powershell
powershell -NoProfile -ExecutionPolicy Bypass -File .\ai-system\tools\Invoke-AIProjectScan.ps1
```

## New-HandoffSnapshot.ps1

Creates a dated session handoff under `ai-system/handoff/sessions/`.

```powershell
powershell -NoProfile -ExecutionPolicy Bypass -File .\ai-system\tools\New-HandoffSnapshot.ps1 -Title "After live-state snapshot"
```

## Update-LayerPointers.ps1

Stages child repo pointers in the mega repo after child repos have already been committed.

```powershell
powershell -NoProfile -ExecutionPolicy Bypass -File .\ai-system\tools\Update-LayerPointers.ps1
powershell -NoProfile -ExecutionPolicy Bypass -File .\ai-system\tools\Update-LayerPointers.ps1 -Commit -Push
```

No tool in this folder pushes to GitHub servers.

## Export-AISystemManifest.ps1

Writes `ai-system/manifests/generated-ai-index.json`.

```powershell
powershell -NoProfile -ExecutionPolicy Bypass -File .\ai-system\tools\Export-AISystemManifest.ps1
```

## Export-ProjectMap.ps1

Writes `ai-system/navigation/generated/project-map.json`.

```powershell
powershell -NoProfile -ExecutionPolicy Bypass -File .\ai-system\tools\Export-ProjectMap.ps1
```

## New-WorkItem.ps1

Creates an individual work item under `ai-system/work/work-items/`.

```powershell
powershell -NoProfile -ExecutionPolicy Bypass -File .\ai-system\tools\New-WorkItem.ps1 -Type feature -Title "Add SQL dump inventory" -Layer live-state
```

## Invoke-LiveServerProbe.ps1

Creates a non-destructive live server report under `ai-system/observability/reports/`.

```powershell
powershell -NoProfile -ExecutionPolicy Bypass -File .\ai-system\tools\Invoke-LiveServerProbe.ps1
```

## New-ChatHandoff.ps1

Creates a chat log and handoff packet for continuity across AIs/tools.

```powershell
powershell -NoProfile -ExecutionPolicy Bypass -File .\ai-system\tools\New-ChatHandoff.ps1 -Title "Session title" -Summary "What changed"
```

## New-AuditEvent.ps1

Creates an individual audit event record.

```powershell
powershell -NoProfile -ExecutionPolicy Bypass -File .\ai-system\tools\New-AuditEvent.ps1 -Summary "Changed restore workflow" -EventType change -Layer live-state
```

## New-RestorePoint.ps1

Creates a restore point manifest and optionally Git tags/bundles for committed repo state.

```powershell
powershell -NoProfile -ExecutionPolicy Bypass -File .\ai-system\tools\New-RestorePoint.ps1 -Name "before-major-change"
```

## Invoke-AIOperationCycle.ps1

Runs the integrated operation cycle: integrity, scan, map, manifest, forensic verification, log intelligence, watched-state baseline, optional live probe, and cognition checklist presence.

```powershell
powershell -NoProfile -ExecutionPolicy Bypass -File .\ai-system\tools\Invoke-AIOperationCycle.ps1 -SkipLiveProbe
```

## Invoke-AIIntegrityCheck.ps1

Verifies required AI-system files, JSON validity, manifest path references, and local-only governance.

```powershell
powershell -NoProfile -ExecutionPolicy Bypass -File .\ai-system\tools\Invoke-AIIntegrityCheck.ps1
```

## Invoke-AIForensicVerification.ps1

Validates the project forensics layer: evidence IDs, evidence paths, claim IDs, evidence-claim links, timeline evidence links, and known unknowns.

```powershell
powershell -NoProfile -ExecutionPolicy Bypass -File .\ai-system\tools\Invoke-AIForensicVerification.ps1
```

## Invoke-AILogIntelligence.ps1

Scans local client/server logs against `ai-system/observability/log-signatures.json` and writes log intelligence reports.

```powershell
powershell -NoProfile -ExecutionPolicy Bypass -File .\ai-system\tools\Invoke-AILogIntelligence.ps1
```

## Invoke-AIWatchedState.ps1

Tracks a rolling hash baseline for selected AI-system, live-state, and server-project files.

```powershell
powershell -NoProfile -ExecutionPolicy Bypass -File .\ai-system\tools\Invoke-AIWatchedState.ps1
```
