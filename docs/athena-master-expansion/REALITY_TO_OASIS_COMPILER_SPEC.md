# Reality-to-OASIS Physical Compiler Specification

Generated: 2026-08-05  
Status: specified architecture; prototype asset pipeline and schemas required.

## Objective

The Reality-to-OASIS Compiler converts a real environment into an executable physical twin containing geometry, materials, conditions, object relationships, physics, interactions, uncertainty and evidence provenance.

```text
REALITY → scan → understand → compile → OASIS
OASIS → requirements → design → simulate → blueprint → manufacture → rescan
```

## Ingestion pipeline

```text
synchronized R2S sensor capture
→ calibration and common coordinates
→ scene segmentation and persistent object IDs
→ geometric reconstruction
→ material/condition inference using the Material Behavioral Atlas
→ hidden-layer hypotheses from RF/THz/acoustic evidence
→ joint, constraint and affordance inference
→ simulation proxy generation
→ scene graph and code generation
→ validation against source environment
→ OASIS world package
```

## Object compilation

Every object receives complementary representations:

- high-resolution mesh, Gaussian-splat or radiance representation;
- watertight collision and simulation meshes;
- level-of-detail models;
- finite-element or reduced-order models where justified;
- thermal, electrical, RF, optical and acoustic material records;
- joints, hinges, sliders, cables, pipes and connection graphs;
- navigation, support, containment and occlusion relationships;
- state-machine and interaction code;
- raw-evidence and confidence links.

## Scene graph

```text
World
├── CoordinateFrames
├── Environment: illumination, atmosphere, temperature, RF and acoustic fields
├── Architecture
├── Objects
├── Systems: structural, thermal, fluid, electrical and data/RF
├── Agents / occupants
├── BehavioralMapLinks
├── SimulationModels
└── Evidence / uncertainty
```

## Material compilation

A surface is not assigned only `wood`, `metal` or `plastic`. The compiler emits ranked material candidates, layers/coatings, spectral albedo, density/stiffness/damping/friction ranges, thermal properties, conductivity/dielectric response, moisture/degradation/defects, validity domains and KBM links. Unknown properties remain distributions or explicit TBD fields.

## Behavioral code generation

The compiler may infer OASIS-native behavior from observed motion, topology, connections and approved templates for doors, drawers, switches, wheels, valves, pumps and interfaces. It cannot recover proprietary source code from appearance. Software behavior is reconstructed only from documentation, exposed interfaces, observed state transitions and approved active testing.

## Interchange

- OpenUSD for hierarchy, transforms, variants and large scenes;
- MaterialX for portable visual material networks;
- glTF/GLB for lightweight clients;
- OASIS schemas for physical behavior, KBM links, confidence and provenance;
- Nexus-V state objects for branch/commit lineage.

```text
OASIS_WORLD_PACKAGE/
├── world.usda
├── geometry/
├── materials/
├── physics/
├── behavior/
├── spectra/
├── thermal/
├── rf_thz/
├── navigation/
├── evidence/
├── calibration/
└── manifest.json
```

## Validation loop

The twin is validated against real camera views, dimensions, transforms, joint timing, thermal fields, acoustics, RF propagation, structural deformation, illumination and reflection. Discrepancies update model parameters but never overwrite source evidence.

## L.O.D.E / RoomSense role

L.O.D.E provides the display/telemetry anchor. RoomSense supplies persistent coordinates, occlusion handling and live updates. The R2S research head provides high-information scientific scans. Together they keep a location synchronized with its OASIS counterpart.

## Limits

The compiler does not claim exact internals behind arbitrary metal/water-rich barriers, exact elemental composition without analytical evidence, recovered original source code, safety-critical accuracy without validation, optical resolution from radar, or certainty where multiple models explain the same observations.
