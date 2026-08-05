# Project Athena Copilot Instructions

Read `AGENTS.md` first. It contains the repository-wide authority, privacy, and validation rules for coding agents.

Project Athena is a local-first institutional-intelligence repository plus a Nexus-V hardware/toolchain research stack. It is mostly Markdown, YAML, JSON, CSV, PowerShell, Python, and SystemVerilog. There is no single app entry point, package-manager root, or normal web build.

Use these source-of-truth rules:

- Root docs are current operational state.
- `Plan/` is design authority and backlog.
- `Nexus V/` is the source-heavy hardware/toolchain subsystem.
- `Nexus V/docs/**` is mirror/archive material unless a task explicitly targets it.
- Do not collapse ATHENA, JARVIS, JANUS, and OASIS into one entity.
- Do not publish or expose raw private chats, credentials, account exports, local runtime state, or unrelated host details.

Important paths:

- `AI-PORTAL.md`, `README.md`, `START-HERE.md`, `context.md`: orientation and operating identity.
- `governance/`: non-negotiable rules, cloud publication policy, and review gates.
- `agents/`: Athena's internal agent registry and lifecycle model.
- `.github/agents/`: GitHub Copilot custom agent profiles for the repository Agents tab.
- `.github/instructions/`: path-specific Copilot cloud agent and code review instructions.
- `tools/`: PowerShell validation, scan, import, export, audit, and handoff scripts.
- `Nexus V/rtl`, `Nexus V/scripts`, `Nexus V/toolchain`, `Nexus V/tb`: Nexus-V implementation and verification sources.
- `work/`, `diagnostics/`, `forensics/`, `continuity/`: task state, issue/risk evidence, and handoff records.

Preferred validation sequence:

```powershell
python -m pip install --upgrade pip -r requirements-ci.txt
python tools/validate_repository.py
python -m compileall -q tools "Nexus V/scripts" "Nexus V/toolchain"
powershell -NoProfile -ExecutionPolicy Bypass -File .\tools\Test-AthenaRepository.ps1 -NoWrite
```

On GitHub-hosted Linux runners, use `pwsh` instead of `powershell`.

The Python validator checks required paths, JSON, JSON Schema, YAML, forensic CSV headers, selected path references, and the manifest publication policy. The PowerShell repository test checks required Athena files, JSON/JSONL parseability, PowerShell parsing, asset manifest integrity, Athena integrity, `git diff --check`, and common credential patterns.

Known limits:

- Nexus-V has static checks and scaffolded regression assets, but real SystemVerilog simulation is not proven unless a simulator/linter is installed and run successfully.
- Generated reports and indexes can be stale. Refresh them only when the task asks for report generation or the change requires it.
- Use `-NoWrite` when inspecting or validating unless the task explicitly needs generated report updates.

When opening a pull request, summarize the exact files touched, the validation commands run, and any checks skipped or unavailable.
