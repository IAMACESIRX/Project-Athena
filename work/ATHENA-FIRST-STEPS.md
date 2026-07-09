# Athena First Steps

This is the immediate build path for turning Athena from a structured AI-OS
workspace into a usable AI prosthetic external brain.

## Operating Thesis

Athena extends the human operator by acting as:

- External memory: durable context, history, decisions, evidence, and work state.
- Database: organized files, registries, schemas, ledgers, indexes, and source
  packages.
- Processor: a repeatable loop that converts intent into context, decisions,
  actions, verification, and updated memory.

## Phase 0: Canonicalize The Brain

Goal: make the repo describe itself correctly.

- Keep `context.md` as the whole-project canonical context.
- Keep `Plan/context.md` as the Plan-priority architecture context.
- Treat `context-file-index.md` as the current file inventory until the next
  full scan.
- Add future high-level changes to context in the same pass that creates them.
- Preserve legacy-layout notes only in historical/generated mirror material.
  First-read manifests and tools now use root-relative Project Athena paths.

## Phase 1: Define Task Intake

Goal: make every Athena run start with structured intent.

Create or update:

- `schemas/athena-task-intake.schema.json`
- `work/intake/`
- `templates/athena-task-intake.md`

Minimum fields:

- Human goal.
- Active project layer.
- Priority source, especially whether `Plan/` controls the task.
- Files read.
- Known facts.
- Assumptions.
- Unknowns.
- Risks.
- Required output.
- Verification method.
- Memory writeback targets.

## Phase 2: Define Memory Layers

Goal: make Athena's memory explicit instead of implicit.

Recommended layers:

- Core identity memory: `identity/`, `AI-PORTAL.md`, `context.md`.
- Architecture memory: `Plan/`, `Plan/context.md`, `Nexus V/docs/Plan/`.
- Working memory: `work/`, `handoff/`, `continuity/`.
- Evidence memory: `forensics/`, `audit/`, `engine/cycle-reports/`.
- Capability memory: `manifests/`, `registries/`, `agents/`,
  `orchestration/`.
- Runtime and implementation memory: `Nexus V/`, `tools/`, `runtime/`,
  `modules/`.

## Phase 3: Make The Processor Repeatable

Goal: turn the manual test run into a repeatable workflow.

Use `engine/order-of-operations.md` as the canonical cycle:

1. Authority and boundary.
2. Context anchoring.
3. Observation.
4. Evidence discipline.
5. Problem framing.
6. Truth and anti-hallucination gate.
7. Relational mapping.
8. Cognitive pass.
9. Decision gate.
10. Execution.
11. Verification.
12. Audit and continuity.
13. End state.

Near-term implementation options:

- Fix existing PowerShell scripts so they operate from this standalone repo.
- Add a lightweight `Invoke-AthenaCycle.ps1` wrapper.
- Generate one markdown report per run under `engine/cycle-reports/`.
- Append important learned facts into `context.md`, `Plan/context.md`, or
  handoff files depending on scope.

## Phase 4: Connect Nexus V To Athena

Goal: make Nexus V the execution architecture branch of the external brain.

- Keep `Plan/` as architecture authority.
- Keep `Nexus V/` as the source-heavy hardware/toolchain implementation branch.
- Use cycle reports to link Plan claims to implemented RTL, scripts, generated
  outputs, and missing tests.
- Do not treat generated Verilator/build artifacts as design authority.

## Phase 5: Brainstorm-Derived Improvement Stack

Goal: turn Athena's own thinking methods into an improvement sequence.

Source:
: `council/reasoning-rounds/council-20260710-athena-improvement-brainstorm.md`

Priority order:

1. Create Athena task-intake schema and template.
2. Create Athena memory-layer map.
3. Build or wrap a standalone Athena cycle runner.
4. Keep root-relative path normalization verified as tools evolve.
5. Mine `Plan/` into implementation matrices and work items.
6. Keep Nexus V connected to Plan through an implementation-status matrix.

Guiding decision:
: Build intake and memory contracts before automation-heavy work. Automation is
  more useful after Athena knows what kind of memory it is reading and where
  verified outputs should be written back.

## Next Reversible Experiment

Created:

- `schemas/athena-task-intake.schema.json`
- `templates/athena-task-intake.md`
- one sample intake packet for a small Athena task

Next use:

- Run one real task from intake through decision, implementation, verification,
  cycle report, and memory writeback.

Verification:

- The sample task names its goal, files read, evidence labels, unknowns,
  required output, verification method, and memory writeback target.
- Another agent should be able to replay the packet and understand why Athena
  chose its next action.

## First Test Result

The first Athena use test passed as a manual file-native cycle. Athena could
anchor context, classify itself, identify stale operating assumptions, and write
back updated memory. The next step is to make that cycle repeatable through
schemas, templates, and corrected tooling.
