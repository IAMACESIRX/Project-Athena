# Concept Feed And Benefit Map

Generated: 2026-08-05

This document maps how the major Project Athena concepts feed each other and what each subsystem contributes.

## 1. High-level dependency graph

```text
A.E.S.I.R.
  feeds → Athena cognitive method
  feeds → research workflow
  feeds → evidence/assumption/hypothesis discipline

OASIS
  feeds → simulation environment
  feeds → engineering/game/workspace world
  receives ← Athena orchestration
  receives ← L.O.D.E/RoomSense spatial interface

Athena / AI-OS
  feeds → project memory
  feeds → governance
  feeds → cognitive orchestration
  feeds → evidence/audit
  feeds → agent routing
  feeds → Nexus-V semantic work objects

Nexus-V
  receives ← Athena tasks/claims/evidence/state
  feeds → versioned execution, commit, rollback, Aegis proof
  feeds → Lightcore execution profile
  feeds → L.O.D.E frame/audit commit path

Lightcore
  receives ← Nexus-V execution semantics
  feeds → photonic compute, memory, interconnect, render path
  feeds → L.O.D.E photonic display endpoint
  feeds → RoomSense processing and sensor fusion

L.O.D.E TV
  receives ← Lightcore render/optical state
  feeds → visual output
  feeds → screen telemetry
  feeds → RoomSense front anchor
  feeds → interaction/control/security events

RoomSense
  receives ← L.O.D.E sensors + towers + headset + controllers
  feeds → BodyRig
  feeds → security/safety inference
  feeds → OASIS spatial interaction
  feeds → Athena evidence and context

BodyRig
  receives ← RoomSense fusion
  feeds → VRChat/VR/XR avatar skeleton
  feeds → embodied motion fidelity
  feeds → motion capture, fitness, accessibility

Operative Duplex AI
  receives ← Athena governance/context + OASIS interface + local program state
  feeds → direct PC action execution
  feeds → task automation
  feeds → software control layer
```

## 2. Subsystem benefit table

| Subsystem | Feeds into | Benefits provided |
|---|---|---|
| A.E.S.I.R. | Athena, research, council, roadmap | Structured first-principles reasoning, mechanism-level analysis, disciplined assumptions, validation paths. |
| OASIS | L.O.D.E, RoomSense, Operative Duplex, engineering simulation | Shared digital world for simulation, R&D, games, virtual spaces, workspaces, production/schematic workshops. |
| Athena / AI-OS | every layer | Long-term project memory, evidence discipline, governance, agent routing, anti-hallucination, continuity, external-brain function. |
| Cognitive Orchestrator | council, agents, task graph | Chooses the right reasoning mode, resolves disagreement, calculates confidence, preserves useful results. |
| Nexus-V | Lightcore, Aegis, execution, audit | Versioned state compute, rollback, branch/merge, proof-carrying execution, semantic dataflow, auditability. |
| Aegis | Nexus-V, Athena, L.O.D.E, RoomSense | Commit gates, attestation, proof summaries, telemetry trust, rollback protection. |
| Lightcore | L.O.D.E, RoomSense, future hardware | Photonic-native compute fabric, optical signalling, lower data-movement overhead, heterogeneous CPU/GPU/NPU fabric. |
| L.O.D.E TV | RoomSense, OASIS, games, XR, security | Photonic display endpoint, screen-as-sensor, optical UI mixing, frame telemetry, light-gun/gesture interaction. |
| RoomSense | BodyRig, Sentinel/security, XR, accessibility | Local spatial sensing, LiDAR/RF/camera fusion, room model, occlusion recovery, intent/risk inference. |
| BodyRig | VRChat, XR, mocap, fitness | Markerless full-body tracking, relational skeleton solving, human-state reconstruction, embodied motion fidelity. |
| Operative Duplex AI | local PC action, Codex/Jarvis/OASIS workflows | AI arms-and-legs layer: program control, task execution, UI scanning, local automation under Athena governance. |

## 3. Evidence and state lifecycle

```text
sensor/event/task/goal occurs
→ Athena intake
→ evidence classification
→ cognitive/council pass
→ task graph and state object
→ Nexus-V style branchable work unit
→ execution through local adapter or simulated pipeline
→ Aegis/provenance/commit report
→ memory writeback
→ handoff/roadmap update
```

For L.O.D.E/RoomSense:

```text
physical movement / controller packet / display frame
→ L.O.D.E sensor read
→ RoomSense fusion
→ BodyRig or interaction inference
→ confidence and provenance score
→ game/OASIS/action response
→ Athena audit/memory if important
```

## 4. Why each layer should exist separately

### Athena is not Nexus-V

Athena decides what should be reasoned, remembered, governed, routed, and preserved.

Nexus-V defines how work/state could be represented as versioned executable state.

### Nexus-V is not Lightcore

Nexus-V is semantic execution architecture.

Lightcore is a future physical substrate that can execute Nexus-V-like state natively.

### Lightcore is not L.O.D.E

Lightcore is the computer fabric.

L.O.D.E is the display/sensing endpoint that speaks Lightcore-native optical state.

### L.O.D.E is not RoomSense

L.O.D.E is the screen/display endpoint and front room anchor.

RoomSense is the spatial-sensing fabric that uses L.O.D.E plus towers/headset/RF/camera/LiDAR.

### RoomSense is not BodyRig

RoomSense senses the room.

BodyRig turns fused sensor data into a full-body skeleton/pose/intent model.

### OASIS is not Athena

OASIS is the outer digital world/simulation/workspace.

Athena is the institutional brain that can operate inside it.

### Operative Duplex AI is not Athena

Operative Duplex AI performs direct program control/action.

Athena governs, contextualizes, audits, and remembers it.

## 5. Combined advantage

The advantage is compounding:

```text
Athena gives continuity.
Nexus-V gives state safety.
Lightcore gives physical execution ambition.
L.O.D.E gives display/interaction embodiment.
RoomSense gives spatial perception.
BodyRig gives human motion presence.
OASIS gives world-scale simulation space.
Operative Duplex gives real software action.
```

Together, the stack becomes:

> a local-first institutional intelligence with a spatial body, a versioned execution spine, a future photonic compute substrate, and an immersive simulation/action environment.

## 6. Practical development order

1. Stabilize Athena memory/governance/intake.
2. Finish canonical ontology and module map.
3. Define adapter SDK for Codex/Jarvis/GPT/local models.
4. Convert Nexus-V concepts into state-object schemas usable now.
5. Build L.O.D.E/RoomSense as conventional hardware prototypes first.
6. Build BodyRig virtual tracker output from available sensors.
7. Add Aegis-like event provenance to frame/sensor/task data.
8. Keep Lightcore as a future execution profile until physical prototypes exist.
9. Integrate OASIS as the simulated environment receiving these capabilities.
10. Add Operative Duplex AI as a constrained local action layer after governance and audit are stable.
