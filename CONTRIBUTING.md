# Contributing to Project Athena

Project Athena uses evidence-first, architecture-aware changes.

## Branch and pull-request policy

1. Create focused branches from the current `main`.
2. Do not treat an unmerged feature branch as canonical.
3. Use pull requests for architecture, governance, schemas, runtime, hardware,
   or generated-state changes.
4. Declare merge dependencies and conflicts with other open pull requests.
5. Keep generated artifacts separate from source authority where practical.
6. Do not force-update `main`.
7. After repository integrity CI is enabled, require it before merge.

## Architecture authority

- The latest explicit human instruction has highest authority.
- `Plan/` defines intended architecture.
- Root context and manifests describe current operating state.
- Source, tests, and reports establish implementation evidence.
- A specification is not proof that its runtime or hardware exists.

## Evidence discipline

Important changes should record:

- what was observed;
- what was inferred or assumed;
- what remains unknown;
- the verification performed;
- skipped checks and missing tools;
- memory or context writeback;
- rollback or recovery procedure.

## Project-specific profiles

Project-neutral Athena roles belong in `council/roles.yml`. Domain-specific
roles, such as WoW/AzerothCore operations, belong in
`council/profiles/<project>.yml` and activate only for that project.

## Publication

Follow `governance/cloud-publication-policy.md`. Public repository access does
not authorize publication of secrets, personal memory, local runtime state,
credentials, private logs, or unsanitized evidence.
