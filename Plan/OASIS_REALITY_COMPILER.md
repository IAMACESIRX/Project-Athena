# OASIS Reality Compiler

Updated: 2026-08-01
Status: Research architecture intent; no complete compiler or sensor fabric is implemented.

## Purpose

The OASIS Reality Compiler converts observations of a physical environment into
a versioned, evidence-carrying, simulation-ready digital environment. Its goal
is not only visual reconstruction. It aims to preserve geometry, materials,
relationships, conditions, behavior, uncertainty, provenance, and validation.

```text
physical environment
  -> registered multidomain sensing
  -> geometry and material reconstruction
  -> object and relationship graph
  -> behavioral-map matching
  -> physics and interaction models
  -> scene and code generation
  -> validation against reality
  -> versioned OASIS environment package
```

## Epistemic Rule

Every generated property is labeled as one of:

- directly measured;
- derived from calibrated measurements;
- inferred from a behavioral atlas or prior model;
- supplied by documentation or a human;
- simulated;
- unresolved.

The compiler must not convert an inference into a measurement by writing it into
a realistic model.

## Sensor Fabric

The recovered chats propose a specialist sensor stack whose raw outputs remain
available alongside fused interpretations.

Candidate modalities include:

- high-resolution RGB and conventional imaging;
- UV, visible, near-IR, short/mid/long-wave IR, and thermal branches;
- polarization, reflectance, roughness, and spectral response;
- open or imaging spectroscopy where practical;
- depth, LiDAR, structured light, stereo, and multi-view geometry;
- acoustic and ultrasonic sensing;
- electric and magnetic field sensing;
- RF, microwave, millimeter-wave, sub-THz, and THz branches;
- environmental sensors such as temperature, pressure, humidity, and chemical
  indicators;
- controlled stimulation for active material characterization.

No literal universal receiver covers all bands well. Each branch requires
appropriate optics or antennas, detectors, amplifiers, filters, calibration,
sampling, safety, and environmental controls.

## Experimental Optical Branches

The red-phosphor/full-spectrum and dicyanin-filter ideas are retained as
experimental branches only.

Required controls include:

- detector spectral-response curves;
- filter transmission curves and lot identity;
- lens and phosphor emission/absorption behavior;
- dark frames, flat fields, reference targets, and repeatability;
- contamination and fluorescence controls;
- comparison against calibrated spectrometers or certified standards;
- eye, UV, laser, chemical, and handling safety.

Custom white balance can change representation but does not expand a detector's
physical sensitivity. A filter can isolate or attenuate bands; it cannot create
information that the sensor did not capture.

## Registered Observation Volume

All modalities map to shared spatial and temporal coordinates:

```text
ObservationVolume(x, y, z, t) = {
  geometry,
  radiometry,
  spectrum,
  temperature,
  field_response,
  material_response,
  motion,
  uncertainty,
  provenance
}
```

Registration records:

- sensor identity and calibration;
- capture time and synchronization error;
- pose and coordinate frame;
- sampling resolution;
- environment and stimulation conditions;
- missing, saturated, occluded, or invalid regions;
- transformation uncertainty.

## Object And Relationship Graph

The compiler segments observations into persistent entities and relationships:

- transform, geometry, scale, and coordinate frame;
- parent, child, containment, attachment, support, and contact;
- fixed, movable, articulated, deformable, fluid, or unknown behavior;
- collision and navigation representation;
- material layers and condition;
- connections across structural, electrical, thermal, fluid, RF, and control
  systems;
- confidence, evidence, and unresolved alternatives.

The output is a scene and systems graph, not a bag of disconnected meshes.

## Representation Layers

Each object may need multiple purpose-specific representations.

### Visual

- high-detail mesh or captured radiance representation;
- textures and spectral appearance;
- material/shading network;
- levels of detail and occlusion geometry.

### Engineering

- watertight and finite-element meshes where justified;
- rigid, articulated, deformable, fluid, thermal, electrical, electromagnetic,
  chemical, and acoustic models;
- loads, constraints, tolerances, and validity ranges;
- uncertainty and calibration state.

### Interaction And Runtime

- state machines;
- joints and controls;
- causal links;
- navigation and affordances;
- generated behaviors with validation tests;
- interfaces to external applications or equipment.

OpenUSD, MaterialX, glTF, or similar formats may serve portions of the package,
but OASIS-specific schemas are required for evidence, uncertainty, behavior,
engineering state, and governance.

## Known Behavioral Map

A Known Behavioral Map describes how a material, composite, object, or system
responds across controlled variables and time.

It is not a single averaged material value. A record includes:

- specimen and preparation identity;
- geometry and constituent structure;
- test protocol and equipment calibration;
- input variables and boundary conditions;
- synchronized raw sensor observations;
- derived features and model parameters;
- temporal response and history dependence;
- repeatability and between-specimen variation;
- uncertainty and confidence;
- failure, degradation, and validity boundaries;
- provenance, reviewer, and version.

