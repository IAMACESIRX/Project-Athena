# Repository Baseline and Reconciliation Register

Generated: 2026-08-05  
Audited base: `main@de3ddd00ab72d394b3d9fc549b72ae38b8d4b469`

## Canonicality rule

- `main` is the current merged operating baseline.
- An open feature branch is proposed work, not canonical truth.
- `Plan/` is architecture intent, but implementation claims require source,
  tests, and current reports.
- A generated report validates only the source state and commit it names.

## Open architecture releases at the audited base

| Order | Change | Branch / PR | Required treatment |
|---:|---|---|---|
| 1 | Independent JANUS identity and corrected OASIS substrate | PR #5 | Resolve identity and authority first. |
| 2 | Reality-to-Simulation and Material Intelligence | PR #4 | Reconcile on top of the accepted identity model. |
| 3 | Repository integrity and legacy scoping | `agent/repository-integrity-reconciliation` | Merge independently unless review finds conflicts. |

## Supersession rules

- `agent/reality-to-simulation-material-intelligence` is an earlier R2S branch.
  Preserve it until PR #4 is confirmed to contain every unique required change,
  then archive or delete it.
- `assets/full-system-visual-atlas-2026-08-05` has already supplied merged work.
  Confirm no unique unmerged commits remain before deletion.
- Do not delete a branch solely because it is behind `main`.

## Verification debt

The committed Athena operation-cycle report predates the August architecture
changes. Nexus-V reports also state that SystemVerilog simulation was not run.
After the architecture PRs are reconciled:

1. run the full local Athena operation cycle;
2. run repository-integrity CI;
3. run Nexus-V lint, compile, and simulation using a documented toolchain;
4. regenerate reports with the exact commit SHA and tool versions;
5. publish only sanitized reports allowed by the cloud publication policy.

## Repository settings still required

Repository settings are not stored in this tree. After the integrity workflow
passes, enable protection for `main` with:

- pull requests required;
- repository-integrity check required;
- force pushes disabled;
- branch deletion disabled;
- stale approvals dismissed after new commits;
- conversation resolution required where available;
- secret scanning and push protection enabled where available.
