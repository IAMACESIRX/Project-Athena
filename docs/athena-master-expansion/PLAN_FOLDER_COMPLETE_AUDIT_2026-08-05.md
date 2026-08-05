# Plan Folder Complete Audit — 2026-08-05

## Purpose

This file records a complete accessible-audit pass over the Project Athena `Plan/` folder and adjacent Nexus-V Plan mirror. It distinguishes content read directly, tree/inventory verified, and binary/deep-extraction work still required.

## Audit standard

| Level | Meaning |
|---|---|
| Content-read | Markdown/text content was fetched and semantically inspected. |
| Inventory-verified | File path, file type, and presence were verified in the GitHub tree or folder listing. |
| Binary-present | File is present but needs extraction/conversion before full semantic audit. |
| Derived-update | Existing roadmap/matrix was updated from chat concepts and repo scan. |

## Root Plan folder inventory status

The root `Plan/` folder was queried through GitHub contents/tree. It contains the AI-OS staged specifications, roadmap/matrix files, hardware notes, Nexus-V/NVISC/NVASM/NVIR/NVVM documents, and binary architecture packs.

### Content-read authority files

| File | Audit level | Key authority extracted |
|---|---|---|
| `Plan/AI-OS-v7.0-Master-Specification.md` | Content-read | Persistent institutional intelligence; constitution, identity, hierarchy, reasoning council, governance, memory, knowledge graph, decision ledger, reputation/trust, audit, adaptive learning, meta-evolution, runtime, infrastructure, federation, civilization, security, disaster recovery. |
| `Plan/AI-OS-v13.0-Unified-Encyclopedia.md` | Content-read | AI-OS as simultaneous Agent / Multi-Agent System / Artificial Organization / Persistent Institution with future Federation and Civilization stages; integrates Nexus-V beneath AI-OS as execution fabric. |
| `Plan/AI-OS-v10.0-Knowledge-and-Memory-Constitution.md` | Content-read | Fact / Assumption / Hypothesis / Prediction / Opinion classification and auditable memory lifecycle. |
| `Plan/AI-OS-v11.0-Agent-Species-Catalog.md` | Content-read | Board, Executive, Governance, Instructional, Coordination, Management, Observation, Adaptive, Meta, council, capability, and specialist agents. |
| `Plan/AI-OS-v12.0-Federation-and-Civilization-Framework.md` | Content-read | Agent -> MAS -> Organization -> Institution -> Federation -> Civilization progression. |
| `Plan/FEATURE_ROADMAP.md` | Content-read / derived-update | Expanded roadmap tracks for Athena Core, Plan/Knowledge, Nexus-V, Lightcore, L.O.D.E/RoomSense/BodyRig, OASIS, Operative Interface, and operator features. |
| `Plan/IMPLEMENTATION_MATRIX.md` | Content-read / derived-update | Links Plan intent to current files, including Athena/Nexus-V bridge, Lightcore profile, L.O.D.E completion, RoomSense/BodyRig, OASIS, Operative Duplex, plugin sync, and validation anchors. |

### Inventory-verified Plan classes

| Class | Status | Notes |
|---|---|---|
| AI-OS staged specs v2-v13 | Inventory-verified; key files content-read | Root Plan contains staged AI-OS documents from organizational specification through unified encyclopedia. |
| Feature roadmap and implementation matrix | Content-read and updated | These now point at current master expansion docs. |
| Hardware plan and hardware specifics | Inventory-verified | Requires a separate hardware extraction pass for full detailed synthesis. |
| NVISC / NVASM / NVIR / NVVM / Nexus-V documents | Inventory-verified | Multiple `.docx` files are present and need extraction. |
| Nexus V mirrored `docs/Plan/` | Inventory-verified | Tree shows a second Plan copy under `Nexus V/docs/Plan/`; this should be deduplicated or canonicalized later. |
| Binary `.docx` architecture packs | Binary-present | Full semantic audit needs conversion to Markdown/text. |

## Authority alignment

The Plan folder supports these canonical claims:

1. Project Athena is not merely a chatbot; it is an external-brain / institutional-intelligence project.
2. AI-OS is designed as an artificial organization with governance, memory, audit, reputation, and project-brain continuity.
3. AI-OS intentionally evolves along the path: Agent -> Multi-Agent System -> Artificial Organization -> Persistent Institution -> Federation -> Artificial Civilization.
4. Knowledge must be classed as Fact, Assumption, Hypothesis, Prediction, or Opinion.
5. Nexus-V is the execution/hardware research layer below AI-OS, not a replacement for Athena.
6. New chat-derived tracks, including Lightcore, L.O.D.E TV, RoomSense, BodyRig, OASIS, Operative Duplex, multisensor/material mapping, and Known Behavioral Map, belong in the expansion layer unless/until promoted into core Plan authority.

## Gap list

| Gap | Risk | Fix |
|---|---|---|
| Binary `.docx` files not extracted | Major architecture details may remain hidden from Markdown search. | Convert all `.docx` to Markdown and index in `docs/athena-master-expansion/plan-extracts/`. |
| Root `Plan/` and `Nexus V/docs/Plan/` overlap | Duplicate authority can drift. | Create canonicality map and deduplication policy. |
| Hardware notes not fully synthesized | Lightcore/Nexus-V boundary may remain fuzzy. | Add `HARDWARE_PLAN_SYNTHESIS.md`. |
| L.O.D.E graphics pack not fully produced | Engineering visuals are listed but not complete. | Use controlled SVG/PDF generation, not generated text images. |
| Material Known Behavioral Map not yet formalized | Reality-to-simulation track lacks schema. | Add `KNOWN_BEHAVIORAL_MAP_SPEC.md` and sensor fusion/property inference schema. |
| Operative Duplex AI not tied to a permission/action API | Action layer could become unsafe or ambiguous. | Add action trace, capability lease, undo/rollback, and human authority gates. |

## Recommended next extraction pass

```text
1. Download/convert every Plan `.docx` into Markdown.
2. Place converted files in docs/athena-master-expansion/plan-extracts/.
3. Create PLAN_AUTHORITY_INDEX.yml with source path, extracted path, sha, status, and canonicality.
4. Update IMPLEMENTATION_MATRIX.md rows with links to each extracted source.
5. Run a second sanity pass after extraction.
```

## Current conclusion

The Plan folder has been checked at repository-tree and key-authority content level. The master expansion is aligned with the visible Markdown authority files. The remaining blocker is not access to the repo; it is deep extraction of binary documents and full conversion into searchable canonical Markdown.