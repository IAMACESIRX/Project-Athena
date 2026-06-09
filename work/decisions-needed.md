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
