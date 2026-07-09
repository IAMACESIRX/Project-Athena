# TODO

## Now

- Keep `context.md`, `Plan/context.md`, and `context-file-index.md` current.
- Use `work/intake/ATHENA-INTAKE-20260710-003-update-athena.md` as the current
  sample intake packet.
- Verify standalone path normalization for the PowerShell tools.
- Validate `schemas/athena-task-intake.schema.json`.
- Keep `Plan/OASIS_ATHENA_AGENT_MODEL.md` aligned with the human-provided
  OASIS/Athena diagram.
- Keep root Plan files mirrored into `Nexus V/docs/Plan` when they are intended
  to remain archive-equivalent.

## Next

- Fill `Plan/IMPLEMENTATION_MATRIX.md` with detailed links from AI-OS,
  Athena, Odysseus, Nexus-V, NVISC, NVASM, NVIR, and NVVM concepts to current
  files.
- Expand `Nexus V/docs/NEXUS-V-IMPLEMENTATION-MATRIX.md` with RTL/toolchain
  status and missing tests.
- Create work items for the highest-priority gaps from the implementation
  matrix.
- Add expected traces for Nexus-V regression.
- Create `agents/adapters/` contracts for Codex, Jarvis, GPT, and future local
  model surfaces.
- Define sync and conflict-resolution rules between local Athena adapters and
  central Athena memory.
- Decide whether local-only governance should remove, ignore, or explicitly
  allow the current GitHub remote.

## Later

- Build a richer Athena operator console.
- Add persistent task state and scheduler contracts.
- Add graph/vector/relational memory adapters.
- Add Plan extraction tooling.
- Add CI-like local checks for schemas, tool syntax, and Nexus-V reports.

## Parking Lot

- Full autonomous operation.
- Cloud synchronization.
- Runtime mutation tools.
- UI dashboard.
