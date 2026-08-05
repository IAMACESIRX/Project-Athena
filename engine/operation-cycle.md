# Operation Cycle

The operation cycle turns the AI-OS into a working control plane rather than a passive folder.

## Execution Layers

1. Human authority, local-only rules, and bounded exceptions.
2. Governance and safety gates.
3. Project scan and topology map.
4. Project and system forensic evidence verification.
5. Log and runtime intelligence.
6. Watched-state baseline and drift check.
7. Cognition and council reasoning.
8. Work execution.
9. Audit, restore readiness, and continuity update.

## Cycle Contract

Every cycle must produce or refresh:

- `ai-system/sensory/scans/latest-scan.json`
- `ai-system/navigation/generated/project-map.json`
- `ai-system/manifests/generated-ai-index.json`
- `ai-system/diagnostics/reports/latest-integrity-report.json`
- `ai-system/forensics/verification-reports/latest-forensic-verification.json`
- `ai-system/observability/reports/latest-log-intelligence.json`
- `ai-system/sensory/scans/latest-watched-changes.json`
- `ai-system/engine/cycle-reports/latest-cycle-report.json`

## Routine Modes

- `observe`: scan, map, inspect logs, verify evidence.
- `diagnose`: classify risks, contradictions, missing files, and unresolved claims.
- `reason`: run the cognition checklist before any irreversible change.
- `execute`: make scoped edits only after evidence and rollback path are known.
- `audit`: prove what changed and update handoff memory.

## Failure Handling

- Red findings stop destructive work.
- Yellow findings require a named mitigation before action.
- Missing evidence keeps claims provisional.
- Broken scripts become correction-queue items, not silent failures.
- Cloud remotes are a stop condition unless an explicit bounded exception names
  the repository, scope, and permitted mutation.
