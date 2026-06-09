# Forensic Verification Protocol

Run this protocol when adding evidence, changing generated reports, making claims, or preparing a handoff.

## Checks

1. Evidence register parses.
2. Evidence IDs are unique.
3. Claim IDs are unique.
4. Evidence paths resolve when paths are supplied.
5. Canonical names match expected identity.
6. Evidence-to-claim map references existing evidence IDs.
7. Evidence-to-claim map references existing claim IDs.
8. Hashes match when fixed hashes are recorded.
9. Known unknowns are listed separately from claims.
10. Verification output is refreshed.

## Command

```powershell
powershell -NoProfile -ExecutionPolicy Bypass -File .\ai-system\tools\Invoke-AIForensicVerification.ps1
```

## Interpretation

- `PASS`: no structural evidence issues.
- `WARN`: usable, but some records are missing paths, hashes, or anchors.
- `FAIL`: duplicate IDs, missing referenced files, or broken claim/evidence links.

