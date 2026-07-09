param(
    [string]$ProjectRoot = (Resolve-Path (Join-Path $PSScriptRoot "..")).Path,
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
    Get-Node -Id "project-athena" -Path "." -Type "athena_workspace"
    Get-Node -Id "plan" -Path "Plan" -Type "architecture_intent_vault"
    Get-Node -Id "nexus-v" -Path "Nexus V" -Type "hardware_toolchain_subsystem"
    Get-Node -Id "engine" -Path "engine" -Type "processor_loop"
    Get-Node -Id "memory" -Path "memory" -Type "memory_layer"
    Get-Node -Id "work" -Path "work" -Type "working_memory"
    Get-Node -Id "tools" -Path "tools" -Type "tooling_layer"
    Get-Node -Id "cognition" -Path "cognition" -Type "reasoning_methods"
    Get-Node -Id "council" -Path "council" -Type "decision_roles"
    Get-Node -Id "schemas" -Path "schemas" -Type "machine_contracts"
)

$edges = @(
    @{ from = "project-athena"; to = "plan"; relation = "uses_as_design_authority" }
    @{ from = "project-athena"; to = "nexus-v"; relation = "contains_implementation_branch" }
    @{ from = "project-athena"; to = "engine"; relation = "uses_as_processor_loop" }
    @{ from = "project-athena"; to = "memory"; relation = "uses_as_memory_layer" }
    @{ from = "project-athena"; to = "work"; relation = "uses_as_working_memory" }
    @{ from = "engine"; to = "tools"; relation = "invokes" }
    @{ from = "engine"; to = "cognition"; relation = "uses_reasoning_methods" }
    @{ from = "council"; to = "work"; relation = "produces_decisions_and_tasks" }
    @{ from = "schemas"; to = "tools"; relation = "constrains_inputs_outputs" }
)

$map = [PSCustomObject]@{
    schema = "ai-system.project_map.v1"
    generated_at = (Get-Date).ToString("o")
    project_root = $ProjectRoot
    nodes = $nodes
    edges = $edges
}

if (-not $NoWrite) {
    $outDir = Join-Path $ProjectRoot "navigation\generated"
    New-Item -ItemType Directory -Force -Path $outDir | Out-Null
    $outPath = Join-Path $outDir "project-map.json"
    $map | ConvertTo-Json -Depth 8 | Set-Content -LiteralPath $outPath -Encoding UTF8
}

$map

