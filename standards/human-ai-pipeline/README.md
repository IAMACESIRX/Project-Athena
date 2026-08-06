# Human–AI Interoperable Pipeline

This folder contains the project-wide execution standard shared by ATHENA, A.E.S.I.R., F.O.R.G.E., Aegis, Nexus‑V and future systems.

## Contract authority

The single canonical contract is `contracts/AIO-MASTER-CONTRACT.yml`. Profiles and subsystem adapters are generated or specialised views of that shared contract; they do not form independent pairwise authorities.

## Read order

1. `../../contracts/AIO-MASTER-CONTRACT.yml`
2. `AIO-UNIFIED-PIPELINE.md`
3. `STANDARD-v0.1.md`
4. `ONBOARDING.md`
5. `MITIGATION-OFFSET-FRAMEWORK.md`
6. `INTERVENTION-PROTOCOL.md`
7. the relevant generated/specialised profile under `profiles/`
8. `templates/manual-run-packet.md`

## Canonical implementation

- Master contract: `contracts/AIO-MASTER-CONTRACT.yml`.
- Shared contract CLI: `tools/aio_contract.py`.
- Open human format: Markdown.
- Open machine formats: JSON and YAML.
- Contract instance schema: `contracts/aio-contract-instance.schema.json`.
- Legacy/shared run tooling: `tools/human_ai_pipeline.py` and `run-packet.schema.json`.

## Operating modes

Manual, AI-assisted, automated and hybrid operators all use the same logical AIO instance. Every input traverses all required phases; weights change depth, priority and resource allocation rather than removing perspectives.
