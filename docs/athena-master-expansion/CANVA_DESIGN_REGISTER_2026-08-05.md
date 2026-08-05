# Canva Design Register — 2026-08-05

## Purpose

This register records Canva visual artifacts created for Project Athena during the Athena docking-fabric / hot-swap architecture pass. GitHub remains the canonical source of truth; Canva is a visual-design mirror used for editable infographic boards and presentation-ready graphics.

## Canonicality rule

```text
GitHub = canonical architecture, controlled text, diagrams, specs, audit trail.
Canva = editable visual mirror / infographic surface.
Generated Canva candidates = visual drafts until reviewed and reconciled against GitHub-controlled wording.
```

## Canva artifacts

### 1. Docking-fabric infographic

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

### 2. Full-system visual atlas

| Field | Value |
|---|---|
| Artifact name | Project Athena — Full System Atlas |
| Canva design ID | `DAHRZXB4TNw` |
| Design type | Editable 16:9 multi-page presentation |
| Page count | 65 |
| Edit URL | https://www.canva.com/d/bGfuI3P6zhg_bha |
| View URL | https://www.canva.com/d/odSB-mjGkLbnTck |
| Source | 58 generated Athena images, integrated system canvases, section/index pages, and repository-derived visual coverage |
| Status | Imported successfully; editable Canva mirror available |
| Repo register | `CANVA_FULL_SYSTEM_ATLAS_2026-08-05.md` and `visual-atlas/README.md` |
| Source package SHA-256 | Embedded HTML `318d8d5641fa382ec9387dc664b73258e6e94d3f5672ee8f4ad645ddafce975e` |

## Required review before production use

1. Compare all Canva text against the GitHub canonical spec.
2. Correct any AI-generated spelling, layout, icon, hierarchy, truncation, or claim-status errors inside Canva.
3. Export final static versions as SVG/PDF/PNG when available.
4. Add reviewed exported files to the repo under `docs/athena-master-expansion/graphics/` or a controlled `exports/` directory.
5. Keep the Canva editable link, design ID, source commit, page number, and export checksum in this register or the atlas register.

## Intended content structure

The Canva visual system should communicate the following stack:

```text
AI ↔ AI-Local Athena Node ↔ Athena Connective Highway ↔ External Athena Core ↔ Project Athena Capsule ↔ Database / Memory / Repo Substrate ↔ Nexus-V / Aegis Versioned State Layer ↔ Lightcore / OASIS Runtime
```

The full atlas extends that stack across institutional cognition, evidence, agents, memory, continuity, project brains, governance, model routing, distributed compute, L.O.D.E TV, RoomSense, BodyRig, and visual system-of-systems navigation.

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
canva-full-system-atlas
needs-text-reconciliation
```

## Notes

Canva artifacts are visual mirrors, not canonical architecture definitions. Any disagreement between a Canva page and repository-controlled Markdown, YAML, Mermaid, SVG, schema, audit, or maturity-state files must be resolved in favor of the repository-controlled source until the visual is reviewed and re-exported.
