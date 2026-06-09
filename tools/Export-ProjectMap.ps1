param(
    [string]$ProjectRoot = (Resolve-Path (Join-Path $PSScriptRoot "..\..")).Path,
    [switch]$IncludeFileCounts,
    [switch]$NoWrite
)

$ErrorActionPreference = "Stop"

function Get-GitHead {
    param([string]$Path)

    $head = & git -C $Path rev-parse --short HEAD 2>$null
    if ($LASTEXITCODE -ne 0) { return $null }
    return ($head | Select-Object -First 1).ToString()
}

function Get-Node {
    param(
        [string]$Id,
        [string]$Path,
        [string]$Type
    )

    $full = Join-Path $ProjectRoot $Path
    if ($Path -eq ".") { $full = $ProjectRoot }

    $exists = Test-Path -LiteralPath $full
    $fileCount = $null
    $sizeMB = $null

    if ($exists -and $IncludeFileCounts) {
        $measure = Get-ChildItem -LiteralPath $full -Recurse -File -Force -ErrorAction SilentlyContinue |
            Where-Object { $_.FullName -notmatch "\\.git\\" } |
            Measure-Object -Property Length -Sum
        $fileCount = $measure.Count
        $sizeMB = [math]::Round($measure.Sum / 1MB, 2)
    }

    [PSCustomObject]@{
        id = $Id
        path = $Path
        type = $Type
        exists = $exists
        head = if ($exists) { Get-GitHead -Path $full } else { $null }
        file_count = $fileCount
        size_mb = $sizeMB
    }
}

$nodes = @(
    Get-Node -Id "mega" -Path "." -Type "orchestrator_repo"
    Get-Node -Id "ai-system" -Path "ai-system" -Type "control_plane"
    Get-Node -Id "game-client" -Path "GameClient-ChromieCraft-3.3.5a" -Type "client_repo"
    Get-Node -Id "live-state" -Path "Server-Live-State" -Type "state_repo"
    Get-Node -Id "server-project" -Path "WoW-Server-Project" -Type "project_repo"
    Get-Node -Id "azerothcore-clean" -Path "WoW-Server-Project\servers\wow\azerothcore-wotlk" -Type "nested_source_repo"
    Get-Node -Id "azerothcore-playerbots" -Path "WoW-Server-Project\servers\wow\azerothcore-wotlk-playerbots" -Type "nested_source_repo"
    Get-Node -Id "mod-playerbots" -Path "WoW-Server-Project\servers\wow\azerothcore-wotlk-playerbots\modules\mod-playerbots" -Type "nested_module_repo"
)

$edges = @(
    @{ from = "mega"; to = "ai-system"; relation = "contains" }
    @{ from = "mega"; to = "game-client"; relation = "points_to" }
    @{ from = "mega"; to = "live-state"; relation = "points_to" }
    @{ from = "mega"; to = "server-project"; relation = "points_to" }
    @{ from = "server-project"; to = "azerothcore-clean"; relation = "points_to" }
    @{ from = "server-project"; to = "azerothcore-playerbots"; relation = "points_to" }
    @{ from = "azerothcore-playerbots"; to = "mod-playerbots"; relation = "contains_module" }
)

$map = [PSCustomObject]@{
    schema = "ai-system.project_map.v1"
    generated_at = (Get-Date).ToString("o")
    project_root = $ProjectRoot
    nodes = $nodes
    edges = $edges
}

if (-not $NoWrite) {
    $outDir = Join-Path $ProjectRoot "ai-system\navigation\generated"
    New-Item -ItemType Directory -Force -Path $outDir | Out-Null
    $outPath = Join-Path $outDir "project-map.json"
    $map | ConvertTo-Json -Depth 8 | Set-Content -LiteralPath $outPath -Encoding UTF8
}

$map
