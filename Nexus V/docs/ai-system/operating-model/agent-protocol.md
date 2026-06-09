# Agent Protocol

This protocol applies to AI agents and humans acting in an agent role.

## Entry Protocol

1. Read `ai-system/START-HERE.md`.
2. Read `ai-system/handoff/CURRENT_STATE.md`.
3. Read `ai-system/handoff/NEXT_ACTIONS.md`.
4. Run `ai-system/tools/Invoke-AIProjectScan.ps1`.
5. Identify the active layer before editing.

## Change Protocol

1. State the layer and intent.
2. Inspect relevant files before editing.
3. Make scoped edits.
4. Verify with a command, scan, test, or direct file inspection.
5. Commit in the layer that changed.
6. If a child repo changed, update the mega repo pointer.
7. Update handoff and risk/decision files if new context was discovered.

## Exit Protocol

1. Run `git status --ignore-submodules=untracked` in the mega repo.
2. Run `git status` in any child repo that was touched.
3. Push only to local bare remotes.
4. Record what changed in `handoff/CHANGELOG.md` or a session handoff.

## Red Lines

- Do not push to GitHub servers.
- Do not delete live-state dumps without explicit human instruction.
- Do not overwrite the game client payload casually.
- Do not run destructive Git commands unless the human explicitly asked for them.
- Do not change internet exposure without explicit human confirmation.
