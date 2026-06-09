# Playbook: Update Game Client

Use when changing client state such as addons, realmlist, ReShade, or account-local settings.

## Preflight

- Decide whether this is a targeted config commit or full payload commit.
- Check free disk space before staging large files.
- Avoid `git add .` unless full payload commit is intentional.

## Suggested Targeted Commit

```powershell
Set-Location .\GameClient-ChromieCraft-3.3.5a
git add .gitignore GIT-LAYER.md WTF Interface ReShade.ini ReShadePreset.ini dxvk.conf
git status
git commit -m "Snapshot client config"
git push
```

## Parent Pointer

```powershell
Set-Location ..
git add GameClient-ChromieCraft-3.3.5a
git commit -m "Update game client pointer"
git push
```
