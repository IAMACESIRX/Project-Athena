param(
    [string]$ProjectRoot = (Resolve-Path (Join-Path $PSScriptRoot "..")).Path,
    [switch]$Commit,
    [switch]$Push,
    [switch]$AllowDirtyChildren,
    [string]$Message = "Update child repo pointers"
)

$ErrorActionPreference = "Stop"

$status = & git -C $ProjectRoot status --short --branch 2>&1
if ($LASTEXITCODE -ne 0) {
    throw "Could not inspect Project Athena root: $ProjectRoot"
}

Write-Host "Project Athena is currently a standalone root checkout."
Write-Host "No legacy child repo pointers are configured for this workspace."
Write-Host ""
Write-Host "Current root status:"
$status | ForEach-Object { Write-Host $_ }

if ($Commit -or $Push) {
    throw "This compatibility shim does not commit or push. Stage and commit explicit files intentionally."
}

if ($AllowDirtyChildren) {
    Write-Host ""
    Write-Host "-AllowDirtyChildren was ignored because there are no configured child pointer layers."
}

if ($Message -ne "Update child repo pointers") {
    Write-Host ""
    Write-Host "Message was ignored: $Message"
}
