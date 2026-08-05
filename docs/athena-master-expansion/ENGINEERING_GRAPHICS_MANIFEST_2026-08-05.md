# Engineering Graphics Manifest — 2026-08-05

## Purpose

This manifest converts the user's request for engineering concepts, infographics, graphics, and documentation across the Project Athena board into a controlled graphics production register.

The rule is simple:

```text
Generated images may be used as inspiration or reference plates.
Engineering-facing graphics must use controlled vector text, measured callouts, explicit labels, and repo-tracked source files.
```

## Graphics created in this fix pass

| Graphic | Path | Role | Status |
|---|---|---|---|
| Athena system-of-systems map | `docs/athena-master-expansion/graphics/ATHENA_SYSTEM_OF_SYSTEMS_MAP.svg` | Top-level feed map from human intent to telemetry/memory writeback. | Added |
| L.O.D.E + Lightcore pipeline | `docs/athena-master-expansion/graphics/LODE_LIGHTCORE_PIPELINE.svg` | Shows Lightcore-native render-state flow into L.O.D.E optical compositor and reverse telemetry. | Added |
| RoomSense / BodyRig / Sentinel loop | `docs/athena-master-expansion/graphics/ROOMSENSE_BODYRIG_SENTINEL_LOOP.svg` | Shows L.O.D.E, LiDAR/camera/RF towers, headset sensors, BodyRig skeleton output, Sentinel privacy/security, and Athena/Aegis audit. | Added |
| JANUS Canva multi-page visual-report candidates | `CANVA_JANUS_VISUAL_REPORT_CANDIDATES_2026-08-05.md` and `graphics/canva-janus-report-candidates-2026-08-05.json` | Four editable Canva visual-report candidates covering JANUS, ATHENA, JARVIS, OASIS, Nexus-V/Aegis and connected systems. | Generated; permanent design selection and validation pending |

## Required graphics still to produce or promote

| Graphic | Required source | Notes |
|---|---|---|
| L.O.D.E measured assembly sheet | `LODE_TV_ENGINEERING_COMPLETION_MAP.md` | A3/A2 vector/PDF blueprint with dimensions and readable tables. |
| L.O.D.E optical engine module sheet | `LODE_TV_ENGINEERING_COMPLETION_MAP.md` | Photonic input, demux, T-junction/X-prism, K-filter, adaptive lens, UST path. |
| Lightcore physical execution stack | `LIGHTCORE_PHYSICAL_EXECUTION_PROFILE.md` | Layered CNT/silicon/SiN photonic compute and memory hierarchy. |
| Nexus-V/Aegis commit path | `NEXUSV_ATHENA_BRIDGE_SPEC.md` | Task -> branch -> commit gate -> attestation -> rollback/merge. |
| OASIS simulation loop | `OASIS_ARCHITECTURE_SPEC.md` | Reality scan -> material maps -> digital twin -> simulation -> validated blueprint. |
| JANUS operative metacognitive action loop | `JANUS_OPERATIVE_METACOGNITIVE_AI_MASTER_SPEC.md` | Observe UI -> model state -> propose action -> permission gate -> execute -> verify -> commit/rollback -> Skill Capsule. |
| Known Behavioral Map material pipeline | New `KNOWN_BEHAVIORAL_MAP_SPEC.md` | Repeated tests -> material database -> property inference -> OASIS import. |
| Sensor/material fusion map | New `MULTISENSOR_MATERIAL_MAPPING_SPEC.md` | UV/IR/visible/thermal/spectrograph/terahertz/RF/radar fusion into material maps. |
| Plugin mirror dashboard | `PLUGIN_WORKSPACE_SYNC_LOG_2026-08-05.md` | Shows GitHub canonicality, Notion mirror, Asana roadmap, Drive mirror, Canva candidate state and Figma blocker. |
| Promoted JANUS Canva visual report | `CANVA_JANUS_VISUAL_REPORT_CANDIDATES_2026-08-05.md` | Select candidate, convert to permanent design, validate every page, then record design ID and canonical links. |

## Canva generation record

- Generation job: `b3b767f2-3b98-4c90-84b7-b123cd26c753`
- Candidates: four
- Page counts: 17, 16, 16 and 17
- Selection status: pending
- Canonicality: editable visual mirror only
- Candidate register: `docs/athena-master-expansion/CANVA_JANUS_VISUAL_REPORT_CANDIDATES_2026-08-05.md`
- Machine-readable manifest: `docs/athena-master-expansion/graphics/canva-janus-report-candidates-2026-08-05.json`

## Visual style standard

- Dark blueprint background or white engineering sheet, depending on context.
- No illegible generated-image text.
- Use SVG, PDF, Mermaid, Canva, FigJam or Markdown tables for visual documentation, with controlled text for production-facing outputs.
- Every graphic must include a title, date, status, canonical source and truth boundary.
- Speculative hardware must be visibly labelled `R&D concept / needs validation`.
- Use subsystem tags: `athena`, `jarvis`, `janus`, `aesir`, `nexus-v`, `aegis`, `lightcore`, `lode-tv`, `roomsense`, `bodyrig`, `sentinel`, `oasis`, `reality-to-simulation`.
- `operative-duplex` may appear only as a legacy alias or as a description of JANUS's Interior/Exterior duplex structure, never as a separate current system.

## Release policy

Graphics in `docs/athena-master-expansion/graphics/` are source-controlled documentation assets. Canva, Figma, Gamma and Drive versions are mirrors unless explicitly promoted by the user.

Canva candidates remain unpromoted until one is selected, converted to a permanent design, checked against canonical terminology and recorded with its permanent design ID and URLs.