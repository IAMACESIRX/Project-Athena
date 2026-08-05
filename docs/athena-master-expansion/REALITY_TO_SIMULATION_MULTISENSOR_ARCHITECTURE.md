# Reality-to-Simulation Multisensor Architecture

Generated: 2026-08-05  
Status: specified R&D architecture; Rev-B mobile research-platform fabrication baseline exists, but the full stack is not yet physically integrated or certified.

## 1. Purpose

This specification makes the Project Athena sensor concept a formal subsystem. It defines a simultaneous pan-spectral, RF, terahertz, geometric, thermal, acoustic and environmental perception fabric that preserves every sensor independently while producing one confidence-weighted fused world model.

The system is not one universal camera. It is one electromagnetic and physical-perception nervous system built from multiple specialist transducers, synchronized clocks, calibrated coordinate frames, per-band specialist AIs, and a central fusion AI.

## 2. Canonical position inside Project Athena

```text
physical environment
→ Reality-to-Simulation sensor fabric
→ sensor calibration and registration
→ per-band / per-property specialist AIs
→ fusion AI + uncertainty verifier
→ material / condition / object world model
→ Nexus-V branchable state and Aegis evidence gate
→ Athena institutional memory and reasoning
→ OASIS executable physical twin
→ L.O.D.E / RoomSense display and interaction
→ engineering simulation / inverse design / operative action
```

The subsystem is named **R2S-MSP**: Reality-to-Simulation Multisensor Platform.

## 3. Sensor families

| ID | Sensor family | Primary contribution | Important boundary |
|---|---|---|---|
| R2S-IMG-RGB | Ultra-high-resolution conventional RGB | Natural colour, fine texture, text, faces, high-resolution structural anchor | Remains colour-calibrated and UV/IR blocked. |
| R2S-IMG-FS | Full-spectrum silicon camera | UV/VIS/NIR mixed response, detector/lens dependent | Does not cover thermal IR; external filters and calibration are required. |
| R2S-UV | Dedicated UV-enhanced channels | UVA/UVB reflectance and fluorescence; optional specialist UVC path | Requires UV-compatible optics and visible/IR rejection. |
| R2S-SPEC | Snapshot/integral-field imaging spectrograph | Spatial spectral cube, radiance/reflectance, absorption/emission features | Spectral and spatial resolution trade against photon budget and frame rate. |
| R2S-NV | Red-phosphor night-vision channel | Intensified low-light visible/NIR structure and motion | Phosphor output collapses original wavelengths into red luminance. |
| R2S-NIR | Dedicated NIR camera | Reflected NIR, active illumination, vegetation and material contrast | Not thermal imaging. |
| R2S-SWIR | InGaAs/extended-SWIR branch | Moisture, organics, haze, plastics and material absorption | Detector/cooling cost and resolution are limiting. |
| R2S-MWIR | MWIR thermal branch | Hot-object emission, gases and selected molecular features | Usually cooled and expensive. |
| R2S-LWIR | Radiometric LWIR branch | Ambient-temperature thermal emission and heat distribution | Emissivity/reflection must be modelled. |
| R2S-DIC-A/B | Dicyanin target and matched reference | Differential optical response of a characterised dye/glass path | Experimental differential filter channel, not universal detection. |
| R2S-POL | Polarisation-resolved camera | Glare, surface orientation, dielectric/metal response, stress and roughness cues | Needs angle and illumination context. |
| R2S-GEO | LiDAR, ToF, stereo and structured light | Depth, pose, displacement, normals, occlusion and geometry | Resolution and material response vary by range and surface. |
| R2S-EVT | Event/high-speed camera | Rapid motion, brightness transients and high dynamic range edges | Event data is not an ordinary frame. |
| R2S-RF-LF | Static/ELF/VLF/LF/HF field and receiver arrays | Current flow, field environment, lower-frequency penetration and emitters | Requires distributed apertures for useful directionality. |
| R2S-RF-UWB | UWB/VHF/UHF/microwave radar | Range, motion, through-material structure and dielectric contrast | Active transmission is regulated. |
| R2S-RF-MMW | mmWave/sub-THz phased or synthetic aperture | Finer concealed geometry, scattering and material response | Less penetration than lower RF. |
| R2S-THZ | THz imaging/TDS/tomography | Thin layers, moisture, dielectric properties, amplitude, phase and time delay | Strongly attenuated by water and atmosphere; metal is reflective. |
| R2S-ACOUST | Audio, ultrasound and vibration arrays | Internal boundaries, resonance, damping, leaks and mechanical state | Contact or coupling may be required for strong results. |
| R2S-ENV | Temperature, humidity, pressure, gas, particles, light, IMU/GNSS | Boundary conditions and sensor-confidence context | Explains, but does not replace, material measurements. |

