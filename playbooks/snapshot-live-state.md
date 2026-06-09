# Playbook: Snapshot Live State

Use when capturing a fresh server live-state backup.

## Preflight

- Confirm target server stack.
- Confirm Docker Desktop is running.
- Confirm enough disk space.
- Confirm whether services should be stopped first.

## Capture

1. Export `acore_auth`.
2. Export `acore_characters`.
3. Export `acore_playerbots`.
4. Export `acore_world`.
5. Capture Docker images, volumes, and compose status.
6. Update `server-identity.txt`.

## Git

1. Commit in `Server-Live-State`.
2. Push to local bare remote.
3. Commit updated `Server-Live-State` pointer in mega repo.
4. Push mega repo to local bare remote.

## Verification

- Required SQL files exist.
- SQL files are not zero bytes.
- Restore checklist names the right files.