Candidate domains include structural, fatigue/fracture, impact, thermal,
chemical, electrical, magnetic, optical, RF/THz, acoustic, moisture/diffusion,
aging, corrosion, processing, and manufacturing effects.

## Material Behavioral Atlas

The atlas is the governed database of behavioral maps. It supports:

- candidate material identification;
- condition and degradation estimation;
- composite and interface models;
- uncertainty-preserving matches;
- retrieval by measured response, not only name;
- active-learning selection of the next discriminating test;
- transfer into bounded simulation models.

A large number of repeated tests does not remove bias. Sampling must cover the
intended variable space, specimens, equipment, labs, operators, failure modes,
and out-of-distribution conditions.

## Behavioral Code Generation

The compiler may generate OASIS-native behavior from observed structure,
controlled interaction, documentation, known templates, and behavioral-map
matches.

Generated behavior records:

- supporting observations;
- assumptions and unresolved internals;
- operating envelope;
- expected state transitions;
- prohibited and untested transitions;
- validation procedure;
- failure behavior and safe fallback.

The compiler cannot recover proprietary source code, hidden logic, ownership,
design intent, or unobserved failure behavior merely by scanning an exterior.

## Package Shape

```text
environment-package/
  manifest
  world-and-scene
  geometry
  materials
  systems-and-connections
  physics-models
  behavior
  navigation
  sensor-evidence
  confidence-and-unknowns
  validation
  provenance-and-audit
  version-history
```

The manifest identifies coordinate systems, unit conventions, schema versions,
reality class, evidence coverage, unresolved regions, and compatible runtimes.

## Validation Loop

Validation compares real and generated behavior under named conditions:

- camera and sensor observations;
- object transforms and dimensions;
- joint motion and timing;
- thermal, acoustic, RF, and lighting behavior;
- structural response and deformation;
- electrical or control-state transitions;
- collision and navigation behavior.

Calibration updates become new versions with recorded parameter changes. The
system must retain prior state and avoid overfitting one validation scene.

## Reality Classes

| Class | Meaning |
|---|---|
| fictional | no claim of real-world correspondence |
| conceptual | architecture or design hypothesis |
| approximate | bounded resemblance with known simplifications |
| simulated | executed by a named model under stated assumptions |
| validated | compared against measurements for a defined operating envelope |
| production-qualified | independently reviewed and accepted for a named use |

One package can contain components at different classes.

## Reverse Reality Compiler

The reverse path performs governed generative engineering:

```text
use case and success criteria
  -> explicit requirements and constraints
  -> candidate mechanisms, materials, and structures
  -> behavioral-atlas retrieval
  -> simulation and uncertainty propagation
  -> competing designs and failure analysis
  -> prototype and test plan
  -> validated blueprint candidate
```

It supports materials, composites, geometry, processes, repairability,
manufacturing, cost, energy, lifetime, safety, and environmental constraints.
Outputs remain candidates until independently validated and qualified.

## Privacy And Human Sensing

Room, RF, LiDAR, gait, gesture, and habit sensing can reveal identity and
behavior even without ordinary video. The pipeline therefore requires:

- informed scope and consent;
- local-first processing where possible;
- modality and purpose limitation;
- retention and deletion policy;
- access controls and audit;
- re-identification and inference-risk testing;
- visible disablement and emergency controls;
- separation of gaming, security, health, and research uses.

## Current Repository Mapping

| Requirement | Current Precursor | Gap |
|---|---|---|
| Evidence and truth | `truth/`, `forensics/`, `audit/` | no sensor evidence schema |
| Object and project schemas | `schemas/`, `projects/` | no OASIS object/package schema |
| Sensor state | `sensory/`, `observability/` | project-state sensors only |
| Versioning and rollback | Git, `restore/`, Nexus-V RSM intent | no environment version engine |
| Simulation runtime | Plan documents and Nexus-V scaffolds | no OASIS simulator |
| Material atlas | chat intent only | no dataset or protocol |
| Operative embodiment | `runtime/agent-platform/` and Operative Duplex Plan | no duplex runtime |

## First Build Slice

1. Define observation, calibration, object, material, relationship, uncertainty,
   and environment-package schemas.
2. Capture one tabletop scene with RGB plus depth using calibrated commodity
   hardware.
3. Preserve raw data and generate a simple object/relationship graph.
4. Assign only measured geometry and documented generic materials.
5. Export a visual scene and a separate evidence manifest.
6. Validate dimensions and transforms against manual measurements.
7. Add one controlled behavioral test, such as a hinge motion, with uncertainty.

This slice deliberately avoids universal material identification and safety-
critical simulation.

## Success Criteria

- Measurements, inferences, simulations, and unknowns remain distinguishable.
- Every generated property resolves to provenance and a validity range.
- The environment can be versioned and compared against later scans.
- Validation can reject an attractive but inaccurate reconstruction.
- The reverse compiler produces testable candidates rather than authoritative
  manufacturing instructions.
