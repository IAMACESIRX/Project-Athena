# Project Athena Work Queue

Updated: 2026-08-05

This is the current repository-wide queue. Project-specific legacy work belongs
under its project brain, not in this root queue.

## Reconciliation completed

- Repository governance, CI and legacy-project scoping merged through PR #7.
- Independent JANUS identity and corrected OASIS substrate merged through PR #8.
- Reality-to-Simulation and Material Intelligence merged through PR #9.
- Repository Integrity passed on each replacement PR and on the resulting
  canonical `main` commits.
- Superseded PRs #4 and #5 were closed with provenance links to their clean
  replacements; their source branches remain temporarily available.

## Now — Refresh measured state

- Run the complete local Athena operation cycle against
  `main@cc8da6b42cb871afad121ab5bf104428137615ea` or its latest descendant.
- Regenerate the system manifest, project map, file index, sensory scans and
  cycle reports so every generated status record names the exact validated
  commit and tool versions.
- Install and document a canonical SystemVerilog simulator/linter, then run real
  Nexus-V lint, compilation and simulation.
- Configure GitHub branch protection and secret scanning through repository
  settings; track completion in the dedicated GitHub issue.
- Confirm superseded branches contain no unique required work, then archive or
  delete them through GitHub branch management.

## Next — Build one executable Athena slice

- Run one real task from structured intake through context resolution, policy
  gate, model/tool routing, execution, independent verification, evidence IDs,
  cycle report and memory writeback.
- Connect task-intake claims to `forensics/evidence-register.csv`,
  `forensics/claim-catalog.csv` and `forensics/evidence-claim-map.csv`.
- Implement project-profile activation so domain-specific council roles are
  selected mechanically rather than only by documentation convention.
- Convert architecture claims into testable requirements and implementation
  issues instead of adding untracked specification layers.
- Generate a current capability matrix from source, tests and reports.

## Nexus-V verification

- Replace artifact-presence-only regression with simulator-backed execution in
  `Nexus V/scripts/run_regression.py`.
- Add expected traces, negative tests, assertions and subsystem coverage.
- Record simulator version, command line, source commit and generated-artifact
  hashes in every verification report.
- Separate source authority, generated vectors, simulator outputs and reports.
- Keep quantum-domain, Lightcore and advanced physical-fabric work explicitly
  staged until conventional simulation and prototype evidence exists.

## Repository engineering

- Require the `Repository Integrity / integrity` check before merging to `main`.
- Disable force pushes and branch deletion on `main`.
- Enable secret scanning and push protection where available.
- Select a long-term licence to replace the interim all-rights-reserved notice.
- Add a machine-readable release/baseline register generated from merged PRs and
  validated commits.
- Keep external plugin workspaces labelled as mirrors, design surfaces or
  execution queues rather than independent canonical brains.

## Runtime and adapters

- Build the local Athena service/API while preserving file-native authority.
- Define Codex, JARVIS, GPT/local-model, research, governance and JANUS adapter
  contracts.
- Add a local operations dashboard driven by generated evidence and reports.
- Implement the Athena ↔ Nexus-V evidence/state bridge.
- Implement bounded R2S proof-of-concept stages on conventional hardware before
  any Lightcore acceleration assumptions.
- Advance L.O.D.E, RoomSense, BodyRig, OASIS and material intelligence through
  simulation and bench validation without promoting R&D hypotheses to verified
  engineering.

## Scoped legacy work

WoW Backup Stack tasks are retained at:

`projects/wow-backup-stack/TODO.md`
