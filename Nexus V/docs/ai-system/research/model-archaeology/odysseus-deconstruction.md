# Odysseus Deconstruction

Source: https://github.com/pewdiepie-archdaemon/odysseus

Source: https://github.com/pewdiepie-archdaemon/odysseus/blob/main/ROADMAP.md

Odysseus is useful to study because it is not just a model. It is a self-hosted AI workspace pattern: UI, model providers, local memory, search, MCP tools, files, shell, documents, email, calendar, tasks, deep research, and hardware-aware local model serving.

## Extracted System Patterns

### Local-First Workspace

Odysseus positions itself as a self-hosted ChatGPT/Claude-like workspace that runs on user hardware with user data. The AI-OS lesson is that model power must sit inside a usable workspace with auth, settings, data folders, provider setup, backups, and local service boundaries.

### Multi-Provider Model Layer

It supports local models and APIs through runtimes/providers such as vLLM, llama.cpp, Ollama, OpenRouter, and OpenAI. The AI-OS lesson is to keep provider routing abstract and pluggable instead of hard-coding one model.

### Agent Tooling Layer

Its agent mode is built around tools such as MCP, web, files, shell, skills, and memory. The AI-OS lesson is that agent execution is a permissioned tool graph, not a free-form model output.

### Cookbook / Hardware Fit

Odysseus includes a model cookbook that scans hardware, recommends models, and scores fit for formats/backends such as GGUF, FP8, AWQ, vLLM, and llama.cpp. The AI-OS lesson is to build a hardware-aware model router and downloader instead of asking users to guess.

### Deep Research

It includes multi-step deep research that gathers, reads, and synthesizes sources into visual reports. The AI-OS lesson is to separate query planning, retrieval, reading, contradiction checking, synthesis, and report production.

### Documents, Email, Calendar, Notes, Tasks

The repo presents documents, email triage, notes/tasks, reminders, and calendar integration as first-class AI workspace surfaces. The AI-OS lesson is that "work IQ" comes from cross-app context, not just chat.

### Memory And Skills

Odysseus uses persistent memory/skills with ChromaDB and fastembed, combining vector and keyword retrieval. The AI-OS lesson is to use layered memory and retrieval instead of relying on context windows alone.

### Security Posture

The docs warn that shell access, file uploads, model downloads, web research, email/calendar integrations, and API tokens make the app an admin console. The AI-OS lesson is to gate high-risk capabilities, keep raw services internal, avoid public exposure, and make secrets/data gitignored.

### Architecture Pattern

The public README describes a FastAPI entry point, core auth/database/middleware, source modules for LLM/agent/chat/search, route modules, services for docs/memory/search/hardware fit, static frontend, and gitignored local data. The AI-OS lesson is to keep runtime, routes, services, front-end, and private data clearly separated.

## Reconstruction Decisions For Our AI-OS

- Add a hardware-aware model fit layer before local model downloads.
- Add a provider-agnostic model router that can target local, remote, multimodal, code, and research models.
- Treat every tool as permissioned by class: read, reversible edit, operational action, risky mutation.
- Store user/project data in gitignored runtime state, not in the code/manifests layer.
- Build deep research as a pipeline with citations and contradiction checks.
- Treat notes, tasks, documents, email, calendar, files, and repos as first-class work surfaces.
- Keep raw model, search, database, memory, and notification services internal-only unless explicitly exposed behind auth and a trusted private access layer.

## Do Not Copy Blindly

- Do not copy UI/code just because it exists; use it as architectural inspiration.
- Do not adopt public exposure defaults without a threat model.
- Do not let shell/file/email/calendar tools bypass AI-OS authority levels.
- Do not store secrets, tokens, uploads, logs, or personal runtime data in Git.
