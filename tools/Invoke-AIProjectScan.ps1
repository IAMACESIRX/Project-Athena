param(
    [string]$ProjectRoot = (Resolve-Path (Join-Path $PSScriptRoot "..")).Path,
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
        $inspectGit = ($Path -eq ".")
        $isGit = $inspectGit -and ((Test-Path -LiteralPath (Join-Path $fullPath ".git")) -or ((Invoke-GitCommand -RepoPath $fullPath -Arguments @("rev-parse", "--is-inside-work-tree")).ExitCode -eq 0))

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
    @{ Id = "project-athena"; Name = "Project Athena"; Path = "."; Role = "athena_workspace"; ManagementRemote = $true },
    @{ Id = "plan"; Name = "Plan Architecture Vault"; Path = "Plan"; Role = "architecture_intent_vault"; ManagementRemote = $false },
    @{ Id = "nexus-v"; Name = "Nexus V Hardware And Toolchain"; Path = "Nexus V"; Role = "implementation_subsystem"; ManagementRemote = $false },
    @{ Id = "engine"; Name = "Athena Operation Engine"; Path = "engine"; Role = "processor_loop"; ManagementRemote = $false },
    @{ Id = "memory"; Name = "Athena Memory"; Path = "memory"; Role = "memory_layer"; ManagementRemote = $false },
    @{ Id = "work"; Name = "Athena Work System"; Path = "work"; Role = "working_memory"; ManagementRemote = $false },
    @{ Id = "tools"; Name = "Athena Tools"; Path = "tools"; Role = "tooling_layer"; ManagementRemote = $false }
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

if (-not (Test-Path -LiteralPath (Join-Path $ProjectRoot "context.md"))) {
    Add-Signal -Signals $signals -Severity "yellow" -Id "missing-context" -Message "Root context.md is missing."
}

if (-not (Test-Path -LiteralPath (Join-Path $ProjectRoot "Plan\context.md"))) {
    Add-Signal -Signals $signals -Severity "yellow" -Id "missing-plan-context" -Message "Plan/context.md is missing."
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
    $scanDir = Join-Path $ProjectRoot "sensory\scans"
    New-Item -ItemType Directory -Force -Path $scanDir | Out-Null

    $scanPath = Join-Path $scanDir "latest-scan.json"
    $scan | ConvertTo-Json -Depth 8 | Set-Content -LiteralPath $scanPath -Encoding UTF8

    $logPath = Join-Path $scanDir "SCAN-LOG.md"
    $summary = "- $($scan.generated_at): layers=$($repoStates.Count); signals=$($signals.Count); free_gb=$freeGB"
    Add-Content -LiteralPath $logPath -Value $summary -Encoding UTF8
}

$scan

