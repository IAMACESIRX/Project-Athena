# Module: Playerbots Stack

## Purpose

Run the bot-enabled AzerothCore server using the Playerbot fork and `mod-playerbots`.

## Path

`WoW-Server-Project/servers/wow/azerothcore-wotlk-playerbots`

## Current Status

Nested Git repo on `Playerbot`, with `modules/mod-playerbots` nested inside.

## Key Files

- `docker-compose.yml`
- `docker-compose.override.yml`
- `modules/mod-playerbots`

## Current Bot Defaults

From `docker-compose.override.yml`:

- random bot autologin enabled,
- min random bots: `8`,
- max random bots: `12`,
- max added bots: `4`,
- disabled without real player: enabled.

## Risks

- Docker operations can mutate live state.
- Module and fork must remain compatible.
- Database imports can overwrite characters/accounts.

## Verification

- `docker compose ps`
- `docker logs ac-db-import --tail 100`
- `docker logs ac-worldserver --tail 100`
- Confirm realm address after restore.
