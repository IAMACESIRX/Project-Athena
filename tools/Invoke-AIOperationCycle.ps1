param(
    [string]$ProjectRoot = (Resolve-Path (Join-Path $PSScriptRoot "..\..")).Path,
    [switch]$SkipLiveProbe
)

$ErrorActionPreference = "Stop"

$aiRoot = Join-Path $ProjectRoot "ai-system"
$tools = Join-Path $aiRoot "tools"
$reportDir = Join-Path $aiRoot "engine\cycle-reports"
$historyPath = Join-Path $aiRoot "engine\cycle-history.csv"
$cycleId = "CYCLE-$((Get-Date).ToString('yyyyMMdd-HHmmss'))"
$started = Get-Date
$steps = New-Object 'System.Collections.Generic.List[object]'
$overall = "PASS"

function Run-Step {
    param(
        [string]$Name,
        [scriptblock]$Action,
        [string]$ReportPath = "",
        [switch]$AllowWarn
    )

    $s = Get-Date
    $status = "PASS"
    $message = ""
    try {
        & $Action | Out-Null
        if ($ReportPath -and (Test-Path -LiteralPath $ReportPath)) {
            try {
                $subReport = Get-Content -Raw -LiteralPath $ReportPath | ConvertFrom-Json
                if ($subReport.status -eq "FAIL") {
                    if ($AllowWarn) {
                        $status = "WARN"
                        if ($script:overall -eq "PASS") { $script:overall = "WARN" }
                    }
                    else {
                        $status = "FAIL"
                        $script:overall = "FAIL"
                    }
                    $message = "Sub-report status: FAIL"
                }
                elseif ($subReport.status -eq "WARN") {
                    $status = "WARN"
                    if ($script:overall -eq "PASS") { $script:overall = "WARN" }
                    $message = "Sub-report status: WARN"
                }
            }
            catch {
                $status = "WARN"
                if ($script:overall -eq "PASS") { $script:overall = "WARN" }
                $message = "Could not parse sub-report status: $($_.Exception.Message)"
            }
        }
    }
    catch {
        if ($AllowWarn) {
            $status = "WARN"
            if ($script:overall -eq "PASS") { $script:overall = "WARN" }
        }
        else {
            $status = "FAIL"
            $script:overall = "FAIL"
        }
        $message = $_.Exception.Message
    }
    $e = Get-Date
    $steps.Add([PSCustomObject]@{
        name = $Name
        status = $status
        started = $s.ToString("o")
        ended = $e.ToString("o")
        seconds = [math]::Round(($e - $s).TotalSeconds, 2)
        message = $message
    }) | Out-Null
}

Run-Step -Name "R01 Integrity Gate" -Action {
    powershell -NoProfile -ExecutionPolicy Bypass -File (Join-Path $tools "Invoke-AIIntegrityCheck.ps1") -ProjectRoot $ProjectRoot
} -ReportPath (Join-Path $aiRoot "diagnostics\reports\latest-integrity-report.json")

Run-Step -Name "R02 Project Scan" -Action {
    powershell -NoProfile -ExecutionPolicy Bypass -File (Join-Path $tools "Invoke-AIProjectScan.ps1") -ProjectRoot $ProjectRoot
}

Run-Step -Name "R03 Project Map Export" -Action {
    powershell -NoProfile -ExecutionPolicy Bypass -File (Join-Path $tools "Export-ProjectMap.ps1") -ProjectRoot $ProjectRoot
}

Run-Step -Name "R04 AI Manifest Export" -Action {
    powershell -NoProfile -ExecutionPolicy Bypass -File (Join-Path $tools "Export-AISystemManifest.ps1") -ProjectRoot $ProjectRoot
}

Run-Step -Name "R05 Forensic Verification" -Action {
    powershell -NoProfile -ExecutionPolicy Bypass -File (Join-Path $tools "Invoke-AIForensicVerification.ps1") -ProjectRoot $ProjectRoot
} -ReportPath (Join-Path $aiRoot "forensics\verification-reports\latest-forensic-verification.json")

Run-Step -Name "R06 Log Intelligence" -Action {
    powershell -NoProfile -ExecutionPolicy Bypass -File (Join-Path $tools "Invoke-AILogIntelligence.ps1") -ProjectRoot $ProjectRoot
} -ReportPath (Join-Path $aiRoot "observability\reports\latest-log-intelligence.json")

Run-Step -Name "R07 Watched State Baseline" -Action {
    powershell -NoProfile -ExecutionPolicy Bypass -File (Join-Path $tools "Invoke-AIWatchedState.ps1") -ProjectRoot $ProjectRoot
}

if ($SkipLiveProbe) {
    $steps.Add([PSCustomObject]@{
        name = "R08 Live Server Probe"
        status = "SKIP"
        started = (Get-Date).ToString("o")
        ended = (Get-Date).ToString("o")
        seconds = 0
        message = "Skipped by operator flag."
    }) | Out-Null
}
else {
    Run-Step -Name "R08 Live Server Probe" -AllowWarn -Action {
        powershell -NoProfile -ExecutionPolicy Bypass -File (Join-Path $tools "Invoke-LiveServerProbe.ps1") -ProjectRoot $ProjectRoot
    }
}

Run-Step -Name "R09 Cognition Checklist Presence" -Action {
    $checklist = Join-Path $aiRoot "engine\checklists\full-reasoning-chain.md"
    if (-not (Test-Path -LiteralPath $checklist)) {
        throw "Missing cognition checklist: $checklist"
    }
}

$ended = Get-Date
$report = [PSCustomObject]@{
    schema = "ai-system.operation_cycle_report.v1"
    cycle_id = $cycleId
    started = $started.ToString("o")
    ended = $ended.ToString("o")
    duration_sec = [math]::Round(($ended - $started).TotalSeconds, 2)
    status = $overall
    project_root = $ProjectRoot
    steps = $steps
}

New-Item -ItemType Directory -Force -Path $reportDir | Out-Null
$report | ConvertTo-Json -Depth 8 | Set-Content -LiteralPath (Join-Path $reportDir "latest-cycle-report.json") -Encoding UTF8

$md = @()
$md += "# AI Operation Cycle Report"
$md += ""
$md += "Cycle ID: $cycleId"
$md += "Started: $($report.started)"
$md += "Ended: $($report.ended)"
$md += "Duration Seconds: $($report.duration_sec)"
$md += "Status: $overall"
$md += ""
$md += "| Step | Status | Seconds | Message |"
$md += "|---|---|---:|---|"
foreach ($step in $steps) {
    $safeMessage = ($step.message -replace "\|", "/" -replace "`r?`n", " ").Trim()
    $md += "| $($step.name) | $($step.status) | $($step.seconds) | $safeMessage |"
}
$md | Set-Content -LiteralPath (Join-Path $reportDir "latest-cycle-report.md") -Encoding UTF8

if (-not (Test-Path -LiteralPath $historyPath)) {
    @('"cycle_id","started","ended","duration_sec","status","step_count","notes"') | Set-Content -LiteralPath $historyPath -Encoding UTF8
}

[PSCustomObject]@{
    cycle_id = $cycleId
    started = $report.started
    ended = $report.ended
    duration_sec = $report.duration_sec
    status = $overall
    step_count = $steps.Count
    notes = "Operation cycle completed."
} | Export-Csv -LiteralPath $historyPath -NoTypeInformation -Append -Encoding UTF8

$report
