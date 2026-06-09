# Pruning Policy

Pruning removes or demotes low-value context while preserving important concepts.

## Prune Candidates

- duplicate scan outputs,
- stale handoffs with no unique content,
- transient command output,
- resolved issue noise,
- failed experiments with no reusable lesson.

## Never Prune Without Replacement

- decisions,
- rollback records,
- evidence for major changes,
- restore manifests,
- policy violations,
- user constraints,
- known bugs still relevant.

## Strengthening

When a concept appears repeatedly, distill it into:

- `memory/facts.md`,
- `continuity/distilled-context/`,
- `learning/concept-bank/`,
- a module card,
- a playbook.

## Pruning Record

Material pruning should create an audit event.
