param(
    [string]$ProjectRoot = (Resolve-Path (Join-Path $PSScriptRoot "..\..")).Path,
    [int]$MaxFiles = 40,
    [int]$TailLines = 500,
    [switch]$NoWrite
)

$ErrorActionPreference = "Stop"

$aiRoot = Join-Path $ProjectRoot "ai-system"
$catalogPath = Join-Path $aiRoot "observability\log-signatures.json"
$reportDir = Join-Path $aiRoot "observability\reports"
$queuePath = Join-Path $aiRoot "diagnostics\resolvable-issues.md"

function Get-RelativePath {
    param([string]$Path)
    if ($Path.StartsWith($ProjectRoot)) {
        return $Path.Substring($ProjectRoot.Length + 1) -replace "\\", "/"
    }
    return $Path
}

function Escape-Cell {
    param([string]$Value)
    if ($null -eq $Value) { return "" }
    return ($Value -replace "\|", "/" -replace "`r?`n", " ").Trim()
}

function Set-TextFileWithRetry {
    param(
        [string]$Path,
        [object]$Value
    )

    $text = if ($Value -is [array]) {
        ($Value -join [Environment]::NewLine) + [Environment]::NewLine
    }
    else {
        [string]$Value
    }

    $tmp = "$Path.tmp-$PID"
    $lastError = $null
    for ($attempt = 1; $attempt -le 10; $attempt++) {
        try {
            Set-Content -LiteralPath $tmp -Value $text -Encoding UTF8
            Move-Item -LiteralPath $tmp -Destination $Path -Force
            return
        }
        catch {
            $lastError = $_
            Start-Sleep -Milliseconds (250 * $attempt)
        }
    }

    throw $lastError
}

if (-not (Test-Path -LiteralPath $catalogPath)) {
    throw "Missing log signature catalog: $catalogPath"
}

$catalog = Get-Content -Raw -LiteralPath $catalogPath | ConvertFrom-Json
$signatures = @($catalog.signatures)

$files = New-Object 'System.Collections.Generic.List[object]'

$gameClient = Join-Path $ProjectRoot "GameClient-ChromieCraft-3.3.5a"
if (Test-Path -LiteralPath $gameClient) {
    Get-ChildItem -LiteralPath $gameClient -File -ErrorAction SilentlyContinue |
        Where-Object { $_.Extension.ToLowerInvariant() -in @(".log", ".txt") } |
        ForEach-Object { $files.Add($_) | Out-Null }
}

$topLevelRoots = @(
    (Join-Path $ProjectRoot "Server-Live-State"),
    (Join-Path $ProjectRoot "WoW-Server-Project")
)

foreach ($root in $topLevelRoots) {
    if (-not (Test-Path -LiteralPath $root)) { continue }
    Get-ChildItem -LiteralPath $root -File -ErrorAction SilentlyContinue |
        Where-Object { $_.Extension.ToLowerInvariant() -in @(".log", ".txt", ".err", ".out") -or $_.Name.ToLowerInvariant() -match "log|stderr|stdout|error" } |
        ForEach-Object { $files.Add($_) | Out-Null }
}

$logRoots = @(
    (Join-Path $ProjectRoot "Server-Live-State\logs"),
    (Join-Path $ProjectRoot "WoW-Server-Project\logs"),
    (Join-Path $ProjectRoot "WoW-Server-Project\servers\wow\azerothcore-wotlk\logs"),
    (Join-Path $ProjectRoot "WoW-Server-Project\servers\wow\azerothcore-wotlk-playerbots\logs"),
    (Join-Path $ProjectRoot "WoW-Server-Project\servers\wow\azerothcore-wotlk-playerbots\var\logs"),
    (Join-Path $ProjectRoot "WoW-Server-Project\servers\wow\azerothcore-wotlk-playerbots\docker\logs")
)

$exclude = "\\.git\\|\\.venv\\|\\node_modules\\|\\build\\|\\_deps\\|\\CMakeFiles\\|\\Data\\|\\Cache\\|\\WDB\\"
foreach ($root in $logRoots) {
    if (-not (Test-Path -LiteralPath $root)) { continue }
    Get-ChildItem -LiteralPath $root -Recurse -File -ErrorAction SilentlyContinue |
        Where-Object {
            $_.FullName -notmatch $exclude -and
            ($_.Extension.ToLowerInvariant() -in @(".log", ".txt", ".err", ".out") -or $_.Name.ToLowerInvariant() -match "log|stderr|stdout|error")
        } |
        Sort-Object LastWriteTime -Descending |
        Select-Object -First $MaxFiles |
        ForEach-Object { $files.Add($_) | Out-Null }
}

$dedup = @{}
foreach ($file in $files) {
    $dedup[$file.FullName] = $file
}
$scanFiles = @($dedup.Values | Sort-Object LastWriteTime -Descending | Select-Object -First $MaxFiles)

$hits = New-Object 'System.Collections.Generic.List[object]'
$fileSummaries = New-Object 'System.Collections.Generic.List[object]'

