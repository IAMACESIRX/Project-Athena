param(
    [string]$ProjectRoot = "",
    [string]$PlanPath = "",
    [string]$Token = "",
    [switch]$Apply,
    [switch]$UpdateExisting,
    [switch]$SyncProject,
    [switch]$RequireProject
)

$ErrorActionPreference = "Stop"
if (-not $ProjectRoot) { $ProjectRoot = (Resolve-Path (Join-Path $PSScriptRoot "..")).Path }

if (-not $PlanPath) { $PlanPath = Join-Path $ProjectRoot "work\github-plan.json" }
$plan = Get-Content -Raw -LiteralPath $PlanPath | ConvertFrom-Json
$parts = $plan.repository -split "/", 2
if ($parts.Count -ne 2) { throw "Invalid repository in plan: $($plan.repository)" }
$owner = $parts[0]
$repo = $parts[1]

$summary = [ordered]@{
    schema = "athena.github_sync_report.v1"
    generated_at = (Get-Date).ToString("o")
    repository = $plan.repository
    mode = if ($Apply) { "apply" } else { "plan" }
    desired = [ordered]@{
        labels = @($plan.labels).Count
        milestones = @($plan.milestones).Count
        issues = @($plan.issues).Count
        project = $plan.project.title
    }
    actions = @()
    warnings = @()
}

if (-not $Apply) {
    $summary.actions += "Plan validated. No GitHub mutations were attempted."
    [PSCustomObject]$summary
    return
}

if (-not $Token) { $Token = $env:ATHENA_GITHUB_TOKEN }
if (-not $Token) { $Token = $env:GH_TOKEN }
if (-not $Token) { $Token = $env:GITHUB_TOKEN }
if (-not $Token) { throw "Set -Token, ATHENA_GITHUB_TOKEN, GH_TOKEN, or GITHUB_TOKEN before applying the GitHub plan." }

$headers = @{
    Authorization = "Bearer $Token"
    Accept = "application/vnd.github+json"
    "X-GitHub-Api-Version" = "2022-11-28"
    "User-Agent" = "Project-Athena-Sync"
}

function Invoke-GitHubRest {
    param([string]$Method, [string]$Path, $Body = $null)
    $parameters = @{
        Method = $Method
        Uri = "https://api.github.com$Path"
        Headers = $headers
        ErrorAction = "Stop"
    }
    if ($null -ne $Body) {
        $parameters.ContentType = "application/json"
        $parameters.Body = ($Body | ConvertTo-Json -Depth 20 -Compress)
    }
    return Invoke-RestMethod @parameters
}

function Get-AllPages {
    param([string]$Path)
    $items = @()
    $page = 1
    do {
        $separator = if ($Path.Contains("?")) { "&" } else { "?" }
        $batch = @(Invoke-GitHubRest -Method GET -Path "$Path${separator}per_page=100&page=$page")
        $items += $batch
        $page++
    } while ($batch.Count -eq 100)
    return $items
}

$existingLabels = @{}
foreach ($label in @(Get-AllPages -Path "/repos/$owner/$repo/labels")) { $existingLabels[$label.name] = $label }
foreach ($label in @($plan.labels)) {
    if (-not $existingLabels.ContainsKey($label.name)) {
        Invoke-GitHubRest -Method POST -Path "/repos/$owner/$repo/labels" -Body @{ name = $label.name; color = $label.color; description = $label.description } | Out-Null
        $summary.actions += "Created label: $($label.name)"
    }
    elseif ($UpdateExisting) {
        $encoded = [Uri]::EscapeDataString([string]$label.name)
        Invoke-GitHubRest -Method PATCH -Path "/repos/$owner/$repo/labels/$encoded" -Body @{ new_name = $label.name; color = $label.color; description = $label.description } | Out-Null
        $summary.actions += "Reconciled label: $($label.name)"
    }
}

$milestones = @{}
foreach ($milestone in @(Get-AllPages -Path "/repos/$owner/$repo/milestones?state=all")) { $milestones[$milestone.title] = $milestone }
foreach ($desired in @($plan.milestones)) {
    if (-not $milestones.ContainsKey($desired.title)) {
        $created = Invoke-GitHubRest -Method POST -Path "/repos/$owner/$repo/milestones" -Body @{ title = $desired.title; description = $desired.description; state = $desired.state }
        $milestones[$desired.title] = $created
        $summary.actions += "Created milestone: $($desired.title)"
    }
    elseif ($UpdateExisting) {
        $number = $milestones[$desired.title].number
        $updated = Invoke-GitHubRest -Method PATCH -Path "/repos/$owner/$repo/milestones/$number" -Body @{ title = $desired.title; description = $desired.description; state = $desired.state }
        $milestones[$desired.title] = $updated
        $summary.actions += "Reconciled milestone: $($desired.title)"
    }
}

$issues = @{}
foreach ($issue in @(Get-AllPages -Path "/repos/$owner/$repo/issues?state=all" | Where-Object { -not $_.pull_request })) { $issues[$issue.title] = $issue }
foreach ($desired in @($plan.issues)) {
    if (-not $milestones.ContainsKey($desired.milestone)) { throw "Issue $($desired.id) references unknown milestone $($desired.milestone)" }
    $body = "<!-- athena-work-id: $($desired.id) -->`n`n$($desired.body)"
    $payload = @{
        title = $desired.title
        body = $body
        labels = @($desired.labels)
        milestone = $milestones[$desired.milestone].number
    }
    if (-not $issues.ContainsKey($desired.title)) {
        $created = Invoke-GitHubRest -Method POST -Path "/repos/$owner/$repo/issues" -Body $payload
        $issues[$desired.title] = $created
        $summary.actions += "Created issue #$($created.number): $($desired.title)"
    }
    elseif ($UpdateExisting) {
        $number = $issues[$desired.title].number
        $updated = Invoke-GitHubRest -Method PATCH -Path "/repos/$owner/$repo/issues/$number" -Body $payload
        $issues[$desired.title] = $updated
        $summary.actions += "Reconciled issue #${number}: $($desired.title)"
    }
}

if ($SyncProject) {
    $gh = Get-Command gh -ErrorAction SilentlyContinue
    if ($null -eq $gh) {
        $message = "GitHub CLI is unavailable; labels, milestones, and issues were synchronized, but the user-level Project was not."
        if ($RequireProject) { throw $message }
        $summary.warnings += $message
    }
    else {
        $previousToken = $env:GH_TOKEN
        try {
            $env:GH_TOKEN = $Token
            $projectList = (& gh project list --owner $owner --format json | ConvertFrom-Json)
            $projects = if ($projectList.PSObject.Properties.Name -contains "projects") { @($projectList.projects) } else { @($projectList) }
            $project = $projects | Where-Object title -eq $plan.project.title | Select-Object -First 1
            if ($null -eq $project) {
                $project = & gh project create --owner $owner --title $plan.project.title --format json | ConvertFrom-Json
                $summary.actions += "Created GitHub Project: $($plan.project.title)"
            }
            $projectNumber = [int]$project.number
            foreach ($issue in $issues.Values) {
                & gh project item-add $projectNumber --owner $owner --url $issue.html_url | Out-Null
                if ($LASTEXITCODE -ne 0) { throw "Unable to add issue $($issue.html_url) to project $projectNumber" }
            }
            $summary.actions += "Reconciled $($issues.Count) issue items in GitHub Project #$projectNumber."
            $summary.warnings += "Custom Project fields and views remain a UI/API configuration step; their desired definitions are preserved in work/github-plan.json."
        }
        finally {
            $env:GH_TOKEN = $previousToken
        }
    }
}

[PSCustomObject]$summary
