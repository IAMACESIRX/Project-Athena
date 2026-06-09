param(
    [string]$ProjectRoot = (Resolve-Path (Join-Path $PSScriptRoot "..\..")).Path,
    [string]$Title = "Session handoff",
    [switch]$IncludeScan
)

$ErrorActionPreference = "Stop"

function Get-StatusBlock {
    param(
        [string]$Name,
        [string]$Path,
        [string[]]$ExtraArgs = @()
    )

    $arguments = @("status", "--short", "--branch") + $ExtraArgs
    $output = & git -C $Path @arguments 2>&1
    if ($LASTEXITCODE -ne 0) {
        $output = "Unable to read git status for $Name"
    }

$fence = [string]([char]96) + [string]([char]96) + [string]([char]96)

    return @"
### $Name

${fence}text
$($output -join "`n")
$fence
"@
}

$sessionDir = Join-Path $ProjectRoot "ai-system\handoff\sessions"
New-Item -ItemType Directory -Force -Path $sessionDir | Out-Null

$timestamp = Get-Date -Format "yyyyMMdd-HHmmss"
$filePath = Join-Path $sessionDir "session-$timestamp.md"
$now = (Get-Date).ToString("o")

$scanNote = ""
if ($IncludeScan) {
    $scanOutput = & (Join-Path $PSScriptRoot "Invoke-AIProjectScan.ps1") -ProjectRoot $ProjectRoot
    $scanNote = "Scan generated at `ai-system/sensory/scans/latest-scan.json`."
}

$megaStatus = Get-StatusBlock -Name "Mega repo" -Path $ProjectRoot -ExtraArgs @("--ignore-submodules=untracked")
$clientStatus = Get-StatusBlock -Name "Game client" -Path (Join-Path $ProjectRoot "GameClient-ChromieCraft-3.3.5a")
$liveStatus = Get-StatusBlock -Name "Server live state" -Path (Join-Path $ProjectRoot "Server-Live-State")
$projectStatus = Get-StatusBlock -Name "WoW server project" -Path (Join-Path $ProjectRoot "WoW-Server-Project")

$content = @"
# $Title

Generated: $now

## Summary

$scanNote

## Git Status

$megaStatus

$clientStatus

$liveStatus

$projectStatus

## What Changed

-

## Verification

-

## Risks Or Open Questions

-

## Next Best Action

-
"@

Set-Content -LiteralPath $filePath -Value $content -Encoding UTF8
Write-Host $filePath
