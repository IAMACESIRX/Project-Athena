# Semantic Drift Correction Protocol

## Drift Signals

- same term used differently in separate files,
- module scope expands without registry update,
- "memory" used for both handoff and durable facts,
- "backup" used for Git state and untracked filesystem payload,
- generated terms not linked to definitions.

## Method

1. Identify drifting term.
2. Find all active meanings.
3. Choose canonical meaning.
4. Create aliases if needed.
5. Update registry/docs.
6. Record correction.

## Output

```text
Term:
Observed meanings:
Canonical meaning:
Aliases:
Files updated:
Risk if uncorrected:
```
