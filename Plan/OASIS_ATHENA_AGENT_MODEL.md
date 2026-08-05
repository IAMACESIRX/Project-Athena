# OASIS / ATHENA / JARVIS / JANUS Collaboration Model

Generated: 2026-07-10
Corrected: 2026-08-05
Reconciled with ATHENA project chats: 2026-08-01
Status: Plan-level identity and interface model

## Supersession notice

The original version of this file described OASIS as an outer container holding a central ATHENA brain and described JARVIS, GPT, Codex and future systems as local ATHENA limbs/adapters.

That interpretation is superseded where it conflicts with the user's corrected architecture.

- ATHENA is an independent institutional intelligence.
- JARVIS is an independent personal/executive intelligence.
- JANUS is an independent operative metacognitive intelligence.
- OASIS is a persistent digital-world, creation and simulation substrate; it is not an AI.
- GPT, Codex and other models/tools can use ATHENA adapters without every intelligence being reduced to an ATHENA adapter.

## Canonical model

```text
                         HUMAN AUTHORITY
                               |
          +--------------------+--------------------+
          |                    |                    |
       ATHENA               JARVIS                JANUS
institutional intelligence  personal/executive AI  operative metacognitive AI
          |                    |                    |
          +---------- explicit governed contracts --+
                               |
                             OASIS
          digital reality / simulation / engineering / R&D
          games / living-work / production / workshops
```

OASIS can host embodiments, simulations, project spaces and runtime services for any connected intelligence, but does not own their cognition or canonical memory.

## Terms

### ATHENA

Persistent institutional intelligence for:

- governance and evidence;
- institutional, workspace and call memory;
- project brains and ontology;
- cognitive orchestration and councils;
- continuity and audit;
- long-horizon research and coordination.

### JARVIS

Independent human-facing personal/executive intelligence for:

- immediate dialogue and intent interpretation;
- personal context and preferences;
- scheduling, devices and daily workflow;
- status and executive orchestration.

### JANUS

Independent operative metacognitive intelligence, formally:

**J.A.N.U.S. - Joint Adaptive Neurocognitive Operative System**

JANUS has an Interior Face for metacognition and an Exterior Face for perception/action. It maps unfamiliar programs, operates software without depending primarily on shell access, compiles reusable Skill Capsules and validates actual state changes.

Authoritative spec:

`docs/athena-master-expansion/JANUS_OPERATIVE_METACOGNITIVE_AI_MASTER_SPEC.md`

### OASIS

Persistent programmable digital reality for:

- engineering and digital twins;
- scientific simulation;
- games and fictional worlds;
- virtual living and workspaces;
- R&D think tanks;
- production, CAD and schematic workshops;
- human and AI embodiment.

### Adapter

A scoped interoperability layer. Adapters translate identity, task, state, evidence and authority contracts between systems. An adapter does not imply that the attached system is owned by ATHENA.

### Athena Highway

The replaceable protocol and translation layer connecting systems, models, databases, project capsules, tools and agents. It carries identity, authority, context, state, evidence, capability and result envelopes without becoming a second source of project truth.

### Project capsule

A portable project-brain package containing project identity, goals, terminology, memory, skills, source, artifacts, experiments, decisions, evidence, permissions, adapters and validation paths.

### Agent/model surface

A specific interface or worker such as GPT, Codex, a local model, browser agent, simulation service or hardware-backed runtime. It can be replaceable while institutional/project state remains durable.

## Collaboration flow

1. Human intent may enter through JARVIS, ATHENA, JANUS, OASIS or another authorized interface.
2. The receiving system identifies requester, goal, assumptions, constraints, privacy class and requested authority.
3. ATHENA may provide institutional evidence, policy, ontology and project history.
4. JARVIS may provide personal context, immediate clarification and executive scheduling.
5. JANUS may provide application/environment capability, action planning, execution and verification.
6. OASIS may provide a persistent world, simulation, digital twin or spatial workshop.
7. The Athena Highway may bind identity, authority, context, project capsule, capability, evidence requirements and failure policy for cross-system work.
8. Results return through explicit contracts as files, reports, memory updates, observations or verified outputs.
9. Each system writes to its own authoritative memory and promotes knowledge only under its governance rules.

## Cross-system request contract

