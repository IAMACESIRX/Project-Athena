# Governance Cloud-Push Exception — 2026-08-05

Generated: 2026-08-05

## 1. Purpose

Project Athena is local-first by default. The repository governance has repeatedly been interpreted as:

```text
local-only by default
no cloud/GitHub push unless explicitly authorized by the human
```

This file records the narrow exception allowing the current documentation push into GitHub.

## 2. Exception summary

The human explicitly requested that findings from the Project Athena expansion, plugin sanity check, L.O.D.E/Lightcore/RoomSense consolidation, and A.E.S.I.R. project action review be pushed into the Project Athena repository so they are accessible in one place.

Allowed push category:

```text
sanitized documentation and project-control artifacts only
```

Not allowed by this exception:

```text
raw private chats
raw saved-memory screenshots
credentials
API keys
tokens
SQL dumps
local runtime dumps
account files
private sensor data
private filesystem scans
private host/network details
unreviewed local verification outputs
```

## 3. Files covered by this exception

This exception covers sanitized files in:

```text
docs/athena-master-expansion/
```

including:

- master expansion docs,
- L.O.D.E / RoomSense / Lightcore concept specs,
- A.E.S.I.R. project action reviews,
- ontology/control files,
- capability matrix,
- plugin action register,
- research-anchor summaries,
- and issue/task planning summaries.

It does not authorize unrestricted future uploads.

## 4. Privacy handling

The user provided screenshots of a saved-memory A.E.S.I.R. workflow. Those screenshots were used to derive the project method and action plan. The raw screenshots themselves were not pushed.

Derived project-control content is allowed because it contains:

- method names,
- workflow stages,
- project action decisions,
- plugin routing,
- and non-secret project architecture.

Raw UI captures are not pushed because they can contain private account/user-interface context.

## 5. Source-of-truth hierarchy

For this exception:

```text
GitHub repo = canonical public/project documentation store
Local machine = private runtime and verification store
Notion = planning mirror
Asana = execution queue
Gamma = communication artifact
Consensus/SciSpace = research input surfaces
```

Plugins do not become governing authority. They support the repository and local Athena process.

## 6. Required gate before any future local-output push

Before pushing any local verification output, run a privacy review for:

- secrets,
- keys,
- tokens,
- passwords,
- local absolute paths,
- account identifiers,
- IP addresses and hostnames if sensitive,
- database contents,
- private messages,
- raw sensor data,
- raw saved-memory exports,
- screenshots with private UI state,
- and generated reports containing private context.

## 7. Expiry / scope limit

This exception is valid only for the documentation-control expansion pass around 2026-08-05.

Any future push of private/local/runtime/generated artifacts requires a new explicit user instruction or a repo-local governance decision.

## 8. Final rule

```text
Push sanitized architecture and control docs.
Do not push private raw state.
Local-first remains the default.
```
