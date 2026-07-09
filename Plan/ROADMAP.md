# ROADMAP

## Purpose

This roadmap turns Plan architecture intent into a sequence of buildable Athena
and Nexus-V work. `Plan/` remains the design authority; root folders and
`Nexus V/` are implementation surfaces.

## Phase 0: Current Baseline

Status: active

- Root context and Plan context exist.
- Complete file index exists.
- First Athena test cycle and brainstorm cycle exist.
- Athena has a task-intake schema/template, memory map, and cycle report
  template.
- OASIS/Athena local-agent adapter model is captured as Plan intent.
- Stale old-layout paths are being normalized.

Exit criteria:

- Operation tools run from `D:\Projects\Project Athena`.
- Plan placeholder files are filled.
- Context and file index describe the current checkout.

## Phase 1: Athena Brain Stem

Goal: make every non-trivial Athena task start and end cleanly.

- Use `work/intake/` for task intake.
- Use `memory/athena-memory-map.md` for writeback routing.
- Use `engine/cycle-reports/` for auditable cycles.
- Keep `tools/Invoke-AthenaCycle.ps1` lightweight and reversible.

Exit criteria:

- One intake packet can be created, processed, verified, and closed.
- Another agent can replay the packet and understand the decision.

## Phase 2: Plan Extraction

Goal: convert architecture documents into implementation queues.

- Convert the OASIS/Athena model into adapter contracts for Codex, Jarvis, GPT,
  and future local agents.
- Extract AI-OS v13 concepts into root architecture/work docs.
- Extract Cognitive Orchestrator concepts into cognition/orchestration tasks.
- Extract Athena memory architecture into memory contracts.
- Extract Odysseus Nexus into ontology/schema tasks.
- Extract Nexus-V hardware specs into implementation matrix rows.

Exit criteria:

- `Plan/IMPLEMENTATION_MATRIX.md` maps design intent to implementation state.
- Work items exist for the highest-priority missing pieces.
- Agent adapter contract work is represented in `agents/`, `orchestration/`,
  and `work/`.

## Phase 3: Nexus-V Alignment

Goal: connect Plan intent to the hardware/toolchain branch.

- Maintain `Nexus V/docs/NEXUS-V-IMPLEMENTATION-MATRIX.md`.
- Link RTL/toolchain files to Plan concepts.
- Separate generated outputs from source authority.
- Add expected traces and simulator/lint instructions.

Exit criteria:

- Each major Nexus-V subsystem has status, evidence, and next tests.

## Phase 4: Repeatable Processor

Goal: make Athena's operation cycle reliable.

- Normalize remaining path assumptions.
- Run integrity, scan, map, manifest, forensics, log intelligence, and watched
  state from the standalone checkout.
- Add validation around intake and cycle reports.

Exit criteria:

- `tools/Invoke-AIOperationCycle.ps1 -SkipLiveProbe` completes without stale
  path failures.

## Phase 5: Operator Experience

Goal: make Athena easy to use as an external brain.

- Add a small operator console or command workflow.
- Add task status summaries.
- Add "what should Athena read next?" guidance.
- Add compact context refresh output for new sessions.

Exit criteria:

- Human can start a task with one command or template and receive a clear next
  action, evidence state, and memory writeback.
