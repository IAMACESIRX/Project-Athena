# Absolutes

These rules override convenience.

## A-001: Local-Only By Default

Do not push this project to GitHub servers or any cloud remote unless the human explicitly changes this rule.

## A-002: Preserve Recoverability

Before changing live-state, restore scripts, server runtime, or client payload files, identify how to get back to the previous state.

## A-003: Do Not Destroy State Casually

Do not delete SQL dumps, Docker volumes, client account state, or Git history without explicit human instruction.

## A-004: Commit At The Correct Layer

If a child repo changes, commit the child first. Then update and commit the child pointer in the mega repo.

## A-005: Private Data Stays Private

SQL dumps, account data, IPs, host paths, and client `WTF` files are private.

## A-006: Runtime Mutation Needs Intent

Reading logs and status is allowed. Starting, stopping, importing, overwriting, deleting, or changing network exposure needs clear human intent.

## A-007: Handoff Is Part Of The Work

If the session changes system state or learns important facts, update handoff, memory, risk, issue, or work files.

## A-008: Generated State Must Be Marked

Generated maps, scans, and reports must live in generated/report folders or be clearly named so they are not confused with human-authored source of truth.
