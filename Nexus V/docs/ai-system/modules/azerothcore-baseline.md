# Module: AzerothCore Baseline

## Purpose

Maintain a clean rollback/reference checkout of official AzerothCore.

## Path

`WoW-Server-Project/servers/wow/azerothcore-wotlk`

## Current Status

Nested Git repo on `master`, clean at scan time.

## Risks

- Local changes here reduce its value as a clean rollback path.
- Upstream updates can change server behavior.

## Recommended Handling

- Keep clean unless the human explicitly asks for baseline customization.
- Use the Playerbots path for bot-enabled changes.
- Record upstream commit when updating.

## Verification

- `git status --short --branch`
- `git remote -v`
- Docker compose file exists.
