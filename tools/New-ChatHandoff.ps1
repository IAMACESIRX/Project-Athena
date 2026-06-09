param(
    [Parameter(Mandatory = $true)]
    [string]$Title,

    [Parameter(Mandatory = $true)]
    [string]$Summary,

    [string]$Source = "codex",
    [string]$Actor = "ai",
    [string]$Layer = "mega",
    [string]$Decisions = "",
    [string]$Changes = "",
    [string]$Risks = "",
    [string]$NextActions = "",
    [string]$ProjectRoot = ""
)

$ErrorActionPreference = "Stop"

if (-not $ProjectRoot) {
    $ProjectRoot = (Resolve-Path (Join-Path $PSScriptRoot "..\..")).Path
}

$timestamp = Get-Date -Format "yyyyMMdd-HHmmss"
$safeTitle = ($Title.ToLowerInvariant() -replace "[^a-z0-9]+", "-").Trim("-")
if (-not $safeTitle) { $safeTitle = "handoff" }

$id = "CHAT-$timestamp"
$chatDir = Join-Path $ProjectRoot "ai-system\continuity\chat-logs"
$packetDir = Join-Path $ProjectRoot "ai-system\continuity\handoff-packets"
New-Item -ItemType Directory -Force -Path $chatDir, $packetDir | Out-Null

$chatPath = Join-Path $chatDir "$id-$Source-$safeTitle.md"
$packetPath = Join-Path $packetDir "$id-$safeTitle.md"
$now = (Get-Date).ToString("o")

$body = @"
# ${id}: $Title

## Metadata

- time: $now
- source: $Source
- actor: $Actor
- layer: $Layer

## Summary

$Summary

## Decisions

$Decisions

## Changes

$Changes

## Risks

$Risks

## Next Actions

$NextActions
"@

Set-Content -LiteralPath $chatPath -Value $body -Encoding UTF8
Set-Content -LiteralPath $packetPath -Value $body -Encoding UTF8

Write-Host $chatPath
Write-Host $packetPath
