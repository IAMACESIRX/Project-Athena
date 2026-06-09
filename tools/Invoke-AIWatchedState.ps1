param(
    [string]$ProjectRoot = (Resolve-Path (Join-Path $PSScriptRoot "..\..")).Path,
    [int]$MaxFiles = 5000,
    [switch]$NoBaselineUpdate,
    [switch]$NoWrite
)

$ErrorActionPreference = "Stop"

$aiRoot = Join-Path $ProjectRoot "ai-system"
$baselineDir = Join-Path $aiRoot "sensory\baselines"
$baselinePath = Join-Path $baselineDir "watched-state-baseline.csv"
$changeJson = Join-Path $aiRoot "sensory\scans\latest-watched-changes.json"
$changeMd = Join-Path $aiRoot "sensory\scans\latest-watched-changes.md"

function Get-RelativePath {
    param([string]$Path)
    if ($Path.StartsWith($ProjectRoot)) {
        return $Path.Substring($ProjectRoot.Length + 1) -replace "\\", "/"
    }
    return $Path
}

$watchRoots = @(
    (Join-Path $ProjectRoot "ai-system"),
    (Join-Path $ProjectRoot "Server-Live-State"),
    (Join-Path $ProjectRoot "WoW-Server-Project\scripts"),
    (Join-Path $ProjectRoot "WoW-Server-Project\docs"),
    (Join-Path $ProjectRoot "WoW-Server-Project\servers\wow\azerothcore-wotlk-playerbots\modules\mod-playerbots\conf")
)

$exclude = "\\.git\\|\\.venv\\|\\node_modules\\|\\build\\|\\_deps\\|\\CMakeFiles\\|\\Data\\|\\Cache\\|\\WDB\\|\\Plan\\"
$current = New-Object 'System.Collections.Generic.List[object]'

foreach ($root in $watchRoots) {
    if (-not (Test-Path -LiteralPath $root)) { continue }
    Get-ChildItem -LiteralPath $root -Recurse -File -Force -ErrorAction SilentlyContinue |
        Where-Object { $_.FullName -notmatch $exclude -and $_.Length -lt 104857600 } |
        Sort-Object FullName |
        Select-Object -First $MaxFiles |
        ForEach-Object {
            $hash = (Get-FileHash -LiteralPath $_.FullName -Algorithm SHA256).Hash
            $current.Add([PSCustomObject]@{
                path = Get-RelativePath -Path $_.FullName
                hash = $hash
                last_write = $_.LastWriteTime.ToString("o")
                bytes = $_.Length
            }) | Out-Null
        }
}

$old = @()
$bootstrap = -not (Test-Path -LiteralPath $baselinePath)
if (-not $bootstrap) {
    $old = @(Import-Csv -LiteralPath $baselinePath)
}

$oldMap = @{}
foreach ($item in $old) { $oldMap[$item.path] = $item }
$currentMap = @{}
foreach ($item in $current) { $currentMap[$item.path] = $item }

$added = @()
$modified = @()
$removed = @()

foreach ($item in $current) {
    if (-not $oldMap.ContainsKey($item.path)) {
        $added += $item
    }
    elseif ($oldMap[$item.path].hash -ne $item.hash) {
        $modified += $item
    }
}

foreach ($item in $old) {
    if (-not $currentMap.ContainsKey($item.path)) {
        $removed += $item
    }
}

$report = [PSCustomObject]@{
    schema = "ai-system.watched_state_changes.v1"
    generated_at = (Get-Date).ToString("o")
    project_root = $ProjectRoot
    bootstrap = $bootstrap
    watched_count = $current.Count
    added_count = $added.Count
    modified_count = $modified.Count
    removed_count = $removed.Count
    added = $added
    modified = $modified
    removed = $removed
}

if (-not $NoWrite) {
    New-Item -ItemType Directory -Force -Path $baselineDir | Out-Null
    New-Item -ItemType Directory -Force -Path (Split-Path -Parent $changeJson) | Out-Null

    $report | ConvertTo-Json -Depth 8 | Set-Content -LiteralPath $changeJson -Encoding UTF8

    $md = @()
    $md += "# Watched State Changes"
    $md += ""
    $md += "Generated: $($report.generated_at)"
    $md += "Bootstrap: $bootstrap"
    $md += "Watched Files: $($current.Count)"
    $md += "Added: $($added.Count)"
    $md += "Modified: $($modified.Count)"
    $md += "Removed: $($removed.Count)"
    $md += ""
    $md += "## Added"
    if ($added.Count -eq 0) { $md += "- none" } else { $added | Select-Object -First 40 | ForEach-Object { $md += "- $($_.path)" } }
    $md += ""
    $md += "## Modified"
    if ($modified.Count -eq 0) { $md += "- none" } else { $modified | Select-Object -First 40 | ForEach-Object { $md += "- $($_.path)" } }
    $md += ""
    $md += "## Removed"
    if ($removed.Count -eq 0) { $md += "- none" } else { $removed | Select-Object -First 40 | ForEach-Object { $md += "- $($_.path)" } }
    $md | Set-Content -LiteralPath $changeMd -Encoding UTF8

    if (-not $NoBaselineUpdate) {
        $current | Export-Csv -LiteralPath $baselinePath -NoTypeInformation -Encoding UTF8
    }
}

$report

