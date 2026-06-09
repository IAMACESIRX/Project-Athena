param(
    [string]$ProjectRoot = (Resolve-Path (Join-Path $PSScriptRoot "..\..")).Path,
    [switch]$IncludeFileCounts,
    [switch]$NoWrite
)

$ErrorActionPreference = "Stop"

function Invoke-GitCommand {
    param(
        [Parameter(Mandatory = $true)]
        [string]$RepoPath,

        [Parameter(Mandatory = $true)]
        [string[]]$Arguments
    )

    $output = & git -C $RepoPath @Arguments 2>&1
    $exitCode = $LASTEXITCODE

    return [PSCustomObject]@{
        ExitCode = $exitCode
        Output = (($output | ForEach-Object { $_.ToString() }) -join "`n").Trim()
    }
}

function Get-GitValue {
    param(
        [string]$RepoPath,
        [string[]]$Arguments
    )

    $result = Invoke-GitCommand -RepoPath $RepoPath -Arguments $Arguments
    if ($result.ExitCode -ne 0) {
        return $null
    }

    return $result.Output
}

function Get-RepoState {
    param(
        [string]$Id,
        [string]$Name,
        [string]$Path,
        [string]$Role,
        [bool]$ManagementRemote = $false
    )

    $fullPath = Join-Path $ProjectRoot $Path
    if ($Path -eq ".") {
        $fullPath = $ProjectRoot
    }

    $exists = Test-Path -LiteralPath $fullPath
    $isGit = $false
    $branch = $null
    $head = $null
    $origin = $null
    $status = $null
    $trackedDirtyCount = $null
    $untrackedCount = $null
    $fileCount = $null
    $sizeMB = $null

    if ($exists) {
        $isGit = (Test-Path -LiteralPath (Join-Path $fullPath ".git")) -or ((Invoke-GitCommand -RepoPath $fullPath -Arguments @("rev-parse", "--is-inside-work-tree")).ExitCode -eq 0)

        if ($isGit) {
            $branch = Get-GitValue -RepoPath $fullPath -Arguments @("branch", "--show-current")
            $head = Get-GitValue -RepoPath $fullPath -Arguments @("rev-parse", "--short", "HEAD")
            $origin = Get-GitValue -RepoPath $fullPath -Arguments @("remote", "get-url", "origin")
            $statusArgs = @("status", "--short", "--branch")
            $porcelainArgs = @("status", "--porcelain")

            if ($Role -in @("orchestrator", "child_project_layer")) {
                $statusArgs += "--ignore-submodules=untracked"
                $porcelainArgs += "--ignore-submodules=untracked"
            }

            $status = Get-GitValue -RepoPath $fullPath -Arguments $statusArgs

            $porcelain = Get-GitValue -RepoPath $fullPath -Arguments $porcelainArgs
            if ($porcelain) {
                $lines = $porcelain -split "`n" | Where-Object { $_.Trim().Length -gt 0 }
                $untrackedCount = @($lines | Where-Object { $_.StartsWith("??") -or $_.StartsWith(" ?") }).Count
                $trackedDirtyCount = @($lines | Where-Object { -not ($_.StartsWith("??") -or $_.StartsWith(" ?")) }).Count
            }
            else {
                $untrackedCount = 0
                $trackedDirtyCount = 0
            }
        }

        if ($IncludeFileCounts) {
            $measure = Get-ChildItem -LiteralPath $fullPath -Recurse -File -Force -ErrorAction SilentlyContinue |
                Where-Object { $_.FullName -notmatch "\\.git\\" } |
                Measure-Object -Property Length -Sum
            $fileCount = $measure.Count
            $sizeMB = [math]::Round(($measure.Sum / 1MB), 2)
        }
    }

    return [PSCustomObject]@{
        id = $Id
        name = $Name
        role = $Role
        path = $Path
        full_path = $fullPath
        exists = $exists
        is_git = $isGit
        branch = $branch
        head = $head
        origin = $origin
        management_remote = $ManagementRemote
        tracked_dirty_count = $trackedDirtyCount
        untracked_count = $untrackedCount
        file_count = $fileCount
        size_mb = $sizeMB
        status = $status
    }
}

function Add-Signal {
    param(
        [System.Collections.Generic.List[object]]$Signals,
        [string]$Severity,
        [string]$Id,
        [string]$Message
    )

    $Signals.Add([PSCustomObject]@{
        severity = $Severity
        id = $Id
        message = $Message
    }) | Out-Null
}

