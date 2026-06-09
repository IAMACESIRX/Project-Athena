# Interaction Map

## Client Login Path

```text
Game client realmlist.wtf
  -> authserver port 3724
  -> acore_auth.realmlist
  -> worldserver address and port 8085
  -> character database
  -> world database
```

## Restore Path

```text
Server-Live-State SQL dumps
  -> Docker ac-database
  -> acore_auth / acore_characters / acore_world / acore_playerbots
  -> restart authserver and worldserver
  -> validate realm and login
```

## AI Work Path

```text
AI reads portal and manifest
  -> scans project
  -> selects layer
  -> consults governance
  -> edits or probes
  -> verifies
  -> records memory/handoff/work item
  -> commits locally
```
