# Error Correction

## Error Classes

### Documentation Error

The docs say something false or stale.

Correction: update the doc and, if meaningful, record in `handoff/CHANGELOG.md`.

### Registry Error

A path, module, layer, or interface registry is wrong.

Correction: update registry and run `Export-AISystemManifest.ps1`.

### Scan Error

A scanner reports misleading state.

Correction: fix scanner logic, refresh scan, and record why.

### Runtime Error

Server, Docker, DB, or client runtime is failing.

Correction: use diagnostic playbooks. Do not mutate live state until evidence is collected.

### Git Layer Error

Child repo and mega repo pointers disagree.

Correction: commit child repo if needed, then run `Update-LayerPointers.ps1`.

### Policy Error

An action violates governance.

Correction: stop, record incident in `diagnostics/issue-ledger.md`, and restore previous state where possible.
