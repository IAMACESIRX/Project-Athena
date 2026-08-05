# Project Athena Work Queue

Updated: 2026-08-05

This is the current repository-wide queue. Project-specific legacy work belongs
under its project brain, not in this root queue.

## Now — Canonicalize and verify

- Review and reconcile PR #5, the JANUS identity and OASIS substrate correction.
- Rebase or reconstruct PR #4 on top of the accepted identity model, then review
  the Reality-to-Simulation and Material Intelligence release.
- Merge the repository-integrity repair and enable branch protection after its
  workflow has produced a successful run.
- Run the complete local Athena operation cycle against the merged baseline.
- Regenerate the system manifest, project map, file index, scan outputs, and
  cycle reports so every generated status record names the validated commit.
- Remove or archive superseded feature branches only after their unique work is
  merged or explicitly rejected.

## Next — Build one executable Athena slice

- Run one real task from structured intake through context resolution, policy
  gate, model/tool routing, execution, independent verification, evidence IDs,
  cycle report, and memory writeback.
- Connect task-intake claims to `forensics/evidence-register.csv`,
  `forensics/claim-catalog.csv`, and `forensics/evidence-claim-map.csv`.
- Add project-profile activation so domain-specific council roles cannot leak
  into unrelated work.
- Convert architecture claims into testable requirements and implementation
  issues rather than adding further untracked specification layers.
- Add a current capability matrix generated from source, tests, and reports.

## Nexus-V verification

- Install and document a canonical SystemVerilog simulator/linter.
- Make `Nexus V/scripts/run_regression.py` invoke real compilation and
  simulation rather than only checking artifact presence.
- Add expected traces, negative tests, assertions, and subsystem coverage.
- Record tool versions and commit SHAs in every Nexus-V verification report.
- Separate source authority, generated vectors, simulator outputs, and reports.

## Repository engineering

- Require repository-integrity CI on pull requests after the first successful
  run.
- Select a long-term licence to replace the interim all-rights-reserved notice.
- Add automated secret scanning in repository settings or a reviewed CI action.
- Configure branch protection for `main`: pull requests, required checks, stale
  approval dismissal, and no force pushes.
- Keep open PR dependencies and merge order in a machine-readable register.

## Later — Runtime and adapters

- Build the local Athena service/API while preserving file-native authority.
- Define Codex, Jarvis, GPT/local-model, research, governance, and JANUS adapter
  contracts.
- Add a local operations dashboard driven by generated reports rather than
  manually asserted status.
- Implement the Athena ↔ Nexus-V evidence/state bridge.
- Advance Lightcore, L.O.D.E, RoomSense, BodyRig, OASIS, and material
  intelligence through simulation and bench validation without promoting R&D
  hypotheses to verified engineering.

## Scoped legacy work

WoW Backup Stack tasks are retained at:

`projects/wow-backup-stack/TODO.md`
