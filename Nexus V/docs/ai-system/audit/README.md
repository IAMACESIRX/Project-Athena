# Audit System

The audit system records decisions, actions, evidence, causes, effects, and reversibility.

## Main Files

- `audit-ledger.yml`: durable event index.
- `decision-trace-ledger.yml`: decision-making records.
- `causality-graph.yml`: cause/effect links.
- `rollback-ledger.yml`: how to reverse changes.
- `faithful-reasoning-protocol.md`: how to record reasoning without pretending certainty.
- `decision-framework.md`: refined decision method.

## Rule

If a change matters, log enough context that future-you can answer:

- Who or what caused it?
- What changed?
- Why was it done?
- What evidence supported it?
- What could go wrong?
- How do we reverse it?
