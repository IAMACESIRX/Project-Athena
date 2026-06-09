# Black Swan Protocol

Black swan events are low-probability, high-impact failures.

## Examples

- Local drive failure.
- Accidentally pushing private data to cloud.
- SQL restore corrupts live state.
- Client payload overwrite.
- Docker volume deletion.
- Wrong realm/network exposure.
- AI tool writes to wrong layer.

## Pre-Mortem

Before high-risk work, ask:

- What is the worst plausible failure?
- What evidence would reveal it early?
- What backup exists?
- What action should be blocked?
- What rollback is available?

## Negation Check

For every plan, ask:

- What would make this plan harmful?
- What assumption, if false, breaks it?
- What state do we not understand?
- What should we refuse to do until confirmed?

## Logging

Record high-risk concerns in:

- `diagnostics/risk-register.md`
- `audit/decision-trace-ledger.yml`
- `work/bugs.yml` or `work/backlog.yml`
