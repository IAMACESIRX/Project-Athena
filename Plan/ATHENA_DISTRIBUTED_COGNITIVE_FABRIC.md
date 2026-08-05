# Athena Distributed Cognitive Fabric

Updated: 2026-08-01
Status: Plan intent; runtime implementation is incomplete.

## Definition

Athena is a distributed cognitive interface fabric, not a capability that
belongs to one model. Models dock into Athena through replaceable local nodes
and adapters. Durable intelligence is separated into independently versioned
project, group-skill, memory, routing, and governance layers.

The central rule is:

> Never store irreplaceable intelligence in only one replaceable layer.

## Four Positions

```text
                         OASIS
          future execution and collaboration habitat
                              |
                              v
                   External Athena Core
           governance + routing + evidence + memory
                     /        |         \
                    v         v          v
            AI-local node  Highway   Project capsule
                  |           |          |
                  v           v          v
              AI model   data/tools   project state
```

### AI-Local Athena Node

The model-facing compatibility layer contains:

- model-specific bootstrap instructions;
- tool and capability mappings;
- retrieval and context-window strategy;
- prompt and response grammar;
- known model limitations and fallback behavior;
- writeback and handoff rules;
- local session cache.

It must not become the sole owner of durable project memory.

### External Athena Core

The model-independent core owns:

- canonical context and project state;
- governance and human authority;
- memory routing and promotion;
- evidence and audit trails;
- capability and skill registries;
- task decomposition and orchestration;
- resource and model selection;
- conflict resolution;
- continuity and recovery.

The current repository is the file-native precursor to this core.

### Athena Highway

The highway is the replaceable interconnection layer between:

```text
models <-> Athena <-> project capsules <-> databases <-> tools <-> agents
```

Required highway services:

- capability discovery and negotiation;
- model, database, tool, and project adapters;
- authenticated identity and authority propagation;
- task, state, evidence, and result envelopes;
- context packaging and semantic compression;
- request routing and fallback ordering;
- state synchronization and conflict detection;
- idempotency, retry, timeout, and failure isolation;
- provenance and audit events;
- import, export, and migration contracts.

The highway must transport state without silently changing its meaning or
authority.

### Project Capsule

A project capsule is a portable project-brain package containing:

```text
project-capsule/
  manifest
  identity-and-goals
  project-memory
  terminology-and-ontology
  skills
  source-and-artifacts
  experiments
  decisions
  evidence-and-audit
  adapters-and-tool-routes
  permissions
  validation-tests
```

The existing `projects/`, `memory/`, `work/`, `Plan/`, `forensics/`, and
registry structures are file-native precursors. A future capsule manifest must
point to these assets without copying authoritative state into competing trees.

## Skill Ownership Classes

| Class | Owner | Examples | Portability |
|---|---|---|---|
| Model-specific | AI-local node | prompt grammar, context limits, model tool mapping | similar model surfaces |
| Project-specific | project capsule | Nexus-V lowering rules, Lightcore constraints, project terminology | travels with project |
| Group/generalized | external Athena | evidence review, experimental design, ontology building | reusable across projects |
| Backend/native interface | highway adapter | SQL, vector store, files, APIs, audit writeback | reusable for matching backend |

No skill may be promoted from one ownership class to another without a source,
compatibility test, and named owner.

## Docking Contract

A model is docked only when the following handshake succeeds:

1. The model surface presents its identity, version, context limits, modalities,
   tool permissions, and adapter version.
2. Athena returns the relevant project capsule manifest, authority envelope,
   read scope, write scope, and required invariants.
3. The highway negotiates message, evidence, memory, and failure contracts.
4. A read-only capability probe confirms that required sources are reachable.
5. A bounded writeback test confirms that provenance and validation survive.
6. The model enters an available state only after the adapter test passes.

## Hot-Swap Contract

Hot swapping replaces a model or backend without losing project continuity.

Preconditions:

- pending writes are committed, aborted, or transferred explicitly;
- session state is compressed into a handoff packet;
- unresolved assumptions and unknowns remain labeled;
- active authority grants are revoked or transferred;
- the replacement adapter passes the docking contract;
- the project capsule and canonical memory remain unchanged unless migration is
  part of the approved operation.

