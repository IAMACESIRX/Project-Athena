param(
    [string]$ProjectRoot = (Resolve-Path (Join-Path $PSScriptRoot "..")).Path,
    [switch]$NoWrite
)

$ErrorActionPreference = "Stop"

function Get-RelativeFileSet {
    param(
        [string]$Root,
        [string]$Filter = "*"
    )

    Get-ChildItem -LiteralPath $Root -Recurse -File -Force -Filter $Filter -ErrorAction SilentlyContinue |
        Where-Object { $_.FullName -notmatch "\\.git\\" } |
        ForEach-Object { $_.FullName.Substring($ProjectRoot.Length + 1) -replace "\\", "/" } |
        Sort-Object
}

$aiRoot = $ProjectRoot
$baseManifestPath = Join-Path $aiRoot "manifests\system-manifest.json"
$baseManifest = Get-Content -Raw -LiteralPath $baseManifestPath | ConvertFrom-Json

$index = [PSCustomObject]@{
    schema = "ai-system.generated_index.v1"
    generated_at = (Get-Date).ToString("o")
    base_manifest = "manifests/system-manifest.json"
    project = $baseManifest.project
    entrypoints = $baseManifest.entrypoints
        file_groups = [PSCustomObject]@{
        root_context = @(
            "AI-PORTAL.md",
            "START-HERE.md",
            "README.md",
            "context.md",
            "context-file-index.md"
        )
        plan = @(Get-RelativeFileSet -Root (Join-Path $aiRoot "Plan"))
        nexus_v_docs = @(Get-RelativeFileSet -Root (Join-Path $aiRoot "Nexus V\docs"))
        templates = @(Get-RelativeFileSet -Root (Join-Path $aiRoot "templates"))
        identity = @(Get-RelativeFileSet -Root (Join-Path $aiRoot "identity"))
        organization = @(Get-RelativeFileSet -Root (Join-Path $aiRoot "organization"))
        agents = @(Get-RelativeFileSet -Root (Join-Path $aiRoot "agents"))
        orchestration = @(Get-RelativeFileSet -Root (Join-Path $aiRoot "orchestration"))
        projects = @(Get-RelativeFileSet -Root (Join-Path $aiRoot "projects"))
        governance = @(Get-RelativeFileSet -Root (Join-Path $aiRoot "governance"))
        registries = @(Get-RelativeFileSet -Root (Join-Path $aiRoot "registries"))
        manifests = @(Get-RelativeFileSet -Root (Join-Path $aiRoot "manifests"))
        schemas = @(Get-RelativeFileSet -Root (Join-Path $aiRoot "schemas"))
        engine = @(Get-RelativeFileSet -Root (Join-Path $aiRoot "engine"))
        forensics = @(Get-RelativeFileSet -Root (Join-Path $aiRoot "forensics"))
        navigation = @(Get-RelativeFileSet -Root (Join-Path $aiRoot "navigation"))
        memory = @(Get-RelativeFileSet -Root (Join-Path $aiRoot "memory"))
        research = @(Get-RelativeFileSet -Root (Join-Path $aiRoot "research"))
        handoff = @(Get-RelativeFileSet -Root (Join-Path $aiRoot "handoff"))
        work = @(Get-RelativeFileSet -Root (Join-Path $aiRoot "work"))
        diagnostics = @(Get-RelativeFileSet -Root (Join-Path $aiRoot "diagnostics"))
        observability = @(Get-RelativeFileSet -Root (Join-Path $aiRoot "observability"))
        cognition = @(Get-RelativeFileSet -Root (Join-Path $aiRoot "cognition"))
        continuity = @(Get-RelativeFileSet -Root (Join-Path $aiRoot "continuity"))
        council = @(Get-RelativeFileSet -Root (Join-Path $aiRoot "council"))
        learning = @(Get-RelativeFileSet -Root (Join-Path $aiRoot "learning"))
        training = @(Get-RelativeFileSet -Root (Join-Path $aiRoot "training"))
        model_ops = @(Get-RelativeFileSet -Root (Join-Path $aiRoot "model-ops"))
        runtime = @(Get-RelativeFileSet -Root (Join-Path $aiRoot "runtime"))
        reputation = @(Get-RelativeFileSet -Root (Join-Path $aiRoot "reputation"))
        resources = @(Get-RelativeFileSet -Root (Join-Path $aiRoot "resources"))
        truth = @(Get-RelativeFileSet -Root (Join-Path $aiRoot "truth"))
        reverse_engineering = @(Get-RelativeFileSet -Root (Join-Path $aiRoot "reverse-engineering"))
        physics = @(Get-RelativeFileSet -Root (Join-Path $aiRoot "physics"))
        tools = @(Get-RelativeFileSet -Root (Join-Path $aiRoot "tools"))
    }
}

if (-not $NoWrite) {
    $outPath = Join-Path $aiRoot "manifests\generated-ai-index.json"
    $index | ConvertTo-Json -Depth 8 | Set-Content -LiteralPath $outPath -Encoding UTF8
}

$index

