# Project Athena Agent Instructions

Scope: the entire repository.

## Operating Posture

- Treat this repository as Project Athena's file-native institutional-intelligence and Nexus-V research substrate, not as a conventional application root.
- The human owner has final authority. Do not turn assumptions, generated material, or speculative plans into implementation claims without evidence.
- Root operational docs describe the current working control plane. `Plan/` is the design authority and backlog. `Nexus V/docs/**` contains mirrors and archives unless a task explicitly targets it.
- Keep ATHENA, JARVIS, JANUS, and OASIS separate. ATHENA is institutional intelligence. JARVIS is personal/executive intelligence. JANUS is operative metacognitive intelligence. OASIS is a persistent digital reality substrate, not an AI.
- Preserve recoverability. Avoid broad rewrites, history changes, generated-output churn, and unrelated cleanup.
- Keep private or local-only material private. Do not publish credentials, raw account exports, private chat material, local runtime state, personal data, or unrelated host details.
- Label capability state plainly: implemented, scaffolded, specified, conceptual, speculative, blocked, or validated for a named use.

## First Read

For non-trivial work, read these before editing:

1. `AI-PORTAL.md`
2. `README.md`
3. `context.md`
4. `Plan/context.md`
5. `governance/absolutes.md`
6. `governance/cloud-publication-policy.md`
7. `agents/agent-registry.yml`
8. The most specific file or folder docs for the requested area

For Nexus-V work, also read:

1. `Nexus V/docs/NEXUS-V-IMPLEMENTATION-MATRIX.md`
2. `Nexus V/reports/phase6_bringup_run_001_summary.md`
3. The relevant `Nexus V/rtl`, `Nexus V/scripts`, or `Nexus V/toolchain` files

## Change Rules

- Make the smallest change that satisfies the task and matches existing structure.
- Do not edit archival mirrors when the root source file is the actual target.
- Do not create new canonical claims from chat exports or generated media unless a promotion record or explicit human instruction authorizes it.
- When changing GitHub-facing files, keep the publication set minimal and public-safe.
- If a result was not verified by a named command or file inspection, say so.

## Validation

Use the checks that match the change:

```powershell
python -m pip install --upgrade pip -r requirements-ci.txt
python tools/validate_repository.py
python -m compileall -q tools "Nexus V/scripts" "Nexus V/toolchain"
powershell -NoProfile -ExecutionPolicy Bypass -File .\tools\Test-AthenaRepository.ps1 -NoWrite
```

Use `pwsh` instead of `powershell` on GitHub-hosted Linux runners.

Do not claim SystemVerilog simulation or lint is verified unless a real simulator/linter is installed and the exact command passes.
