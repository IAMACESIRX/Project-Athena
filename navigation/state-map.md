# State Map

## Static State

State that should change rarely:

- governance,
- absolutes,
- layer topology,
- module definitions,
- schema contracts,
- core mission.

## Dynamic State

State expected to change often:

- scans,
- handoffs,
- work items,
- bug status,
- live server logs,
- SQL snapshots,
- child repo pointers.

## Runtime State

State visible only when server/client are active:

- Docker container status,
- database health,
- worldserver logs,
- authserver logs,
- active realm address,
- connected players,
- game client behavior.

## Reconciliation Rule

When static, dynamic, and runtime state disagree, runtime evidence wins, then Git state, then generated scans, then registries, then docs.
