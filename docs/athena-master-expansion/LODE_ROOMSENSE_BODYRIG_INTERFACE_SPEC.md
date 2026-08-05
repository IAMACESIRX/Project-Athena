# L.O.D.E / RoomSense / BodyRig Interface Specification

Generated: 2026-08-05

## Definitions

- **L.O.D.E TV** = Lightcore Optical Display Endpoint. It is a photonic display/interaction endpoint, not a normal HDMI/DP panel in the final architecture.
- **RoomSense** = local-first room-scale spatial sensing fabric.
- **BodyRig** = markerless full-body XR/VR body reconstruction and avatar-retargeting layer.

## Stack relation

```text
Lightcore render/optical state
→ L.O.D.E display endpoint
→ bidirectional display telemetry and screen sensing
→ RoomSense sensor fusion
→ BodyRig skeleton/human-state reconstruction
→ OASIS / VR / XR / games / accessibility / Sentinel security modes
→ Athena evidence and governance if important
```

## Sensor sources

| Source | Role |
|---|---|
| L.O.D.E screen sensors | front anchor, reflection, frame telemetry, optical input. |
| TV-edge sensors | display-side field tracking and gesture/control detection. |
| 360° LiDAR/camera/RF towers | outside-in room reconstruction. |
| Headset cameras/LiDAR/IMU | inside-out user-centred tracking. |
| Controllers | hand/controller priors and optical packets. |
| RF/mmWave/UWB | supplemental occlusion/motion/material cues. |

## Core interfaces

```yaml
DisplayFrameTelemetry:
  frame_id: string
  intended_state_hash: string
  emitted_state_hash: string
  brightness_map_ref: string
  color_shift_map_ref: string
  optical_timing: object
  sensor_return_refs: list[string]
```

```yaml
RoomSenseObservation:
  timestamp: string
  coordinate_frame: room | headset | player | display
  source: lode | lidar_tower | rf | camera | headset | controller
  observation_type: geometry | motion | reflection | occlusion | gesture | body_pose
  confidence: number
  raw_ref: string
  processed_ref: string
```

```yaml
BodyRigPose:
  timestamp: string
  skeleton_model: string
  joints: object
  virtual_trackers: object
  confidence_by_joint: object
  occlusion_state: object
  output_targets: [openxr, steamvr, osc, vrchat]
```

## Privacy model

Default mode is local-first. Non-video spatial streams are treated as pseudonymous sensing data unless identity/familiarity profiles are explicitly enabled. Identity mode requires separate consent and local profile controls.

## Development order

1. Define schemas and simulation mock data.
2. Build virtual tracker output from existing headset/controller data.
3. Add camera/depth/LiDAR mock fusion.
4. Add RoomSense confidence scoring.
5. Add L.O.D.E display telemetry model.
6. Add hardware only after safety and privacy review.

## Capability state

Current state: `Specified / Conceptual`.

The interface map is defined. Physical L.O.D.E/RoomSense/BodyRig hardware remains future R&D.
