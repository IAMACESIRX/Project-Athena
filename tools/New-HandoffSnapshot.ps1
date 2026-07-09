param(
    [string]$ProjectRoot = (Resolve-Path (Join-Path $PSScriptRoot "..")).Path,
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

$sessionDir = Join-Path $ProjectRoot "handoff\sessions"
New-Item -ItemType Directory -Force -Path $sessionDir | Out-Null

$timestamp = Get-Date -Format "yyyyMMdd-HHmmss"
$filePath = Join-Path $sessionDir "session-$timestamp.md"
$now = (Get-Date).ToString("o")

$scanNote = ""
if ($IncludeScan) {
    $scanOutput = & (Join-Path $PSScriptRoot "Invoke-AIProjectScan.ps1") -ProjectRoot $ProjectRoot
    $scanNote = "Scan generated at `sensory/scans/latest-scan.json`."
}

$rootStatus = Get-StatusBlock -Name "Project Athena" -Path $ProjectRoot -ExtraArgs @("--ignore-submodules=untracked")
$planStatus = Get-StatusBlock -Name "Plan architecture vault" -Path (Join-Path $ProjectRoot "Plan")
$nexusStatus = Get-StatusBlock -Name "Nexus V subsystem" -Path (Join-Path $ProjectRoot "Nexus V")

$content = @"
# $Title

Generated: $now

## Summary

$scanNote

## Git Status

$rootStatus

$planStatus

$nexusStatus

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

