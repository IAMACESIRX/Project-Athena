# Self Correction

Self correction is the process of noticing when the agent, project, or tool output has become unreliable and then repairing the path.

## Triggers

- A scan contradicts handoff.
- A registry points at a missing path.
- A script reports a state that Git disagrees with.
- A live-state doc disagrees with SQL evidence.
- A command failed because the environment has drifted.
- An agent discovers that it assumed a fact without checking.

## Correction Loop

1. Stop expanding scope.
2. Write down the contradiction.
3. Identify the source of truth.
4. Inspect the smallest evidence set that resolves it.
5. Update the wrong doc, registry, script, or issue.
6. Re-run the relevant scan or verification.
7. Record the fix in handoff or changelog.

## Agent Self-Check

Before finalizing a session:

- Did I answer the newest human request?
- Did I avoid cloud pushes?
- Did I update the right layer?
- Did I leave a test, scan, or command result?
- Did I record new context?
