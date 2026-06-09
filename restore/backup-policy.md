# Backup Policy

## Default

Use local Git commits and local bare remotes for regular project state.

## Restore Points

Create restore points before:

- live-state import/export,
- restore script edits,
- client config changes,
- AI system tool changes,
- command hub execution module work,
- nested repo updates.

## Full Payload Backup

The game client payload needs a separate storage plan.

Do not pretend a Git restore point protects files that are untracked.

## Backup Verification

A backup is not trusted until:

- it has a manifest,
- it names what is included and excluded,
- it can be located later,
- and at least one restore path is documented.
