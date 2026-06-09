# Contextual Work IQ

Contextual Work IQ is the system's ability to understand what work means inside a project, not just what words mean in a prompt.

## Inputs

- current user request,
- project brain,
- repo map,
- git state,
- file ownership,
- active task state,
- recent chat/handoff,
- source ledger,
- evidence register,
- model/tool capability registry,
- local constraints and absolutes.

## Outputs

- task interpretation,
- relevant files and modules,
- risk level,
- needed tools,
- model routing mode,
- memory reads,
- verification plan,
- rollback plan,
- handoff summary.

## Context Classes

- immediate: current turn, visible files, active command output;
- working: current task plan, edits, tests, open warnings;
- project: stable architecture, modules, decisions, known issues;
- institutional: policies, standards, evaluation rubrics, model knowledge;
- cold: archived chats, old logs, prior reports, rarely used but searchable.

## Work IQ Loop

1. Anchor to user goal and current date.
2. Load only relevant project memory.
3. Check current local state before assuming.
4. Pick model/tool route by task type.
5. Preserve evidence for every important claim.
6. Compress useful outcomes into memory.
7. Prune repeated or low-value noise.

## Failure Modes

- stale context masquerading as current state,
- overloading the model with raw logs instead of summaries,
- treating unverified web claims as facts,
- losing user constraints after handoff,
- repeating old work because no memory key exists,
- making changes without a rollback path.