## 4. Physical-property acquisition

The platform measures or derives real-world analogues of rendering and engineering maps:

- position, depth, displacement, surface normal, curvature, cavity and occlusion;
- base colour, spectral albedo, diffuse/specular separation, roughness, gloss, anisotropy and polarisation;
- opacity, transmission, refraction, fluorescence, phosphorescence and emission;
- temperature, emissivity, heat flow and thermal history;
- conductivity, permittivity, permeability, impedance and frequency-dependent loss;
- moisture, porosity, layer boundaries and limited subsurface structure;
- vibration, acoustic propagation, deformation and temporal change.

Every value carries an epistemic status:

```text
MEASURED = direct calibrated sensor output
DERIVED = deterministic calculation from measurements
INFERRED = model-based estimate or database match
HYPOTHESIS = plausible explanation awaiting discriminating evidence
UNKNOWN = not supported by the current sensing geometry or range
```

## 5. Specialist AI contract

Each sensor/property specialist receives raw payloads, calibration, global timing, shared geometry, environment and object history. It returns calibrated data, feature maps, bounded observations, confidence and uncertainty maps, failure flags and raw-evidence provenance.

The RGB, UV, spectroscopy, NIR, SWIR, thermal, night-vision, depth, polarisation, RF, THz, acoustic and environmental specialists remain independently queryable.

## 6. Fusion AI

The fusion AI consumes both low-level calibrated data and high-level specialist interpretations. It combines intermediate feature fusion with late decision fusion.

For sensor `i`, the local confidence field is conceptually:

```text
C_i = signal_quality × calibration_validity × registration × timing × environmental_suitability × domain_relevance
```

The fused state must not be a blind average. It must:

1. favour the sensor whose physics is strongest for the local question;
2. discount correlated evidence sharing the same path or source;
3. preserve disagreement rather than hiding it;
4. expose raw and individual views beside the combined view;
5. mark AI super-resolution/reconstruction as inferred;
6. maintain per-object and per-voxel provenance.

## 7. Unified object model

Each persistent object contains transform, geometry, appearance, ranked material candidates, condition, thermal state, electromagnetic response, mechanical/acoustic behavior, relations, confidence and provenance. Object relationships include supports, contains, connected-to, behind, occludes, heats and powers.

## 8. Red-filter and dicyanin experimental branch

The temporary R25A custom-white-balance procedure is retained only as a perceptual rendering experiment:

```text
set custom white balance through R25A red filter
→ remove R25A
→ keep the red-derived transform locked
→ capture dicyanin and matched-reference paths
→ preserve untouched RAW measurements
```

The scientific output is the calibrated differential spectrum/image between matched paths. The red-derived white balance is a display LUT and cannot be used as evidence of a new wavelength band.

## 9. Output products

- independent live views for every band;
- one adaptive fused visual field;
- registered spectral data cubes;
- 3D scene graph and material/condition map;
- RF emitter/propagation field;
- THz/RF limited subsurface volume;
- object-specific behavioral observations;
- simulation-ready OASIS package;
- uncertainty/provenance overlays for L.O.D.E and engineering consoles.

## 10. Safety and regulatory gates

- Active RF transmission is jurisdiction, frequency, power and duty-cycle controlled.
- UV and laser/structured-light sources require exposure limits, covers, interlocks and emergency stop.
- Night-vision and thermal modules may be export-controlled depending on model and jurisdiction.
- The system must not present inferred concealed content as direct measurement.
- Privacy modes support local-only capture, recording indicators, consent profiles and hard sensor kill switches.

## 11. Current evidence and status

Available project artifacts include a Rev-B fabrication baseline for a modular mobile sensor head, an A3 drawing set, GLB assembly, DXF front plate, BOM/module registers and a concept infographic. These define a prototype integration envelope, not a certified final instrument.

The complete UV-to-THz system remains an R&D program requiring selected vendor modules, calibration standards, real-time synchronization, optical/mechanical tolerance analysis, thermal/EMC design and first-article testing.
