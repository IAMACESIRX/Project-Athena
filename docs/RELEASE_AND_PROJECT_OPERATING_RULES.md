# Release And GitHub Project Operating Rules

These rules make public collaboration predictable without replacing Project Athena's repository, GitHub Project, issues, pull requests, discussions, or Wiki.

## Source Of Truth

- Repository files on `main` are canonical after reviewed merge.
- The GitHub Project is the live planning surface for issue state and prioritization.
- Issues define bounded work.
- Pull requests prove and review changes.
- Discussions hold exploratory material until it becomes tracked work.
- The Wiki is an orientation index only.

## Issue Routing

Use GitHub issue forms for new work:

- Architecture work: identity, Plan, schemas, system maps, capability state, and cross-system contracts.
- Implementation work: tools, runtime, adapters, CI, tests, fixtures, and source changes.
- Research or R&D work: hypotheses, experiments, simulations, evidence gathering, physical R&D, and validation planning.
- Governance or publication work: authority, privacy, settings, security, release, publication, and GitHub operating changes.

Blank issues are disabled. Use Discussions for ideas that are not ready for tracked work.

## GitHub Project Fields

The desired project fields are:

- Status: Intake, Ready, In Progress, In Review, Blocked, Done.
- Priority: P0, P1, P2, P3.
- Type: architecture, implementation, research, governance, documentation, security, CI, release.
- Area: governance, GitHub, agents, cognition, continuity, Nexus-V, OASIS, R2S, Lightcore, L.O.D.E, runtime, docs.
- Milestone: matching the active GitHub milestone.
- Capability state: implemented, verified, specified, conceptual, speculative, scaffolded, blocked, validated for a named use.
- Evidence state: direct, derived, inferred, reported, provisional, stale, contradicted, needs test.
- Publication class: public architecture/documentation, public source code, sanitized generated report, private/local-only state, third-party material requiring licence review.
- Owner/system: ATHENA, JARVIS, JANUS, OASIS, Nexus-V/Aegis, Lightcore, L.O.D.E, RoomSense, BodyRig, R2S, repository.

## GitHub Project Views

The desired views are:

- Triage: new unclassified issues.
- Current milestone: ready and active work grouped by status.
- Governance and security: publication, branch protection, secret scanning, policy, and settings work.
- Runtime and adapters: ATHENA, JARVIS, JANUS, local model, Codex, API, and tool integration work.
- Nexus-V and physical R&D: Nexus-V, Aegis, Lightcore, L.O.D.E, RoomSense, BodyRig, and hardware validation work.
- Research and evidence: R2S, OASIS, experiments, validation, claims, and provenance work.
- Blocked: work waiting on human decision, missing toolchain, missing evidence, or external dependency.
- Done/archive: completed work retained for traceability.

## Release Note Categories

Every release or release-like milestone note should separate:

- Implemented: source behavior, tools, schemas, workflows, or docs merged to `main`.
- Verified: behavior proven by named commands, reports, checks, or live settings inspection.
- Specified: architecture or design intent without implementation proof.
- Experimental: research, R&D, prototype, or bounded validation work.
- Security and publication: branch protection, secret scanning, policy, ignored local-only paths, and review gates.
- Known gaps: missing toolchains, skipped validation, unresolved licensing, stale context, or unproven claims.

Do not describe specified, conceptual, speculative, or generated material as working runtime or certified hardware.

## Required Checks

Before merge:

- Repository integrity validation must pass.
- Relevant Python and PowerShell parsing checks must pass or skipped checks must be recorded.
- Publication gate requirements from `governance/publication-gate.yml` must apply.
- Pull requests must classify publication state and evidence posture.
- Sensitive local-only paths must remain ignored or excluded.
- Claims need evidence links, labels, or explicit unknowns.

## Release Checklist

Use this checklist for release notes, milestone closeout, or public mirror updates:

- [ ] Scope and publication target are explicit.
- [ ] Release notes use the categories above.
- [ ] Implemented, verified, specified, and experimental items are separated.
- [ ] Required checks passed or skipped checks are recorded.
- [ ] Private/local-only state, credentials, account exports, raw private chats, and unsanitized logs are excluded.
- [ ] Third-party material has licence review or is excluded.
- [ ] Related issues, PRs, reports, and evidence records are linked.
- [ ] Remaining gaps are linked to follow-up issues.
