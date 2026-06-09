# Diagnostic Cycle Checklist

## Observe

- Run project scan.
- Run log intelligence.
- Run live probe if server state matters.
- Inspect relevant repo status.
- Capture new evidence IDs for important logs or reports.

## Classify

- Runtime issue.
- Config issue.
- Database or live-state issue.
- Client issue.
- Source/build issue.
- Git/layering issue.
- AI-system/process issue.

## Investigate

- Compare current state to watched baseline.
- Link symptoms to evidence.
- Separate correlation from causation.
- Keep unresolved interpretations open.
- Add known unknowns.

## Resolve

- Prefer reversible changes.
- Update correction queue.
- Add or update work items.
- Verify with logs, scans, or tests.
- Record outcome and rollback notes.

