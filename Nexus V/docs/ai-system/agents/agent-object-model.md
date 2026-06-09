# Agent Object Model

Every agent profile should include:

- `agent_id`
- `name`
- `type`
- `role`
- `authority_level`
- `capabilities`
- `tools_allowed`
- `memory_access`
- `knowledge_access`
- `parent_supervisor`
- `active_tasks`
- `performance_metrics`
- `trust_domains`
- `escalation_triggers`

The object model is deliberately file-native now. Future runtimes can convert this into API records or database rows.

