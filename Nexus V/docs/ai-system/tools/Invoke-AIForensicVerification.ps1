param(
    [string]$ProjectRoot = (Resolve-Path (Join-Path $PSScriptRoot "..\..")).Path,
    [switch]$NoWrite
)

$ErrorActionPreference = "Stop"

$forensics = Join-Path $ProjectRoot "ai-system\forensics"
$reportDir = Join-Path $forensics "verification-reports"
$issues = New-Object 'System.Collections.Generic.List[object]'

function Add-Issue {
    param(
        [string]$Severity,
        [string]$Kind,
        [string]$Summary,
        [string]$Reference
    )

    $issues.Add([PSCustomObject]@{
        severity = $Severity
        kind = $Kind
        summary = $Summary
        reference = $Reference
    }) | Out-Null
}

function Escape-Cell {
    param([string]$Value)
    if ($null -eq $Value) { return "" }
    return ($Value -replace "\|", "/" -replace "`r?`n", " ").Trim()
}

$evidencePath = Join-Path $forensics "evidence-register.csv"
$claimPath = Join-Path $forensics "claim-catalog.csv"
$mapPath = Join-Path $forensics "evidence-claim-map.csv"
$timelinePath = Join-Path $forensics "event-timeline.csv"
$unknownPath = Join-Path $forensics "known-unknowns.csv"

foreach ($path in @($evidencePath, $claimPath, $mapPath, $timelinePath, $unknownPath)) {
    if (-not (Test-Path -LiteralPath $path)) {
        Add-Issue -Severity "red" -Kind "missing-file" -Summary "Missing forensics file." -Reference $path
    }
}

$evidence = @()
$claims = @()
$links = @()
$timeline = @()
$unknowns = @()

if (Test-Path -LiteralPath $evidencePath) { $evidence = @(Import-Csv -LiteralPath $evidencePath) }
if (Test-Path -LiteralPath $claimPath) { $claims = @(Import-Csv -LiteralPath $claimPath) }
if (Test-Path -LiteralPath $mapPath) { $links = @(Import-Csv -LiteralPath $mapPath) }
if (Test-Path -LiteralPath $timelinePath) { $timeline = @(Import-Csv -LiteralPath $timelinePath) }
if (Test-Path -LiteralPath $unknownPath) { $unknowns = @(Import-Csv -LiteralPath $unknownPath) }

$evidenceIds = @{}
foreach ($row in $evidence) {
    if (-not $row.evidence_id) {
        Add-Issue -Severity "red" -Kind "evidence-id" -Summary "Evidence row missing evidence_id." -Reference $row.relative_path
        continue
    }
    if ($evidenceIds.ContainsKey($row.evidence_id)) {
        Add-Issue -Severity "red" -Kind "duplicate-evidence-id" -Summary "Duplicate evidence ID: $($row.evidence_id)" -Reference $row.relative_path
    }
    $evidenceIds[$row.evidence_id] = $true

    if ($row.relative_path) {
        $full = Join-Path $ProjectRoot ($row.relative_path -replace "/", "\")
        if (-not (Test-Path -LiteralPath $full)) {
            Add-Issue -Severity "red" -Kind "missing-evidence-path" -Summary "Evidence path does not resolve: $($row.relative_path)" -Reference $row.evidence_id
        }
        else {
            if ($row.sha256) {
                $hash = (Get-FileHash -LiteralPath $full -Algorithm SHA256).Hash
                if ($hash -ne $row.sha256) {
                    Add-Issue -Severity "red" -Kind "hash-mismatch" -Summary "SHA256 mismatch for $($row.relative_path)" -Reference $row.evidence_id
                }
            }
        }
    }

    if ($row.canonical_name -and $row.evidence_id -and ($row.canonical_name -notlike "$($row.evidence_id)*")) {
        Add-Issue -Severity "yellow" -Kind "canonical-name" -Summary "Canonical name does not begin with evidence ID: $($row.canonical_name)" -Reference $row.evidence_id
    }
}

$claimIds = @{}
foreach ($claim in $claims) {
    if (-not $claim.claim_id) {
        Add-Issue -Severity "red" -Kind "claim-id" -Summary "Claim row missing claim_id." -Reference $claim.summary
        continue
    }
    if ($claimIds.ContainsKey($claim.claim_id)) {
        Add-Issue -Severity "red" -Kind "duplicate-claim-id" -Summary "Duplicate claim ID: $($claim.claim_id)" -Reference $claim.summary
    }
    $claimIds[$claim.claim_id] = $true
}

foreach ($link in $links) {
    if (-not $evidenceIds.ContainsKey($link.evidence_id)) {
        Add-Issue -Severity "red" -Kind "broken-evidence-link" -Summary "Evidence-claim link references unknown evidence: $($link.evidence_id)" -Reference $link.claim_id
    }
    if (-not $claimIds.ContainsKey($link.claim_id)) {
        Add-Issue -Severity "red" -Kind "broken-claim-link" -Summary "Evidence-claim link references unknown claim: $($link.claim_id)" -Reference $link.evidence_id
    }
}

foreach ($event in $timeline) {
    if ($event.evidence_id -and -not $evidenceIds.ContainsKey($event.evidence_id)) {
        Add-Issue -Severity "yellow" -Kind "timeline-evidence-link" -Summary "Timeline references unknown evidence: $($event.evidence_id)" -Reference $event.event_id
    }
}

$status = "PASS"
if (@($issues | Where-Object { $_.severity -eq "red" }).Count -gt 0) {
    $status = "FAIL"
}
elseif ($issues.Count -gt 0) {
    $status = "WARN"
}

$report = [PSCustomObject]@{
    schema = "ai-system.forensic_verification.v1"
    generated_at = (Get-Date).ToString("o")
    project_root = $ProjectRoot
    status = $status
    evidence_count = $evidence.Count
    claim_count = $claims.Count
    evidence_claim_link_count = $links.Count
    timeline_event_count = $timeline.Count
    known_unknown_count = $unknowns.Count
    issue_count = $issues.Count
    issues = $issues
}

if (-not $NoWrite) {
    New-Item -ItemType Directory -Force -Path $reportDir | Out-Null
    $report | ConvertTo-Json -Depth 8 | Set-Content -LiteralPath (Join-Path $reportDir "latest-forensic-verification.json") -Encoding UTF8

    $md = @()
    $md += "# Forensic Verification Report"
    $md += ""
    $md += "Generated: $($report.generated_at)"
    $md += "Status: $status"
    $md += "Evidence Rows: $($evidence.Count)"
    $md += "Claim Rows: $($claims.Count)"
    $md += "Evidence-Claim Links: $($links.Count)"
    $md += "Timeline Events: $($timeline.Count)"
    $md += "Known Unknowns: $($unknowns.Count)"
    $md += "Issues: $($issues.Count)"
    $md += ""
    $md += "| Severity | Kind | Summary | Reference |"
    $md += "|---|---|---|---|"
    if ($issues.Count -eq 0) {
        $md += "| green | verification | No forensic structure issues detected. | - |"
    }
    else {
        foreach ($issue in $issues) {
            $md += "| $(Escape-Cell $issue.severity) | $(Escape-Cell $issue.kind) | $(Escape-Cell $issue.summary) | $(Escape-Cell $issue.reference) |"
        }
    }
    $md | Set-Content -LiteralPath (Join-Path $reportDir "latest-forensic-verification.md") -Encoding UTF8
}

$report

