# AIO Benchmarks

This directory contains two complementary benchmark classes.

## Golden truth benchmarks

Golden benchmarks test whether the unified AIO pipeline reaches a known conclusion, preserves assumptions and uncertainty, challenges apparent positives and negatives, reconstructs valid alternatives, and retains all required pipeline phases.

Each golden benchmark contains:

- `input.json` — the single input given to the pipeline;
- `ai-solution.json` — structured AI completion of all 21 phases;
- `golden.json` — machine-checkable expected truth and acceptance criteria;
- `RESULT.md` — human-readable outcome and reproduction command.

## OMEGA maximum-capability benchmarks

OMEGA benchmarks are blinded, seeded, closed-world programmes. The evaluator knows the complete hidden state and can objectively score diagnosis, experiment selection, architecture, simulated outcomes, crisis adaptation, mitigation, governance, simplicity and manual operability.

The solver receives only the public brief, evidence corpus and permitted interaction interface. Secret seeds, held-out scenario families and stochastic replays prevent memorisation and exact-text gaming.

The flagship scenario is:

- `omega/yggdrasil-habitat` — diagnose, reconstruct, operate and adapt a 48-person isolated habitat across nine rounds.

Benchmarks test pipeline integrity and reasoning behaviour. They do not establish that every output from AIO is correct, and they do not replace empirical validation where physical evidence is required.
