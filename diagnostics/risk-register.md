# Risk Register

## R-001: Game Client Payload Not Fully Committed

Severity: Medium

The game client repo is initialized but the full payload is untracked. This is intentional because the payload is very large and disk free space is limited.

Mitigation: Use targeted client tracking first. Revisit full snapshot only when storage strategy is clear.

## R-002: Live-State SQL Is Sensitive

Severity: High

The live-state repo contains auth, characters, playerbots, and world SQL dumps.

Mitigation: Local-only hosting. No cloud push. Avoid sharing.

## R-003: Broken Python Virtual Environment

Severity: Medium

`WoW-Server-Project/.venv` points to an old machine path and cannot run here.

Mitigation: Recreate venv locally and reinstall `backend/requirements.txt`.

## R-004: Realm Address Mismatch

Severity: Medium

Live-state metadata says LAN-friendly, but `acore_auth.sql` realmlist row appears to advertise `127.0.0.1`.

Mitigation: Add restore step to set realm address after import.

## R-005: Local Bare Host Is Not Off-Machine Backup

Severity: Medium

The local bare repos provide hosted local remotes, not disaster recovery from disk failure.

Mitigation: Later mirror the local host folder to another local disk.

## R-006: Nested Repos Can Drift

Severity: Medium

The server project tracks nested source repos as embedded Git pointers.

Mitigation: Commit nested repo changes first, then update the containing repo pointer, then update the mega pointer.
