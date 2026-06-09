param(
    [string]$ProjectRoot = (Resolve-Path (Join-Path $PSScriptRoot "..\..")).Path,
    [switch]$Commit,
    [switch]$Push,
    [switch]$AllowDirtyChildren,
    [string]$Message = "Update child repo pointers"
)

$ErrorActionPreference = "Stop"

$children = @(
    "GameClient-ChromieCraft-3.3.5a",
    "Server-Live-State",
    "WoW-Server-Project"
)

$dirtyChildren = @()

foreach ($child in $children) {
    $childPath = Join-Path $ProjectRoot $child
    $trackedDirty = & git -C $childPath status --porcelain --untracked-files=no
    if ($LASTEXITCODE -ne 0) {
        throw "Could not inspect child repo: $child"
    }

    if ($trackedDirty) {
        $dirtyChildren += $child
    }
}

if ($dirtyChildren.Count -gt 0 -and -not $AllowDirtyChildren) {
    Write-Host "Tracked changes exist inside child repos. Commit them first or rerun with -AllowDirtyChildren."
    $dirtyChildren | ForEach-Object { Write-Host " - $_" }
    exit 1
}

foreach ($child in $children) {
    & git -C $ProjectRoot add $child
    if ($LASTEXITCODE -ne 0) {
        throw "Failed to stage child pointer: $child"
    }
}

$staged = & git -C $ProjectRoot diff --cached --name-only

if (-not $staged) {
    Write-Host "No child repo pointer changes to commit."
    exit 0
}

Write-Host "Staged child pointer changes:"
$staged | ForEach-Object { Write-Host " - $_" }

if ($Commit) {
    & git -C $ProjectRoot commit -m $Message
    if ($LASTEXITCODE -ne 0) {
        throw "Failed to commit child pointer changes."
    }

    if ($Push) {
        & git -C $ProjectRoot push
        if ($LASTEXITCODE -ne 0) {
            throw "Failed to push mega repo to local origin."
        }
    }
}
else {
    Write-Host "Run again with -Commit to create the mega repo pointer commit."
}
