# Deconstruction Protocol

Use this protocol to pick apart an open model family and convert it into safe, useful design knowledge.

## 1. Identity And License

- Record model name, family, release date, provider, source URLs, and license.
- Separate `open-source`, `open-weight`, `source-available`, `API-only`, and `announced but not released`.
- Do not use weights, code, datasets, or benchmark data unless the license allows the intended use.

## 2. Architecture Extraction

Capture only public, documented details:

- dense vs MoE,
- total parameters and active parameters,
- attention design,
- context window,
- modality stack,
- tokenizer/chat template,
- tool-call format,
- reasoning modes,
- deployment engines,
- quantization format,
- hardware notes.

## 3. Capability Extraction

Map each model into the capability families in `open-model-capability-matrix.yml`:

- repo-level coding,
- agentic execution,
- long-context document work,
- web/deep research,
- multimodal understanding,
- structured output/artifacts,
- data analysis,
- creative work,
- enterprise search,
- local computer operation,
- memory/context management.

## 4. Behavioral Testing

If a model can be run locally or through an allowed API, test it with project-relevant tasks:

- multi-file patch with tests,
- repository map generation,
- long document summary with citations,
- image/screenshot interpretation,
- structured JSON output,
- tool-calling loop,
- task recovery after deliberate error,
- memory update and prune decision,
- Windows file/app workflow.

## 5. Safety And Truth

- Keep benchmark claims source-labeled until reproduced.
- Record failures as useful evidence.
- Preserve user authority and local-only hosting constraints.
- Do not let a model self-certify; require cross-checks from logs, tests, or another model/agent.

## 6. Reconstruction

Convert findings into our own system using a clean-room pattern:

- use public high-level ideas,
- write our own protocols and code,
- cite source inspiration,
- avoid copying proprietary prompts, hidden traces, or protected assets,
- build evaluation first, then capability.
