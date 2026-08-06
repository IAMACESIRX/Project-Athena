# AIO Contract Authority

`AIO-MASTER-CONTRACT.yml` is the single canonical cross-system contract for Project Athena's interoperating human, AI, software, simulation, compiler and future hardware participants.

## Core rule

One input creates one shared logical contract instance. ATHENA, A.E.S.I.R., F.O.R.G.E., Aegis, Nexus-V, JANUS, JARVIS, OASIS and implementation toolchains read and write authorised portions of that same versioned state.

Pairwise contracts are not independent authorities. Participant-specific contracts or adapter documents are generated projections of the master contract and must retain the canonical contract ID, instance ID, version, state hash and provenance.

## Files

- `AIO-MASTER-CONTRACT.yml` — canonical participants, weights, contract families, pipeline, scale ladder, lenses and compatibility rules.
- `aio-contract-instance.schema.json` — machine validation for live contract instances.
- `aio-master-contract.schema.json` — machine validation for the master contract definition.

## Operating properties

- multi-weighted rather than one-dimensional scoring;
- hard gates cannot be outweighed;
- all pipeline phases remain present at non-zero depth;
- depth, priority, resource use and review intensity are weighted dynamically;
- append-only events preserve historical paths;
- updates require an expected parent SHA-256 or become explicit conflicts/branches;
- human-readable YAML/Markdown and machine-readable JSON represent the same state;
- unknown fields are preserved for forward compatibility;
- AI is preferred for throughput but never required for validity;
- manual intervention, editing, branching, rollback and risk acceptance remain available.

## Single-input pipeline

Use:

```powershell
python tools/aio_contract.py validate-master contracts/AIO-MASTER-CONTRACT.yml
python tools/aio_contract.py instantiate `
  --master contracts/AIO-MASTER-CONTRACT.yml `
  --input standards/human-ai-pipeline/examples/aio-input.example.json `
  --out work/aio-instance.json
python tools/aio_contract.py validate-instance work/aio-instance.json
python tools/aio_contract.py render work/aio-instance.json --out work/aio-instance.md
```

The instantiated pipeline covers full scientific, intra- and cross-scientific, polymath, multiscale, systems, synthesis, engineering, simulation, mitigation, governance, attestation, execution, output and method-revalidation phases.
