# Liquid State Machine Model

## Components

### Inputs

- user requests,
- chat logs,
- file changes,
- Git commits,
- scans,
- runtime probes,
- logs,
- work items,
- audit events.

### Reservoir

Transient mixed state:

- recent events,
- correlations,
- unresolved risks,
- active assumptions,
- dynamic priorities,
- live runtime signals.

### Readouts

- next action,
- risk signal,
- causality hypothesis,
- work item,
- decision trace,
- memory promotion,
- pruning candidate.

## Operating Loop

1. Ingest signals.
2. Keep transient state visible.
3. Read out useful patterns.
4. Cross-check outputs.
5. Store or discard.
6. Update processes.

## Guardrail

Reservoir outputs are hypotheses until truth-checked.
