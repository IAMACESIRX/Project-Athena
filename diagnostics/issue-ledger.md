# Issue Ledger

## Open

### I-001: Recreate Project Virtual Environment

Layer: `WoW-Server-Project`

Need a fresh Python environment on this machine so the FastAPI backend can be run and tested.

### I-002: Add Dated Live-State Snapshot Workflow

Layer: `Server-Live-State`

Future exports should avoid overwriting the previous snapshot without a dated record.

### I-003: Decide Client Tracking Strategy

Layer: `GameClient-ChromieCraft-3.3.5a`

Need a disk-aware plan for tracking client config and possibly large binaries.

### I-004: Resolve Restore Realm Address

Layer: `Server-Live-State`

Need restore flow to set `realmlist.address` to the intended LAN/local/online address.

## Closed

None yet.
