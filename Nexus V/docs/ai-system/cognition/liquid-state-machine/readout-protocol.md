# Readout Protocol

## Readout Types

- urgent risk,
- likely cause,
- stale context,
- next best action,
- repeated pattern,
- memory promotion candidate,
- pruning candidate,
- experiment candidate.

## Process

1. Choose signal window.
2. Identify active signals.
3. Detect co-occurrence.
4. Apply anti-hallucination checks.
5. Label confidence.
6. Emit readout as work item, audit event, or memory update.

## Output Template

```text
Signal window:
Active signals:
Readout:
Confidence:
Evidence:
Action:
Storage:
```
