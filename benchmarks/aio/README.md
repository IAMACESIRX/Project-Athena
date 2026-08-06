# AIO Golden Truth Benchmarks

This directory contains known-answer benchmarks used to test whether the unified AIO pipeline reaches the correct conclusion, preserves assumptions and uncertainty, challenges apparent positives and negatives, reconstructs valid alternatives, and retains all required pipeline phases.

Each benchmark contains:

- `input.json` — the single input given to the pipeline;
- `ai-solution.json` — structured AI completion of all 21 phases;
- `golden.json` — machine-checkable expected truth and acceptance criteria;
- `RESULT.md` — human-readable outcome and reproduction command.

Golden benchmarks test pipeline integrity and reasoning behaviour. They do not establish that every output from AIO is correct, and they do not replace empirical validation where physical evidence is required.
