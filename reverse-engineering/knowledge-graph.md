# Knowledge Graph

## Entities

- Mega repo
- Game client
- Live-state SQL dumps
- Server project
- FastAPI command hub
- AzerothCore baseline
- AzerothCore Playerbots
- mod-playerbots
- Docker stack
- MySQL database
- Authserver
- Worldserver
- Game client realmlist

## Relationships

- Mega repo points to child repo commits.
- Server project points to nested source repo commits.
- Live-state SQL restores database state into Docker MySQL.
- Authserver reads auth database.
- Worldserver reads character/world/playerbot databases.
- Game client reads realmlist and connects to authserver.
- Auth database realmlist sends client toward worldserver.
- AI system reads and governs all layers.

## Unknowns To Resolve

- Exact runtime container health on this machine.
- Whether current active server is running from backup copy or original path.
- Best long-term client payload tracking strategy.
