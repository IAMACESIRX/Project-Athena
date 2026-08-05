# Athena Task Intake: A.E.S.I.R. War-Systems Council Ingest

## Metadata

- schema: ai-system.athena_task_intake.v1
- intake_id: ATHENA-INTAKE-20260802-001
- created_at: 2026-08-02T13:40:00+10:00
- status: implemented
- active_layer: continuity
- priority_source: human instruction

## Human Goal

Inspect Project Athena, identify its processing pipeline and configuration, and
prepare the A.E.S.I.R. geopolitical council dataset from ChatGPT thread
`6a6e9ce8-5e70-83ec-b483-89393c0f296a` for Athena ingestion while preserving
fact, inference, hypothesis, and forecast boundaries.

## Files Read

- AI-PORTAL.md
- START-HERE.md
- README.md
- tools/README.md
- integration/ai-ingestion-guide.md
- integration/adapter-contract.md
- schemas/chat-source-bundle.schema.json
- schemas/chat-promotion.schema.json
- schemas/athena-adapter.schema.json
- tools/Import-AthenaChatExport.ps1
- tools/Export-AthenaChatContext.ps1
- tools/Invoke-AthenaCycle.ps1
- Plan/CHAT_REPOSITORY_CONTINUITY_PIPELINE.md
- continuity/chat-repository-sync/sync-policy.json
- continuity/chat-repository-sync/promotion-ledger.jsonl
- cognition/cognition-workflow.md
- cognition/output-labels.md
- forensics/evidence-labeling-guide.md
- engine/order-of-operations.md
- engine/operation-cycle.md
- tools/Test-AthenaRepository.ps1

## Known Facts

| Statement | Truth Value | Confidence | Evidence |
|---|---|---:|---|
| Project Athena is a file-native AI external-brain repository, not a single server app. | observed | 1.0 | README.md, AI-PORTAL.md |
| Chat ingestion is local-only and writes unreviewed imports under `continuity/transcript-inbox/imports/`. | observed | 1.0 | Plan/CHAT_REPOSITORY_CONTINUITY_PIPELINE.md, .gitignore |
| Canonical writeback is not automatic; accepted changes go through promotion records. | observed | 1.0 | sync-policy.json, chat-promotion schema |
| The referenced conversation preview available to Codex was bounded and partly truncated. | observed | 1.0 | Codex read_thread result for thread 6a6e9ce8-5e70-83ec-b483-89393c0f296a |

## Assumptions

| Statement | Truth Value | Confidence | Evidence |
|---|---|---:|---|
| The full A.E.S.I.R. dataset should be imported from an official ChatGPT export or audited JSONL cache rather than from a truncated preview. | inferred | 0.9 | Chat-source pipeline source rules |

## Unknowns

| Statement | Truth Value | Confidence | Evidence |
|---|---|---:|---|
| Whether the user has a full official ChatGPT export available locally. | unknown | 0.0 | Not present in provided workspace paths |

## Decision

Add a scoped A.E.S.I.R. import adapter, add an ingest configuration, and extend
the generic chat import tool so official exports can be filtered by conversation
ID. Do not promote geopolitical claims as facts during this pass.

## Verification

- Ran import selector smoke test with `-ConversationId` and `-NoWrite`.
- Ran `tools/Test-AthenaRepository.ps1 -NoWrite`.
- Baseline repository validation passed before edits and passed after edits.

## Storage Decision

- work item
- audit/cycle report
- memory promotion only after full source import and claim review
