param(
    [Parameter(Mandatory = $true)]
    [string]$Goal,

    [string]$ProjectRoot = (Resolve-Path (Join-Path $PSScriptRoot "..")).Path,
    [string]$ActiveLayer = "root",
    [string]$PrioritySource = "human instruction",
    [string]$RequiredOutput = "Cycle report and memory writeback recommendation.",
    [string]$VerificationMethod = "Review generated intake and cycle report.",
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

$now = (Get-Date).ToString("o")
$targets = ($MemoryWritebackTargets | ForEach-Object { "- " + $_ }) -join [Environment]::NewLine

$intake = @"
# Athena Task Intake: $Goal

## Metadata

- schema: ai-system.athena_task_intake.v1
- intake_id: $intakeId
- created_at: $now
- status: created
- active_layer: $ActiveLayer
- priority_source: $PrioritySource

## Human Goal

$Goal

## Required Output

$RequiredOutput

## Files To Read

- AI-PORTAL.md
- context.md
- Plan/context.md
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
: generated intake and report files can be removed if not used.

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
- Safety constraints: no destructive action in generated intake cycle.

## Context Loaded

- pending

## Decision Pass

Problem:
: pending

Known:
: intake was created.

Assumed:
: operator supplied the correct goal and layer.

Unknown:
: task-specific evidence has not been read yet.

Chosen action:
: start from the generated intake packet.

Why:
: Athena uses intake packets to prevent unstructured work and memory drift.

## Execution

1. Created an Athena task-intake packet.
2. Created this cycle report shell.

## Verification

- Confirm files exist.
- Review and fill pending fields before implementation work.

## Result

CREATED

## Files Produced Or Updated

- $intakePath
- $reportPath

## Memory Writeback

Pending.

## Next Action

Read the files listed in the intake packet, complete the decision pass, then
execute the smallest reversible action.
"@

if (-not $NoWrite) {
    New-Item -ItemType Directory -Force -Path $intakeDir, $reportDir | Out-Null
    Set-Content -LiteralPath $intakePath -Value $intake -Encoding UTF8
    Set-Content -LiteralPath $reportPath -Value $report -Encoding UTF8
}

[PSCustomObject]@{
    schema = "ai-system.athena_cycle_bootstrap.v1"
    cycle_id = $cycleId
    intake_id = $intakeId
    intake_path = $intakePath
    report_path = $reportPath
    wrote_files = -not $NoWrite
}
