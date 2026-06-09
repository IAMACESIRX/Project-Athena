# Target AI Architecture

This is the reconstruction target for our own AI system. It is not a clone of any single model. It is a local AI-OS that can plug in many models, tools, agents, files, apps, memories, and project brains.

## Core Thesis

The useful AI is not just a foundation model. It is a complete operating loop:

`model + tools + memory + retrieval + project map + evaluation + rollback + human authority + long-running task state`

The model provides language, reasoning, vision, and code ability. The AI-OS provides continuity, safety, file access, structured work, evidence, and recovery.

## Capability Pillars

1. Coding and repo-level engineering.
2. Agentic execution with long-running task management.
3. Multimodal perception across screenshots, documents, diagrams, images, video, and UI state.
4. Research-grade reasoning with source tracking and contradiction checks.
5. Massive document and knowledge-base analysis.
6. Artifacts and structured output, including JSON, reports, docs, slides, sheets, code, and patches.
7. Creative writing, brainstorming, planning, and asset generation.
8. Enterprise/project search across local files, logs, chats, repos, and external sources when allowed.
9. Windows as an agent platform with active computer operation and localized annotations.
10. Memory across short-term context, long-term memory, interchat continuity, and project brains.

## Model Portfolio

The system should route work across tiers:

- local fast model: private, cheap, always available, good for simple summaries, tags, routing, extraction, and draft edits;
- local capable model: coding, multimodal, repo-level work where hardware allows;
- remote/open API model: deep research, advanced reasoning, large context, and hard coding when explicitly allowed;
- specialist models: vision, OCR, embedding, reranking, speech, image generation, code execution, and data analysis.

## Orchestration Design

- Every task gets a task object, owner, goal, risk level, context packet, tools allowed, checkpoints, and stop conditions.
- Every model call is source-labeled with model ID, mode, input class, output class, and verification status.
- Deep tasks use a council pattern: planner, implementer, verifier, skeptic, researcher, safety reviewer, and human consultant.
- Long tasks persist state after every meaningful step so another AI can resume.
- Tool outputs are compressed into durable observations instead of pasted endlessly into context.

## Memory Design

- short-term memory: current task state and immediate working context;
- session memory: chat summary, decisions, constraints, and open questions;
- project memory: files, modules, maps, evidence, bugs, features, and facts;
- semantic memory: compressed concepts, lessons, patterns, and design rules;
- episodic memory: timestamped events, commands, edits, and outcomes;
- cold memory: archived data retrievable by search but not loaded by default.

## Execution Design

- Use active computer operation only through declared tools.
- Before editing, gather local context and record intent.
- After editing, run the smallest meaningful verification.
- For background work, emit heartbeat reports, checkpoints, and resumable state.
- For risky operations, require human approval or a rollback plan.

## Reconstruction Targets From Open Models

- From Kimi: coordinated agents, artifact production, and tool-result context management.
- From GLM: long-horizon engineering loops and experiment-analyze-optimize cycles.
- From Qwen: local/open multimodal coding, Qwen Code style terminal agents, and tool parser discipline.
- From DeepSeek: efficient long context, reasoning effort modes, and fast/deep routing.
- From MiniMax: coding plus multimodal plus private deployment as one design objective, pending full M3 license verification.
- From Odysseus: self-hosted workspace design, model cookbook, memory/search services, MCP tools, documents/email/calendar/tasks, mobile access, and security posture for powerful local tools.

## Non-Negotiables

- Human authority stays above agent authority.
- Local-only constraints are respected unless explicitly changed.
- Evidence beats vibes.
- Generated work must be inspectable, reversible, and attributable.
- The system must know when it does not know.
