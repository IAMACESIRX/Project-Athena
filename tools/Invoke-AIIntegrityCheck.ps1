param(
    [string]$ProjectRoot = (Resolve-Path (Join-Path $PSScriptRoot "..\..")).Path,
    [switch]$NoWrite
)

$ErrorActionPreference = "Stop"

$aiRoot = Join-Path $ProjectRoot "ai-system"
$reportDir = Join-Path $aiRoot "diagnostics\reports"
$queuePath = Join-Path $aiRoot "diagnostics\correction-queue.md"
$issues = New-Object 'System.Collections.Generic.List[object]'

function Add-Issue {
    param(
        [string]$Severity,
        [string]$Source,
        [string]$Summary,
        [string]$RecommendedAction
    )

    $issues.Add([PSCustomObject]@{
        severity = $Severity
        source = $Source
        summary = $Summary
        recommended_action = $RecommendedAction
    }) | Out-Null
}

function Escape-Cell {
    param([string]$Value)
    if ($null -eq $Value) { return "" }
    return ($Value -replace "\|", "/" -replace "`r?`n", " ").Trim()
}

function Test-JsonFile {
    param([string]$RelativePath)

    $full = Join-Path $ProjectRoot ($RelativePath -replace "/", "\")
    if (-not (Test-Path -LiteralPath $full)) {
        Add-Issue -Severity "red" -Source "json" -Summary "Missing JSON file: $RelativePath" -RecommendedAction "Restore or regenerate the file."
        return
    }

    try {
        Get-Content -Raw -LiteralPath $full | ConvertFrom-Json | Out-Null
    }
    catch {
        Add-Issue -Severity "red" -Source "json" -Summary "JSON parse failure: $RelativePath" -RecommendedAction $_.Exception.Message
    }
}

function Visit-ManifestNode {
    param([object]$Node)

    if ($null -eq $Node) { return }

    if ($Node -is [string]) {
        if ($Node -like "ai-system/*" -or $Node -like "ai-system\*") {
            $full = Join-Path $ProjectRoot ($Node -replace "/", "\")
            if (-not (Test-Path -LiteralPath $full)) {
                Add-Issue -Severity "yellow" -Source "manifest" -Summary "Manifest path does not resolve: $Node" -RecommendedAction "Create the file/folder or update system-manifest.json."
            }
        }
        return
    }

    if ($Node -is [System.Collections.IEnumerable] -and -not ($Node -is [string])) {
        foreach ($item in $Node) { Visit-ManifestNode -Node $item }
        return
    }

    if ($Node.PSObject -and $Node.PSObject.Properties) {
        foreach ($prop in $Node.PSObject.Properties) {
            Visit-ManifestNode -Node $prop.Value
        }
    }
}

$required = @(
    "ai-system/AI-PORTAL.md",
    "ai-system/START-HERE.md",
    "ai-system/manifests/system-manifest.json",
    "ai-system/manifests/ingestion-order.yml",
    "ai-system/manifests/capability-matrix.yml",
    "ai-system/manifests/tool-index.yml",
    "ai-system/identity/README.md",
    "ai-system/identity/constitution.md",
    "ai-system/identity/mission-and-scope.md",
    "ai-system/projects/project-registry.yml",
    "ai-system/organization/hierarchy.yml",
    "ai-system/organization/authority-levels.yml",
    "ai-system/organization/executive-operating-model.md",
    "ai-system/agents/agent-registry.yml",
    "ai-system/agents/agent-object-model.md",
    "ai-system/orchestration/model-router.yml",
    "ai-system/orchestration/task-routing-pipeline.md",
    "ai-system/model-ops/model-registry.yml",
    "ai-system/model-ops/evaluation-rubric.yml",
    "ai-system/model-ops/target-ai/target-ai-architecture.md",
    "ai-system/model-ops/target-ai/capability-roadmap.yml",
    "ai-system/model-ops/target-ai/evaluation-benchmarks.yml",
    "ai-system/research/model-archaeology/source-ledger.yml",
    "ai-system/research/model-archaeology/deconstruction-protocol.md",
    "ai-system/research/model-archaeology/open-model-capability-matrix.yml",
    "ai-system/research/model-archaeology/odysseus-deconstruction.md",
    "ai-system/runtime/agent-platform/windows-agent-platform.md",
    "ai-system/memory/context-iq/contextual-work-iq.md",
    "ai-system/training/curriculum.md",
    "ai-system/runtime/service-map.yml",
    "ai-system/reputation/trust-model.yml",
    "ai-system/resources/resource-budget.yml",
    "ai-system/governance/absolutes.md",
    "ai-system/engine/README.md",
    "ai-system/engine/order-of-operations.md",
    "ai-system/engine/routine-catalog.yml",
    "ai-system/forensics/evidence-register.csv",
    "ai-system/forensics/claim-catalog.csv",
    "ai-system/forensics/evidence-claim-map.csv",
    "ai-system/cognition/cognition-workflow.md",
    "ai-system/tools/Invoke-AIOperationCycle.ps1",
    "ai-system/tools/Invoke-AIForensicVerification.ps1",
    "ai-system/tools/Invoke-AILogIntelligence.ps1",
    "ai-system/tools/Invoke-AIWatchedState.ps1"
)

foreach ($rel in $required) {
    $full = Join-Path $ProjectRoot ($rel -replace "/", "\")
    if (-not (Test-Path -LiteralPath $full)) {
        Add-Issue -Severity "red" -Source "required-file" -Summary "Missing required file: $rel" -RecommendedAction "Restore the file or remove it from the required list if obsolete."
    }
}

$jsonFiles = @(
    "ai-system/manifests/system-manifest.json",
    "ai-system/manifests/generated-ai-index.json",
    "ai-system/navigation/generated/project-map.json",
    "ai-system/sensory/scans/latest-scan.json",
    "ai-system/observability/log-signatures.json",
    "ai-system/schemas/open-model-source.schema.json"
)

foreach ($jsonPath in $jsonFiles) {
    Test-JsonFile -RelativePath $jsonPath
}

$manifestPath = Join-Path $aiRoot "manifests\system-manifest.json"
if (Test-Path -LiteralPath $manifestPath) {
    try {
        $manifest = Get-Content -Raw -LiteralPath $manifestPath | ConvertFrom-Json
        Visit-ManifestNode -Node $manifest
        if ($manifest.project.cloud_push_allowed -ne $false) {
            Add-Issue -Severity "red" -Source "governance" -Summary "cloud_push_allowed is not false." -RecommendedAction "Restore local-only governance unless the human explicitly changed it."
        }
    }
    catch {
        Add-Issue -Severity "red" -Source "manifest" -Summary "Unable to inspect system manifest." -RecommendedAction $_.Exception.Message
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
    schema = "ai-system.integrity_report.v1"
    generated_at = (Get-Date).ToString("o")
    project_root = $ProjectRoot
    status = $status
    issue_count = $issues.Count
    issues = $issues
}

if (-not $NoWrite) {
    New-Item -ItemType Directory -Force -Path $reportDir | Out-Null
    $report | ConvertTo-Json -Depth 8 | Set-Content -LiteralPath (Join-Path $reportDir "latest-integrity-report.json") -Encoding UTF8

    $md = @()
    $md += "# AI Integrity Report"
    $md += ""
    $md += "Generated: $($report.generated_at)"
    $md += "Status: $status"
    $md += "Issues: $($issues.Count)"
    $md += ""
    $md += "| Severity | Source | Summary | Recommended Action |"
    $md += "|---|---|---|---|"
    if ($issues.Count -eq 0) {
        $md += "| green | integrity | No issues detected. | Continue. |"
    }
    else {
        foreach ($issue in $issues) {
            $md += "| $(Escape-Cell $issue.severity) | $(Escape-Cell $issue.source) | $(Escape-Cell $issue.summary) | $(Escape-Cell $issue.recommended_action) |"
        }
    }
    $md | Set-Content -LiteralPath (Join-Path $reportDir "latest-integrity-report.md") -Encoding UTF8

    if (-not (Test-Path -LiteralPath $queuePath)) {
        @(
            "# Correction Queue",
            "",
            "| ID | Time | Severity | Source | Summary | Recommended Action | Status |",
            "|---|---|---|---|---|---|---|"
        ) | Set-Content -LiteralPath $queuePath -Encoding UTF8
    }

    $now = (Get-Date).ToString("o")
    $n = 1
    foreach ($issue in $issues) {
        $id = "CORR-$((Get-Date).ToString('yyyyMMdd-HHmmss'))-$('{0:d2}' -f $n)"
        $n++
        $line = "| $id | $now | $(Escape-Cell $issue.severity) | $(Escape-Cell $issue.source) | $(Escape-Cell $issue.summary) | $(Escape-Cell $issue.recommended_action) | Open |"
        Add-Content -LiteralPath $queuePath -Value $line -Encoding UTF8
    }
}

$report
