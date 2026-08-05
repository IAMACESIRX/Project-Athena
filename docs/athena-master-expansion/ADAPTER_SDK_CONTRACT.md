# Athena Adapter SDK Contract

Generated: 2026-08-05

## Purpose

The Adapter SDK Contract defines how external tools, plugins, local models, Codex/Jarvis-style agents, OASIS, and the future Operative Duplex AI connect to Athena without becoming the source of truth.

## Rule

```text
Repo = source of truth.
Athena = governance/orchestration/memory.
Adapters = controlled interfaces.
Plugins = mirrors, research tools, or execution views.
```

## Adapter object

```yaml
AthenaAdapter:
  adapter_id: string
  name: string
  provider: github | notion | asana | gamma | consensus | scispace | drive | local | oasis | custom
  capability_class: observe | retrieve | create | update | execute | publish
  permission_level: low | medium | high | human_required
  canonicality: canonical | mirror | execution_view | research_anchor | export
  allowed_roots: list[string]
  audit_required: boolean
  rollback_supported: boolean
```

## Standard call envelope

```yaml
AthenaAdapterCall:
  call_id: string
  adapter_id: string
  human_request_ref: string
  input_summary: string
  target: string
  action: string
  expected_output: string
  risk_level: low | medium | high
  governance_gate: none | soft | hard | human
  result_ref: string
  evidence_refs: list[string]
```

## Required adapter behavior

- State what it reads.
- State what it writes.
- State whether output is canonical, mirrored, or temporary.
- Return IDs/URLs for created artifacts.
- Avoid silent divergence from GitHub docs.
- Produce enough metadata for cycle reports.

## Plugin classes

| Plugin | Class | Canonical role |
|---|---|---|
| GitHub | canonical source | stores source docs, issues, state files. |
| Notion | mirror/dashboard | maps docs and states for navigation. |
| Asana | execution queue | tracks work and status. |
| Gamma | presentation layer | makes review decks/dossiers. |
| Consensus | research anchor | finds/fetches peer-reviewed support. |
| SciSpace | research anchor | independent academic table/search. |
| Google Drive | export/archive mirror | holds optional exported or shared copies. |

## Capability state

Current state: `Specified`.

Implementation requires local adapter wrappers and cycle-report integration.
