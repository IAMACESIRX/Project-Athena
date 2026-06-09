# Provider Policy

The AI-OS control plane is provider-neutral.

## Default

- Local-first.
- Evidence-first.
- No cloud use for local-only projects unless the human explicitly allows it.

## Provider Selection

Use the model router to choose a provider by:

- capability,
- trust,
- cost,
- latency,
- privacy,
- tool access,
- project policy.

## Multi-Model Rule

When multiple AIs are used, each output must preserve:

- source agent,
- model class if known,
- task ID,
- evidence IDs,
- confidence,
- uncertainty notes.

