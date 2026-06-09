# Live Server Observability

This folder defines how AI and humans can read the live server safely.

## Current Implemented Level

Read-only probe scaffolding.

## Target Observability

- Docker compose status.
- Container health.
- Authserver logs.
- Worldserver logs.
- Database import logs.
- Realm address.
- Database table inventory.
- Player/account counts.
- Bot configuration.
- Client realmlist agreement.

## Read-Only First

The first live observability tools must not start, stop, import, delete, or rewrite anything.

## Probe Command

```powershell
powershell -NoProfile -ExecutionPolicy Bypass -File .\ai-system\tools\Invoke-LiveServerProbe.ps1
```

## Future Build Targets

- `Get-RealmState`
- `Get-DatabaseTableInventory`
- `Get-PlayerbotConfig`
- `Get-ServerLogSignals`
- `Compare-ClientAndRealmAddress`
- `Export-RestoreReadinessReport`
