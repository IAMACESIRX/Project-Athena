# Module: WoW Server Project

## Purpose

Maintain the project scaffold, assistant backend, WoW docs, helper scripts, and nested server source repos.

## Layer

`WoW-Server-Project`

## Current Status

Committed and pushed to local bare remote.

## Important Areas

- `backend/`: FastAPI command hub.
- `docs/`: planning, architecture, WoW setup notes.
- `scripts/wow/`: clone/start/realmlist helpers.
- `servers/wow/azerothcore-wotlk`: clean baseline source.
- `servers/wow/azerothcore-wotlk-playerbots`: Playerbot server source.

## Risks

- Copied `.venv` is not portable.
- Runtime DB `data/jarvis.db` is ignored by design.
- Nested repos need careful pointer management.

## Recommended Handling

- Recreate `.venv` on this machine.
- Keep generated caches and runtime DB out of commits.
- Use local bare remote only.
- Commit child source pointer changes deliberately.

## Verification

- Backend dependencies install.
- `GET /health` works.
- WoW scripts resolve expected paths.
- Nested repo branches remain correct.
