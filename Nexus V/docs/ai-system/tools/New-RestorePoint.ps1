param(
    [Parameter(Mandatory = $true)]
    [string]$Name,

    [string]$ProjectRoot = "",
    [switch]$CreateTags,
    [switch]$IncludeBundles
)

$ErrorActionPreference = "Stop"

if (-not $ProjectRoot) {
    $ProjectRoot = (Resolve-Path (Join-Path $PSScriptRoot "..\..")).Path
}

function Get-RepoRecord {
    param(
        [string]$Id,
        [string]$Path,
        [string]$TagPrefix
    )

    $fullPath = Join-Path $ProjectRoot $Path
    if ($Path -eq ".") { $fullPath = $ProjectRoot }

    $head = (& git -C $fullPath rev-parse --short HEAD 2>$null | Select-Object -First 1).ToString()
    $status = (& git -C $fullPath status --short --branch 2>$null) -join "`n"
    $tag = "$TagPrefix-$Id"

    if ($CreateTags) {
        $existing = & git -C $fullPath tag --list $tag
        if (-not $existing) {
            & git -C $fullPath tag -a $tag -m "Restore point $TagPrefix for $Id"
            if ($LASTEXITCODE -ne 0) { throw "Failed to tag $Id" }
        }
    }

    [PSCustomObject]@{
        id = $Id
        path = $Path
        head = $head
        tag = if ($CreateTags) { $tag } else { $null }
        status = $status
    }
}

$timestamp = Get-Date -Format "yyyyMMdd-HHmmss"
$safeName = ($Name.ToLowerInvariant() -replace "[^a-z0-9]+", "-").Trim("-")
if (-not $safeName) { $safeName = "restore-point" }
$restoreId = "RP-$timestamp-$safeName"
$tagPrefix = "restore/$timestamp-$safeName"

$repos = @(
    Get-RepoRecord -Id "mega" -Path "." -TagPrefix $tagPrefix
    Get-RepoRecord -Id "game-client" -Path "GameClient-ChromieCraft-3.3.5a" -TagPrefix $tagPrefix
    Get-RepoRecord -Id "live-state" -Path "Server-Live-State" -TagPrefix $tagPrefix
    Get-RepoRecord -Id "server-project" -Path "WoW-Server-Project" -TagPrefix $tagPrefix
)

$manifest = [PSCustomObject]@{
    schema = "ai-system.restore_point.v1"
    id = $restoreId
    name = $Name
    created_at = (Get-Date).ToString("o")
    created_tags = [bool]$CreateTags
    included_bundles = [bool]$IncludeBundles
    repos = $repos
    limitations = @(
        "Untracked game client payload is not protected by Git restore point.",
        "Git bundles include committed history only.",
        "Full filesystem backup requires separate storage target."
    )
}

$outDir = Join-Path $ProjectRoot "ai-system\restore\restore-points"
New-Item -ItemType Directory -Force -Path $outDir | Out-Null
$manifestPath = Join-Path $outDir "$restoreId.json"
$manifest | ConvertTo-Json -Depth 8 | Set-Content -LiteralPath $manifestPath -Encoding UTF8

if ($IncludeBundles) {
    $bundleDir = Join-Path $ProjectRoot "ai-system\restore\bundles\$restoreId"
    New-Item -ItemType Directory -Force -Path $bundleDir | Out-Null

    foreach ($repo in $repos) {
        $repoPath = Join-Path $ProjectRoot $repo.path
        if ($repo.path -eq ".") { $repoPath = $ProjectRoot }
        $bundlePath = Join-Path $bundleDir "$($repo.id).bundle"
        & git -C $repoPath bundle create $bundlePath --all
        if ($LASTEXITCODE -ne 0) { throw "Failed to create bundle for $($repo.id)" }
    }
}

Write-Host $manifestPath
