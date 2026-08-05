# Operative Duplex AI Specification

Generated: 2026-08-05

## Definition

Operative Duplex AI is the future local action and metacognitive PC-control layer for Project Athena. It is the system's arms-and-legs layer. It is not Athena, not OASIS, and not Nexus-V. It operates under Athena governance and uses OASIS/Jarvis/local-program context where available.

## Boundary

```text
Athena = decides, governs, remembers, audits.
OASIS = simulated/world workspace.
Nexus-V = versioned state representation.
Operative Duplex AI = executes approved local software actions.
```

## Core responsibilities

- Convert approved tasks into local action plans.
- Interact with programs through adapters, UI observation, or documented APIs.
- Produce replayable action traces.
- Ask Athena for governance decisions before high-impact actions.
- Return outcomes, errors, screenshots/state descriptions, and evidence references.

## Non-goals

- It does not replace Athena's memory or governance.
- It does not bypass user authority.
- It does not claim unrestricted control.
- It does not perform hidden cloud execution.

## Permission model

```yaml
PermissionClass:
  observe_only: can inspect state but cannot modify
  draft_only: can prepare but not submit
  reversible_action: can act if rollback exists
  irreversible_action: requires explicit human approval
  external_action: requires explicit human approval and audit
```

## Action lifecycle

```text
user goal
→ Athena task classification
→ evidence/context lookup
→ Operative action proposal
→ governance gate
→ execution trace
→ result capture
→ Athena memory/evidence writeback
```

## Adapter classes

| Adapter | Purpose |
|---|---|
| API adapter | uses documented application APIs. |
| UI adapter | uses controlled visual/UI interaction where APIs are absent. |
| File adapter | edits local project files under allowed roots. |
| Repo adapter | prepares Git changes or issue updates under user authorization. |
| OASIS adapter | manipulates simulated objects/world state. |

## Required audit object

```yaml
OperativeTrace:
  trace_id: string
  human_request: string
  athena_task_id: string
  target_application: string
  permission_class: string
  planned_actions: list[string]
  executed_actions: list[string]
  result_summary: string
  evidence_refs: list[string]
  rollback_available: boolean
  final_state: success | partial | blocked | failed
```

## Capability state

Current state: `Specified / Conceptual`.

The role boundary is now formalized. Implementation requires adapter SDK, permission gates, local runtime, and trace logging.
