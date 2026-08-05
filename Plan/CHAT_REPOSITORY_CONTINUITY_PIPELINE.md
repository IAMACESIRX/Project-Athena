# Chat And Repository Continuity Pipeline

Status: active architecture and implementation contract

Updated: 2026-08-01

## Purpose

Project Athena uses chats and the repository as two connected but unequal
memory surfaces:

- chats are high-bandwidth working sessions and sources of human intent,
  proposals, questions, and generated artifacts;
- the repository is the durable, reviewable project memory and implementation
  record;
- GitHub is an existing public planning and automation surface used only within
  explicit human authority and the publication gate.

The pipeline is bidirectional. Chat exports can propose repository changes, and
repository state is exported into a context capsule for later chats. Neither
direction silently replaces canonical memory.

## Authority Order

When sources disagree, use this order:

1. Latest explicit human instruction.
2. Constitution, governance, and recorded human decisions.
3. Accepted `Plan/` architecture intent.
4. Verified implementation and test evidence.
5. Current repository context, manifests, and work state.
6. Human statements recovered from source chats.
7. Assistant proposals recovered from source chats.
8. Generated images, speculative models, and research hypotheses.

Generated media is explanatory evidence. It is never implementation proof and
does not override canonical text.

## Chat To Repository

```text
export or audited cache
  -> source hash and scope check
  -> immutable local source record
  -> normalized messages and attachment references
  -> deduplication and branch accounting
  -> candidate promotion records
  -> evidence and contradiction review
  -> accepted Plan, memory, work, or implementation change
  -> validation and cycle report
  -> optional GitHub publication
```

### Source Rules

- Preserve the source file hash and retrieval timestamp.
- Keep account-wide exports and unreviewed normalized transcripts out of Git.
- Require a Project Athena scope filter for official account exports unless the
  operator explicitly enables an all-conversation import.
- Preserve alternate branch metadata when the export exposes it.
- Record missing media, attachments, tool traces, deleted chats, and reader
  limits as gaps instead of inferring completeness.

### Promotion States

| State | Meaning |
|---|---|
| `source-only` | Preserved evidence; no canonical effect. |
| `proposed` | Candidate change awaiting review. |
| `accepted` | Human or delegated review approved a bounded writeback. |
| `implemented` | Repository changes exist and validation evidence is linked. |
| `rejected` | Reviewed and intentionally not adopted. |
| `superseded` | Replaced by a later accepted record. |

Every promotion record identifies the source conversation and message, the
claim type, target files, evidence label, contradictions, reviewer, and result.

## Repository To Chat

The repository exports a context capsule containing:

- identity and authority;
- architecture summaries and source hashes;
- current milestones and GitHub issue blueprint;
- accepted decisions and unresolved questions;
- implementation status and verification posture;
- source-memory coverage and known gaps;
- current Git commit and dirty-state summary;
- explicit truncation metadata for every embedded file.

The normal capsule is bounded for interactive use. A full export mode produces
untruncated chunks plus a manifest so completeness can be checked without
pretending one prompt can safely contain the entire repository.

Chats consume the capsule as context, not as permission to write. Important
results return through the chat-to-repository promotion path.

## GitHub Role

The local repository remains the primary working substrate and cloud push stays
disabled by default. The 2026-08-01 task authorizes a bounded update to Project
Athena workflow files and planning metadata: labels, milestones, issues, and
project-board configuration. It is not blanket authorization for future pushes
or unrelated source publication.

Never publish:

- credentials, tokens, private keys, or local authentication material;
- account-wide ChatGPT exports;
- private or personal conversations outside the Athena scope;
- unreviewed attachments or files with unclear rights;
- machine-local caches that are not needed to reproduce the project.

Remote updates must be previewable, idempotent where practical, and recorded in
an Athena cycle report or synchronization report.

## Operating Files

- Policy: `continuity/chat-repository-sync/sync-policy.json`
- Promotion ledger: `continuity/chat-repository-sync/promotion-ledger.jsonl`
- Import tool: `tools/Import-AthenaChatExport.ps1`
- Context export: `tools/Export-AthenaChatContext.ps1`
- GitHub desired state: `work/github-plan.json`
- GitHub synchronization: `tools/Sync-AthenaGitHub.ps1`
- Repository validation: `tools/Test-AthenaRepository.ps1`
- Asset verification: `tools/Test-AthenaAssetManifest.ps1`

## Definition Of Done For A Reconciliation Cycle

1. Source scope and hash are recorded.
2. Message, branch, media, and attachment coverage are stated.
3. Candidate changes have promotion records.
4. Accepted changes name their canonical targets and evidence.
5. Repository checks pass or failures are recorded.
6. Context capsule is regenerated.
7. GitHub state is synchronized only after the publication gate.
8. Remaining gaps and next actions are durable work items.
