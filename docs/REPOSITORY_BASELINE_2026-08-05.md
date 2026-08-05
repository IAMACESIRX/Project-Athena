# Repository Baseline and Reconciliation Register

Generated: 2026-08-05  
Original audited base: `main@de3ddd00ab72d394b3d9fc549b72ae38b8d4b469`  
Reconciled architecture baseline: `main@cc8da6b42cb871afad121ab5bf104428137615ea`

## Canonicality rule

- `main` is the current merged operating baseline.
- An open or retained feature branch is proposed or historical work, not
  canonical truth.
- `Plan/` defines architecture intent, but implementation claims require source,
  tests and current reports.
- A generated report validates only the exact source state, commit, environment
  and tool versions it names.
- External plugin workspaces are mirrors, design surfaces or execution queues
  unless an explicit governance record says otherwise.

## Reconciliation results

| Order | Change | Resolution | Canonical commit |
|---:|---|---|---|
| 1 | Repository integrity, publication controls and legacy-project scoping | PR #7 merged | `42c671e4f5800ce83e1dca15b1c9bce976896c5a` |
| 2 | Independent JANUS identity and corrected OASIS substrate | Divergent PR #5 superseded by PR #8; PR #8 merged | `2ce3d135df2b1e0a8524a3dac80e02892757f849` |
| 3 | Reality-to-Simulation and Material Intelligence | Divergent PR #4 superseded by PR #9; PR #9 merged | `cc8da6b42cb871afad121ab5bf104428137615ea` |

## Canonical identity model

```text
ATHENA = independent institutional intelligence
JARVIS = independent personal/executive intelligence
JANUS  = independent operative metacognitive intelligence
OASIS  = non-AI persistent digital reality, simulation and creation substrate
```

Reality-to-Simulation is an evidence-producing sensing and physical-twin
compilation track. It feeds ATHENA, JANUS, OASIS, Nexus-V/Aegis, L.O.D.E and
RoomSense; it is not a universal detector or an independent governing identity.

## Verified repository state

Repository Integrity passed on the repository-governance repair, the JANUS/OASIS
replacement, the R2S replacement and their resulting `main` commits. The
workflow verifies:

- required repository paths;
- JSON parsing;
- Draft 2020-12 JSON Schema validity;
- YAML parsing;
- forensic CSV headers;
- canonical path references;
- publication-policy consistency;
- Python compilation;
- PowerShell parsing.

This proves repository structural integrity for those commits. It does not prove
that Athena is a complete autonomous runtime, that JANUS or OASIS is implemented,
that the R2S hardware stack is calibrated, or that Nexus-V RTL is functionally
correct.

## Superseded branches

Retain branches until unique-work comparison is complete. Current provenance
branches include:

- `agent/janus-independent-operative-ai-correction` — superseded by PR #8;
- `agent/r2s-material-intelligence-release` — superseded by PR #9;
- `agent/reality-to-simulation-material-intelligence` — earlier R2S branch;
- `assets/full-system-visual-atlas-2026-08-05` — merged visual-atlas source;
- temporary reconciliation branches used for PRs #7, #8 and #9.

Do not delete a branch solely because it is behind `main`. Compare unique commits
or files first, then archive or delete only after provenance is preserved.

## Remaining verification debt

1. Run the full local Athena operation cycle against the reconciled baseline.
2. Regenerate manifests, indexes, scans and reports with the exact commit SHA and
   tool versions.
3. Install a canonical SystemVerilog simulator/linter.
4. Run Nexus-V lint, compilation, simulation, assertions and regression tests.
5. Validate JANUS and OASIS through bounded conventional-software prototypes.
6. Validate R2S through selected sensors, traceable calibration, synchronized
   capture and bounded physical campaigns.
7. Keep Lightcore, advanced L.O.D.E hardware and other physical concepts staged
   until simulation, bench testing and specialist review support them.

## GitHub repository settings verification

Verified through the signed-in GitHub UI on 2026-08-05.

### `main` branch protection

- Branch protection rule `main` applies to 1 branch.
- Pull requests are required before merging.
- Required status checks are enabled.
- Required check: `integrity`, provided by GitHub Actions.
- Branches must be up to date before merging.
- Conversation resolution is required before merging.
- Administrators are included in enforcement, leaving no routine bypass path.
- Force pushes are disabled.
- Branch deletion is disabled.

Approving reviews are not currently required. Because this is a solo-owner
repository and administrators are included in enforcement, enabling required
approvals would likely block owner-authored maintenance PRs. Stale approval
dismissal is therefore not active or meaningful until an additional reviewer is
added.

### Security features

- Private vulnerability reporting is enabled.
- Dependency graph is enabled.
- Dependabot alerts are enabled.
- Dependabot malware alerts are enabled.
- Dependabot security updates are enabled.
- Grouped security updates are enabled.
- CodeQL default setup is enabled.
- Secret scanning is enabled.
- Push protection is enabled.

Security alert review on 2026-08-05:

- Dependabot alerts: 0 open, 0 closed.
- Secret scanning alerts: 0 open, 0 closed.
- Code scanning alerts: 2 open before this baseline update, both reported by
  CodeQL in `tools/validate_repository.py`:
  - alert #1: clear-text storage of sensitive information at line 118;
  - alert #2: clear-text logging of sensitive information at line 434.
- The CodeQL findings were traced to the repository validator persisting and
  logging diagnostics that can be derived from credential-pattern matches. The
  validator now withholds secret-derived line details and no longer persists or
  prints detailed diagnostics in CI artifacts or logs. Credential-pattern
  matches still fail the integrity check; the persisted report records status
  and diagnostic counts only.
- Tracked hygiene review removed generated `__pycache__` bytecode and
  `latest-integrity-report.*` outputs that contained absolute local paths.
  `.gitignore` blocks those generated report files going forward.

### Verification limits

No deliberately failing pull request was opened, and no direct commit was pushed
to `main` as a negative branch-protection test. Those tests would create
publicly visible noise or intentionally invalid repository history. Enforcement
was verified from the live branch protection rule, and recent maintenance merges
used the protected PR path with the required `integrity` check.

## Rights and publication

The repository currently uses an interim all-rights-reserved notice. Select a
long-term licence through an explicit reviewed decision. Until then, follow
`governance/cloud-publication-policy.md`: publication is default-deny, scoped to
the explicitly authorized files, sanitized, and never standing permission to
publish private memory, credentials, local runtime state or third-party material
without licence review.
