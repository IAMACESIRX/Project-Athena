param(
    [string]$ProjectRoot = (Resolve-Path (Join-Path $PSScriptRoot "..\..")).Path,
    [string]$ServerPath = "WoW-Server-Project\servers\wow\azerothcore-wotlk-playerbots",
    [int]$Tail = 80,
    [switch]$NoWrite
)

$ErrorActionPreference = "Stop"

function Invoke-Capture {
    param(
        [string]$Command,
        [string]$WorkingDirectory
    )

    $output = & powershell -NoProfile -Command "Set-Location -LiteralPath '$WorkingDirectory'; $Command" 2>&1
    $exit = $LASTEXITCODE

    [PSCustomObject]@{
        command = $Command
        exit_code = $exit
        output = (($output | ForEach-Object { $_.ToString() }) -join "`n")
    }
}

$fullServerPath = Join-Path $ProjectRoot $ServerPath
$dockerCommand = Get-Command docker -ErrorAction SilentlyContinue
$dockerAvailable = $null -ne $dockerCommand
$dockerVersion = if ($dockerAvailable) { & docker --version 2>&1 } else { "docker command not found" }

$composePs = $null
$logs = @()

if ($dockerAvailable -and (Test-Path -LiteralPath $fullServerPath)) {
    $composePs = Invoke-Capture -WorkingDirectory $fullServerPath -Command "docker compose ps"

    foreach ($container in @("ac-database", "ac-db-import", "ac-authserver", "ac-worldserver")) {
        $logs += [PSCustomObject]@{
            container = $container
            result = Invoke-Capture -WorkingDirectory $fullServerPath -Command "docker logs $container --tail $Tail"
        }
    }
}

$probe = [PSCustomObject]@{
    schema = "ai-system.live_probe.v1"
    generated_at = (Get-Date).ToString("o")
    project_root = $ProjectRoot
    server_path = $fullServerPath
    docker_available = $dockerAvailable
    docker_version = (($dockerVersion | ForEach-Object { $_.ToString() }) -join "`n")
    compose_ps = $composePs
    logs = $logs
    mutates_live_state = $false
}

if (-not $NoWrite) {
    $outDir = Join-Path $ProjectRoot "ai-system\observability\reports"
    New-Item -ItemType Directory -Force -Path $outDir | Out-Null
    $outPath = Join-Path $outDir "latest-live-probe.json"
    $probe | ConvertTo-Json -Depth 8 | Set-Content -LiteralPath $outPath -Encoding UTF8

    $logPath = Join-Path $outDir "LIVE-PROBE-LOG.md"
    Add-Content -LiteralPath $logPath -Value "- $($probe.generated_at): docker_available=$dockerAvailable; server_path=$fullServerPath" -Encoding UTF8
}

$probe
