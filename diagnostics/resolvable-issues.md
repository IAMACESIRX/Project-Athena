# Resolvable Issues

This queue stores one open row per distinct current signal. Repeated scanner runs should update reports, not duplicate open issues.

| ID | First Seen | Severity | Signature | Source | Summary | Suggested Action | Status |
|---|---|---|---|---|---|---|---|
| RES-LOG-AUTH-REALM-SERVER-LIVE-STATE-SERVER-IDENTITY-TXT-L4 | 2026-06-03T18:44:27+10:00 | yellow | LOG-AUTH-REALM | Server-Live-State/server-identity.txt | Authentication or realm signal: Realm name: AzerothCore | Verify authserver state, realmlist address, and account database state. | Open |
| RES-LOG-AUTH-REALM-SERVER-LIVE-STATE-SERVER-IDENTITY-TXT-L5 | 2026-06-03T18:44:27+10:00 | yellow | LOG-AUTH-REALM | Server-Live-State/server-identity.txt | Authentication or realm signal: Advertised realm address: 192.168.1.113 | Verify authserver state, realmlist address, and account database state. | Open |
| RES-LOG-AUTH-REALM-SERVER-LIVE-STATE-DOCKER-IMAGES-TXT-L1 | 2026-06-03T18:44:27+10:00 | yellow | LOG-AUTH-REALM | Server-Live-State/docker-images.txt | Authentication or realm signal: acore/ac-wotlk-authserver master image is present. | Confirm image/tag is expected for the current live-state. | Open |
| RES-LOG-AUTH-REALM-SERVER-LIVE-STATE-DOCKER-COMPOSE-PS-TXT-L2 | 2026-06-03T18:44:27+10:00 | yellow | LOG-AUTH-REALM | Server-Live-State/docker-compose-ps.txt | Authentication or realm signal: ac-authserver is up and mapped to port 3724. | Run the live server probe when the server is available and verify auth reachability. | Open |
| RES-LOG-DOCKER-SERVER-LIVE-STATE-DOCKER-COMPOSE-PS-TXT-L3 | 2026-06-03T18:44:27+10:00 | yellow | LOG-DOCKER | Server-Live-State/docker-compose-ps.txt | Docker or container signal: ac-database is up and healthy. | Run the live server probe and verify container availability. | Open |

## Retired Noise

| ID | Time | Action |
|---|---|---|
| DEDUPE-20260603-001 | 2026-06-03T20:11:00+10:00 | Collapsed repeated LOG-AUTH-REALM and LOG-DOCKER rows produced by multiple scanner runs. |
| FALSE-POSITIVE-20260603-001 | 2026-06-03T20:11:00+10:00 | Retired earlier LOG-SQL-ERROR rows caused by matching plain MySQL image/container names instead of actual database error text. |
| FALSE-POSITIVE-20260710-001 | 2026-07-10T01:13:12+10:00 | Removed self-scan rows created when log intelligence scanned its own generated reports; the scanner now reads Nexus V report inputs only. |
