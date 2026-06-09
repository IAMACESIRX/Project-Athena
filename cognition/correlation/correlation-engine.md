# Correlation Engine

## Purpose

Find patterns across the project.

## Correlation Types

- file change -> bug,
- decision -> later risk,
- scan signal -> work item,
- runtime log -> server behavior,
- client config -> login result,
- disk pressure -> Git strategy,
- tool failure -> process update.

## Method

1. Collect observations.
2. Group by time, layer, file, module, and actor.
3. Look for repeated co-occurrence.
4. Label as correlation, not causation.
5. Create a test or audit event if useful.

## Output Template

```text
Signal A:
Signal B:
Observed relationship:
Confidence:
Possible causal mechanisms:
Counterexamples:
Next test:
```
