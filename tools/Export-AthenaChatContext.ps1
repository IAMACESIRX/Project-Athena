param(
    [string]$ProjectRoot = "",
    [int]$MaxCharactersPerFile = 24000,
    [int]$FullChunkCharacters = 120000,
    [switch]$Full,
    [switch]$NoWrite
)

$ErrorActionPreference = "Stop"
if (-not $ProjectRoot) { $ProjectRoot = (Resolve-Path (Join-Path $PSScriptRoot "..")).Path }

function Get-RelativePath {
    param([string]$Base, [string]$Path)
    $baseUri = [Uri]($Base.TrimEnd([IO.Path]::DirectorySeparatorChar) + [IO.Path]::DirectorySeparatorChar)
    return [Uri]::UnescapeDataString($baseUri.MakeRelativeUri([Uri]$Path).ToString()).Replace("\", "/")
}

function Get-GitValue {
    param([string[]]$Arguments)
    try {
        $value = & git -C $ProjectRoot @Arguments 2>$null
        if ($LASTEXITCODE -eq 0) { return ($value -join "`n").Trim() }
    }
    catch { }
    return $null
}

function Get-SelectedFiles {
    if (-not $Full) {
        $relative = @(
            "AI-PORTAL.md",
            "START-HERE.md",
            "context.md",
            "Plan/context.md",
            "Plan/CHAT_REPOSITORY_CONTINUITY_PIPELINE.md",
            "Plan/CHAT_DERIVED_CONCEPT_REGISTER.md",
            "Plan/IMPLEMENTATION_MATRIX.md",
            "Plan/ROADMAP.md",
            "memory/athena-memory-map.md",
            "projects/project-athena/capsule.json",
            "manifests/system-manifest.json",
            "continuity/chat-repository-sync/sync-policy.json",
            "work/milestones.md",
            "work/github-plan.json",
            "work/decisions-needed.md",
            "work/ATHENA-FIRST-STEPS.md",
            "athena_context/RECONCILIATION.md",
            "athena_context/ASSET_INVENTORY.md",
            "handoff/CURRENT_STATE.md",
            "engine/cycle-reports/latest-cycle-report.md"
        )
        return @($relative | ForEach-Object { Join-Path $ProjectRoot ($_ -replace "/", "\") } | Where-Object { Test-Path -LiteralPath $_ -PathType Leaf })
    }

    $extensions = @(".md", ".txt", ".json", ".jsonl", ".yml", ".yaml", ".csv", ".ps1", ".toml", ".ini")
    return @(Get-ChildItem -LiteralPath $ProjectRoot -Recurse -File -Force | Where-Object {
        $relative = Get-RelativePath -Base $ProjectRoot -Path $_.FullName
        $_.Extension.ToLowerInvariant() -in $extensions -and
        $relative -notlike ".git/*" -and
        $relative -notlike "athena_context/*.jsonl" -and
        $relative -notlike "athena_context/assets/*" -and
        $relative -notlike "continuity/transcript-inbox/imports/*" -and
        $relative -notlike "continuity/chat-repository-sync/generated/*" -and
        $relative -notlike "Nexus V/generated/*" -and
        $relative -notlike "Nexus V/build/*" -and
        $relative -ne "context-file-index.md"
    } | Sort-Object FullName | ForEach-Object { $_.FullName })
}

$files = @(Get-SelectedFiles)
$gitStatusText = Get-GitValue -Arguments @("status", "--short")
$gitStatus = @($gitStatusText -split "`r?`n" | Where-Object { $_ })
$git = [ordered]@{
    commit = Get-GitValue -Arguments @("rev-parse", "HEAD")
    branch = Get-GitValue -Arguments @("branch", "--show-current")
    dirty = $gitStatus.Count -gt 0
    status = $gitStatus
}

$records = @()
$sections = @()
$totalIncluded = 0
$totalOmitted = 0
foreach ($path in $files) {
    $item = Get-Item -LiteralPath $path
    $relative = Get-RelativePath -Base $ProjectRoot -Path $path
    $raw = Get-Content -Raw -LiteralPath $path
    $characters = $raw.Length
    $included = $raw
    $truncated = $false
    if (-not $Full -and $characters -gt $MaxCharactersPerFile) {
        $headLength = [Math]::Floor($MaxCharactersPerFile * 0.7)
        $tailLength = $MaxCharactersPerFile - $headLength
        $omitted = $characters - $headLength - $tailLength
        $included = $raw.Substring(0, $headLength) + "`n`n[ATHENA CAPSULE OMITTED $omitted CHARACTERS; VERIFY AGAINST FILE HASH]`n`n" + $raw.Substring($characters - $tailLength)
        $truncated = $true
    }
    $includedCharacters = if ($truncated) { [Math]::Min($MaxCharactersPerFile, $characters) } else { $characters }
    $totalIncluded += $includedCharacters
    $totalOmitted += ($characters - $includedCharacters)
    $hash = (Get-FileHash -Algorithm SHA256 -LiteralPath $path).Hash.ToLowerInvariant()
    $records += [PSCustomObject]@{
        path = $relative
        sha256 = $hash
        bytes = $item.Length
        characters = $characters
        included_characters = $includedCharacters
        truncated = $truncated
    }
    $sections += "<!-- ATHENA_FILE_BEGIN path=$relative sha256=$hash truncated=$($truncated.ToString().ToLowerInvariant()) -->`n`n$included`n`n<!-- ATHENA_FILE_END path=$relative -->"
}

$manifest = [ordered]@{
    schema = "athena.repository_context_capsule.v1"
    generated_at = (Get-Date).ToString("o")
    project = [ordered]@{
        name = "Project Athena"
        root = $ProjectRoot
        repository = "IAMACESIRX/Project-Athena"
    }
    profile = if ($Full) { "full" } else { "bounded" }
    git = $git
    files = $records
    coverage = [ordered]@{
        selected_files = $records.Count
        included_characters = $totalIncluded
        omitted_characters = $totalOmitted
        source_transcripts_excluded = $true
        binary_assets_excluded = $true
        complete_repository_export = $false
        note = if ($Full) {
            "All selected text files are included, but raw chat transcripts, binary assets, generated/build trees, and the full file index are intentionally excluded."
        }
        else {
            "This is a bounded operational capsule. Per-file truncation and hashes make omissions explicit. Use -Full for untruncated selected text."
        }
    }
}

$header = @"
# Project Athena Repository Context Capsule

Generated: $($manifest.generated_at)
Profile: $($manifest.profile)
Commit: $($git.commit)
Branch: $($git.branch)
Dirty: $($git.dirty)
Selected files: $($records.Count)
Included characters: $totalIncluded
Omitted characters: $totalOmitted

This capsule is context, not canonical authority. File hashes and truncation
markers are part of the record. Raw chat transcripts and binary assets are
excluded; consult their audited manifests when source-level detail is needed.

---
"@

if (-not $NoWrite) {
    if ($Full) {
        $generatedRoot = Join-Path $ProjectRoot "continuity\chat-repository-sync\generated"
        $outputRoot = Join-Path $generatedRoot ("full-" + (Get-Date -Format "yyyyMMdd-HHmmss"))
        New-Item -ItemType Directory -Force -Path $outputRoot | Out-Null
        $manifestPath = Join-Path $outputRoot "manifest.json"
        $manifest | ConvertTo-Json -Depth 20 | Set-Content -LiteralPath $manifestPath -Encoding UTF8

        $part = 1
        $buffer = $header
        foreach ($section in $sections) {
            if ($buffer.Length -gt $header.Length -and ($buffer.Length + $section.Length) -gt $FullChunkCharacters) {
                $partPath = Join-Path $outputRoot ("capsule-part-{0:d3}.md" -f $part)
                Set-Content -LiteralPath $partPath -Value $buffer -Encoding UTF8
                $part++
                $buffer = $header
            }
            $buffer += "`n`n$section"
        }
        if ($buffer.Length -gt $header.Length) {
            $partPath = Join-Path $outputRoot ("capsule-part-{0:d3}.md" -f $part)
            Set-Content -LiteralPath $partPath -Value $buffer -Encoding UTF8
        }
        $manifest.output_root = $outputRoot
        $manifest.parts = $part
    }
    else {
        $outputRoot = Join-Path $ProjectRoot "continuity\chat-repository-sync"
        $manifestPath = Join-Path $outputRoot "latest-context-capsule.json"
        $markdownPath = Join-Path $outputRoot "latest-context-capsule.md"
        $manifest | ConvertTo-Json -Depth 20 | Set-Content -LiteralPath $manifestPath -Encoding UTF8
        Set-Content -LiteralPath $markdownPath -Value ($header + "`n`n" + ($sections -join "`n`n---`n`n")) -Encoding UTF8
        $manifest.output_manifest = $manifestPath
        $manifest.output_markdown = $markdownPath
    }
}

[PSCustomObject]$manifest
