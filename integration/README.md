# Integration

This folder defines how any AI, human, program, script, or external software should plug into the project.

## Integration Levels

1. Read-only consumer: reads manifest, registries, maps, scans, and work files.
2. Diagnostic tool: reads project state and writes reports.
3. Work tool: creates work items, handoffs, or generated maps.
4. Editor: changes project files under governance.
5. Runtime operator: reads or changes live server/client state under strict policy.

## Minimum Contract

Any integration must:

- identify itself,
- declare read/write scope,
- declare whether it can mutate live state,
- log outputs,
- respect local-only Git hosting,
- update handoff or work records when it changes important state.
