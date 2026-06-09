# Restore Readiness

## Current Rating

Partial.

## Ready

- SQL dumps exist for auth, characters, playerbots, and world.
- Restore script exists.
- Docker metadata exists.
- Server project and playerbots source trees exist.
- Local Git layers are initialized.

## Not Yet Ready

- Restore path defaults point to old machine/user paths.
- Database password is hardcoded as Docker default.
- Realm address needs explicit post-restore verification.
- No recorded restore drill has been run from this backup copy.

## Restore Drill Checklist

1. Pick disposable restore target.
2. Start Docker Desktop.
3. Start Playerbots stack.
4. Confirm `ac-database` is healthy.
5. Import SQL dumps.
6. Set realm address.
7. Restart auth and world services.
8. Log in with client.
9. Record result in `diagnostics/issue-ledger.md`.
