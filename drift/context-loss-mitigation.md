# Context Loss Mitigation

Context loss happens when a future AI or human cannot reconstruct why the project is shaped the way it is.

## Anchors

- `AI-PORTAL.md`: universal entry point.
- `system-manifest.json`: machine-readable index.
- `handoff/CURRENT_STATE.md`: current story.
- `sensory/scans/latest-scan.json`: current measured state.
- `memory/decision-ledger.md`: why decisions were made.
- `work/TODO.md`: what to do next.

## Mitigation Pattern

1. Put stable facts in `memory/facts.md`.
2. Put decisions in `memory/decision-ledger.md`.
3. Put changing state in `handoff/CURRENT_STATE.md`.
4. Put future work in `work/`.
5. Put measured state in `sensory/scans/`.
6. Put capability assumptions in `manifests/capability-matrix.yml`.

## Anti-Patterns

- Important facts only in chat.
- Scripts without docs.
- Work items only in memory.
- Runtime state without a scan.
- Parent repo committed without child pointer awareness.
