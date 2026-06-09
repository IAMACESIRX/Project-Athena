# R&D Backlog

## RDB-001: Client Tracking Strategy

Research partial Git tracking for client configs without committing massive MPQ payloads.

Options:

- track only `WTF`, `Interface`, ReShade, realmlist,
- use Git LFS for selected binaries,
- keep binary payload as filesystem backup only,
- mirror full client to a separate drive.

## RDB-002: Restore Automation

Build a restore assistant that validates Docker, imports SQL, sets realm address, restarts services, and produces a report.

## RDB-003: Command Hub Execution Modules

Define safe modules for server status, log inspection, and realmlist updates before allowing any destructive command.

## RDB-004: AI Inventory Engine

Generate machine-readable inventories for:

- repos,
- SQL dump metadata,
- Docker compose services,
- game client config files,
- addon list,
- server script capabilities.

## RDB-005: Local Mirror Strategy

Mirror local bare host to a second local drive for stronger backup resilience.

## RDB-006: Open Model Archaeology Lab

Maintain primary-source source cards for open-weight and open-source model families, including MiniMax, Kimi, GLM, Qwen, DeepSeek, and self-hosted AI workspace systems such as Odysseus.

Deliverables:

- source ledger,
- license status,
- architecture traits,
- capability matrix,
- target AI design implications,
- reproducible evaluation tasks.

## RDB-007: Hardware-Aware Model Cookbook

Build a local model fit layer inspired by open model serving practices and self-hosted workspace cookbooks.

Inputs:

- CPU, RAM, VRAM, GPU vendor, disk, OS,
- model size, active parameters, modality, quantization,
- backend support for vLLM, llama.cpp, Ollama, SGLang, KTransformers, Transformers,
- context-window target,
- vision/mmproj requirements,
- download and serve reliability.

## RDB-008: Deep Research Engine

Build a pipeline for deep web research and local knowledge research:

- query planner,
- source fetcher,
- primary-source prioritizer,
- source reliability scorer,
- contradiction detector,
- citation-bound synthesis,
- project memory updater.

## RDB-009: Self-Hosted AI Workspace

Design a local workspace around the AI-OS with model settings, chat, agents, documents, notes, tasks, calendar, email, memory, search, files, repo coding, and background jobs.

Security constraints:

- raw services internal by default,
- auth required before exposure,
- shell/file/email/calendar tools treated as admin-console power,
- runtime user data stays gitignored.
