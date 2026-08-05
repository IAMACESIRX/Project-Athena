# Athena Context Cache

This directory contains a scoped local cache of the ChatGPT project `ATHENA`.

- Project chats: 5
- Total turns: 249
- Uploaded project sources: 0
- Project instructions: empty
- Project memory: Default
- Retrieved: 2026-08-01T02:53:59.777Z

Each `.jsonl` file contains one complete ChatGPT turn per line. The cache preserves message text and turn metadata and excludes chats outside ATHENA.

Supporting records:

- `AUDIT.md`: retrieval coverage, integrity checks, and remaining edge cases.
- `RECONCILIATION.md`: comparison between chat concepts and repository state.
- `ASSET_INVENTORY.md`: verified images, source mapping limits, missing bundles,
  and generated documents.
- `Plan/CHAT_DERIVED_CONCEPT_REGISTER.md`: promoted, evidence-bounded project
  concepts.

Use `rg -i "search terms" athena_context` from the repository root to search
the cache. Refresh the cache after adding or changing ATHENA project chats, and
re-run the audit before treating the refresh as complete.

Do not edit the JSONL records in place. Treat them as source evidence. The
verified 58-image package is preserved under
`athena_context/assets/generated-storyboards-2026-08-01/`. Put future recovered
binary outputs under `athena_context/assets/inbox/`, hash and inspect them, then
update `ASSET_INVENTORY.md`.
