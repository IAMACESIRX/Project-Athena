param(
    [Parameter(Mandatory = $true)]
    [ValidateSet("todo", "bug", "feature", "research", "decision", "risk")]
    [string]$Type,

    [Parameter(Mandatory = $true)]
    [string]$Title,

    [string]$Layer = "mega",

    [ValidateSet("low", "medium", "high", "critical")]
    [string]$Severity = "medium",

    [string]$ProjectRoot = ""
)

$ErrorActionPreference = "Stop"

if (-not $ProjectRoot) {
    $ProjectRoot = (Resolve-Path (Join-Path $PSScriptRoot "..")).Path
}

$prefix = switch ($Type) {
    "todo" { "TODO" }
    "bug" { "BUG" }
    "feature" { "FEAT" }
    "research" { "RND" }
    "decision" { "DECIDE" }
    "risk" { "RISK" }
}

$timestamp = Get-Date -Format "yyyyMMdd-HHmmss"
$id = "$prefix-$timestamp"
$safeTitle = ($Title.ToLowerInvariant() -replace "[^a-z0-9]+", "-").Trim("-")
if (-not $safeTitle) { $safeTitle = "item" }

$outDir = Join-Path $ProjectRoot "work\work-items"
New-Item -ItemType Directory -Force -Path $outDir | Out-Null
$outPath = Join-Path $outDir "$id-$safeTitle.md"
$now = (Get-Date).ToString("o")

$content = @"
# ${id}: $Title

## Metadata

- type: $Type
- status: open
- layer: $Layer
- severity: $Severity
- created_at: $now
- updated_at: $now

## Summary

$Title

## Evidence

-

## Next Action

-

## Resolution

-
"@

Set-Content -LiteralPath $outPath -Value $content -Encoding UTF8
Write-Host $outPath

