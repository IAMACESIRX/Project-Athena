# Windows Agent Platform

This is the local operating layer for active computer work. It lets an AI use Windows as a controlled agent platform without turning local automation into chaos.

## Capability Targets

- inspect files, folders, git status, logs, and app state;
- read screenshots and UI state through visual tools when available;
- edit files with tracked diffs;
- operate browsers and local apps through approved tools;
- run background work with checkpoints;
- attach localized annotations to code, docs, images, and UI regions;
- recover through restore points, git, backups, and audit logs.

## Permission Classes

- read-only observation: file reads, status checks, screenshots, logs;
- reversible local edit: text patches, generated reports, staged diffs;
- operational action: starting dev servers, running tests, probing services;
- risky mutation: deletes, moves, live server changes, credentials, network publication;
- forbidden by default: cloud push, destructive reset, secret exposure, unlicensed model/data use.

## Agent Loop

1. Observe current local state.
2. Identify goal, risk, and required tools.
3. Create or update task state.
4. Execute the smallest reversible step.
5. Verify result.
6. Record observation, decision, and artifact.
7. Continue, escalate, or stop.

## Localized Editing

For code:

- attach file path and line number;
- keep changes scoped;
- run related checks;
- explain exact behavior changed.

For visual/UI work:

- attach screenshot path or browser target;
- identify region, element, and expected change;
- verify with a second screenshot or pixel/state check.

For documents/data:

- attach sheet range, page, section, or field;
- preserve source references;
- validate formulas, schemas, or rendered output.
