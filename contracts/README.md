# AIO Unified Contract System

`AIO-MASTER-CONTRACT.yml` is the single canonical contract definition for ATHENA, A.E.S.I.R., F.O.R.G.E., Aegis, Nexus‑V and future participants.

## Operating rule

One idea or task creates one AIO contract instance. Every authorised human, AI, script, compiler, simulator or hardware gate reads and writes that same logical state. Pairwise contracts are not independent authorities; any subsystem-specific contract is a generated view of the master instance.

## Why

This prevents circular ingestion, semantic drift and duplicated state. It also maps cleanly to future packet, register, memory-map and NVIR representations.

## Contract mechanics

- Append-only events plus a materialised current state.
- Atomic writes using `expected_parent_sha256`.
- Unknown fields are preserved for forward compatibility.
- Human-readable JSON/YAML remains the manual fallback.
- AI and automation are preferred accelerators, not dependencies.
- All 21 pipeline phases run for every input. Weights change depth and resource allocation, never phase presence.
- Hard gates for authority, truth, safety, privacy, provenance, rollback, mitigation and Aegis attestation cannot be outweighed.

## CLI

```text
python tools/aio_contract.py validate-master contracts/AIO-MASTER-CONTRACT.yml
python tools/aio_contract.py instantiate --master contracts/AIO-MASTER-CONTRACT.yml --input standards/human-ai-pipeline/examples/aio-input.example.json --out work/aio/example.json
python tools/aio_contract.py validate-instance work/aio/example.json --master contracts/AIO-MASTER-CONTRACT.yml
python tools/aio_contract.py render work/aio/example.json --out work/aio/example.md
```
