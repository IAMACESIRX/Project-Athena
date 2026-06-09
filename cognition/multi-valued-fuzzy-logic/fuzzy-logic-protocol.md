# Fuzzy Logic Protocol

## Truth Values

- true,
- false,
- unknown,
- partially_true,
- likely_true,
- likely_false,
- contradicted,
- stale,
- not_applicable.

## Confidence Scores

Use approximate confidence only as a reasoning aid:

- 0.0 impossible or false by evidence,
- 0.25 weak,
- 0.5 uncertain,
- 0.75 likely,
- 1.0 verified.

## Method

1. State claim.
2. Assign truth value.
3. Assign confidence.
4. Name evidence.
5. Name what would change the value.
6. Decide whether action is safe.

## Guardrail

Do not use numeric confidence to disguise weak evidence.
