# Git Layer Protocol

## Layer Order

1. Nested upstream repos, if changed.
2. Child repo containing the actual change.
3. Mega repo pointer update.

## Normal Child Change

```powershell
Set-Location .\Server-Live-State
git status
git add .
git commit -m "Snapshot live state"
git push

Set-Location ..
git add Server-Live-State
git commit -m "Update live-state pointer"
git push
```

## Parent Status

Use this when the game client payload remains intentionally untracked:

```powershell
git status --ignore-submodules=untracked
```

## Cloud Push Rule

No GitHub server push. Origins for the four management repos must be local disk paths.
