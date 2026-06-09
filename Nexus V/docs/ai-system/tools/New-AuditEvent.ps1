param(
    [Parameter(Mandatory = $true)]
    [string]$Summary,

    [string]$Actor = "ai",
    [string]$EventType = "note",
    [string]$Layer = "mega",
    [string]$Evidence = "",
    [string]$ExpectedEffect = "",
    [string]$Rollback = "",
    [string]$ProjectRoot = ""
)

$ErrorActionPreference = "Stop"

if (-not $ProjectRoot) {
    $ProjectRoot = (Resolve-Path (Join-Path $PSScriptRoot "..\..")).Path
}

$timestamp = Get-Date -Format "yyyyMMdd-HHmmss"
$id = "AUD-$timestamp"
$eventDir = Join-Path $ProjectRoot "ai-system\audit\events"
New-Item -ItemType Directory -Force -Path $eventDir | Out-Null

$safeSummary = ($Summary.ToLowerInvariant() -replace "[^a-z0-9]+", "-").Trim("-")
if (-not $safeSummary) { $safeSummary = "event" }
$eventPath = Join-Path $eventDir "$id-$safeSummary.md"
$now = (Get-Date).ToString("o")

$content = @"
# ${id}: $Summary

## Metadata

- time: $now
- actor: $Actor
- event_type: $EventType
- layer: $Layer

## Evidence

$Evidence

## Expected Effect

$ExpectedEffect

## Actual Effect

-

## Rollback

$Rollback
"@

Set-Content -LiteralPath $eventPath -Value $content -Encoding UTF8
Write-Host $eventPath
