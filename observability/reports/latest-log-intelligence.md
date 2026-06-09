# Log Intelligence Report

Generated: 2026-06-03T20:49:06.4159937+10:00
Status: WARN
Scanned Files: 7
Hits: 5

| Severity | Signature | File | Line | Sample | Suggested Action |
|---|---|---|---:|---|---|
| yellow | LOG-AUTH-REALM | Server-Live-State/server-identity.txt | 4 | Realm name: AzerothCore | Verify authserver state, realmlist address, and account database state. |
| yellow | LOG-AUTH-REALM | Server-Live-State/server-identity.txt | 5 | Advertised realm address: 192.168.1.113 | Verify authserver state, realmlist address, and account database state. |
| yellow | LOG-AUTH-REALM | Server-Live-State/docker-images.txt | 1 | acore/ac-wotlk-authserver    master    a1c0b0177b61   2 hours ago | Verify authserver state, realmlist address, and account database state. |
| yellow | LOG-AUTH-REALM | Server-Live-State/docker-compose-ps.txt | 2 | ac-authserver    acore/ac-wotlk-authserver:master    "/usr/bin/env bash /â€¦"   ac-authserver    2 hours ago   Up 2 hours             0.0.0.0:3724->3724/tcp | Verify authserver state, realmlist address, and account database state. |
| yellow | LOG-DOCKER | Server-Live-State/docker-compose-ps.txt | 3 | ac-database      mysql:8.4                           "docker-entrypoint.sâ€¦"   ac-database      2 hours ago   Up 2 hours (healthy)   0.0.0.0:3306->3306/tcp, 33060/tcp | Run the live server probe and verify container availability. |

