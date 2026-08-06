# Human–AI Interoperable Pipeline

This folder contains the project-wide execution standard shared by ATHENA, A.E.S.I.R., F.O.R.G.E. and future systems.

## Read order

1. `STANDARD-v0.1.md`
2. `ONBOARDING.md`
3. `MITIGATION-OFFSET-FRAMEWORK.md`
4. `INTERVENTION-PROTOCOL.md`
5. the relevant profile under `profiles/`
6. `templates/manual-run-packet.md`

## Canonical implementation

- Open human format: Markdown.
- Open machine formats: JSON and YAML.
- Shared command-line interface: `tools/human_ai_pipeline.py`.
- Canonical run schema: `run-packet.schema.json`.
- Profile schema: `profile.schema.json`.

## System profiles

- `profiles/athena.yml`
- `profiles/aesir.yml`
- `profiles/forge.yml`

Each profile exposes manual, AI-assisted, automated and hybrid operation using the same state model.
