# Athena Cycle Report: A.E.S.I.R. War-Systems Council Ingestion

## Run Type

continuity ingestion mapping and adapter configuration

## Authority And Boundary

- Latest human instruction: process the prior A.E.S.I.R. geopolitical council
  dataset through Project Athena and preserve evidence boundaries.
- Active layer: continuity, integration, and local source ingestion.
- Local-only rule: no GitHub push, publication, or raw transcript publication.
- Source limitation: Codex could inspect only a bounded referenced conversation
  preview; the full dataset needs an official ChatGPT export JSON/ZIP or Athena
  audited JSONL cache.

## Repository Architecture Map

Project Athena is a file-native operating substrate:

| Area | Function |
|---|---|
| `AI-PORTAL.md`, `START-HERE.md`, `context.md` | operator entry, current context, authority, and orientation |
| `Plan/` | highest-priority architecture and design authority |
| `manifests/`, `registries/`, `schemas/` | machine-readable contracts, indexes, and topology |
| `integration/`, `agents/adapters/` | adapter contracts, registries, and model/tool bridges |
| `continuity/` | transcript inbox, chat-repository sync, handoff, and long-session memory |
| `truth/`, `forensics/` | evidence ledgers, claim catalogs, evidence-claim maps, known unknowns |
| `cognition/`, `council/`, `counterfactuals/` | reasoning methods, council passes, uncertainty handling |
| `engine/`, `tools/` | deterministic operation cycle and PowerShell processing tools |
| `memory/`, `work/`, `audit/` | durable memory, task state, decisions, and change trace |
| `Nexus V/` | hardware/toolchain implementation and research branch |

## Processing Pipeline

The native pipeline is:

```text
human scope
  -> context anchoring
  -> source hash and scope check
  -> local ignored transcript import
  -> normalized messages
  -> candidate promotion records
  -> evidence and contradiction review
  -> truth/forensics/cognition routing
  -> validation
  -> cycle report and memory writeback
```

The important control rule is that imported chat is source evidence, not
canonical memory. Forecasts and scenario probabilities remain research
hypotheses unless later validated against dated evidence and reviewed.

## A.E.S.I.R. Dataset Mapping

| Dataset element | Athena classification | Storage path |
|---|---|---|
| User request and scope | `human-intent` | promotion ledger, intake packet |
| Assistant council text | `assistant-proposal` | normalized source bundle |
| Cited news or institutional facts inside council text | `reported` until independently checked | truth/forensics after review |
| Actor weights, system functions, causal loops | `inferred` | cognition or claim catalog |
| Scenario branches and probabilities | `research-hypothesis` | research notes or forecast review records |
| Truncated or unavailable source portions | `unknown` | known unknowns or source manifest notes |

## Files Added Or Updated

- `agents/adapters/aesir-geopolitical-council-import.adapter.json`
- `continuity/chat-repository-sync/aesir-war-systems-council.ingest.json`
- `integration/adapter-registry.yml`
- `tools/Import-AthenaChatExport.ps1`
- `continuity/chat-repository-sync/promotion-ledger.jsonl`
- `work/intake/ATHENA-INTAKE-20260802-001-aesir-war-systems-council-ingest.md`
- `engine/cycle-reports/ATHENA-AESIR-COUNCIL-INGESTION-20260802.md`

## Concrete Run Instructions

From `D:\Projects\Project Athena`:

```powershell
powershell -NoProfile -ExecutionPolicy Bypass -File .\tools\Import-AthenaChatExport.ps1 -SourcePath <path-to-chatgpt-export.zip> -ConversationId 6a6e9ce8-5e70-83ec-b483-89393c0f296a -NoWrite
```

If coverage shows one selected conversation with nonzero messages, run the real
local import:

```powershell
powershell -NoProfile -ExecutionPolicy Bypass -File .\tools\Import-AthenaChatExport.ps1 -SourcePath <path-to-chatgpt-export.zip> -ConversationId 6a6e9ce8-5e70-83ec-b483-89393c0f296a
```

For a raw `conversations.json` file instead of a ZIP, use the same command with
the JSON path:

```powershell
powershell -NoProfile -ExecutionPolicy Bypass -File .\tools\Import-AthenaChatExport.ps1 -SourcePath <path-to-conversations.json> -ConversationId 6a6e9ce8-5e70-83ec-b483-89393c0f296a
```

For an Athena audited JSONL cache:

```powershell
powershell -NoProfile -ExecutionPolicy Bypass -File .\tools\Import-AthenaChatExport.ps1 -SourcePath <path-to-jsonl-or-folder>
```

After import, inspect the reported bundle path under:

```text
continuity/transcript-inbox/imports/<bundle-id>/
```

Then run validation:

```powershell
powershell -NoProfile -ExecutionPolicy Bypass -File .\tools\Test-AthenaRepository.ps1 -NoWrite
```

For a full Athena refresh after accepted promotions:

```powershell
powershell -NoProfile -ExecutionPolicy Bypass -File .\tools\Invoke-AIOperationCycle.ps1 -SkipLiveProbe
```

## Verification Performed

- Baseline no-write integrity check: PASS.
- Baseline no-write repository test: PASS.
- Conversation-id import smoke test against a local fixture: PASS, selecting one
  conversation and two current-branch messages with `-NoWrite`.
- Post-change no-write repository test: PASS.

## Remaining Gap

The prior ChatGPT thread was available only as a bounded Codex preview in this
session. The adapter is ready, but complete ingestion of the full council
dataset requires the official ChatGPT export ZIP/JSON or a full audited JSONL
source.
