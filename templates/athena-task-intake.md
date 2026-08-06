# Athena Task Intake: [Title]

## Metadata

- schema: `ai-system.athena_task_intake.v1`
- intake_id: `[ATHENA-INTAKE-YYYYMMDD-NNN]`
- created_at: `[ISO-8601 timestamp]`
- status: `created`
- execution_mode: `[manual | ai_assisted | automated | hybrid]`
- active_layer: `[root | Plan | Nexus V | tools | memory | work | other]`
- priority_source: `[human instruction | Plan | governance | code | runtime evidence]`

## Human Goal

[State the human request in one or two sentences.]

## Required Output

[State what must exist or be answered by the end of the run.]

## Benefits To Preserve

- [Name useful capabilities that controls or redesigns must not silently suppress.]

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

## Weakness Register

| ID | Weakness | Triggers | Harms | Associated Benefits | Evidence | Disposition | Status |
|---|---|---|---|---|---|---|---|
| W-001 | [negative pressure] | [conditions] | [harms] | [benefits to preserve] | [evidence] | mitigate | open |

## Mitigation And Offset Register

| ID | Weakness IDs | Control/Offset | Benefits Preserved | Activation Trigger | Modes | Trade-offs | New Risks | Manual Verification | Machine Verification | Review/Removal Conditions | Status |
|---|---|---|---|---|---|---|---|---|---|---|---|
| M-001 | W-001 | [control] | [benefit] | [trigger] | manual, hybrid | [costs] | [new risks] | [human check] | [script/test] | [when to revise or retire] | proposed |

## Intervention Log

| ID | Actor/Authority | Stage | Action | Reason | Changed Fields | Required Validation | Rollback Or Branch |
|---|---|---|---|---|---|---|---|

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

[Commands, file checks, tests, or review steps. Include checks that mitigations preserve their named benefits.]

## Memory Writeback Targets

- `[context.md | Plan/context.md | work/... | engine/cycle-reports/... | other]`

## End State

[Filled after completion.]
