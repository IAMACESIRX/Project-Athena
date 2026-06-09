# Module: Command Hub

## Purpose

Provide a local FastAPI command logging hub for future assistant modules.

## Path

`WoW-Server-Project/backend`

## Current Capability

- `GET /health`
- `POST /api/commands`
- `GET /api/commands`

## Current Model

Commands are logged to SQLite. Low-risk commands are marked approved. Medium, high, or confirmation-required commands are blocked.

## Known Gap

The copied virtual environment points to a previous machine path, so it must be recreated before reliable testing.

## Recommended Next Work

- Recreate `.venv`.
- Add tests for command status decisions.
- Add confirmation workflow.
- Add first safe execution module only after audit logging is solid.

## Verification

```powershell
cd WoW-Server-Project\backend
uvicorn app.main:app --reload
```

Then open `/health` and `/docs`.
