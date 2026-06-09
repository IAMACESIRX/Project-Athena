# Module: Game Client

## Purpose

Maintain the ChromieCraft 3.3.5a client backup, including playable files, local account settings, addons, realmlist, and visual configuration.

## Layer

`GameClient-ChromieCraft-3.3.5a`

## Current Status

Initialized as a Git repo with a lightweight management commit. Full payload remains untracked.

## Important Files

- `WTF/`
- `Interface/`
- `Data/enUS/realmlist.wtf`
- `ReShade.ini`
- `ReShadePreset.ini`
- `reshade-shaders/`

## Risks

- Very large binary payload.
- Account-local state in `WTF`.
- Duplicated MPQ data under `backups`.
- Full Git snapshot may exceed available disk capacity.

## Recommended Handling

Track small, high-value configuration areas before committing MPQ payloads.

Suggested first partial snapshot:

- `.gitignore`
- `GIT-LAYER.md`
- `WTF`
- `Interface`
- ReShade config files
- realmlist files

## Verification

- Confirm realmlist target.
- Confirm client launches.
- Confirm addons/settings remain intact.
- Confirm no accidental full binary commit unless intended.
