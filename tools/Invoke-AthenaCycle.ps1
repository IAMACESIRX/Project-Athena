param(
    [Parameter(Mandatory = $true)]
    [string]$Goal,

    [string]$ProjectRoot = (Resolve-Path (Join-Path $PSScriptRoot "..")).Path,
    [ValidateSet("manual", "ai_assisted", "automated", "hybrid")]
    [string]$ExecutionMode = "hybrid",
    [string]$ActiveLayer = "root",
    [string]$PrioritySource = "human instruction",
    [string]$RequiredOutput = "Cycle report and memory writeback recommendation.",
    [string]$VerificationMethod = "Review generated intake, shared run packet, and cycle report.",
    [string[]]$BenefitsToPreserve = @(
        "human authority",
        "evidence traceability",
        "recoverability",
        "institutional continuity",
        "explicit uncertainty"
    ),
    [string[]]$MemoryWritebackTargets = @("engine/cycle-reports", "work/intake"),
    [switch]$NoWrite
)

$ErrorActionPreference = "Stop"

function ConvertTo-Slug {
    param([string]$Value)
    $slug = ($Value.ToLowerInvariant() -replace "[^a-z0-9]+", "-").Trim("-")
    if (-not $slug) { return "athena-cycle" }
    if ($slug.Length -gt 64) { return $slug.Substring(0, 64).Trim("-") }
    return $slug
}

$timestamp = Get-Date -Format "yyyyMMdd-HHmmss"
$date = Get-Date -Format "yyyyMMdd"
$slug = ConvertTo-Slug -Value $Goal
$intakeId = "ATHENA-INTAKE-$date-$timestamp"
$cycleId = "ATHENA-CYCLE-$date-$timestamp"

$intakeDir = Join-Path $ProjectRoot "work\intake"
$reportDir = Join-Path $ProjectRoot "engine\cycle-reports"
$intakePath = Join-Path $intakeDir "$intakeId-$slug.md"
$reportPath = Join-Path $reportDir "$cycleId-$slug.md"
$haipsRunPath = Join-Path $intakeDir "$intakeId-$slug.haips.json"

$now = (Get-Date).ToString("o")
$targets = ($MemoryWritebackTargets | ForEach-Object { "- " + $_ }) -join [Environment]::NewLine
$benefits = ($BenefitsToPreserve | ForEach-Object { "- " + $_ }) -join [Environment]::NewLine

$intake = @"
# Athena Task Intake: $Goal

## Metadata

- schema: ai-system.athena_task_intake.v1
- intake_id: $intakeId
- created_at: $now
- status: created
- execution_mode: $ExecutionMode
- active_layer: $ActiveLayer
- priority_source: $PrioritySource

## Human Goal

$Goal

## Required Output

$RequiredOutput

## Benefits To Preserve

$benefits

## Files To Read

- AI-PORTAL.md
- context.md
- Plan/context.md
- standards/human-ai-pipeline/STANDARD-v0.1.md
- standards/human-ai-pipeline/profiles/athena.yml
- engine/order-of-operations.md

## Files Read

- pending

## Known Facts

| Statement | Truth Value | Confidence | Evidence |
|---|---|---:|---|
| Intake packet created by tools/Invoke-AthenaCycle.ps1. | observed | 1.0 | $intakePath |

## Assumptions

| Statement | Truth Value | Confidence | Evidence |
|---|---|---:|---|
| The selected active layer is correct for the goal. | assumed | 0.5 | Operator input |

## Unknowns

| Statement | Truth Value | Confidence | Evidence |
|---|---|---:|---|
| Task-specific unknowns have not been discovered yet. | unknown | 0.0 | Context not yet read |

## Risks

| Risk | Truth Value | Confidence | Mitigation |
|---|---|---:|---|
| Acting before reading context can cause drift. | inferred | 0.7 | Read context before execution |

## Weakness Register

| ID | Weakness | Triggers | Harms | Associated Benefits | Evidence | Disposition | Status |
|---|---|---|---|---|---|---|---|
| W-001 | Task-specific weakness analysis is pending. | Cognitive and diagnostic passes not yet complete. | Unknown failure modes may remain untreated. | $($BenefitsToPreserve -join "; ") | Pending analysis | research | open |

## Mitigation And Offset Register

