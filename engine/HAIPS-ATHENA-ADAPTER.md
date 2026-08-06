# ATHENA Human–AI Pipeline Adapter

ATHENA uses the project-wide Human–AI Interoperable Pipeline Standard through:

- profile: `standards/human-ai-pipeline/profiles/athena.yml`;
- manual intake: `templates/athena-task-intake.md`;
- domain process: `engine/order-of-operations.md`;
- shared run tooling: `tools/human_ai_pipeline.py`;
- governance and writeback: ATHENA's existing evidence, audit, restore, cycle and memory systems.

## Mitigation insertion point

After council/cognitive analysis and before the decision gate, ATHENA must record:

1. weaknesses or negative pressures;
2. the benefits associated with those same mechanisms;
3. controls or offsets;
4. trade-offs and new risks introduced by the controls;
5. manual and machine verification;
6. review and removal conditions.

This is represented as stage `R08M` in the shared ATHENA profile.

## Manual equivalence

A person can execute the entire cycle by completing the task-intake template, weakness/mitigation registers, intervention log, verification steps and cycle report. Scripts and AI accelerate this work but do not own its validity.
