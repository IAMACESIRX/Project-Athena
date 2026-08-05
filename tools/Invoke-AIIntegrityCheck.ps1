param(
    [string]$ProjectRoot = (Resolve-Path (Join-Path $PSScriptRoot "..")).Path,
    [switch]$NoWrite
)

$ErrorActionPreference = "Stop"

$aiRoot = $ProjectRoot
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
        $looksLikePath = (
            ($Node -match "[/\\]") -or
            ($Node -match "\.(md|json|yml|yaml|csv|ps1|txt)$")
        ) -and ($Node -notmatch "^(https?://|git@|schema:)")

        if ($looksLikePath) {
            $full = if ([System.IO.Path]::IsPathRooted($Node)) {
                $Node
            }
            else {
                Join-Path $ProjectRoot ($Node -replace "/", "\")
            }
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
    "AI-PORTAL.md",
    "START-HERE.md",
    "manifests/system-manifest.json",
    "manifests/ingestion-order.yml",
    "manifests/capability-matrix.yml",
    "manifests/tool-index.yml",
    "context.md",
    "context-file-index.md",
    "Plan/context.md",
    "Plan/CHAT_REPOSITORY_CONTINUITY_PIPELINE.md",
    "memory/athena-memory-map.md",
    "continuity/chat-repository-sync/sync-policy.json",
    "continuity/chat-repository-sync/promotion-ledger.jsonl",
    "work/github-plan.json",
    ".github/workflows/athena-integrity.yml",
    "schemas/athena-task-intake.schema.json",
    "templates/athena-task-intake.md",
    "identity/README.md",
    "identity/constitution.md",
    "identity/mission-and-scope.md",
    "projects/project-registry.yml",
    "organization/hierarchy.yml",
    "organization/authority-levels.yml",
    "organization/executive-operating-model.md",
    "agents/agent-registry.yml",
    "agents/agent-object-model.md",
    "orchestration/model-router.yml",
    "orchestration/task-routing-pipeline.md",
    "model-ops/model-registry.yml",
    "model-ops/evaluation-rubric.yml",
    "model-ops/target-ai/target-ai-architecture.md",
    "model-ops/target-ai/capability-roadmap.yml",
    "model-ops/target-ai/evaluation-benchmarks.yml",
    "research/model-archaeology/source-ledger.yml",
    "research/model-archaeology/deconstruction-protocol.md",
    "research/model-archaeology/open-model-capability-matrix.yml",
    "research/model-archaeology/odysseus-deconstruction.md",
    "runtime/agent-platform/windows-agent-platform.md",
    "memory/context-iq/contextual-work-iq.md",
    "training/curriculum.md",
    "runtime/service-map.yml",
    "reputation/trust-model.yml",
    "resources/resource-budget.yml",
    "governance/absolutes.md",
    "engine/README.md",
    "engine/order-of-operations.md",
    "engine/routine-catalog.yml",
    "forensics/evidence-register.csv",
    "forensics/claim-catalog.csv",
    "forensics/evidence-claim-map.csv",
    "cognition/cognition-workflow.md",
    "tools/Invoke-AIOperationCycle.ps1",
    "tools/Invoke-AIForensicVerification.ps1",
    "tools/Invoke-AILogIntelligence.ps1",
    "tools/Invoke-AIWatchedState.ps1"
)

foreach ($rel in $required) {
    $full = Join-Path $ProjectRoot ($rel -replace "/", "\")
    if (-not (Test-Path -LiteralPath $full)) {
        Add-Issue -Severity "red" -Source "required-file" -Summary "Missing required file: $rel" -RecommendedAction "Restore the file or remove it from the required list if obsolete."
    }
}

$jsonFiles = @(
    "manifests/system-manifest.json",
    "manifests/generated-ai-index.json",
    "navigation/generated/project-map.json",
    "sensory/scans/latest-scan.json",
    "observability/log-signatures.json",
    "schemas/open-model-source.schema.json",
    "schemas/athena-task-intake.schema.json",
    "schemas/chat-source-bundle.schema.json",
    "schemas/chat-promotion.schema.json",
    "schemas/repository-context-capsule.schema.json",
    "continuity/chat-repository-sync/sync-policy.json",
    "work/github-plan.json"
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