Postconditions:

- the replacement can reconstruct the active task;
- evidence identifiers still resolve;
- no model-local cache is treated as canonical;
- an audit record identifies the old and new surfaces;
- rollback to the previous adapter remains possible where supported.

## Capsule Version Operations

Athena may borrow version-state verbs from Nexus-V, but file-level operations
must remain distinct from hardware claims.

| Operation | Capsule Meaning |
|---|---|
| `SNAPSHOT` | capture a recoverable project state reference |
| `BRANCH` | create an alternate work direction in the same project lineage |
| `FORK` | create an independently governed project lineage |
| `CLONE` | duplicate a reusable package without changing lineage intent |
| `DIFF` | compare state, authority, evidence, skills, and artifacts |
| `MERGE` | combine compatible changes after conflict and evidence review |
| `REBASE` | move project work onto a newer shared foundation |
| `ROLLBACK` | restore a named known-good state |
| `DOCK` | attach a model, tool, backend, or capsule |
| `UNDOCK` | detach it after state and authority closure |
| `HOTSWAP` | replace a docked component while preserving continuity |

## Memory Separation

The fabric must keep these memory scopes distinct:

- institutional memory: global, governed, audited, and durable;
- shared/group memory: reusable across authorized projects;
- workspace/project memory: project-specific and capsule-owned;
- call/session memory: temporary task context and scratch state;
- model-local cache: replaceable optimization, never authority.

Promotion follows validation and governance. Workspace or session observations
cannot overwrite institutional memory directly.

## Conflict Resolution

When two nodes or capsules disagree:

1. Preserve both claims and their provenance.
2. Determine whether the conflict is factual, semantic, policy, or version
   divergence.
3. Apply `truth/source-priority.md` to factual state.
4. Apply Plan authority to design intent.
5. Apply human direction to goals, permissions, and unresolved value choices.
6. Verify the selected resolution.
7. Record rejected alternatives when they remain useful or reversible.

Last-writer-wins is not an acceptable default for canonical memory.

## Security Invariants

- Human authority remains ultimate.
- Every request carries identity, project, task, scope, and evidence context.
- Adapters receive least privilege.
- Secrets are referenced through protected handles rather than copied into
  capsules or prompts.
- Consequential actions require the level of confirmation defined by policy.
- Untrusted content cannot grant itself authority.
- A model cannot promote its own output solely because it generated it.
- All mutations have provenance, validation, and a recoverable state boundary.

## Current Repository Mapping

| Fabric Element | Current Precursor | Maturity |
|---|---|---|
| External Athena core | root repository, `memory/`, `engine/`, `governance/`, `forensics/` | active file-native foundation |
| Codex local node | `AI-PORTAL.md`, `START-HERE.md`, intake and cycle tooling | manual precursor |
| Highway | `integration/`, `orchestration/`, `schemas/message.schema.json` | specified/scaffolded |
| Project capsule | `projects/`, `work/`, project-scoped Plan and memory files | partial file structure |
| General skill library | `cognition/`, `playbooks/`, `tools/` | mixed implemented/specified |
| Model-specific skills | `model-ops/`, `agents/`, router entries | partial registry |
| Durable databases | Git/file tree and structured registries | active file-native layer |
| OASIS runtime | conceptual documents only | planned |

## Build Sequence

1. Extend adapter contracts with identity, capability, authority, state, and
   writeback fields.
2. Define project-capsule and skill-package schemas.
3. Implement one read-only Codex adapter manifest against the current repo.
4. Implement a deterministic handoff and hot-swap fixture between two mock
   model surfaces.
5. Add conflict tests for concurrent project-memory changes.
6. Add capability discovery and routing without runtime mutation.
7. Add governed writeback after the read-only path is stable.

## Success Criteria

- A model can be removed without losing canonical project state.
- A replacement model can reconstruct the task from the capsule and handoff.
- Project-specific and generalized skills remain separately versioned.
- Backend adapters can change without rewriting project intent.
- Every state change is attributable and reversible where promised.
- No single model session is the only copy of irreplaceable intelligence.
