# Non-Monotonic Reasoning Protocol

## Principle

Some conclusions are provisional. New evidence may retract or revise them.

## Method

1. Mark claim as default, provisional, or stable.
2. Record evidence.
3. Record retraction conditions.
4. When new evidence arrives, update claim and ledgers.

## Claim Classes

- stable: unlikely to change without explicit policy change.
- provisional: true for now but may change.
- default: assumed only until checked.
- retracted: no longer supported.

## Output

```text
Claim:
Class:
Evidence:
Retraction condition:
Current status:
```