foreach ($file in $scanFiles) {
    $rel = Get-RelativePath -Path $file.FullName
    $lines = @()
    try {
        $lines = @(Get-Content -LiteralPath $file.FullName -Tail $TailLines -ErrorAction Stop)
    }
    catch {
        $hits.Add([PSCustomObject]@{
            signature_id = "LOG-READ-FAIL"
            severity = "yellow"
            category = "filesystem"
            title = "Log read failed"
            file = $rel
            line = 0
            sample = $_.Exception.Message
            suggested_action = "Check file lock, encoding, or permissions."
        }) | Out-Null
        continue
    }

    $localHitCount = 0
    for ($i = 0; $i -lt $lines.Count; $i++) {
        $line = [string]$lines[$i]
        foreach ($sig in $signatures) {
            if ([regex]::IsMatch($line, [string]$sig.regex)) {
                $localHitCount++
                if (@($hits | Where-Object { $_.signature_id -eq $sig.id -and $_.file -eq $rel }).Count -lt 5) {
                    $hits.Add([PSCustomObject]@{
                        signature_id = $sig.id
                        severity = $sig.severity
                        category = $sig.category
                        title = $sig.title
                        file = $rel
                        line = $i + 1
                        sample = if ($line.Length -gt 260) { $line.Substring(0, 260) } else { $line }
                        suggested_action = $sig.suggested_action
                    }) | Out-Null
                }
            }
        }
    }

    $fileSummaries.Add([PSCustomObject]@{
        path = $rel
        bytes = $file.Length
        last_write = $file.LastWriteTime.ToString("o")
        scanned_tail_lines = $lines.Count
        matched_signatures = $localHitCount
    }) | Out-Null
}

$status = "PASS"
if (@($hits | Where-Object { $_.severity -eq "red" }).Count -gt 0) {
    $status = "FAIL"
}
elseif ($hits.Count -gt 0) {
    $status = "WARN"
}

$hitArray = @($hits.ToArray())
$fileSummaryArray = @($fileSummaries.ToArray())

$report = [PSCustomObject]@{
    schema = "ai-system.log_intelligence.v1"
    generated_at = (Get-Date).ToString("o")
    project_root = $ProjectRoot
    status = $status
    scanned_file_count = $scanFiles.Count
    hit_count = $hitArray.Count
    files = $fileSummaryArray
    hits = $hitArray
}

if (-not $NoWrite) {
    New-Item -ItemType Directory -Force -Path $reportDir | Out-Null
    Set-TextFileWithRetry -Path (Join-Path $reportDir "latest-log-intelligence.json") -Value ($report | ConvertTo-Json -Depth 8)

    $md = @()
    $md += "# Log Intelligence Report"
    $md += ""
    $md += "Generated: $($report.generated_at)"
    $md += "Status: $status"
    $md += "Scanned Files: $($scanFiles.Count)"
    $md += "Hits: $($hits.Count)"
    $md += ""
    $md += "| Severity | Signature | File | Line | Sample | Suggested Action |"
    $md += "|---|---|---|---:|---|---|"
    if ($hitArray.Count -eq 0) {
        $md += "| green | none | - | 0 | No matching signatures. | Continue. |"
    }
    else {
        foreach ($hit in $hitArray) {
            $md += "| $(Escape-Cell $hit.severity) | $(Escape-Cell $hit.signature_id) | $(Escape-Cell $hit.file) | $($hit.line) | $(Escape-Cell $hit.sample) | $(Escape-Cell $hit.suggested_action) |"
        }
    }
    Set-TextFileWithRetry -Path (Join-Path $reportDir "latest-log-intelligence.md") -Value $md

    if (-not (Test-Path -LiteralPath $queuePath)) {
        @(
            "# Resolvable Issues",
            "",
            "| ID | Time | Severity | Signature | Source | Summary | Suggested Action | Status |",
            "|---|---|---|---|---|---|---|---|"
        ) | Set-Content -LiteralPath $queuePath -Encoding UTF8
    }

    $now = (Get-Date).ToString("o")
    $existingQueue = if (Test-Path -LiteralPath $queuePath) {
        Get-Content -Raw -LiteralPath $queuePath
    }
    else {
        ""
    }
    foreach ($hit in $hitArray) {
        $sourceKey = ([regex]::Replace(([string]$hit.file).ToUpperInvariant(), "[^A-Z0-9]+", "-")).Trim("-")
        $stableId = "RES-$($hit.signature_id)-$sourceKey-L$($hit.line)"
        $issueKey = "$(Escape-Cell $hit.signature_id) | $(Escape-Cell $hit.file) | $(Escape-Cell $hit.sample)"
        if ($existingQueue.Contains($stableId) -or $existingQueue.Contains($issueKey)) { continue }
        $summary = "$($hit.title): $($hit.sample)"
        Add-Content -LiteralPath $queuePath -Value "| $stableId | $now | $(Escape-Cell $hit.severity) | $(Escape-Cell $hit.signature_id) | $(Escape-Cell $hit.file) | $(Escape-Cell $summary) | $(Escape-Cell $hit.suggested_action) | Open |" -Encoding UTF8
    }
}

$report