| ID | Weakness IDs | Control/Offset | Benefits Preserved | Activation Trigger | Modes | Trade-offs | New Risks | Manual Verification | Machine Verification | Review/Removal Conditions | Status |
|---|---|---|---|---|---|---|---|---|---|---|---|
| M-001 | W-001 | Complete R08M before the decision gate. | $($BenefitsToPreserve -join "; ") | Before action selection. | manual, ai_assisted, automated, hybrid | Additional analysis and documentation. | Controls may become excessive or stale. | Human reviews weakness/benefit/control alignment. | Validate the HAIPS run packet. | Revise when the control suppresses a named benefit or no longer reduces the weakness. | proposed |

## Intervention Log

| ID | Actor/Authority | Stage | Action | Reason | Changed Fields | Required Validation | Rollback Or Branch |
|---|---|---|---|---|---|---|---|

## Athena Decision Pass

Problem frame:
: pending

Relevant cognition methods:
: pending

Decision:
: pending

Why this action:
: pending

Rollback or recovery:
: generated intake, shared run packet, and report files can be removed if not used.

## Verification Method

$VerificationMethod

## Memory Writeback Targets

$targets

## End State

Pending execution.
"@

$report = @"
# Athena Cycle Report: $cycleId

## Run Type

intake

## Human Goal

$Goal

## Authority And Boundaries

- Latest human instruction: $Goal
- Priority source: $PrioritySource
- Active layer: $ActiveLayer
- Execution mode: $ExecutionMode
- Safety constraints: no destructive action in generated intake cycle.

## Benefits To Preserve

$benefits

## Context Loaded

- pending

## Decision Pass

Problem:
: pending

Known:
: intake was created.

Assumed:
: operator supplied the correct goal, layer, mode, and initial benefit set.

Unknown:
: task-specific evidence, weaknesses, and effective mitigations have not been read yet.

Chosen action:
: start from the generated intake packet and shared HAIPS run packet.

Why:
: Athena uses structured intake to prevent unstructured work, memory drift, and controls that suppress project strengths.

## Execution

1. Created an Athena task-intake packet.
2. Requested a shared Human–AI Pipeline run packet when Python tooling is available.
3. Created this cycle report shell.

## Mitigation And Intervention

- Complete the R08M mitigation and offset pass before selecting consequential action.
- Preserve the named benefits while reducing identified weaknesses.
- Record any pause, edit, override, branch, rejection, rollback, mode change, mitigation change, evidence request, or review request.

## Verification

- Confirm files exist.
- Validate the shared run packet when generated.
- Review and fill pending fields before implementation work.
- Confirm each mitigation names preserved benefits, trade-offs, new risks, and review/removal conditions.

## Result

CREATED

## Files Produced Or Updated

- $intakePath
- $haipsRunPath (when shared tooling is available)
- $reportPath

## Memory Writeback

Pending.

## Next Action

Read the files listed in the intake packet, complete the decision and mitigation passes, then execute the smallest reversible action.
"@

$haipsCreated = $false
$haipsMessage = "Not attempted."

if (-not $NoWrite) {
    New-Item -ItemType Directory -Force -Path $intakeDir, $reportDir | Out-Null
    Set-Content -LiteralPath $intakePath -Value $intake -Encoding UTF8
    Set-Content -LiteralPath $reportPath -Value $report -Encoding UTF8

    $python = Get-Command python -ErrorAction SilentlyContinue
    $haipsTool = Join-Path $ProjectRoot "tools\human_ai_pipeline.py"
    $athenaProfile = Join-Path $ProjectRoot "standards\human-ai-pipeline\profiles\athena.yml"

    if ($python -and (Test-Path -LiteralPath $haipsTool) -and (Test-Path -LiteralPath $athenaProfile)) {
        $haipsOutput = & $python.Source $haipsTool new --profile $athenaProfile --goal $Goal --mode $ExecutionMode --title $Goal --out $haipsRunPath 2>&1
        if ($LASTEXITCODE -eq 0 -and (Test-Path -LiteralPath $haipsRunPath)) {
            $haipsCreated = $true
            $haipsMessage = ($haipsOutput | Out-String).Trim()
        }
        else {
            $haipsMessage = "Shared run creation failed: " + (($haipsOutput | Out-String).Trim())
        }
    }
    else {
        $haipsMessage = "Python or shared HAIPS files were not available. Manual Markdown workflow remains usable."
    }
}

[PSCustomObject]@{
    schema = "ai-system.athena_cycle_bootstrap.v2"
    cycle_id = $cycleId
    intake_id = $intakeId
    execution_mode = $ExecutionMode
    benefits_to_preserve = $BenefitsToPreserve
    intake_path = $intakePath
    haips_run_path = $haipsRunPath
    haips_created = $haipsCreated
    haips_message = $haipsMessage
    report_path = $reportPath
    wrote_files = -not $NoWrite
}
