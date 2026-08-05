# Canva Design Register — 2026-08-05

## Purpose

This register records Canva visual artifacts created for Project Athena during the Athena docking-fabric / hot-swap architecture pass. GitHub remains the canonical source of truth; Canva is a visual-design mirror used for editable infographic boards and presentation-ready graphics.

## Canonicality rule

```text
GitHub = canonical architecture, controlled text, diagrams, specs, audit trail.
Canva = editable visual mirror / infographic surface.
Generated Canva candidates = visual drafts until reviewed and reconciled against GitHub-controlled wording.
```

## Added Canva artifact

| Field | Value |
|---|---|
| Artifact name | Infographic - PROJECT ATHENA |
| Canva design ID | `DAHRZEt127U` |
| Design type | Infographic |
| Source concept | Athena Distributed Cognitive Interface Fabric / Hot-Swappable OASIS Docking Architecture |
| Selected candidate | Candidate 3 from Canva generation job `f22833d6-5cdd-4ea1-a9bf-fb14ff425500` |
| Edit URL | https://www.canva.com/d/9NoDKz4zIsZMsBE |
| View URL | https://www.canva.com/d/J3TD0HpL0l3FJLy |
| Status | Created in Canva; requires text reconciliation and export before being treated as production-facing documentation |
| Repo-canonical companion files | `ATHENA_DOCKING_FABRIC_HOTSWAP_SPEC.md`, `ATHENA_DOCKING_FABRIC_INFOGRAPHIC.mmd`, `graphics/ATHENA_SYSTEM_OF_SYSTEMS_MAP.svg` |

## Required review before production use

1. Compare all Canva text against the GitHub canonical spec.
2. Correct any AI-generated spelling, layout, icon, or hierarchy errors inside Canva.
3. Export final static versions as SVG/PDF/PNG when available.
4. Add exported files to the repo under `docs/athena-master-expansion/graphics/` or `docs/athena-master-expansion/exports/`.
5. Keep the Canva editable link in this register and the plugin sync log.

## Intended content structure

The Canva design should communicate the following stack:

```text
AI ↔ AI-Local Athena Node ↔ Athena Connective Highway ↔ External Athena Core ↔ Project Athena Capsule ↔ Database / Memory / Repo Substrate ↔ Nexus-V / Aegis Versioned State Layer ↔ Lightcore / OASIS Runtime
```

## Required labels

```text
project-athena
athena-master-expansion
athena-docking-fabric
athena-highway
ai-local-athena-node
external-athena-core
project-capsule
hot-swap
cloneable-architecture
oasis
nexus-v
aegis
lightcore
lode-tv
roomsense
bodyrig
repo-canonical
plugin-mirror
canva-infographic
needs-text-reconciliation
```

## Notes

This Canva artifact is a visual mirror of the Athena docking architecture, not the canonical architecture definition. Any disagreement between the Canva board and the markdown/YAML/Mermaid/SVG files in the repository should be resolved in favor of the repository-controlled source files.
