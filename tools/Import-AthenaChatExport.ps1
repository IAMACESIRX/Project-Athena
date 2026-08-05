param(
    [Parameter(Mandatory = $true)]
    [string]$SourcePath,

    [string]$ProjectRoot = "",
    [string]$ProjectName = "ATHENA",
    [string]$ProjectId = "",
    [Alias("ConversationId")]
    [string[]]$ConversationIdFilter = @(),
    [string[]]$ConversationTitle = @(),
    [switch]$AllowAllConversations,
    [switch]$Force,
    [switch]$NoWrite
)

$ErrorActionPreference = "Stop"
if (-not $ProjectRoot) { $ProjectRoot = (Resolve-Path (Join-Path $PSScriptRoot "..")).Path }

function Get-StringHash {
    param([string]$Value)

    $sha = [Security.Cryptography.SHA256]::Create()
    try {
        $bytes = [Text.Encoding]::UTF8.GetBytes($Value)
        return ([BitConverter]::ToString($sha.ComputeHash($bytes))).Replace("-", "").ToLowerInvariant()
    }
    finally {
        $sha.Dispose()
    }
}

function Get-SourceDescriptor {
    param([string]$Path)

    $resolved = (Resolve-Path -LiteralPath $Path).Path
    if (Test-Path -LiteralPath $resolved -PathType Leaf) {
        return [PSCustomObject]@{
            Path = $resolved
            Hash = (Get-FileHash -Algorithm SHA256 -LiteralPath $resolved).Hash.ToLowerInvariant()
            Files = @([PSCustomObject]@{
                path = $resolved
                sha256 = (Get-FileHash -Algorithm SHA256 -LiteralPath $resolved).Hash.ToLowerInvariant()
                bytes = (Get-Item -LiteralPath $resolved).Length
            })
        }
    }

    $files = @(Get-ChildItem -LiteralPath $resolved -File -Filter "*.jsonl" | Sort-Object Name)
    if ($files.Count -eq 0) {
        throw "No JSONL files were found in $resolved"
    }

    $records = @($files | ForEach-Object {
        $hash = (Get-FileHash -Algorithm SHA256 -LiteralPath $_.FullName).Hash.ToLowerInvariant()
        [PSCustomObject]@{ path = $_.FullName; sha256 = $hash; bytes = $_.Length }
    })
    $combined = ($records | ForEach-Object { "$($_.path)|$($_.sha256)|$($_.bytes)" }) -join "`n"
    return [PSCustomObject]@{
        Path = $resolved
        Hash = Get-StringHash -Value $combined
        Files = $records
    }
}

function Convert-UnixTime {
    param($Value)

    if ($null -eq $Value) { return $null }
    try {
        $seconds = [Math]::Floor([double]$Value)
        return [DateTimeOffset]::FromUnixTimeSeconds([long]$seconds).ToString("o")
    }
    catch {
        return $null
    }
}

function Convert-ContentToText {
    param($Content)

    if ($null -eq $Content) { return "" }
    $parts = @()
    if ($Content.PSObject.Properties.Name -contains "parts") {
        foreach ($part in @($Content.parts)) {
            if ($part -is [string]) {
                $parts += $part
            }
            elseif ($null -ne $part) {
                $parts += ($part | ConvertTo-Json -Depth 20 -Compress)
            }
        }
    }
    elseif ($Content -is [string]) {
        $parts += $Content
    }
    else {
        $parts += ($Content | ConvertTo-Json -Depth 20 -Compress)
    }
    return ($parts -join "`n")
}

function Get-DefaultConversationTitles {
    param([string]$Root)

    $manifestPath = Join-Path $Root "athena_context\manifest.json"
    if (-not (Test-Path -LiteralPath $manifestPath)) { return @() }
    $manifest = Get-Content -Raw -LiteralPath $manifestPath | ConvertFrom-Json
    return @($manifest.chats | ForEach-Object { $_.title })
}

$source = Get-SourceDescriptor -Path $SourcePath
$sourceItem = Get-Item -LiteralPath $source.Path
$extension = if ($sourceItem.PSIsContainer) { "" } else { $sourceItem.Extension.ToLowerInvariant() }
$format = if ($sourceItem.PSIsContainer -or $extension -eq ".jsonl") {
    "audited-jsonl"
}
elseif ($extension -eq ".json") {
    "chatgpt-conversations-json"
}
elseif ($extension -eq ".zip") {
    "chatgpt-export-zip"
}
else {
    throw "Unsupported source format: $($source.Path)"
}

if ($format -ne "audited-jsonl" -and -not $AllowAllConversations) {
    if (-not $ProjectId -and $ConversationIdFilter.Count -eq 0 -and $ConversationTitle.Count -eq 0) {
        $ConversationTitle = @(Get-DefaultConversationTitles -Root $ProjectRoot)
    }
    if (-not $ProjectId -and $ConversationIdFilter.Count -eq 0 -and $ConversationTitle.Count -eq 0) {
        throw "Official exports require -ProjectId, -ConversationId, or -ConversationTitle unless -AllowAllConversations is explicitly set."
    }
}

