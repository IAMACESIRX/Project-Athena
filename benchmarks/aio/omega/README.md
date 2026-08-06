# AIO OMEGA Benchmarks

AIO OMEGA is the maximum-capability benchmark family for the unified AIO pipeline.

Unlike a golden question with one short known answer, an OMEGA benchmark is a blinded, seeded, closed-world programme. The evaluator knows the complete world state, causal model, failure schedule and feasible performance frontier. The solver receives only the public brief, evidence corpus and permitted interaction interface.

OMEGA measures whether one input can be carried through A.E.S.I.R., F.O.R.G.E., ATHENA, Aegis, Nexus-V and implementation tooling without fragmenting the contract state.

## Required properties

- hidden but objectively known ground truth;
- noisy, incomplete, contradictory and partially stale evidence;
- active experiment selection under a finite budget;
- full scientific and cross-scientific analysis;
- multiscale and full-stack engineering;
- candidate generation, tournament, mechanism mining and native reconstruction;
- benefit-preserving mitigation;
- adversarial shocks and changed constraints;
- rapid adoption without abandonment;
- human intervention and manual-operability checks;
- executable or simulatable outputs;
- calibrated uncertainty rather than unsupported confidence;
- append-only provenance and reproducibility.

## Implementation state

The flagship `yggdrasil-habitat` scenario now includes a runnable v0.1 stack:

- seeded hidden-world generation;
- evaluator-private truth and solver-visible public state;
- finite-budget diagnostic actions;
- staged crisis, upgrade and human-intervention rounds;
- a 730-day habitat resource and failure simulator;
- multi-replay outcome scoring;
- hard-gate enforcement;
- a local authenticated HTTP service;
- a transparent reference solver;
- manual operating documentation and runtime tests.

See `yggdrasil-habitat/RUNNABLE.md` for operation and `REFERENCE-RESULT.md` for the reproducible baseline.

## Benchmark classes

- `golden/` — known-answer integration and truth tests.
- `omega/` — multi-round hidden-world capability trials.

OMEGA results are meaningful only when the solver cannot access evaluator-private state. A local smoke run proves integration; a competitive run requires process and filesystem isolation.
