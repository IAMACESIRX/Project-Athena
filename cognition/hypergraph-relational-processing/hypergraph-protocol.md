# Hypergraph Protocol

## Hyperedge Shape

A hyperedge links many nodes in one relationship:

```text
relationship:
  nodes:
    - user direction
    - policy
    - repo
    - file
    - tool
    - outcome
```

## Use For

- causality,
- module dependencies,
- restore paths,
- AI decision traces,
- runtime diagnosis,
- context anchors.

## Method

1. List entities.
2. Group entities by shared event or effect.
3. Create hyperedge.
4. Label relationship type.
5. Attach evidence and confidence.
6. Use graph to find missing nodes or hidden dependencies.
