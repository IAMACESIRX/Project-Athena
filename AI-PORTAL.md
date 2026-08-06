# AI Portal

This is the universal entry point for any AI model, team member, program, script or software agent that needs to understand or operate Project Athena.

## Identity

Project name: Project Athena

Primary goal: create a local-first institutional-intelligence and prosthetic external-brain system that preserves context, organizes knowledge, routes instructions, processes goals, coordinates AI and human work, audits evidence and safely expands capability over time.

Project Athena is part of a wider system-of-systems. Do not collapse the independent entities into one brain.

```text
ATHENA = independent institutional intelligence
JARVIS = independent personal/executive intelligence
JANUS  = independent operative metacognitive intelligence
F.O.R.G.E. = independent cognitive-synthesis and native-reconstruction system
A.E.S.I.R. = Adaptive Evolutionary System for Intelligent Research
OASIS  = persistent digital reality, simulation and creation substrate; not an AI
```

F.O.R.G.E. complements A.E.S.I.R. and ATHENA. A.E.S.I.R. expands evidence and candidate space; F.O.R.G.E. challenges, compares, mines mechanisms, reverse-reconstructs and compiles functional snapshots; ATHENA preserves and governs the lineage.

ATHENA, A.E.S.I.R. and F.O.R.G.E. share one project-wide human–AI implementation contract under `standards/human-ai-pipeline/`. Every pipeline must remain usable manually, through AI assistance, through scripts/automation, or through a hybrid path with explicit intervention and preserved history.

## Mandatory identity correction

Read before using older OASIS/agent material:

1. `docs/athena-master-expansion/SYSTEM_IDENTITY_AND_AUTHORITY_CORRECTION_2026-08-05.md`
2. `docs/athena-master-expansion/ATHENA_FULL_SYSTEM_MAP.md`
3. `docs/athena-master-expansion/JANUS_OPERATIVE_METACOGNITIVE_AI_MASTER_SPEC.md`
4. `docs/athena-master-expansion/OASIS_ARCHITECTURE_SPEC.md`
5. `Plan/OASIS_ATHENA_AGENT_MODEL.md`

## First read

1. `context.md`
2. `Plan/context.md`
3. `manifests/system-manifest.json`
4. `manifests/ingestion-order.yml`
5. `identity/constitution.md`
6. `projects/project-registry.yml`
7. `standards/human-ai-pipeline/STANDARD-v0.1.md`
8. `standards/human-ai-pipeline/ONBOARDING.md`
9. `aesir/AESIR-PORTAL.md`
10. `aesir/manifest.yml`
11. `forge/FORGE-PORTAL.md`
12. `forge/manifest.yml`
13. `governance/absolutes.md`
14. `engine/order-of-operations.md`
15. `engine/HAIPS-ATHENA-ADAPTER.md`
16. `cognition/cognition-workflow.md`
17. `council/roles.yml`
18. `forensics/evidence-register.csv`
19. `forensics/claim-catalog.csv`
20. `forensics/evidence-claim-map.csv`

## First run

```powershell
powershell -NoProfile -ExecutionPolicy Bypass -File .\tools\Invoke-AIProjectScan.ps1
powershell -NoProfile -ExecutionPolicy Bypass -File .\tools\Export-AISystemManifest.ps1
powershell -NoProfile -ExecutionPolicy Bypass -File .\tools\Invoke-AIOperationCycle.ps1 -SkipLiveProbe
```

For a shared human/AI pipeline run:

```powershell
python .\tools\human_ai_pipeline.py new --profile .\standards\human-ai-pipeline\profiles\athena.yml --goal "Describe the task" --mode hybrid --out .\work\athena-run.json
python .\tools\human_ai_pipeline.py validate .\work\athena-run.json
python .\tools\human_ai_pipeline.py render .\work\athena-run.json --out .\work\athena-run.md
```

Use the A.E.S.I.R. or F.O.R.G.E. profile to run the same interface around those pipelines.

## How to think about this system

### ATHENA and this repository

- The repository is ATHENA's durable project/institutional substrate and source of truth.
- ATHENA handles institutional memory, evidence, governance, project brains, ontology, cognitive routing and long-horizon coordination.
- `Plan/` is the design authority.
- `Nexus V/` is the semantic execution/toolchain implementation branch.
- `aesir/` is the independent polymath research and discovery subsystem.
- `forge/` is the independent cognitive-synthesis and reconstruction subsystem.
- `standards/human-ai-pipeline/` is the shared manual/AI/automation/hybrid implementation layer.

### Shared human–AI pipeline

- Every profile exposes a human entry point, AI entry point, machine manifest, pipeline, manual template, intervention path and validation route.
- AI is favoured for throughput but is never mandatory for methodological validity.
- Human-readable Markdown and machine-readable JSON/YAML are equivalent views of one run.
- Weakness controls must preserve named benefits, declare trade-offs and new risks, and remain reviewable and removable.
- Manual edits and interventions are versioned rather than overwritten.

### F.O.R.G.E. and A.E.S.I.R.

- A.E.S.I.R. performs adaptive polymath research, source discovery, cross-domain exploration, hypothesis generation and evidence gathering.
- F.O.R.G.E. performs intent anchoring, epistemic partition, analogy, first-principles reduction, symmetric challenge, mitigation and offset design, counterfactual branching, candidate tournaments, mechanism mining, reverse reconstruction, simplification and functional-snapshot compilation.
- Outputs remain provisional until evidence, simulation/prototypes, ATHENA governance and human approval support promotion.

## Capability posture

Use only these labels: implemented, scaffolded, specified, conceptual, speculative, blocked, or validated for a named use.

Never treat documentation, compiler scaffolds, generated diagrams, simulations or AI-assisted drafts as proven implementation without evidence.

## Cross-system request rule

Every request between ATHENA, JARVIS, JANUS, F.O.R.G.E., A.E.S.I.R., OASIS runtime services or external tools should carry:

- requester identity;
- objective;
- context/evidence references;
- authority requested;
- privacy class;
- expected state diff;
- validation criteria;
- rollback or escalation requirements;
- execution mode;
- benefits to preserve;
- active mitigations and intervention checkpoints.

## Non-negotiable

The human is the ultimate authority. Cloud/GitHub publication requires explicit human authorization and sanitization.
