# Order Of Operations

This is the long-line checklist for fully fleshed advanced thinking. Use it for any non-trivial diagnosis, feature, repair, reverse-engineering pass, or multi-agent handoff.

## R00 Authority And Boundary

- Confirm the human's latest request.
- Confirm the active layer: mega, game client, live state, server project, nested source, or AI system.
- Confirm local-only hosting and no GitHub server push.
- Identify private or sensitive files before opening or editing.
- Decide whether a restore point is needed before touching state.

## R01 Context Anchoring

- Read `AI-PORTAL.md`.
- Read `manifests/ingestion-order.yml`.
- Read `handoff/CURRENT_STATE.md`.
- Read `handoff/NEXT_ACTIONS.md`.
- Read `governance/absolutes.md`.
- Refresh contextual anchors if the task crosses sessions, modules, or assumptions.

## R02 Sensory Observation

- Run the project scan.
- Export the project map.
- Export the generated AI index.
- Inspect the relevant child repo status.
- Check latest live probe if runtime state matters.
- Check recent log intelligence if a failure is involved.

## R03 Forensic Evidence Discipline

- Assign or reuse stable evidence IDs for files, reports, logs, commands, screenshots, dumps, commits, and observations.
- Verify evidence paths resolve.
- Check for duplicate evidence IDs.
- Check hashes for fixed evidence when hashes are recorded.
- Link evidence to claims in `forensics/evidence-claim-map.csv`.
- Keep unknowns in `forensics/known-unknowns.csv` instead of burying them in prose.

## R04 Problem Framing

- State the problem in one sentence.
- State what is known.
- State what is assumed.
- State what is unknown.
- State what would change your mind.
- Identify the smallest reversible action that could reduce uncertainty.

## R05 Truth And Anti-Hallucination Gate

- Label each claim as observed, inferred, reported, assumed, stale, contradicted, or unknown.
- Reject claims with no evidence anchor.
- Use fuzzy truth values where binary true/false would be fake precision.
- Hold competing interpretations in superposition until evidence collapses them.
- Preserve uncertainty labels in handoffs and decisions.

## R06 Hypergraph Relational Mapping

- Map many-way relationships between file, module, command, config, log, commit, decision, actor, and outcome.
- Record high-value edges in the hypergraph ledger.
- Identify which modules could be affected by the proposed change.
- Identify second-order effects and rollback dependencies.

## R07 Diagnostic Intelligence

- Scan logs for fatal, error, auth, database, worldserver, bot, Docker, SQL, file path, and permission signatures.
- Check watched-state drift.
- Check for broken local tools, missing venvs, and stale generated files.
- Convert resolvable findings into correction-queue or work-item entries.

## R08 Council And Cognitive Pass

- Run Who, What, When, Where, Why, How.
- Run Socratic deconstruction on assumptions.
- Run algorithmic inversion from desired end state back to required conditions.
- Run counterfactuals: what if the obvious cause is false?
- Run correlation without claiming causation.
- Run non-monotonic revision: what prior conclusion should be weakened?
- Run semantic compression: what must survive handoff?

## R08M Mitigation And Offset Pass

- Identify weaknesses, negative pressures, and failure modes exposed by the cognitive pass.
- Identify the useful capability, strength, speed, plasticity, exploration, continuity, or other benefit associated with each weakness.
- Prefer offsets, boundaries, staging, reversible controls, parallel paths, dynamic configuration, and compiler displacement over suppressing the value-bearing mechanism.
- For every mitigation, state the activation trigger, execution modes, trade-offs, new risks, manual verification, machine verification, review condition, and removal condition.
- Record explicit risk acceptance when a weakness is not mitigated.
- Preserve human intervention paths: pause, edit, override, branch, reject, rollback, change mode, change mitigation, request evidence, and request review.
- Treat every control as plastic and subject to later challenge.

## R09 Decision Gate

- Pick the action only after evidence, risk, rollback, mitigation, preserved benefits, and verification are named.
- If the action changes live state, create or confirm a restore path first.
- If the action changes process, update engine or governance docs in the same pass.
- If the action changes code, use the repo's existing patterns.
- If the action changes generated state, commit generated files separately when useful.

## R10 Execution

- Edit only the selected layer.
- Keep changes scoped.
- Preserve unrelated user changes.
- Record commands that prove what happened.
- Do not hide failures.

## R11 Verification

- Run the smallest relevant verification first.
- Run the operation cycle or targeted sub-tools after broader changes.
- Re-check git status.
- Re-check local-only remotes before any push.
- Update evidence and claim maps if new facts were created.
- Verify that active mitigations reduced the named weakness without silently removing the named benefit.

## R12 Audit And Continuity

- Add an audit event for meaningful changes.
- Update changelog or handoff.
- Update lessons learned when a repeated failure or pattern appears.
- Strengthen important concepts in memory.
- Record mitigation performance, interventions, trade-offs, and revalidation triggers.
- Prune low-value noise from active context while preserving archive access.

## R13 End State

- Leave the repo with understandable status.
- Name remaining warnings.
- Name what was committed and where.
- Name what was not pushed to cloud.
- Leave next actions concrete.
