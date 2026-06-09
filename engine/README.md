# AI Operation Engine

This engine is the deterministic operating spine for the local AI-OS control plane.

It adapts the useful function of the Redwire diagnostics cycle into a reusable project-brain system: every serious pass should run through stable routines, produce reports, update ledgers, and leave the next AI or human with less ambiguity than before.

## Core Rule

Do not treat thinking, diagnostics, edits, evidence, and handoff as separate activities. A complete pass moves through all of them in order:

1. Anchor to authority, constraints, and current state.
2. Observe the real project state.
3. Verify evidence, claims, paths, and hashes.
4. Diagnose logs, drift, risks, and broken assumptions.
5. Reason through the cognition chain.
6. Decide under governance.
7. Act in the correct layer.
8. Audit the effect.
9. Learn and update continuity.

## Primary Command

```powershell
powershell -NoProfile -ExecutionPolicy Bypass -File .\ai-system\tools\Invoke-AIOperationCycle.ps1
```

## Engine Files

- `operation-cycle.md`: full operating model.
- `routine-catalog.yml`: machine-readable routine list.
- `order-of-operations.md`: long-form checklist chain for advanced thinking and execution.
- `checklists/full-reasoning-chain.md`: reasoning gate checklist.
- `checklists/engineering-cycle.md`: implementation pass checklist.
- `checklists/diagnostic-cycle.md`: diagnostic pass checklist.
- `cycle-history.csv`: append-only cycle run history.
- `cycle-reports/`: latest and historical operation reports.
