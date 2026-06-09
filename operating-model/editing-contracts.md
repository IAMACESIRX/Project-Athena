# Editing Contracts

## Mega Repo

Use for coordination files, AI system docs, and child repo pointers.

Do not copy child repo payloads into separate mega folders.

## Game Client Repo

Allowed targeted edits:

- `WTF`
- `Interface`
- ReShade config files
- `Data/enUS/realmlist.wtf`

Caution:

- `Data/*.MPQ`
- duplicated `backups/Data/*.MPQ`
- executable and DLL payloads

## Server Live-State Repo

Allowed:

- new dated SQL exports,
- restore docs,
- restore scripts,
- Docker metadata.

Caution:

- manual SQL edits,
- account rows,
- password/hash material,
- IP addresses.

## Server Project Repo

Allowed:

- backend code,
- docs,
- scripts,
- module definitions,
- controlled changes to nested repo pointers.

Caution:

- nested upstream repos,
- Docker volume operations,
- restore paths with machine-specific assumptions.
