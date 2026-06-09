# Facts

## Environment

- Current backup root: `C:\Users\aesir\OneDrive\Desktop\WoW-Backups\2026-05-30_2035`
- Local bare host root: `C:\Users\aesir\OneDrive\Desktop\WoW-Backups\local-git-host\2026-05-30_2035`
- User timezone from session context: Australia/Brisbane
- Current date during setup: 2026-06-03

## WoW Server

- Core: AzerothCore
- Expansion target: Wrath of the Lich King
- Bot path: `mod-playerbots` fork on Playerbot branch
- Local default auth port: `3724`
- Local default world port: `8085`
- Local default SOAP/RA port: `7878`

## Known Accounts In Backup Metadata

Account names are present in live-state metadata and SQL dumps. Treat them as private.

## Known Technical Gaps

- Python venv in `WoW-Server-Project/.venv` points to an old machine path.
- FastAPI smoke test did not run with system Python because dependencies are not installed there.
- Game client payload is not fully committed.
