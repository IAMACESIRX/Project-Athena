# Adapter Contract

An adapter is a bridge between the AI system and a tool, runtime, program, or service.

## Required Fields

- adapter id and schema version;
- adapter class and owner layer;
- surface, provider, model, tool, backend, or application identity;
- supported versions and compatibility range;
- declared capabilities and unsupported operations;
- input and output contracts;
- project-capsule and context requirements;
- read, write, network, credential, and runtime scopes;
- authority ceiling and confirmation requirements;
- consequence and mutation risk;
- state-transfer, handoff, dock, and undock behavior;
- validation and health probe;
- idempotency, timeout, retry, and rate limits;
- failure, rollback, containment, and emergency-stop behavior;
- provenance, audit, and secret-handling policy.

Machine-readable Athena model adapters should validate against
`schemas/athena-adapter.schema.json`.

## Adapter Classes

### Reader Adapter

Reads state and writes reports.

Examples:

- project scan,
- live server probe,
- SQL dump inventory.

### Writer Adapter

Creates or edits project files.

Examples:

- work item creation,
- manifest export,
- handoff generation.

### Runtime Adapter

Interacts with live server/client runtime.

Examples:

- Docker log probe,
- database status query,
- future command hub modules.

Runtime adapters must default to read-only.

### Model Adapter

Connects a replaceable model surface to the Athena Highway. It declares model
identity, context and modality limits, capability mappings, tool permissions,
local cache behavior, writeback, and handoff.

Model-local memory is never canonical project memory.

### Project Capsule Adapter

Imports, exports, docks, or migrates a project capsule while preserving
identity, lineage, permissions, evidence, unknowns, and validation.

Capsule merge and rebase operations require explicit conflict handling; they do
not default to last-writer-wins.

### Learned Application Adapter

Represents a program model learned by the Operative Duplex. It includes
supported application versions, preconditions, state transitions, side effects,
validation, rollback, evidence, and expiry or review policy.
