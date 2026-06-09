# Evidence Labeling Guide

Canonical evidence IDs use this pattern:

`EVD-<PROJECT>-<FAMILY>-<NUMBER>`

Canonical names use this pattern:

`<evidence_id>__<summary_slug>`

## Families

Project namespaces:

- `EVD-WOW-*`: WoW Backup Stack.
- `EVD-AIOS-*`: the general AI-OS control plane itself.

- `EVD-WOW-SCAN-*`: project scan outputs.
- `EVD-WOW-MAP-*`: topology and navigation maps.
- `EVD-WOW-MANIFEST-*`: machine-readable manifests and indexes.
- `EVD-WOW-GIT-*`: commit, remote, branch, and layer evidence.
- `EVD-WOW-LIVE-*`: live server probe or runtime state.
- `EVD-WOW-LOG-*`: log intelligence outputs.
- `EVD-WOW-STATE-*`: watched-state baselines and drift reports.
- `EVD-WOW-FORENSIC-*`: verification reports.
- `EVD-WOW-DECISION-*`: decision, audit, causality, or rollback records.
- `EVD-WOW-HANDOFF-*`: chat handoff and continuity artifacts.
- `EVD-WOW-RISK-*`: risk, incident, or correction records.
- `EVD-AIOS-ID-*`: identity and constitution records.
- `EVD-AIOS-ORG-*`: organization and authority records.
- `EVD-AIOS-AGENT-*`: agent registry and lifecycle records.
- `EVD-AIOS-ROUTE-*`: orchestration, routing, and model operations records.
- `EVD-AIOS-TRAIN-*`: training, evaluation, and feedback records.

## Strength Labels

- `direct`: observed file, command output, scan, log, or commit.
- `derived`: generated from direct evidence.
- `inferred`: reasoned from direct or derived evidence.
- `reported`: user or external system statement.
- `provisional`: useful but not yet verified.
- `stale`: previously true but needs refresh.
- `contradicted`: challenged by newer evidence.
