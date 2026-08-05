# Athena Task Intake: Two-Way Chat, Repository, And GitHub Reconciliation

## Metadata

- schema: `ai-system.athena_task_intake.v1`
- intake_id: `ATHENA-INTAKE-20260801-005`
- created_at: `2026-08-01T17:00:00+10:00`
- status: active
- active_layer: root, continuity, work, GitHub planning
- priority_source: explicit human instruction on 2026-08-01

## Human Goal

Make recovered Project Athena chats influence the repository and make current
repository state influence future chats. Flesh out project structure,
workflows, milestones, issues, and GitHub Project planning while the user
provides recovered images.

## Required Output

- verified image package in source memory;
- governed chat-to-repository promotion lifecycle;
- repository-to-chat context export;
- current milestones, backlog, issue blueprint, templates, and integrity CI;
- bounded GitHub planning reconciliation;
- end-to-end validation and durable cycle report.

## Known Facts

| Statement | Truth Value | Confidence | Evidence |
|---|---|---:|---|
| Five Project Athena chats are cached with two matching retrieval passes. | observed | 1.0 | `athena_context/AUDIT.md` |
| The image archive contains 58 images and all embedded checksums pass. | observed | 1.0 | `athena_context/ASSET_INVENTORY.md` |
| The GitHub repository is public and the connected user has admin permission. | observed | 1.0 | GitHub connector repository metadata |
| The repository had no GitHub issues or milestones at inspection time. | observed | 1.0 | GitHub connector and milestones UI |
| Local GitHub CLI is unavailable. | observed | 1.0 | `work/bugs.yml` |

## Assumptions And Boundaries

| Statement | Truth Value | Confidence | Evidence |
|---|---|---:|---|
| GitHub workflow and planning metadata are within the current human request. | human-intent | 1.0 | Current instruction |
| The request does not create blanket future cloud-push authority. | inferred | 0.9 | Existing governance plus bounded task wording |
| Generated images are useful design references but not architecture proof. | governance | 1.0 | `Plan/CHAT_REPOSITORY_CONTINUITY_PIPELINE.md` |

## Unknowns

- Whether an official ChatGPT account export contains alternate message branches
  or additional attachment metadata.
- Exact source-turn mapping for some recovered generated images.
- Whether the human will authorize the final public GitHub form submissions.
- Whether a narrowly scoped user token will be provided for automated Project
  v2 synchronization.

## Risks

- Public planning text can expose private details if source boundaries fail.
- Automatic promotion can turn assistant proposals into false project truth.
- Large binary assets increase repository size and future clone cost.
- GitHub UI and connector state can diverge from local desired state.

## Verification Method

- Parse all JSON and JSONL.
- Parse all PowerShell scripts.
- Verify all 58 asset hashes against the embedded manifest.
- Exercise import, bounded export, full export, and GitHub plan preview.
- Run `tools/Test-AthenaRepository.ps1 -NoWrite`.
- Re-read GitHub state after any approved remote mutation.

## Memory Writeback Targets

- `Plan/CHAT_REPOSITORY_CONTINUITY_PIPELINE.md`
- `athena_context/ASSET_INVENTORY.md`
- `continuity/chat-repository-sync/`
- `memory/athena-memory-map.md`
- `work/`
- `context.md`
- `engine/cycle-reports/`

## End State

Local implementation and validation complete. Public GitHub submission requires
action-time confirmation immediately before form submission.
