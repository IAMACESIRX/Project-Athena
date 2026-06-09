# Event Bus

The current event bus is file-based. Future implementations may use NATS, RabbitMQ, Kafka, a local queue, or a database-backed scheduler.

## Event Types

- `TaskCreated`
- `TaskAssigned`
- `TaskCompleted`
- `DecisionMade`
- `KnowledgeUpdated`
- `AuditRaised`
- `AgentCreated`
- `AgentRetired`
- `ModelRouted`
- `ToolCalled`
- `HumanApprovalRequested`

## Current File Targets

- Audit events: `ai-system/audit/events/`
- Handoffs: `ai-system/handoff/sessions/`
- Work items: `ai-system/work/work-items/`
- Cycle reports: `ai-system/engine/cycle-reports/`

