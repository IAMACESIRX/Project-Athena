# Faithful Reasoning Protocol

This protocol records reasoning in a way that is useful without pretending the agent has perfect introspection.

## Record

- decision,
- goal,
- evidence used,
- constraints,
- alternatives considered,
- expected effects,
- risks,
- verification plan,
- what would change the decision.

## Do Not Record

- fake certainty,
- hidden chain-of-thought,
- unsupported motives,
- unsupported claims about runtime state.

## Format

Use concise decision traces:

```text
Decision:
Evidence:
Constraints:
Alternatives:
Choice:
Expected effect:
Risk:
Verification:
Review trigger:
```

## Faithfulness Rule

If evidence was weak, say it was weak. If a claim is inferred, label it as inferred. If something was not checked, say so.
