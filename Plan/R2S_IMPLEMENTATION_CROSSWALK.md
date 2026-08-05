# R2S IMPLEMENTATION CROSSWALK

Generated: 2026-08-05

This file connects the new Reality-to-Simulation and Material Intelligence specifications to the existing Athena, Nexus-V, Lightcore, L.O.D.E, RoomSense and OASIS architecture.

## Crosswalk

| Concept | Canonical files | Current status | Evidence | Next implementation gate |
|---|---|---|---|---|
| R2S-MSP sensor fabric | `docs/athena-master-expansion/REALITY_TO_SIMULATION_MULTISENSOR_ARCHITECTURE.md` | specified | Complete modality/AI/output architecture | Select exact MVP sensors and calibration standards. |
| Specialist AI federation | R2S architecture + observation schema | specified | Input/output, confidence and provenance contract | Implement registry and first RGB/thermal/LiDAR specialists. |
| Fusion/verifier AI | R2S architecture | specified | Domain-weighted confidence and disagreement rules | Build synchronized feature/late-fusion prototype. |
| Sensor observation state | `schemas/sensor-observation.schema.json` | specified | JSON schema | Add validation tests and Nexus/Aegis IDs. |
| Known Behavioral Maps | `MATERIAL_BEHAVIORAL_ATLAS_SPEC.md`; KBM schema | specified | Campaign model and schema | Execute a bounded physical campaign. |
| Material Behavioral Atlas | Material Atlas spec | specified | Identity/condition/composite hierarchy | Create database service and certified reference-material ingestion. |
| Reality-to-OASIS compiler | `REALITY_TO_OASIS_COMPILER_SPEC.md`; physical-twin schema | specified | Object/material/package pipeline | Build OpenUSD/MaterialX/glTF proof of concept. |
| Inverse engineering | `ENGINEERING_INVERSE_DESIGN_COMPOSITE_SIMULATION_SPEC.md` | specified | Requirements→simulation→blueprint→validation loop | Build constrained design-intake prototype. |
| Composite/interface simulation | same | specified | Micro/meso/macro and interface model | Define interface Behavioral Map schema and validation coupons. |
| Lithography integration | `LITHOGRAPHY_SENSOR_PROCESS_CONTROL_INTEGRATION.md` | specified | Metrology/specialists/process-map architecture | Select tool-specific research interface. |
| L.O.D.E visualization | `LODE_R2S_SPATIAL_INTERFACE_MAP.md` | specified | Closed loop and benefit map | Prototype fused overlay and provenance telemetry. |
| RoomSense registration | L.O.D.E interface + existing RoomSense docs | specified | Role and feedback boundary | Implement coordinate-frame/timestamp schema. |
| Nexus-V branch model | existing bridge + KBM spec | partial/specification | Version/commit/rollback intent | Map observations and campaigns to concrete state objects. |
| Aegis evidence gate | existing Aegis architecture + schemas | partial/specification | Truth-state and provenance requirements | Implement commit validators and quarantine reasons. |
| Lightcore workload profile | existing Lightcore profile + R2S docs | conceptual | Workload classes identified | Keep hardware claims separate; benchmark on conventional hardware first. |
| Rev-B prototype integration | `assets/reality-to-simulation/README.md` + Drive artifact mirror | prototype baseline | PDF, GLB, DXF, BOM and module register produced | Replace integration envelopes with authoritative vendor CAD and run engineering analyses. |

## MVP sequence

1. RGB + colour calibration.
2. Full-spectrum/filtered mono branch.
3. Radiometric LWIR.
4. LiDAR/depth and common coordinate frame.
5. Polarisation.
6. Hyperspectral snapshot/line scan.
7. Matched dicyanin/reference experiment.
8. Passive RF and legal UWB/mmWave.
9. Acoustic/vibration and environmental boundary conditions.
10. Specialist-lab THz integration.
11. OASIS compiler and physical-twin runtime.
12. First Known Behavioral Map campaign.

## Hard blockers

- Exact module choices and vendor mechanical/optical files.
- Calibration targets, traceable standards and reference specimens.
- Real-time synchronization and data-rate architecture.
- Safety/regulatory cases for active RF, UV, laser and THz sources.
- Physical experiments required to validate simulation-derived properties.
- Qualified engineering review for any safety-critical blueprint or production release.
