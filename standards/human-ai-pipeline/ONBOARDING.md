# Human and AI Onboarding

## Start manually

1. Choose a profile: ATHENA, A.E.S.I.R., or F.O.R.G.E.
2. Copy `templates/manual-run-packet.md` or run the command-line `new` command.
3. Write the objective and the benefits that must survive the work.
4. Work through each stage in order or mark why a stage is skipped.
5. Record weaknesses as they appear.
6. Add mitigations before a weakness can be treated as controlled.
7. Pause or branch at any intervention checkpoint.
8. Perform the listed manual checks.
9. Render or write the final human-readable report.
10. Route evidence and decisions to ATHENA when the run affects canonical project state.

## Start with the command-line tool

```text
python tools/human_ai_pipeline.py new \
  --profile standards/human-ai-pipeline/profiles/aesir.yml \
  --goal "Research the target problem" \
  --mode hybrid \
  --out work/example-aesir-run.json

python tools/human_ai_pipeline.py validate work/example-aesir-run.json
python tools/human_ai_pipeline.py render work/example-aesir-run.json --out work/example-aesir-run.md
```

## Execution modes

- `manual`: humans fill the same fields directly.
- `ai_assisted`: AI proposes content; humans review and edit.
- `automated`: scripts populate stages and evidence.
- `hybrid`: any stage may move between humans, AI, and scripts.

## Intervention actions

At an intervention checkpoint an authorised operator may:

- pause;
- edit fields;
- change mode;
- branch the run;
- reject an output;
- request another council or evidence pass;
- modify a mitigation;
- roll back to a recorded state;
- resume with a written reason.

## Accessibility principle

The Markdown template is the lowest common denominator. JSON/YAML and scripts increase throughput, but they do not own the methodology.
