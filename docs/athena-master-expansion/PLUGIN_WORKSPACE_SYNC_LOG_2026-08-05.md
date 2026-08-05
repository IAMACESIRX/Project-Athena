# Plugin Workspace Sync Log — 2026-08-05

## Purpose

This document records the plugin/toolchain synchronization pass for Project Athena. It defines what each workspace is for, which labels should be used, what was updated, and what remains to be mirrored.

## Canonicality rule

```text
GitHub = canonical source of truth for this documentation consolidation.
Notion = navigable dossier mirror.
Asana = execution roadmap mirror.
Gamma = presentation / public-dossier mirror.
Google Drive = file/distribution mirror.
Canva/Figma = visual design and infographic workspaces.
Consensus/SciSpace/Wolfram = research and sanity-check sources, not canonical project state.
```

## Label taxonomy

Use these labels/tags across plugin workspaces where supported:

```text
project-athena
athena-master-expansion
aesir
ai-os
nexus-v
aegis
lightcore
lode-tv
roomsense
bodyrig
sentinel
oasis
operative-duplex
engineering-concept
speculative-hardware
research-anchor
local-first
privacy-mode
needs-validation
prototype-roadmap
repo-canonical
plugin-mirror
```

## Plugin roles

| Plugin / workspace | Role | Canonicality | Required labels |
|---|---|---|---|
| GitHub | Source of truth for docs, specs, feed maps, research anchors, issue tracking | Canonical | `repo-canonical`, subsystem labels |
| Notion | Navigable knowledge dossier and workspace-readable project map | Mirror | `plugin-mirror`, `project-athena`, subsystem labels |
| Asana | Task execution, roadmap sections, sprint/work breakdown | Mirror | `prototype-roadmap`, subsystem labels |
| Gamma | Polished architecture deck/dossier presentation | Mirror | `project-athena`, subsystem labels |
| Google Drive | File mirror for exported PDFs, docs, graphics, blueprint packs | Mirror | folder/file naming labels |
| Canva | Visual posters, presentation boards, marketing/infographic assets | Visual mirror | `infographic`, subsystem labels |
| Figma | Editable UI/UX and system diagrams, dashboard prototypes | Design mirror | `design-system`, subsystem labels |
| Consensus | Peer-reviewed research anchors | Research source | N/A |
| SciSpace | Research table and literature triage | Research source | N/A |
| Wolfram | Calculations, dimensional checks, physics/math sanity checks | Computation source | N/A |
| Supabase | Future Athena runtime database/backend | Future runtime | `runtime`, `database`, `needs-validation` |
| Vercel | Future docs/dashboard/app deployment | Future deployment | `runtime`, `dashboard`, `needs-validation` |
| Lovable/Replit | Fast prototype surfaces | Prototype mirror | `prototype`, subsystem labels |
| Amplitude | Future telemetry/product analytics | Future observability | `observability`, `telemetry` |
| Gmail/Outlook/Calendar/Contacts | Future personal operating layer integrations | Future integration | `operator-workflow` |

## Actions completed in this pass

| Surface | Action | Status |
|---|---|---|
| GitHub | Scanned repo root and confirmed Project Athena structure. | Completed |
| GitHub | Scanned `Plan/` tree and authority context. | Completed |
| GitHub | Added ChatGPT project concept sync dossier. | Completed |
| GitHub | Added L.O.D.E TV engineering completion map. | Completed |
| GitHub | Added Athena system feed/benefit matrix. | Completed |
| Consensus | Pulled agentic governance/auditability anchors. | Completed |
| Consensus | Pulled silicon nitride photonics anchor. | Completed |
| Consensus | Pulled CNT/silicon-waveguide photonics anchors. | Completed |
| Consensus | Pulled multi-sensor SLAM and LiDAR human-pose anchors. | Completed |
| SciSpace | Ran supporting search for provenance, audit logs, governance gates, and HITL multi-agent systems. | Completed |
| Wolfram | Checked 100-inch 16:9 active-area reference geometry. | Completed |

## Mirror actions still needed

| Surface | Required update | Notes |
|---|---|---|
| Notion | Create/update Project Athena master sync dossier. | Mirror repo docs and label as plugin mirror. |
| Asana | Create/update Project Athena full-system roadmap tasks. | Convert feed matrix and L.O.D.E roadmap into task sections. |
| Gamma | Create/update polished Project Athena / L.O.D.E / Lightcore dossier. | Presentation surface only. |
| Google Drive | Create folder or upload/export pack when generated files exist. | Use repo as source. |
| Canva | Create controlled infographic boards only after template/design selection. | Avoid generated-image text; use vector labels. |
| Figma | Create/edit UI or system-design file when a Figma target file exists. | Useful for Athena dashboard and L.O.D.E UX. |
| Supabase/Vercel/Lovable/Replit | Defer unless building runtime or prototype app. | Not required for documentation sync. |

## Workspace update standard

Each plugin mirror should contain:

1. Link to GitHub canonical folder: `docs/athena-master-expansion/`.
2. Short thesis of Project Athena.
3. Subsystem map.
4. Current status: design-authority consolidation, not complete implementation.
5. Labels/tags from the taxonomy above.
6. Last sync date.
7. Outstanding validation list.

## Engineering graphics policy

Generated images are allowed as inspiration/reference plates only. Production-facing graphics must use controlled text and vector layouts.

Required graphic classes:

- master architecture infographic,
- L.O.D.E optical pipeline,
- L.O.D.E measured assembly sheet,
- Lightcore physical execution stack,
- RoomSense room layout,
- BodyRig relational skeleton graph,
- Sentinel privacy/security mode diagram,
- Nexus-V/Aegis commit path,
- OASIS environment loop,
- Operative Duplex action loop.

## Sync risk notes

- Plugin mirrors can drift from the repo; mark GitHub as canonical.
- Not all plugin workspaces expose full write/update functions in every chat surface.
- Binary `.docx`, `.zip`, image, and generated-design files may require separate extraction or export before deep semantic auditing.
- Speculative hardware must remain marked as R&D concept until validated by simulation, bench tests, or manufacturable component selection.
