# Experiments

## Experiment Template

- ID:
- Question:
- Layer:
- Hypothesis:
- Method:
- Safety constraints:
- Result:
- Decision:

## Planned Experiments

### E-001: Partial Client Snapshot

Question: Can the client repo track only configuration and addon state while excluding massive MPQ payloads?

Layer: Game client

Safety constraints: Do not commit full `Data/*.MPQ` payload.

### E-002: Backend Smoke Test After Venv Rebuild

Question: Does the command hub run cleanly after recreating `.venv`?

Layer: WoW server project

Safety constraints: No live server mutation.

### E-003: Model Fit Scoring

Question: Can a hardware-aware score predict whether a model can run locally without disrupting normal AI-OS work?

Layer: model-ops

Safety constraints: No downloads until the human approves disk and bandwidth use.

### E-004: Repo-Level Coding Eval

Question: Which model/router configuration can localize edits, patch files, run checks, and produce a useful handoff on this repository?

Layer: coding agent

Safety constraints: Use reversible edits and avoid unrelated user changes.

### E-005: Deep Research Eval

Question: Can the research pipeline gather primary sources, reject weak claims, and produce a citation-bound brief for a fast-changing AI model?

Layer: research engine

Safety constraints: Source-label every claim and do not treat benchmark claims as verified until reproduced.

### E-006: Windows Agent Platform Eval

Question: Can an agent inspect local state, operate approved tools, and annotate localized edits without overstepping authority?

Layer: runtime

Safety constraints: Read-only first, reversible edits second, high-risk actions require explicit approval.
