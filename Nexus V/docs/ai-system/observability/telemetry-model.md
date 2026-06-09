# Telemetry Model

## Event Types

- git_status
- scan_generated
- live_probe_generated
- work_item_created
- bug_detected
- bug_resolved
- restore_started
- restore_finished
- server_probe
- client_probe
- command_hub_request
- policy_violation

## Observation Shape

Each observation should include:

- time,
- source,
- layer,
- signal,
- severity,
- evidence,
- recommended action.

## Storage

Generated telemetry reports should live under:

- `sensory/scans/`
- `observability/reports/`
- `handoff/sessions/`

Do not mix generated reports with source-of-truth registries unless the report is intentionally committed as a baseline.
