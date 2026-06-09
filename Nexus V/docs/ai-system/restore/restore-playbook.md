# Restore Playbook

## Restore Git State

1. Find restore point manifest in `restore/restore-points/`.
2. Identify target repo and tag.
3. Inspect before changing:

```powershell
git status
git tag --list
```

4. Use Git checkout/revert/reset only with a clear target and human approval for destructive resets.

## Restore Live State

Use `playbooks/snapshot-live-state.md` and `diagnostics/restore-readiness.md`.

Database import is high risk and requires explicit intent.

## Restore Game Client Payload

If payload files are untracked, restore from filesystem backup, not Git.

## Post-Restore

- Run project scan.
- Run live probe if runtime is involved.
- Update audit ledger.
- Update handoff.
