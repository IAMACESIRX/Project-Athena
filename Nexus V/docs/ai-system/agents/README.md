# Agents

Agents are role-bound workers in the AI-OS control plane.

An agent may be a human, Codex, GPT-style assistant, local model, external model, script, tool, or future service. The registry records intended role, authority, capabilities, and routing hints.

## Agent Contract

Every agent must know:

- identity,
- role,
- authority level,
- allowed tools,
- evidence requirements,
- memory access,
- parent coordinator,
- output format,
- escalation trigger.

