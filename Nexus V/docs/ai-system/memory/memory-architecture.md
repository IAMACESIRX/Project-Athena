# Memory Architecture

The project uses three memory tiers.

## Tier 1: Working Memory

Short-lived state needed for the current task.

Examples:

- current command output,
- current file under edit,
- active issue.

Storage:

- chat/session,
- latest scan,
- current handoff.

## Tier 2: Core Long-Term Memory

Stable facts that should be read often.

Storage:

- `memory/facts.md`
- `memory/project-memory.md`
- `memory/decision-ledger.md`
- `governance/absolutes.md`

## Tier 3: Deep Archive / Strengthened Concepts

Important but not always-needed context that can be reaccessed when relevant.

Storage:

- `continuity/distilled-context/`
- `learning/concept-bank/`
- `research/`
- `audit/decision-trace-ledger.yml`

## Promotion Rules

Promote from working to long-term when:

- it changes future decisions,
- it prevents repeated mistakes,
- it defines a constraint,
- it explains causality,
- it is repeatedly rediscovered.

Promote to deep archive when:

- it is useful but not needed every session,
- it is background research,
- it is a detailed explanation,
- it supports future retrieval.
