# Signals

Signals are things the AI system should watch when scanning the project.

## Git Signals

- Child repo commit pointer changed.
- Child repo has tracked modifications.
- Remotes point to non-local URLs.
- Nested server repo branch changed.

## Storage Signals

- C: drive free space below 80 GB.
- Game client binary payload remains untracked.
- Local bare host grows unexpectedly.

## Runtime Signals

- Docker containers not running when expected.
- Database import logs show errors.
- Worldserver logs show startup failure.
- Realm address does not match intended mode.

## Project Signals

- Handoff older than the latest commit.
- Risk register has stale high-risk items.
- New scripts lack playbook or verification notes.
- Backend dependency environment is broken.
