# Dependency Map

## Structural Dependencies

- Mega repo depends on child repo commit pointers.
- Server project depends on nested AzerothCore repos.
- Playerbots stack depends on Playerbot fork plus `mod-playerbots`.
- Live-state restore depends on Docker stack and SQL dumps.
- Game client login depends on `realmlist.wtf` and auth database realm address agreeing.

## Failure Propagation

- Broken local Git host affects push/pull but not working tree.
- Broken live-state restore affects recoverability.
- Broken venv affects command hub testing.
- Wrong realm address affects client login.
- Disk pressure affects game client snapshot strategy.

## Dependency Questions For Future Tools

- What files affect server runtime?
- What files affect client login?
- What files affect restore?
- What files are safe to edit without runtime mutation?
- Which nested repo commit is active?
