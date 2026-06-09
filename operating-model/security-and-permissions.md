# Security And Permissions

## Default Security Mode

Private local-only project.

## Data Classes

### Public Or Low Sensitivity

- General AzerothCore source code.
- Generic setup docs without personal data.
- AI system process docs without secrets.

### Private

- Account names.
- Client `WTF` files.
- Character state.
- LAN IPs and host paths.
- Restore scripts with machine-specific paths.

### High Sensitivity

- SQL auth dumps.
- Password hashes.
- Live database exports.
- Any file that can restore or mutate live server state.

## Permission Rules

- Read-only inspection is generally allowed.
- Local commits and local pushes are allowed.
- Cloud pushes are blocked by default.
- Runtime server changes require clear intent.
- Destructive database or Docker volume actions require explicit human confirmation.
