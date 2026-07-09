param(
  [string]$ProjectRoot = (Resolve-Path (Join-Path $PSScriptRoot '..')).Path,
  [string]$OutputPath = ''
)

$ErrorActionPreference = 'Stop'

if (-not $OutputPath) {
  $OutputPath = Join-Path $ProjectRoot 'context-file-index.md'
}

$textExtensions = @(
  '.md', '.txt', '.yml', '.yaml', '.json', '.ps1', '.csv', '.log', '.xml',
  '.html', '.css', '.js', '.ts', '.tsx', '.jsx', '.zig', '.c', '.cpp', '.h',
  '.hpp', '.sql', '.schema', '.toml', '.ini', '.bat', '.cmd', '.gitignore',
  '.gitattributes'
)
$imageExtensions = @('.png', '.jpg', '.jpeg', '.gif', '.bmp', '.webp', '.ico', '.svg')

function Get-RelativePath {
  param(
    [string]$Base,
    [string]$Path
  )

  $baseUri = [Uri]($Base.TrimEnd([IO.Path]::DirectorySeparatorChar) + [IO.Path]::DirectorySeparatorChar)
  $pathUri = [Uri]$Path
  return [Uri]::UnescapeDataString($baseUri.MakeRelativeUri($pathUri).ToString()).Replace('\', '/')
}

function Test-GitPath {
  param([string]$Path)

  $relative = Get-RelativePath -Base $ProjectRoot -Path $Path
  return ($relative -eq '.git' -or $relative.StartsWith('.git/') -or $relative.Contains('/.git/'))
}

function Get-Sha12 {
  param([string]$Path)

  return (Get-FileHash -Algorithm SHA256 -Path $Path).Hash.Substring(0, 12)
}

function Get-TextSummary {
  param([string]$Path)

  try {
    $raw = Get-Content -Raw -LiteralPath $Path -ErrorAction Stop
    $lines = if ($raw.Length -eq 0) { 0 } else { ($raw -split "`r?`n").Count }
    $first = (($raw -split "`r?`n") | Where-Object { $_.Trim().Length -gt 0 } | Select-Object -First 1)
    if (-not $first) {
      $first = 'blank text file'
    }
    return @{ Lines = $lines; Detail = ($first.Trim() -replace '\|', '/') }
  } catch {
    return @{ Lines = 0; Detail = 'text read failed' }
  }
}

function Get-ZipSummary {
  param([string]$Path)

  try {
    Add-Type -AssemblyName System.IO.Compression.FileSystem -ErrorAction SilentlyContinue
    $zip = [System.IO.Compression.ZipFile]::OpenRead($Path)
    try {
      $entries = $zip.Entries | Select-Object -ExpandProperty FullName
      $sample = ($entries | Select-Object -First 4) -join ', '
      if (-not $sample) {
        $sample = 'empty archive'
      }
      return @{ Count = $entries.Count; Detail = ($sample -replace '\|', '/') }
    } finally {
      $zip.Dispose()
    }
  } catch {
    return @{ Count = 0; Detail = 'archive open failed' }
  }
}

function Get-DocxSummary {
  param([string]$Path)

  try {
    Add-Type -AssemblyName System.IO.Compression.FileSystem -ErrorAction SilentlyContinue
    $zip = [System.IO.Compression.ZipFile]::OpenRead($Path)
    try {
      $entry = $zip.GetEntry('word/document.xml')
      if ($null -eq $entry) {
        return @{ Count = $zip.Entries.Count; Detail = 'docx without word/document.xml' }
      }

      $reader = New-Object IO.StreamReader($entry.Open())
      try {
        $xml = $reader.ReadToEnd()
      } finally {
        $reader.Dispose()
      }

      $text = ($xml -replace '<[^>]+>', ' ' -replace '\s+', ' ').Trim()
      $snippet = if ($text.Length -gt 120) { $text.Substring(0, 120) } else { $text }
      if (-not $snippet) {
        $snippet = 'docx text empty'
      }
      return @{ Count = $zip.Entries.Count; Detail = ($snippet -replace '\|', '/') }
    } finally {
      $zip.Dispose()
    }
  } catch {
    return @{ Count = 0; Detail = 'docx extraction failed' }
  }
}

function Get-Role {
  param(
    [string]$RelativePath,
    [string]$Extension
  )

  if ($RelativePath -like 'Plan/*') { return 'Top-priority Athena planning source.' }
  if ($RelativePath -like 'Nexus V/docs/ai-system/*') { return 'Archived legacy AI-system mirror.' }
  if ($RelativePath -like 'Nexus V/*') { return 'Nexus V subsystem source, docs, or generated artifact.' }
  if ($RelativePath -like 'tools/*') { return 'Automation/tooling script or tool documentation.' }
  if ($RelativePath -like 'manifests/*') { return 'Machine-readable system manifest or registry export.' }
  if ($RelativePath -like 'schemas/*') { return 'Validation schema.' }
  if ($RelativePath -like 'templates/*') { return 'Reusable Athena workflow template.' }
  if ($RelativePath -like 'engine/*') { return 'Athena operation-cycle report or engine history.' }
  if ($RelativePath -like 'memory/*') { return 'Athena memory and recall guidance.' }
  if ($RelativePath -like 'work/*') { return 'Working packet, intake, or execution note.' }
  if ($RelativePath -like 'council/*') { return 'Council reasoning and decision artifact.' }
  if ($RelativePath -like 'diagnostics/*') { return 'Diagnostic report or issue queue.' }
  if ($RelativePath -like 'forensics/*') { return 'Evidence register or verification output.' }
  if ($RelativePath -like 'observability/*') { return 'Log intelligence or observability output.' }
  if ($RelativePath -like 'sensory/*') { return 'Scan, baseline, or watched-state output.' }
  if ($RelativePath -like 'identity/*') { return 'Project identity and mission context.' }
  if ($RelativePath -like 'navigation/*') { return 'Project map/navigation context.' }
  if ($RelativePath -like 'projects/*') { return 'Project registry or legacy project brain.' }
  if ($Extension -eq '.docx') { return 'Word document source or planning/reference artifact.' }
  if ($Extension -eq '.zip') { return 'Archive/package artifact.' }
  if ($Extension -in $imageExtensions) { return 'Image or visual asset.' }
  return 'Project file.'
}

$files = Get-ChildItem -LiteralPath $ProjectRoot -Recurse -File -Force |
  Where-Object { -not (Test-GitPath -Path $_.FullName) -and $_.FullName -ne $OutputPath } |
  Sort-Object FullName

$rows = foreach ($file in $files) {
  $relative = Get-RelativePath -Base $ProjectRoot -Path $file.FullName
  $extension = $file.Extension.ToLowerInvariant()
  $kind = 'binary/opaque'
  $metric = 0
  $detail = ''

  if ($extension -eq '.docx') {
    $summary = Get-DocxSummary -Path $file.FullName
    $kind = 'docx/extracted'
    $metric = $summary.Count
    $detail = $summary.Detail
  } elseif ($extension -eq '.zip') {
    $summary = Get-ZipSummary -Path $file.FullName
    $kind = 'zip/opened'
    $metric = $summary.Count
    $detail = $summary.Detail
  } elseif ($extension -in $imageExtensions) {
    $kind = 'image/metadata'
    $detail = "$($file.Extension.TrimStart('.').ToUpperInvariant()) image asset"
  } elseif ($extension -in $textExtensions -or $file.Name -eq '.gitignore') {
    $summary = Get-TextSummary -Path $file.FullName
    $kind = 'text/read'
    $metric = $summary.Lines
    $detail = $summary.Detail
  } else {
    $detail = 'opaque or toolchain binary artifact'
  }

  if ($detail.Length -gt 140) {
    $detail = $detail.Substring(0, 140)
  }

  [pscustomobject]@{
    Path = $relative
    KB = [math]::Round($file.Length / 1KB, 1)
    Kind = $kind
    Metric = $metric
    Sha12 = Get-Sha12 -Path $file.FullName
    Role = Get-Role -RelativePath $relative -Extension $extension
    Detail = ($detail -replace '\|', '/' -replace "`r|`n", ' ')
    Top = (($relative -split '/')[0])
  }
}

$kindGroups = $rows | Group-Object Kind | Sort-Object Name
$topGroups = $rows | Group-Object Top | Sort-Object @{Expression = 'Count'; Descending = $true}, Name
$totalBytes = ($files | Measure-Object Length -Sum).Sum

$builder = [System.Text.StringBuilder]::new()
[void]$builder.AppendLine('# Project Athena Complete File Index')
[void]$builder.AppendLine('')
[void]$builder.AppendLine('Generated: 2026-07-10')
[void]$builder.AppendLine('')
[void]$builder.AppendLine("This generated index accounts for every file under ``$ProjectRoot`` that existed at scan time, except ``.git`` internals and this generated index file itself. Text-like files were opened directly, Word documents were opened as OOXML and text-indexed, zip archives were opened and entry-indexed, images/binaries were metadata-indexed, and each file received a role hint.")
[void]$builder.AppendLine('')
[void]$builder.AppendLine('## Coverage Summary')
[void]$builder.AppendLine('')
[void]$builder.AppendLine("- Files indexed: $($rows.Count)")
[void]$builder.AppendLine("- Total size: $([math]::Round($totalBytes / 1MB, 3)) MB")
[void]$builder.AppendLine('')
[void]$builder.AppendLine('### By Extraction Kind')
[void]$builder.AppendLine('')
[void]$builder.AppendLine('| Kind | Count |')
[void]$builder.AppendLine('|---|---:|')
foreach ($group in $kindGroups) {
  [void]$builder.AppendLine("| $($group.Name) | $($group.Count) |")
}

[void]$builder.AppendLine('')
[void]$builder.AppendLine('### By Top-Level Folder')
[void]$builder.AppendLine('')
[void]$builder.AppendLine('| Top-Level | Count |')
[void]$builder.AppendLine('|---|---:|')
foreach ($group in $topGroups) {
  [void]$builder.AppendLine("| $($group.Name) | $($group.Count) |")
}

[void]$builder.AppendLine('')
[void]$builder.AppendLine('## Complete File Index')
[void]$builder.AppendLine('')
[void]$builder.AppendLine('| Path | KB | Kind | Lines/Entries | SHA12 | Role | Detail |')
[void]$builder.AppendLine('|---|---:|---|---:|---|---|---|')
foreach ($row in $rows) {
  [void]$builder.AppendLine("| $($row.Path) | $($row.KB) | $($row.Kind) | $($row.Metric) | $($row.Sha12) | $($row.Role) | $($row.Detail) |")
}

Set-Content -LiteralPath $OutputPath -Value $builder.ToString() -Encoding UTF8

[pscustomobject]@{
  output_path = $OutputPath
  files_indexed = $rows.Count
  total_mb = [math]::Round($totalBytes / 1MB, 3)
}
