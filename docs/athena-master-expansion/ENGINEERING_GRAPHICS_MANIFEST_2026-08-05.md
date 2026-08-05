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

## Required graphics still to produce

| Graphic | Required source | Notes |
|---|---|---|
| L.O.D.E measured assembly sheet | `LODE_TV_ENGINEERING_COMPLETION_MAP.md` | A3/A2 vector/PDF blueprint with dimensions and readable tables. |
| L.O.D.E optical engine module sheet | `LODE_TV_ENGINEERING_COMPLETION_MAP.md` | Photonic input, demux, T-junction/X-prism, K-filter, adaptive lens, UST path. |
| Lightcore physical execution stack | `LIGHTCORE_PHYSICAL_EXECUTION_PROFILE.md` | Layered CNT/silicon/SiN photonic compute and memory hierarchy. |
| Nexus-V/Aegis commit path | `NEXUSV_ATHENA_BRIDGE_SPEC.md` | Task -> branch -> commit gate -> attestation -> rollback/merge. |
| OASIS simulation loop | `OASIS_ARCHITECTURE_SPEC.md` | Reality scan -> material maps -> digital twin -> simulation -> validated blueprint. |
| Operative Duplex action loop | `OPERATIVE_DUPLEX_AI_SPEC.md` | Observe UI -> propose action -> permission gate -> execute -> trace -> undo/rollback. |
| Known Behavioral Map material pipeline | New `KNOWN_BEHAVIORAL_MAP_SPEC.md` | Repeated tests -> material database -> property inference -> OASIS import. |
| Sensor/material fusion map | New `MULTISENSOR_MATERIAL_MAPPING_SPEC.md` | UV/IR/visible/thermal/spectrograph/terahertz/RF/radar fusion into material maps. |
| Plugin mirror dashboard | `PLUGIN_WORKSPACE_SYNC_LOG_2026-08-05.md` | Shows GitHub canonicality, Notion mirror, Asana roadmap, Drive mirror, Gamma blocked. |

## Visual style standard

- Dark blueprint background or white engineering sheet, depending on context.
- No illegible generated-image text.
- Use SVG, PDF, Mermaid, or Markdown tables for production docs.
- Every graphic must include a title, date, status, and truth boundary.
- Speculative hardware must be visibly labelled `R&D concept / needs validation`.
- Use subsystem tags: `athena`, `aesir`, `nexus-v`, `aegis`, `lightcore`, `lode-tv`, `roomsense`, `bodyrig`, `sentinel`, `oasis`, `operative-duplex`.

## Release policy

Graphics in `docs/athena-master-expansion/graphics/` are source-controlled documentation assets. Canva, Figma, Gamma, and Drive versions are mirrors unless explicitly promoted by the user.