$bundleId = "athena-chat-source-$($source.Hash.Substring(0, 12))"
$outputRoot = Join-Path $ProjectRoot "continuity\transcript-inbox\imports"
$bundleRoot = Join-Path $outputRoot $bundleId
if ((Test-Path -LiteralPath $bundleRoot) -and -not $Force) {
    $existing = Join-Path $bundleRoot "source-manifest.json"
    if (Test-Path -LiteralPath $existing) {
        Get-Content -Raw -LiteralPath $existing | ConvertFrom-Json
        return
    }
    throw "Import directory exists without a manifest: $bundleRoot"
}
if ((Test-Path -LiteralPath $bundleRoot) -and $Force) {
    $bundleRoot = "$bundleRoot-$((Get-Date).ToString('yyyyMMdd-HHmmss'))"
}

$normalizedPath = Join-Path $bundleRoot "normalized-messages.jsonl"
$writer = $null
if (-not $NoWrite) {
    New-Item -ItemType Directory -Force -Path $bundleRoot | Out-Null
    $writer = [IO.StreamWriter]::new($normalizedPath, $false, [Text.UTF8Encoding]::new($false))
}

$conversationIds = @{}
$messageIds = @{}
$messageCount = 0
$duplicateMessageCount = 0
$branchMetadataAvailable = $false
$currentBranchMessages = 0
$alternateBranchMessages = 0

function Write-NormalizedMessage {
    param(
        [string]$ConversationId,
        [string]$ConversationTitle,
        [string]$MessageId,
        [string]$TurnId,
        [string]$Role,
        [string]$Text,
        $CreatedAt,
        [string]$ParentId,
        [string[]]$Children,
        [bool]$IsCurrentBranch,
        [string]$SourceFile,
        [string]$SourceLocator
    )

    if (-not $MessageId) {
        $MessageId = Get-StringHash -Value "$ConversationId|$TurnId|$Role|$Text|$SourceLocator"
    }
    $dedupeKey = "$ConversationId|$MessageId"
    if ($messageIds.ContainsKey($dedupeKey)) {
        $script:duplicateMessageCount++
        return
    }
    $messageIds[$dedupeKey] = $true
    $conversationIds[$ConversationId] = $ConversationTitle
    $script:messageCount++
    if ($IsCurrentBranch) { $script:currentBranchMessages++ } else { $script:alternateBranchMessages++ }

    $record = [ordered]@{
        schema = "athena.normalized_chat_message.v1"
        bundle_id = $bundleId
        conversation_id = $ConversationId
        conversation_title = $ConversationTitle
        message_id = $MessageId
        turn_id = $TurnId
        role = $Role
        created_at = Convert-UnixTime -Value $CreatedAt
        parent_id = if ($ParentId) { $ParentId } else { $null }
        children = @($Children)
        is_current_branch = $IsCurrentBranch
        text = $Text
        text_sha256 = Get-StringHash -Value $Text
        source_file = $SourceFile
        source_locator = $SourceLocator
        promotion_state = "source-only"
    }
    if ($null -ne $writer) {
        $writer.WriteLine(($record | ConvertTo-Json -Depth 12 -Compress))
    }
}

