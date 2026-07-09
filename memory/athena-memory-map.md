# Athena Memory Map

Athena's memory is file-native. The repository is the durable substrate, and
each folder has a memory role. Agents should choose writeback targets based on
the type of fact being preserved.

## Memory Layers

| Layer | Purpose | Primary Paths | Write When |
|---|---|---|---|
| Identity memory | Durable definition of what Athena is. | `AI-PORTAL.md`, `identity/`, `context.md` | The system's purpose, boundaries, or operating identity changes. |
| Architecture memory | Design intent and future direction. | `Plan/`, `Plan/context.md`, `Plan/OASIS_ATHENA_AGENT_MODEL.md`, `Nexus V/docs/Plan/` | Plan concepts are interpreted, prioritized, or converted into build work. |
| Working memory | Current tasks, roadmaps, and decisions. | `work/`, `handoff/`, `continuity/` | A task is created, reprioritized, resumed, or handed off. |
| Evidence memory | Claims, observations, audit events, and cycle reports. | `forensics/`, `audit/`, `engine/cycle-reports/` | A claim needs support, a decision needs traceability, or a cycle completes. |
| Capability memory | What Athena can do and how tools are routed. | `manifests/`, `registries/`, `agents/`, `orchestration/` | A tool, agent, capability, route, or ownership rule changes. |
| Runtime memory | Execution contracts and service behavior. | `runtime/`, `observability/`, `sensory/`, `tools/` | Scripts, probes, runtime state, or service contracts change. |
| Implementation memory | Source-heavy implementation detail. | `Nexus V/`, `modules/`, `schemas/`, `templates/` | Code, schemas, hardware design, or reusable templates change. |

## Writeback Rules

1. Durable facts go in `context.md` only when they are observed or explicitly
   labeled as inference.
2. Plan-derived intent goes in `Plan/context.md` or Plan planning files before
   being treated as implementation truth.
3. Task state goes in `work/`; session continuity goes in `handoff/` or
   `continuity/`.
4. Evidence-backed decisions get a cycle report or audit record.
5. Generated outputs must be clearly named or placed in generated/report
   folders.
6. Speculative brainstorms stay in council or work files until verified.

## Intake To Memory Flow

1. Human goal enters through conversation, `AI-PORTAL.md`, or an intake packet.
2. Athena anchors context through `context.md`, `Plan/context.md`, and the
   relevant subsystem files.
3. Athena labels facts, assumptions, unknowns, and risks.
4. Athena acts through the smallest reversible change.
5. Athena verifies with file checks, tests, reports, or command output.
6. Athena writes the result to the narrowest durable memory target.

## Anti-Drift Rule

When a term changes meaning, update the local definition immediately. Current
canonical meanings:

- Athena: AI prosthetic external brain, database, and processor.
- OASIS: outer operating environment that can contain Athena, agents, tools,
  project state, and future runtime services.
- Central Athena: canonical memory, database, processor, router, and evidence
  trail.
- Local Athena adapter: the Athena-facing layer inside an agent surface such as
  Codex, Jarvis, GPT, or a future local model.
- Plan: highest-priority architecture-intent vault.
- Nexus V: hardware/toolchain implementation branch for semantic execution.
- Cycle report: evidence memory for a non-trivial Athena run.
- Intake packet: structured input contract for a task.
