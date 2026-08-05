# Project Map

## Current Topology

```text
Project Athena/
  AI-PORTAL.md                         universal AI entry point
  context.md                           whole-project context
  context-file-index.md                repository file index
  Plan/                                architecture intent and design authority
  Nexus V/                             hardware, RTL, toolchain, generated outputs
  engine/                              operation cycle and cycle reports
  memory/                              durable Athena memory contracts
  work/                                working memory, roadmaps, intake packets
  cognition/                           reasoning protocols
  council/                             decision roles and reasoning rounds
  tools/                               local PowerShell tools
  schemas/                             machine contracts
  templates/                           reusable markdown templates
  manifests/                           machine-readable project indexes
  registries/                          ownership, layer, module, interface maps
```

GitHub Wiki companion index: `https://github.com/IAMACESIRX/Project-Athena/wiki`

## Navigation Rules

- Use `AI-PORTAL.md` for universal entry.
- Use the GitHub Wiki as a companion orientation index, not a source-of-truth replacement.
- Use `context.md` for the current whole-project explanation.
- Use `Plan/context.md` for Plan-specific architecture authority.
- Use `memory/athena-memory-map.md` to choose writeback targets.
- Use `work/intake/` for non-trivial task intake packets.
- Use `engine/order-of-operations.md` for the processor loop.
- Use `engine/cycle-reports/` for auditable run records.
- Use `Plan/` when architecture intent or product direction matters.
- Use `Nexus V/` when implementation state, RTL, toolchain, or generated
  hardware artifacts matter.

## Source Of Truth By Question

- "What is Athena?" -> `context.md` and `AI-PORTAL.md`
- "What does Plan intend?" -> `Plan/context.md` and `Plan/`
- "Where should I write memory?" -> `memory/athena-memory-map.md`
- "What is the next build step?" -> `work/ATHENA-FIRST-STEPS.md`
- "What files exist?" -> `context-file-index.md`
- "What can tools do?" -> `manifests/tool-index.yml`
- "What is safe?" -> `governance/absolutes.md`
- "What happened in a run?" -> `engine/cycle-reports/`
- "What is implemented in Nexus V?" -> `Nexus V/docs/NEXUS-V-IMPLEMENTATION-MATRIX.md`
