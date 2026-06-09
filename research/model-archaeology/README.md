# Model Archaeology

This folder is the AI-OS lab for studying open-weight and open-source AI systems, extracting reusable design lessons, and turning those lessons into our own local AI architecture.

The rule is simple: learn from public, licensed, primary-source evidence; do not clone protected systems, do not copy closed weights, and do not treat vendor benchmark claims as truth until reproduced.

## Workflow

1. Register the model in `source-ledger.yml`.
2. Extract capabilities into `open-model-capability-matrix.yml`.
3. Run `deconstruction-protocol.md` before any design decision.
4. Convert stable lessons into `ai-system/model-ops/target-ai/target-ai-architecture.md`.
5. Convert architecture into build tasks in `ai-system/model-ops/target-ai/capability-roadmap.yml`.
6. Evaluate candidates with `ai-system/model-ops/target-ai/evaluation-benchmarks.yml`.

## Research Targets

- MiniMax M3 and MiniMax M-series for coding, agentic workflows, multimodality, and long context.
- Moonshot Kimi K2.6 for agent swarm, long-horizon coding, visual agents, and context management.
- Z.ai GLM-5.1 for long-horizon engineering and sustained autonomous execution.
- Qwen3.6-27B for dense open-weight multimodal coding and local deployment.
- Qwen3.5-397B-A17B for large MoE multimodal agent architecture.
- DeepSeek V4-Flash for efficient MoE, one-million-token context, and reasoning modes.
- Odysseus for self-hosted AI workspace patterns: model cookbook, local memory/search, MCP tools, documents, email, calendar, deep research, and security posture.

## Output Standard

Every extracted claim must include:

- source URL,
- evidence type,
- confidence level,
- capability category,
- implementation implication,
- verification status,
- license/use status.

## System Pattern Targets

Model families teach model and inference design. System repositories such as Odysseus teach product/runtime design: how to package models, tools, memory, search, files, UI, security, and local hardware into an actual usable AI workspace.
