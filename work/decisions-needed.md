# Decisions Needed

## DECIDE-001: Game Client Git Strategy

Options:

- config-only tracking,
- Git LFS for selected binaries,
- external filesystem mirror,
- full Git snapshot on larger disk.

## DECIDE-002: Local Mirror Target

Should the local bare host be mirrored to another drive?

## DECIDE-003: AI Runtime Permission Level

Which live server actions may AI perform without confirmation?

Suggested initial answer: read-only inspection only.

## DECIDE-004: Restore Address Default

Should restore default to local, LAN, or prompt each time?

## DECIDE-005: Operative Duplex Name

Confirm `Operative Duplex`, choose `JANUS`, or define another independent system
name before implementation creates identity-bearing artifacts.

## DECIDE-006: GitHub Project Token

Project Athena's bounded workflow and planning reconciliation is authorized for
the current task. A user-level GitHub Project may require a narrowly scoped
token because repository workflow tokens do not automatically control personal
Projects. Do not create or store one until the human approves the exact scope.

## Resolved: GitHub Planning Exception

On 2026-08-01 the human authorized Project Athena workflow files, milestones,
issues, Projects, and planning metadata for this reconciliation. The general
local-only default remains active outside that scope.
