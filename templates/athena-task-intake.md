# Athena Task Intake: [Title]

## Metadata

- schema: `ai-system.athena_task_intake.v1`
- intake_id: `[ATHENA-INTAKE-YYYYMMDD-NNN]`
- created_at: `[ISO-8601 timestamp]`
- status: `created`
- active_layer: `[root | Plan | Nexus V | tools | memory | work | other]`
- priority_source: `[human instruction | Plan | governance | code | runtime evidence]`

## Human Goal

[State the human request in one or two sentences.]

## Required Output

[State what must exist or be answered by the end of the run.]

## Files To Read

- `[path]`

## Files Read

- `[path]`

## Known Facts

| Statement | Truth Value | Confidence | Evidence |
|---|---|---:|---|
| [fact] | observed | 1.0 | [path or command] |

## Assumptions

| Statement | Truth Value | Confidence | Evidence |
|---|---|---:|---|
| [assumption] | assumed | 0.5 | [why it is reasonable] |

## Unknowns

| Statement | Truth Value | Confidence | Evidence |
|---|---|---:|---|
| [unknown] | unknown | 0.0 | [what would resolve it] |

## Risks

| Risk | Truth Value | Confidence | Mitigation |
|---|---|---:|---|
| [risk] | inferred | 0.5 | [mitigation] |

## Athena Decision Pass

Problem frame:
: [What problem is really being solved?]

Relevant cognition methods:
: [Socratic, inversion, council, hypergraph, anti-hallucination, etc.]

Decision:
: [Chosen action.]

Why this action:
: [Evidence-backed reasoning.]

Rollback or recovery:
: [How to undo or contain the action.]

## Verification Method

[Commands, file checks, tests, or review steps.]

## Memory Writeback Targets

- `[context.md | Plan/context.md | work/... | engine/cycle-reports/... | other]`

## End State

[Filled after completion.]
