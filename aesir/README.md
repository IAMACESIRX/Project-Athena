# A.E.S.I.R. Polymath Research Engine

A.E.S.I.R. operationalises cross-domain, first-principles, analogical, adversarial, counterfactual, simulation-oriented and evolutionary research.

## System role

```text
A.E.S.I.R. → discovers evidence, mechanisms, hypotheses and tests
F.O.R.G.E. → compares, mines, reconstructs and simplifies architectures
ATHENA     → governs, remembers, verifies and preserves lineage
```

## Manual use

Copy `aesir/templates/research-cycle.md` and complete the stages directly. No AI or script is required.

## Tool-assisted use

```text
python tools/human_ai_pipeline.py new \
  --profile standards/human-ai-pipeline/profiles/aesir.yml \
  --goal "State the research question" \
  --mode hybrid \
  --out work/aesir-run.json

python tools/human_ai_pipeline.py validate work/aesir-run.json
python tools/human_ai_pipeline.py render work/aesir-run.json --out work/aesir-run.md
```

## Canonical files

- `aesir/AESIR-PORTAL.md`
- `aesir/manifest.yml`
- `aesir/engine/pipeline.yml`
- `aesir/templates/research-cycle.md`
- `standards/human-ai-pipeline/profiles/aesir.yml`
