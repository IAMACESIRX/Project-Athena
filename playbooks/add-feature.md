# Playbook: Add Feature

Use when adding a new script, module, backend route, or AI capability.

## Steps

1. Define the module or feature in `registries/modules.yml`.
2. Add or update a module card in `modules/`.
3. Identify layer and ownership.
4. Implement the smallest useful version.
5. Add verification.
6. Update docs/playbook if the workflow will recur.
7. Commit in the active layer.
8. Update parent pointer if needed.

## Risk Questions

- Does this mutate live server state?
- Does this expose private data?
- Does this need human confirmation?
- Does this create a new repeated workflow that needs a script?
