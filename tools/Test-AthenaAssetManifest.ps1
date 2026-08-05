param(
    [string]$ProjectRoot = "",
    [string]$AssetRoot = "",
    [switch]$NoThrow
)

$ErrorActionPreference = "Stop"
if (-not $ProjectRoot) { $ProjectRoot = (Resolve-Path (Join-Path $PSScriptRoot "..")).Path }

if (-not $AssetRoot) {
    $AssetRoot = Join-Path $ProjectRoot "athena_context\assets\generated-storyboards-2026-08-01"
}
$AssetRoot = [IO.Path]::GetFullPath($AssetRoot)
$sumPath = Join-Path $AssetRoot "00_MANIFEST\SHA256SUMS.txt"
$csvPath = Join-Path $AssetRoot "00_MANIFEST\images_manifest.csv"
$issues = @()

if (-not (Test-Path -LiteralPath $sumPath)) { $issues += "Missing checksum manifest: $sumPath" }
if (-not (Test-Path -LiteralPath $csvPath)) { $issues += "Missing CSV manifest: $csvPath" }

$expected = @{}
if ($issues.Count -eq 0) {
    foreach ($line in Get-Content -LiteralPath $sumPath) {
        if ($line -match "^([0-9a-fA-F]{64})\s+\*?(.+)$") {
            $expected[$matches[2].Replace("/", "\")] = $matches[1].ToLowerInvariant()
        }
    }
    foreach ($relative in $expected.Keys) {
        $path = [IO.Path]::GetFullPath((Join-Path $AssetRoot $relative))
        if (-not $path.StartsWith($AssetRoot + [IO.Path]::DirectorySeparatorChar, [StringComparison]::OrdinalIgnoreCase)) {
            $issues += "Unsafe manifest path: $relative"
            continue
        }
        if (-not (Test-Path -LiteralPath $path -PathType Leaf)) {
            $issues += "Missing asset: $relative"
            continue
        }
        $actual = (Get-FileHash -Algorithm SHA256 -LiteralPath $path).Hash.ToLowerInvariant()
        if ($actual -ne $expected[$relative]) {
            $issues += "Checksum mismatch: $relative"
        }
    }

    $csv = @(Import-Csv -LiteralPath $csvPath)
    if ($csv.Count -ne $expected.Count) {
        $issues += "CSV count $($csv.Count) does not match checksum count $($expected.Count)."
    }
}

$hashGroups = if ($expected.Count -gt 0) { @($expected.GetEnumerator() | Group-Object Value | Where-Object Count -gt 1) } else { @() }
$result = [PSCustomObject]@{
    schema = "athena.asset_manifest_test.v1"
    asset_root = $AssetRoot
    status = if ($issues.Count -eq 0) { "PASS" } else { "FAIL" }
    expected_assets = $expected.Count
    duplicate_hash_groups = @($hashGroups).Count
    issue_count = $issues.Count
    issues = $issues
}

$result
if ($issues.Count -gt 0 -and -not $NoThrow) { exit 1 }
