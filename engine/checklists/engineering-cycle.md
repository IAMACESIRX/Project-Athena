# Engineering Cycle Checklist

## Before Editing

- Identify target layer and module.
- Check worktree status.
- Read nearby code or docs.
- Check ownership and edit contract.
- Create restore point when the blast radius is high.

## During Editing

- Keep changes scoped.
- Prefer existing patterns.
- Avoid unrelated refactors.
- Add comments only where they reduce confusion.
- Keep generated artifacts separate when that improves auditability.

## After Editing

- Run targeted validation.
- Run integrity and forensic verification when metadata changed.
- Update maps/manifests if files or tools changed.
- Add audit/handoff/changelog entry.
- Commit locally when appropriate.

