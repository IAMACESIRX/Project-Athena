# Current State

Last updated: 2026-08-01

## Project Athena Current Snapshot

- Standalone root: `D:\Projects\Project Athena`.
- Primary project: Project Athena; the WoW backup stack below is retained as
  historical context.
- Five Project Athena chats are cached and retrieval-audited under
  `athena_context/`.
- Fifty-eight generated storyboards and infographics are checksum-verified under
  `athena_context/assets/generated-storyboards-2026-08-01/`.
- Two-way chat/repository policy and tooling live under
  `continuity/chat-repository-sync/` and `tools/`.
- Desired GitHub labels, milestones, issues, and Project configuration are in
  `work/github-plan.json`.
- The 2026-08-01 task has a bounded exception for reviewed workflow files and
  GitHub planning metadata; the local-only default otherwise remains active.

## Legacy WoW Snapshot

## Snapshot

The backup stack has four local Git layers:

- Mega repo at the backup root.
- Game client repo inside `GameClient-ChromieCraft-3.3.5a`.
- Server live-state repo inside `Server-Live-State`.
- Server project repo inside `WoW-Server-Project`.

All four layers have local bare `origin` remotes under:

`C:\Users\aesir\OneDrive\Desktop\WoW-Backups\local-git-host\2026-05-30_2035`

## Legacy Important Context

- No GitHub server push is allowed.
- The game client repository has only a lightweight management commit so far.
- The full game client payload is still untracked inside the client repo because the drive has limited free space.
- The server live-state repo contains SQL dumps and is private-sensitive.
- The server project repo contains embedded pointers to two AzerothCore repos.

## Baseline Commit Anchors

- Mega repo: `683c38e`
- Game client layer: `a2508eb`
- Server live-state layer: `6c66e8f`
- WoW server project layer: `833f12f`

These anchors describe the stack before the AI system layer was committed. Use `tools/Invoke-AIProjectScan.ps1` for the latest layer heads.

## Human Intent

The human wants a project system that acts as shared memory, handoff, diagnostics, research engine, engineering management layer, and AI coordination layer for the complete WoW client/server/live-state stack.
