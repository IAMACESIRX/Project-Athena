# Reconciliation Protocol

Use when two sources disagree.

## Source Priority

1. Direct live system observation.
2. Current working tree and Git state.
3. Generated scans.
4. Registries.
5. Handoff.
6. Older docs.
7. Memory notes.

## Process

1. Name the disagreement.
2. Gather evidence from the highest available source.
3. Update stale records.
4. Re-run scan or verification.
5. Record decision if the choice is non-obvious.

## Example

If `restore-bundle.md` says the realm is LAN-ready but `acore_auth.sql` says `127.0.0.1`, SQL is stronger evidence for what the dump will restore. The docs or restore script must then be updated.
