# Module: Local Git Host

## Purpose

Host local bare Git remotes for the layered project without using GitHub servers.

## Path

`C:\Users\aesir\OneDrive\Desktop\WoW-Backups\local-git-host\2026-05-30_2035`

## Bare Repos

- `mega-backup-stack.git`
- `gameclient-chromiecraft-3.3.5a.git`
- `server-live-state.git`
- `wow-server-project.git`

## Risks

- Deleting this folder removes the local hosted remotes.
- It is not an off-machine backup.
- It is private and should be treated like the working copies.

## Recommended Handling

- Keep it out of the mega working repo.
- Mirror to another local disk later if desired.
- Never replace remotes with GitHub URLs unless the human explicitly asks.

## Verification

```powershell
git remote -v
git ls-remote origin
```
