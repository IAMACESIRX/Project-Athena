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

## Issue routing

Use the GitHub issue forms for new tracked work:

- Architecture work for Plan, identity, schema, and system-map changes.
- Implementation work for tools, runtime, adapters, CI, tests, and source changes.
- Research or R&D work for experiments, hypotheses, physical R&D, and validation planning.
- Governance or publication work for authority, privacy, security, release, and public-mirror changes.

Use Discussions for exploratory ideas that are not ready for a bounded issue.

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

Release and GitHub Project operating rules are tracked in
`docs/RELEASE_AND_PROJECT_OPERATING_RULES.md`.
