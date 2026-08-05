# Evidence / Provenance Schema Alignment

Generated: 2026-08-05

## Purpose

This document aligns Athena evidence registers, claim maps, cycle reports, plugin outputs, Asana tasks, Notion mirrors, Gamma dossiers, and Nexus-V/Aegis-style commit concepts into one provenance model.

## Research alignment

Recent agent provenance literature supports typed execution graphs, evidence-support relations, tool-use provenance, memory lineage, observability, debugging, audit, and recovery as key requirements for trustworthy LLM agents. Trace-based assurance work also supports message-action traces, explicit contracts, replay, stress testing, and governance mediation.

## Core objects

```yaml
EvidenceItem:
  evidence_id: string
  source_type: repo | file | plugin | research | local_tool | human_input | generated_artifact
  source_ref: string
  claim_supported: list[string]
  confidence: number
  freshness: string
  access_boundary: public | private | local_only | user_authorized_push
```

```yaml
ClaimRecord:
  claim_id: string
  text: string
  status: fact | assumption | hypothesis | speculation | prediction | opinion | unresolved
  evidence_refs: list[string]
  contradicts: list[string]
  subsystem: string
  capability_state: string
```

```yaml
ExecutionTrace:
  trace_id: string
  initiator: human | athena | adapter | local_tool
  action: string
  input_refs: list[string]
  output_refs: list[string]
  plugin_refs: list[string]
  governance_gate: none | soft | hard | human
  result: success | partial | blocked | failed
```

## Alignment table

| Athena concept | Provenance role | Nexus-V analogue |
|---|---|---|
| Evidence register | support graph | provenance edge |
| Claim map | assertion state | versioned node |
| Cycle report | change summary | commit report |
| Plugin action | external operation | state mutation |
| Local verification | validation event | commit gate evidence |
| Memory update | durable knowledge write | accepted commit |

## Minimum rule

Any artifact created outside GitHub must be recorded in GitHub with:

- tool name,
- artifact name,
- URL or ID,
- purpose,
- canonicality status,
- next action,
- and whether it is source-of-truth, mirror, research support, or execution queue.

## Capability state

Current state: `Specified`.

Next implementation step: create JSON/YAML schemas and attach them to automated cycle reports.