try {
    if ($format -eq "audited-jsonl") {
        $jsonlFiles = if ($sourceItem.PSIsContainer) {
            @(Get-ChildItem -LiteralPath $source.Path -File -Filter "*.jsonl" | Sort-Object Name)
        }
        else {
            @($sourceItem)
        }

        foreach ($file in $jsonlFiles) {
            $lineNumber = 0
            foreach ($line in [IO.File]::ReadLines($file.FullName)) {
                $lineNumber++
                if (-not $line.Trim()) { continue }
                $row = $line | ConvertFrom-Json
                $conversationId = [string]$row.thread_id
                $title = [string]$row.chat_title
                $turn = $row.turn
                foreach ($item in @($turn.items)) {
                    $role = switch ($item.type) {
                        "userMessage" { "user" }
                        "agentMessage" { "assistant" }
                        default { [string]$item.type }
                    }
                    $text = if ($item.type -eq "userMessage") {
                        (@($item.content | ForEach-Object { if ($_.type -eq "text") { $_.text } else { $_ | ConvertTo-Json -Depth 12 -Compress } }) -join "`n")
                    }
                    else {
                        [string]$item.text
                    }
                    Write-NormalizedMessage -ConversationId $conversationId -ConversationTitle $title -MessageId ([string]$item.id) -TurnId ([string]$turn.id) -Role $role -Text $text -CreatedAt $turn.startedAt -ParentId "" -Children @() -IsCurrentBranch $true -SourceFile $file.FullName -SourceLocator "line:$lineNumber"
                }
            }
        }
    }
    else {
        $raw = if ($format -eq "chatgpt-export-zip") {
            Add-Type -AssemblyName System.IO.Compression.FileSystem
            $zip = [IO.Compression.ZipFile]::OpenRead($source.Path)
            try {
                $entry = $zip.Entries | Where-Object { $_.FullName -eq "conversations.json" -or $_.FullName.EndsWith("/conversations.json") } | Select-Object -First 1
                if ($null -eq $entry) { throw "conversations.json was not found in the export ZIP." }
                $reader = [IO.StreamReader]::new($entry.Open())
                try { $reader.ReadToEnd() } finally { $reader.Dispose() }
            }
            finally {
                $zip.Dispose()
            }
        }
        else {
            Get-Content -Raw -LiteralPath $source.Path
        }

        $parsedConversations = $raw | ConvertFrom-Json
        $conversations = @($parsedConversations)
        foreach ($conversation in $conversations) {
            $title = [string]$conversation.title
            $conversationId = if ($conversation.id) { [string]$conversation.id } else { [string]$conversation.conversation_id }
            $conversationProjectId = if ($conversation.PSObject.Properties.Name -contains "project_id") { [string]$conversation.project_id } else { "" }
            $selected = $AllowAllConversations -or ($ProjectId -and $conversationProjectId -eq $ProjectId) -or ($ConversationIdFilter -contains $conversationId) -or ($ConversationTitle -contains $title)
            if (-not $selected) { continue }

            $nodes = @{}
            foreach ($property in $conversation.mapping.PSObject.Properties) {
                $nodes[$property.Name] = $property.Value
            }
            $currentBranch = @{}
            $cursor = [string]$conversation.current_node
            while ($cursor -and $nodes.ContainsKey($cursor) -and -not $currentBranch.ContainsKey($cursor)) {
                $currentBranch[$cursor] = $true
                $cursor = [string]$nodes[$cursor].parent
            }
            $branchMetadataAvailable = $true

            foreach ($nodeId in @($nodes.Keys | Sort-Object)) {
                $node = $nodes[$nodeId]
                if ($null -eq $node.message) { continue }
                $message = $node.message
                $role = [string]$message.author.role
                $text = Convert-ContentToText -Content $message.content
                Write-NormalizedMessage -ConversationId $conversationId -ConversationTitle $title -MessageId ([string]$message.id) -TurnId $nodeId -Role $role -Text $text -CreatedAt $message.create_time -ParentId ([string]$node.parent) -Children @($node.children | ForEach-Object { [string]$_ }) -IsCurrentBranch ($currentBranch.ContainsKey($nodeId)) -SourceFile $source.Path -SourceLocator "conversation:$conversationId/node:$nodeId"
            }
        }
    }
}
finally {
    if ($null -ne $writer) { $writer.Dispose() }
}

$outputFiles = @()
if (-not $NoWrite -and (Test-Path -LiteralPath $normalizedPath)) {
    $normalizedItem = Get-Item -LiteralPath $normalizedPath
    $outputFiles += [PSCustomObject]@{
        path = $normalizedPath
        sha256 = (Get-FileHash -Algorithm SHA256 -LiteralPath $normalizedPath).Hash.ToLowerInvariant()
        bytes = $normalizedItem.Length
    }
}

$manifest = [ordered]@{
    schema = "athena.chat_source_bundle.v1"
    bundle_id = $bundleId
    created_at = (Get-Date).ToString("o")
    source = [ordered]@{
        kind = $format
        path = $source.Path
        sha256 = $source.Hash
        files = @($source.Files)
    }
    scope = [ordered]@{
        project_name = if ($ProjectName) { $ProjectName } else { $null }
        project_id = if ($ProjectId) { $ProjectId } else { $null }
        conversation_ids = @($ConversationIdFilter)
        conversation_titles = @($ConversationTitle)
        all_conversations_allowed = [bool]$AllowAllConversations
    }
    coverage = [ordered]@{
        conversations = $conversationIds.Count
        messages = $messageCount
        duplicate_messages_skipped = $duplicateMessageCount
        branches_preserved = $branchMetadataAvailable
        current_branch_messages = $currentBranchMessages
        alternate_branch_messages = $alternateBranchMessages
        attachments_embedded = $false
        tool_outputs_proven_complete = $false
    }
    files = $outputFiles
    promotion = [ordered]@{
        automatic_writeback = $false
        next_step = "Review normalized source locally and append bounded decisions to continuity/chat-repository-sync/promotion-ledger.jsonl."
    }
    wrote_files = -not $NoWrite
}

if (-not $NoWrite) {
    $manifest | ConvertTo-Json -Depth 20 | Set-Content -LiteralPath (Join-Path $bundleRoot "source-manifest.json") -Encoding UTF8
}

[PSCustomObject]$manifest