```yaml
SystemRequest:
  request_id: string
  requester: human | athena | jarvis | janus | oasis_runtime | other
  target: string
  objective: string
  context_refs: [string]
  evidence_refs: [string]
  assumptions: [string]
  authority_requested: string
  privacy_class: string
  expected_state_diff: object | null
  rollback_requirement: string | null
  response_contract: object
```

## Repository mapping

| Concept | Current path |
|---|---|
| ATHENA institutional/project memory | `context.md`, `memory/`, `Plan/`, `manifests/`, `forensics/` |
| ATHENA adapter and docking work | `AI-PORTAL.md`, `agents/`, `orchestration/`, `docs/athena-master-expansion/` |
| JANUS canonical spec | `docs/athena-master-expansion/JANUS_OPERATIVE_METACOGNITIVE_AI_MASTER_SPEC.md` |
| OASIS canonical spec | `docs/athena-master-expansion/OASIS_ARCHITECTURE_SPEC.md` |
| System identity correction | `docs/athena-master-expansion/SYSTEM_IDENTITY_AND_AUTHORITY_CORRECTION_2026-08-05.md` |
| OASIS runtime intent | `Plan/OASIS_REALITY_COMPILER.md`, this document, source chat material |
| Distributed docking and hot-swap model | `Plan/ATHENA_DISTRIBUTED_COGNITIVE_FABRIC.md` |
| Athena Highway precursors | `integration/`, `orchestration/`, `schemas/message.schema.json` |
| Project capsule precursors | `projects/`, `work/`, `memory/`, `forensics/` |
| Task intake | `schemas/athena-task-intake.schema.json`, `templates/athena-task-intake.md`, `work/intake/` |
| Evidence/audit | `engine/cycle-reports/`, `forensics/`, `audit/`, `truth/` |
| Agent registry and routing | `agents/`, `orchestration/`, `council/` |
| Nexus-V/Aegis | `Nexus V/`, `Plan/NVISC*`, `Plan/NVASM*`, `Plan/NVIR*`, `Plan/NVVM*` |
| Lightcore/L.O.D.E/spatial interfaces | `docs/athena-master-expansion/` |

## Design invariants

- Human authority remains ultimate.
- ATHENA, JARVIS and JANUS retain distinct identities and memory scopes.
- OASIS remains an environment/runtime, not an AI identity.
- Cross-system links are contracts, not ownership arrows.
- Every supported agent surface needs a local adapter document or bootstrap packet.
- Adapters must read the same first-read context and write back through the same memory rules.
- Central ATHENA must own canonical institutional/project state.
- A model-specific ATHENA node is a replaceable interface and never the only copy of institutional/project intelligence.
- JANUS verifies actual state changes rather than assuming an action succeeded.
- Agent/model-local memories are scoped caches unless explicitly promoted.
- Hot swapping must close pending writes, transfer a handoff, revoke or transfer authority, and pass a replacement adapter probe.
- Project capsules must preserve source, decisions, evidence, unknowns, permissions and validation together.
- If an agent cannot write back, it must produce a handoff packet.
- Disagreements are resolved through evidence, declared authority, system contracts and human direction.
- Plugin/cloud workspaces are mirrors or execution surfaces unless explicitly promoted to canonical status.

## Open build work

1. Create formal ATHENA, JARVIS, JANUS and OASIS request/response schemas.
2. Implement JANUS world-state graph, Application Cartographer and Skill Capsule registry.
3. Define OASIS world/object/export schemas and conventional runtime prototype.
4. Add identity-aware adapter manifests under `agents/adapters/`.
5. Extend the adapter schema with model identity, capabilities, authority, context limits, state transfer, failure and writeback contracts.
6. Define project-capsule and skill-package schemas.
7. Create bootstrap instructions for each agent surface.
8. Add conflict and concurrency rules for multiple independent intelligences editing shared project state.
9. Add explicit memory and privacy boundaries per system.
10. Test a read-only dock, handoff and hot swap between two mock adapters.
11. Connect optional Nexus-V/Aegis branch/attestation semantics after conventional reference implementations work.

## One-sentence model

ATHENA knows and governs institutionally, JARVIS assists and orchestrates personally, JANUS perceives and acts operatively, and OASIS provides the persistent digital world in which people and intelligences can build, simulate, work, live and create.

This is Plan-level design intent. The current repository provides file-native precursors, not a completed OASIS runtime or completed multi-agent docking fabric.
