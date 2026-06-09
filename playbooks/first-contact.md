# Playbook: First Contact

Use when opening a new AI or human work session.

## Steps

1. Read `ai-system/START-HERE.md`.
2. Run:

```powershell
powershell -NoProfile -ExecutionPolicy Bypass -File .\ai-system\tools\Invoke-AIProjectScan.ps1
```

3. Review:

- `handoff/CURRENT_STATE.md`
- `handoff/NEXT_ACTIONS.md`
- `diagnostics/risk-register.md`
- `diagnostics/issue-ledger.md`

4. Decide active layer.
5. Make changes.
6. Update handoff before ending.
