# QUALITY PLAN

## Purpose

Quality for Athena means the system preserves memory accurately, acts only on
evidence or labeled assumptions, remains recoverable, and converts design intent
into verifiable work.

## Quality Gates

### Q1: Context Accuracy

- `context.md` states current root identity.
- `Plan/context.md` states current architecture intent.
- `context-file-index.md` reflects added/changed files after major updates.
- Stale claims are labeled or removed from first-read files.

### Q2: Intake Discipline

- Non-trivial tasks have an intake packet.
- Intake packets name goal, active layer, priority source, known facts,
  assumptions, unknowns, risks, required output, verification, and writeback.
- Claims entering durable memory are observed or clearly labeled.

### Q3: Tool Safety

- PowerShell scripts default to the standalone Project Athena root.
- Write-mode scripts write only inside expected report/work folders.
- Runtime mutation requires explicit human intent.
- Restore or rollback notes exist before risky changes.

### Q4: Plan Traceability

- Plan concepts are not assumed implemented.
- Implementation matrices distinguish done, partial, planned, blocked, and
  speculative.
- Nexus-V source, generated outputs, and reports are not conflated.

### Q5: Verification

- JSON schemas parse.
- PowerShell scripts parse.
- Operation cycle runs or records why it cannot run.
- Nexus-V checks are run when hardware/toolchain files change.

## Review Checklist

- Are all changed first-read files current?
- Did the task use Athena decision-making?
- Is the output useful to a future agent?
- Is there a cycle report for meaningful work?
- Is the next action concrete?
