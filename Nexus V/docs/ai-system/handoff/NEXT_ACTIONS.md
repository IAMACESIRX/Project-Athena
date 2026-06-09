# Next Actions

## Immediate

1. Review the generated scan in `ai-system/sensory/scans/latest-scan.json`.
2. Decide whether the game client should remain metadata-only or get a staged partial snapshot.
3. Recreate the Python virtual environment for `WoW-Server-Project`.

## Recommended Near-Term Work

- Recreate the broken Python virtual environment inside `WoW-Server-Project`.
- Add a live-state export playbook that creates dated snapshots without overwriting the current one.
- Add a restore drill checklist and run it against a disposable local database container.
- Add targeted game-client tracking for `WTF`, `Interface`, ReShade config, and realmlist files before considering full MPQ tracking.
- Fix the mismatch between live-state docs saying LAN-ready and the `acore_auth.sql` realmlist row showing localhost.

## Deferred

- Full game client git snapshot.
- Automated server start/stop orchestration.
- AI-driven command execution against the live server.
- Internet-facing access.
