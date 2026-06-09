# Continuity System

The continuity system lets any AI, team member, script, or external tool hand off context into local project memory.

## Goals

- Preserve chat context across agents and tools.
- Track who changed what, when, why, and with what evidence.
- Turn important chat decisions into durable project records.
- Separate raw transcripts from distilled memory.
- Make context recoverable even when chat history is lost.

## Main Folders

- `chat-logs/`: raw or semi-raw imported chat records.
- `handoff-packets/`: compressed session packets for next agents.
- `interaction-ledger/`: user/AI/tool interaction records.
- `distilled-context/`: reusable summaries extracted from chats.
- `transcript-inbox/`: drop zone for imported transcripts before processing.

## Minimum Handoff

Every meaningful session should leave:

- a chat handoff,
- an audit event,
- updated work/risk/decision records if needed,
- a local commit when files changed.

## Tool

```powershell
powershell -NoProfile -ExecutionPolicy Bypass -File .\ai-system\tools\New-ChatHandoff.ps1 -Title "Session title" -Summary "What happened"
```
