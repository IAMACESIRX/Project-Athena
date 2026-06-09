# Drift Register

## Active Drift Signals

### DR-001: Client Payload Drift

The game client working tree contains untracked payload. This is intentional for now, but must remain visible.

### DR-002: Python Environment Drift

The copied venv references an old user path.

### DR-003: Restore Address Drift

Live-state docs and SQL dump may disagree about realm address.

## Drift Handling

When drift is detected:

1. Identify source of truth.
2. Decide whether drift is intended.
3. If intended, document it.
4. If unintended, create issue or fix.
5. Refresh scan.