$layers = @(
    @{ Id = "mega"; Name = "Mega Backup Stack"; Path = "."; Role = "orchestrator"; ManagementRemote = $true },
    @{ Id = "game-client"; Name = "ChromieCraft Game Client"; Path = "GameClient-ChromieCraft-3.3.5a"; Role = "child_payload_layer"; ManagementRemote = $true },
    @{ Id = "live-state"; Name = "Server Live State"; Path = "Server-Live-State"; Role = "child_state_layer"; ManagementRemote = $true },
    @{ Id = "server-project"; Name = "WoW Server Project"; Path = "WoW-Server-Project"; Role = "child_project_layer"; ManagementRemote = $true },
    @{ Id = "azerothcore-clean"; Name = "AzerothCore Clean Baseline"; Path = "WoW-Server-Project\servers\wow\azerothcore-wotlk"; Role = "nested_source_repo"; ManagementRemote = $false },
    @{ Id = "azerothcore-playerbots"; Name = "AzerothCore Playerbots Fork"; Path = "WoW-Server-Project\servers\wow\azerothcore-wotlk-playerbots"; Role = "nested_source_repo"; ManagementRemote = $false },
    @{ Id = "mod-playerbots"; Name = "mod-playerbots"; Path = "WoW-Server-Project\servers\wow\azerothcore-wotlk-playerbots\modules\mod-playerbots"; Role = "nested_module_repo"; ManagementRemote = $false }
)

$repoStates = foreach ($layer in $layers) {
    Get-RepoState -Id $layer.Id -Name $layer.Name -Path $layer.Path -Role $layer.Role -ManagementRemote $layer.ManagementRemote
}

$drive = Get-PSDrive -Name ((Get-Item -LiteralPath $ProjectRoot).PSDrive.Name)
$signals = New-Object 'System.Collections.Generic.List[object]'

$freeGB = [math]::Round(($drive.Free / 1GB), 2)
if ($freeGB -lt 80) {
    Add-Signal -Signals $signals -Severity "yellow" -Id "disk-low" -Message "Drive free space is below 80 GB: $freeGB GB."
}

foreach ($repo in $repoStates) {
    if (-not $repo.exists) {
        Add-Signal -Signals $signals -Severity "red" -Id "missing-layer" -Message "Layer missing: $($repo.id) at $($repo.path)."
    }

    if ($repo.management_remote -and $repo.origin -and ($repo.origin -match "github\.com|https://|git@")) {
        Add-Signal -Signals $signals -Severity "red" -Id "cloud-remote" -Message "Management repo $($repo.id) has a non-local origin: $($repo.origin)."
    }

    if ($repo.tracked_dirty_count -gt 0) {
        Add-Signal -Signals $signals -Severity "yellow" -Id "tracked-dirty" -Message "Repo $($repo.id) has tracked working tree changes."
    }
}

$gameClient = $repoStates | Where-Object { $_.id -eq "game-client" } | Select-Object -First 1
if ($gameClient.untracked_count -gt 0) {
    Add-Signal -Signals $signals -Severity "yellow" -Id "client-untracked-payload" -Message "Game client has $($gameClient.untracked_count) untracked top-level entries. This is currently intentional."
}

$venvConfig = Join-Path $ProjectRoot "WoW-Server-Project\.venv\pyvenv.cfg"
if (Test-Path -LiteralPath $venvConfig) {
    $venvText = Get-Content -Raw -LiteralPath $venvConfig
    if ($venvText -match "executable\s*=\s*(.+)") {
        $venvExe = $Matches[1].Trim()
        if (-not (Test-Path -LiteralPath $venvExe)) {
            Add-Signal -Signals $signals -Severity "yellow" -Id "broken-venv" -Message "Python venv executable is missing: $venvExe."
        }
    }
}

$authDump = Join-Path $ProjectRoot "Server-Live-State\acore_auth.sql"
if (Test-Path -LiteralPath $authDump) {
    $realmLine = Select-String -LiteralPath $authDump -Pattern "INSERT INTO ``realmlist``" -SimpleMatch | Select-Object -First 1
    if ($realmLine -and $realmLine.Line -match "127\.0\.0\.1") {
        Add-Signal -Signals $signals -Severity "yellow" -Id "realm-localhost" -Message "Live-state auth dump realmlist appears to contain 127.0.0.1."
    }
}

$scan = [PSCustomObject]@{
    schema = "ai-system.scan.v1"
    generated_at = (Get-Date).ToString("o")
    project_root = $ProjectRoot
    disk = [PSCustomObject]@{
        drive = $drive.Name
        free_gb = $freeGB
        used_gb = [math]::Round(($drive.Used / 1GB), 2)
    }
    layers = $repoStates
    signals = $signals
}

if (-not $NoWrite) {
    $scanDir = Join-Path $ProjectRoot "ai-system\sensory\scans"
    New-Item -ItemType Directory -Force -Path $scanDir | Out-Null

    $scanPath = Join-Path $scanDir "latest-scan.json"
    $scan | ConvertTo-Json -Depth 8 | Set-Content -LiteralPath $scanPath -Encoding UTF8

    $logPath = Join-Path $scanDir "SCAN-LOG.md"
    $summary = "- $($scan.generated_at): layers=$($repoStates.Count); signals=$($signals.Count); free_gb=$freeGB"
    Add-Content -LiteralPath $logPath -Value $summary -Encoding UTF8
}

$scan
