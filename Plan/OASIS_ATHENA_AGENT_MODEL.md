# OASIS Athena Agent Model

Generated: 2026-07-10

This file captures the human-provided system diagram of how Athena works across
multiple AI surfaces.

## Core Model

Athena is not a single chatbot. Athena is a central external brain with local
agent adapters.

OASIS is the larger operating environment that can contain Athena, route work
between agents, and preserve the full institutional state.

```text
                         OASIS
                  [contains Athena]
                            ^
                            |
                            v
                    CENTRAL ATHENA
          memory + database + processor + router
                 /           |             \
                v            v              v
          Codex adapter   Jarvis adapter   GPT adapter
            [Athena]        [Athena]       [Athena]
```

## Terms

OASIS
: The outer operating environment. It is the full ecosystem that can host
  Athena, tools, files, agents, project state, human direction, and future
  runtime services.

Central Athena
: The canonical external brain. It stores durable context, organizes memory,
  reasons over current state, routes work, records evidence, and updates the
  project substrate.

Local Athena adapter
: The Athena-facing layer inside each agent surface. Codex, Jarvis, GPT, and
  future agents do not become independent brains; they attach to Athena through
  an adapter that loads context, follows Athena rules, acts within authority,
  and writes back results.

Agent surface
: A specific AI interface or worker, such as Codex, Jarvis, GPT, a local model,
  a tool runner, a browser agent, or a future hardware-backed runtime.

## Data Flow

1. Human intent enters through any agent surface or directly through OASIS.
2. The local Athena adapter translates that intent into Athena-compatible task
   intake: facts, assumptions, unknowns, risks, required output, and writeback
   target.
3. Central Athena anchors the task against durable memory, Plan authority,
   current context, manifests, and evidence.
4. Athena chooses the right agent/tool path.
5. The selected agent acts through its local Athena adapter.
6. Results return to central Athena as files, reports, memory updates, or
   verified outputs.
7. OASIS keeps the larger system coherent across agents and sessions.

## Why This Matters

Without the local adapter model, each AI surface becomes a disconnected worker
with its own memory drift. With the adapter model, each surface becomes a limb
of the same external brain.

The core invariant:

```text
Many agents, one Athena memory.
Many interfaces, one operating truth.
Many task surfaces, one evidence trail.
```

## Implementation Mapping

Current repository mapping:

| Concept | Current Path |
|---|---|
| Central Athena memory | `context.md`, `memory/`, `Plan/`, `manifests/`, `forensics/` |
| OASIS operating environment | Full `D:\Projects\Project Athena` repository |
| Local Athena adapter for Codex | `AI-PORTAL.md`, `START-HERE.md`, `tools/Invoke-AthenaCycle.ps1` |
| Task intake protocol | `schemas/athena-task-intake.schema.json`, `templates/athena-task-intake.md`, `work/intake/` |
| Cycle and evidence trail | `engine/cycle-reports/`, `forensics/`, `audit/` |
| Agent registry and routing | `agents/`, `orchestration/`, `council/` |
| Future semantic execution substrate | `Nexus V/`, `Plan/NVISC*`, `Plan/NVASM*`, `Plan/NVIR*`, `Plan/NVVM*` |

## Design Requirements

- Every supported agent surface needs a local Athena adapter document or
  bootstrap packet.
- Adapters must read the same first-read context.
- Adapters must write back through the same memory rules.
- Central Athena must own the canonical project state.
- OASIS must remain the container, not a competing memory.
- Agent-specific memories are caches, not authority.
- If an agent cannot write back, it must produce a handoff packet.
- If two agents disagree, Athena resolves through evidence, Plan authority, and
  human direction.

## Open Build Work

1. Define `agents/adapters/` as the home for Codex, Jarvis, GPT, and local-model
   adapter contracts.
2. Create a minimal adapter contract schema.
3. Create bootstrap instructions for each agent surface.
4. Add OASIS as a named top-level operating environment in manifests.
5. Add sync rules for importing agent-local findings back into Athena.
6. Add conflict-resolution rules for multiple agents editing the same memory.

## Status

This is a conceptual architecture model derived from the human-provided diagram.
It is now Plan-level design intent. It is not yet fully implemented as a runtime
multi-agent system.
