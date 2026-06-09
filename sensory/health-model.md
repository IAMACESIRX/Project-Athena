# Health Model

## Green

- All active layers clean or intentionally documented.
- All local remotes are local disk paths.
- Local bare remotes contain current branch heads.
- Handoff reflects latest major changes.
- No unresolved high-risk restore blockers.

## Yellow

- Game client payload is intentionally untracked.
- Broken local dev environment exists but is documented.
- Restore scripts need path updates.
- Disk free space is constrained.

## Red

- Any layer remote points to GitHub server without human approval.
- Live-state SQL missing or corrupt.
- Destructive Docker/database action occurred without confirmation.
- Mega repo pointer does not match child repo after child commit.
- Restore flow cannot find required SQL dumps.
