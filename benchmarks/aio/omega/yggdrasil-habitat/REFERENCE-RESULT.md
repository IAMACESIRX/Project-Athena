# AIO-OMEGA-001 Reference Runtime Result

The transparent reference solver was executed against the complete runtime without reading evaluator-private state.

## Fixed reference run

- Seed: `reference-seed-001`
- Score: **99.221 / 100**
- Hard failures: **0**
- Diagnosis precision: **1.0**
- Diagnosis recall: **1.0**
- Diagnosis F1: **1.0**
- Brier score: **0.00993**
- Hidden replay survival probability: **1.0**
- Mean mission completion: **1.0**
- Diagnostic budget used: **90 / 100**

## Seed stress test

The same solver was run across 20 distinct secret seeds:

- Minimum score: **99.039**
- Maximum score: **99.315**
- Mean score: **99.14595**
- Failed runs: **0 / 20**

This high score is expected because the reference solver is deliberately engineered to cover the complete public fault catalogue and uses a conservative, oversized architecture. It is a runtime integration baseline, not evidence that the benchmark is already maximally discriminating.

## What this result proves

- Hidden truth generation is deterministic by secret seed.
- Public state does not expose selected faults or the seed hash.
- Diagnostic budgets and round ordering are enforced.
- Diagnostic evidence is preserved and modification causes a hard failure.
- The habitat simulator differentiates the unreconstructed baseline from a robust reconstruction.
- Staged crisis, upgrade and human-intervention rounds operate end to end.
- Scoring combines diagnosis calibration, experiment use, engineering survival, mitigation, governance and manual operability.

## What must become harder

The reference baseline exposes the next challenge: the public test catalogue currently makes full fault coverage possible within 90 budget units. Later versions should randomise diagnostic capabilities, introduce partial observability, make some tests conditionally unsafe, add model mismatch, and reserve held-out fault families so a fixed diagnostic sweep cannot dominate.
