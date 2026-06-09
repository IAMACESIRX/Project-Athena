# Playbook: Diagnose Server

Use when the server does not start, import, or accept client login.

## Check Order

1. Confirm Docker Desktop is running.
2. Check compose status in the active server folder.
3. Check database import logs.
4. Check worldserver logs.
5. Check authserver logs.
6. Confirm realm address in `acore_auth.realmlist`.
7. Confirm client `realmlist.wtf`.

## Useful Commands

```powershell
docker compose ps
docker logs ac-db-import --tail 100
docker logs ac-worldserver --tail 100
docker logs ac-authserver --tail 100
```

## Record

Log findings in `diagnostics/issue-ledger.md`.
