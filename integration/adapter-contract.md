# Adapter Contract

An adapter is a bridge between the AI system and a tool, runtime, program, or service.

## Required Fields

- adapter id,
- version,
- owner layer,
- input files,
- output files,
- read scope,
- write scope,
- runtime mutation risk,
- confirmation requirements,
- failure behavior.

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
