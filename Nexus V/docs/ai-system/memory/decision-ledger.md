# Decision Ledger

## D-001: Local-Only Git Hosting

Date: 2026-06-03

Decision: Use local bare Git repositories under `local-git-host` instead of GitHub cloud repositories.

Reason: The project contains private live-state data, account metadata, SQL dumps, and large game-client files.

## D-002: Layered Git Repositories

Date: 2026-06-03

Decision: Keep four Git layers: mega repo, game client repo, server live-state repo, and server project repo.

Reason: This supports individual snapshots and all-at-once pointer management.

## D-003: Metadata-Only Game Client Commit For Now

Date: 2026-06-03

Decision: Initialize the game client repo with management files only.

Reason: The client payload is about 36 GB and the drive has limited free space. A full commit would create extra Git object storage pressure.
