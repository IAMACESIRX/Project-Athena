# Module: Server Live State

## Purpose

Preserve restorable game-server state: auth, characters, playerbots, world database, Docker metadata, and restore helpers.

## Layer

`Server-Live-State`

## Current Status

Committed and pushed to local bare remote.

## Important Files

- `acore_auth.sql`
- `acore_characters.sql`
- `acore_playerbots.sql`
- `acore_world.sql`
- `restore-wow-live-state.ps1`
- `restore-checklist.md`
- `restore-bundle.md`
- `server-identity.txt`

## Risks

- Contains private account metadata and password hashes.
- Contains IP addresses and machine-specific restore paths.
- SQL import can overwrite live server state.
- Restore docs and SQL dump currently disagree about realm address state.

## Recommended Handling

- Use dated snapshots for future exports.
- Avoid manual SQL edits unless restoring or redacting.
- Verify restore paths before running scripts.
- Prompt or parameterize database credentials before broader reuse.

## Verification

- Validate required SQL dump files exist.
- Confirm Docker stack target before import.
- Confirm realmlist row after restore.
- Restart auth/world services after import.
