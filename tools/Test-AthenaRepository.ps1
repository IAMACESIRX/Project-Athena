param(
    [string]$ProjectRoot = "",
    [switch]$NoWrite
)

$ErrorActionPreference = "Stop"
if (-not $ProjectRoot) { $ProjectRoot = (Resolve-Path (Join-Path $PSScriptRoot "..")).Path }
$issues = @()

function Add-Issue {
    param([string]$Check, [string]$Message)
    $script:issues += [PSCustomObject]@{ check = $Check; message = $Message }
}

$required = @(
    "Plan/CHAT_REPOSITORY_CONTINUITY_PIPELINE.md",
    "continuity/chat-repository-sync/sync-policy.json",
    "continuity/chat-repository-sync/promotion-ledger.jsonl",
    "schemas/chat-source-bundle.schema.json",
    "schemas/chat-promotion.schema.json",
    "schemas/repository-context-capsule.schema.json",
    "tools/Import-AthenaChatExport.ps1",
    "tools/Export-AthenaChatContext.ps1",
    "tools/Test-AthenaAssetManifest.ps1",
    "work/github-plan.json",
    ".github/workflows/athena-integrity.yml"
)
foreach ($relative in $required) {
    if (-not (Test-Path -LiteralPath (Join-Path $ProjectRoot ($relative -replace "/", "\")))) {
        Add-Issue -Check "required-file" -Message "Missing $relative"
    }
}

foreach ($file in Get-ChildItem -LiteralPath $ProjectRoot -Recurse -File -Filter "*.json" | Where-Object { $_.FullName -notmatch "\\.git\\" }) {
    try { Get-Content -Raw -LiteralPath $file.FullName | ConvertFrom-Json | Out-Null }
    catch { Add-Issue -Check "json" -Message "$($file.FullName): $($_.Exception.Message)" }
}
foreach ($file in Get-ChildItem -LiteralPath $ProjectRoot -Recurse -File -Filter "*.jsonl" | Where-Object { $_.FullName -notmatch "\\.git\\" }) {
    $lineNumber = 0
    foreach ($line in [IO.File]::ReadLines($file.FullName)) {
        $lineNumber++
        if (-not $line.Trim()) { continue }
        try { $line | ConvertFrom-Json | Out-Null }
        catch { Add-Issue -Check "jsonl" -Message "$($file.FullName):$lineNumber $($_.Exception.Message)"; break }
    }
}

foreach ($file in Get-ChildItem -LiteralPath (Join-Path $ProjectRoot "tools") -File -Filter "*.ps1") {
    $tokens = $null
    $parseErrors = $null
    [Management.Automation.Language.Parser]::ParseFile($file.FullName, [ref]$tokens, [ref]$parseErrors) | Out-Null
    foreach ($parseError in @($parseErrors)) {
        Add-Issue -Check "powershell-parse" -Message "$($file.FullName): $($parseError.Message)"
    }
}

try {
    $assetResult = & (Join-Path $ProjectRoot "tools\Test-AthenaAssetManifest.ps1") -ProjectRoot $ProjectRoot -NoThrow
    if ($assetResult.status -ne "PASS") {
        foreach ($message in @($assetResult.issues)) { Add-Issue -Check "asset-manifest" -Message $message }
    }
}
catch {
    Add-Issue -Check "asset-manifest" -Message $_.Exception.Message
}

try {
    $integrity = & (Join-Path $ProjectRoot "tools\Invoke-AIIntegrityCheck.ps1") -ProjectRoot $ProjectRoot -NoWrite
    if ($integrity.status -eq "FAIL") {
        foreach ($item in @($integrity.issues)) { Add-Issue -Check "integrity" -Message $item.summary }
    }
}
catch {
    Add-Issue -Check "integrity" -Message $_.Exception.Message
}

try {
    $previousErrorActionPreference = $ErrorActionPreference
    $ErrorActionPreference = "Continue"
    $diffOutput = @(& git -C $ProjectRoot diff --check 2>$null)
    $diffExitCode = $LASTEXITCODE
    $ErrorActionPreference = $previousErrorActionPreference
    if ($diffExitCode -ne 0) {
        foreach ($line in $diffOutput) { Add-Issue -Check "git-diff" -Message ([string]$line) }
        if ($diffOutput.Count -eq 0) {
            Add-Issue -Check "git-diff" -Message "git diff --check failed with exit code $diffExitCode"
        }
    }
}
catch {
    $ErrorActionPreference = "Stop"
    Add-Issue -Check "git-diff" -Message $_.Exception.Message
}

$secretPatterns = @(
    "-----BEGIN (RSA |EC |OPENSSH )?PRIVATE KEY-----",
    "gh[pousr]_[A-Za-z0-9]{20,}",
    "sk-[A-Za-z0-9_-]{20,}",
    "AKIA[0-9A-Z]{16}"
)
$scanExtensions = @(".md", ".txt", ".json", ".jsonl", ".yml", ".yaml", ".ps1", ".csv")
foreach ($file in Get-ChildItem -LiteralPath $ProjectRoot -Recurse -File | Where-Object {
    $_.Extension.ToLowerInvariant() -in $scanExtensions -and
    $_.FullName -notmatch "\\.git\\" -and
    $_.FullName -notmatch "\\continuity\\transcript-inbox\\imports\\"
}) {
    $text = Get-Content -Raw -LiteralPath $file.FullName -ErrorAction SilentlyContinue
    foreach ($pattern in $secretPatterns) {
        if ($text -match $pattern) {
            Add-Issue -Check "publication-safety" -Message "Potential credential pattern in $($file.FullName)"
            break
        }
    }
}

$report = [PSCustomObject]@{
    schema = "athena.repository_test.v1"
    generated_at = (Get-Date).ToString("o")
    project_root = $ProjectRoot
    status = if ($issues.Count -eq 0) { "PASS" } else { "FAIL" }
    issue_count = $issues.Count
    issues = $issues
}

if (-not $NoWrite) {
    $reportDir = Join-Path $ProjectRoot "diagnostics\reports"
    New-Item -ItemType Directory -Force -Path $reportDir | Out-Null
    $report | ConvertTo-Json -Depth 12 | Set-Content -LiteralPath (Join-Path $reportDir "latest-athena-repository-test.json") -Encoding UTF8
}

$report
if ($issues.Count -gt 0) { exit 1 }
