# Message Protocol

All agent-to-agent messages should be representable with:

- message ID,
- timestamp,
- sender,
- recipient,
- project ID,
- task ID,
- priority,
- message type,
- confidence,
- evidence IDs,
- payload,
- requested output.

## Message Types

- `request`
- `response`
- `observation`
- `decision`
- `audit`
- `escalation`
- `alert`
- `knowledge_update`
- `handoff`

