# FEATURE ROADMAP

## Athena Core Features

| Feature | Status | Purpose | Next Step |
|---|---|---|---|
| Task intake packets | active | Turn human intent into structured work. | Run several tasks through the template and refine fields. |
| Memory layer map | active | Route writeback to the correct file layer. | Add examples from real cycles. |
| Cycle report template | active | Preserve evidence and decisions. | Use for every non-trivial run. |
| Athena cycle runner | active | Bootstrap intake/report files from a goal. | Add validation and closure workflow. |
| Integrity gate | partial | Verify required files and manifests. | Finish standalone path verification. |
| Context refresh | planned | Summarize current state for new sessions. | Build command or report. |

## Plan And Knowledge Features

| Feature | Status | Purpose | Next Step |
|---|---|---|---|
| Plan implementation matrix | active | Convert design intent into build state. | Fill rows from AI-OS v13 and Athena specs. |
| Ontology extraction | planned | Convert Odysseus Nexus into schema/work items. | Extract concept taxonomy. |
| Semantic canon | planned | Prevent term drift across Plan/root/Nexus. | Update semantic canon with Athena terms. |
| GPT project concept sync | active | Capture Athena/Nexus-V/Lightcore/L.O.D.E/RoomSense/OASIS/Operative Duplex concepts from project chats. | Keep `docs/athena-master-expansion/CHATGPT_PROJECT_SYNC_2026-08-05.md` current after major concept shifts. |
| Plugin mirror documentation | active | Keep Notion/Asana/Gamma/Drive/Canva/Figma mirrors labelled and secondary to GitHub. | Maintain `PLUGIN_WORKSPACE_SYNC_LOG_2026-08-05.md` and plugin mirror index. |

## Nexus-V Features

| Feature | Status | Purpose | Next Step |
|---|---|---|---|
| Nexus-V implementation matrix | active | Link Plan to RTL/toolchain state. | Map major RTL folders and toolchain outputs. |
| NVISC toolchain bridge | partial | Compile NVASM to NVIR/NVOBJ/RTL vectors. | Add tests and expected traces. |
| Aegis/security status | partial | Track trust/attestation hardware progress. | Link RTL modules to Plan requirements. |
| Tensor/NPU status | partial | Track AI acceleration path. | Add verification evidence. |
| Quantum-domain scaffold | partial | Track future QSIM/QHW bridge concepts. | Keep clearly labeled as scaffold. |

## Lightcore / Physical Execution Features

| Feature | Status | Purpose | Next Step |
|---|---|---|---|
| Lightcore physical execution profile | specified | Tie XYZ CNT-silicon-photonic compute concepts to Nexus-V without replacing the semantic execution contract. | Expand simulation assumptions, physical interface constraints, and risk register. |
| Dual-purpose CNT electro-photonic cell | speculative | Define CNT as electrical state element plus photonic interaction/conversion/sensing/modulation cell. | Create device-level modelling note and research anchor table. |
| CNT photovoltaic / crystal memory hierarchy | speculative | Define Lightcore memory layers from active optical state through persistent crystal RAM. | Separate power-harvesting assumptions from read/write state assumptions. |
| Multidimensional optical state signalling | specified | Preserve wavelength, PAM, phase, polarisation, OAM, focal depth, K-filter, timing, redundancy, parity, semantic metadata, and Nexus/Aegis metadata. | Convert into a formal signal schema and validation simulator. |
| Lightcore RelayNet / optical confidence field | conceptual | Capture future free-space optical relay, process telemetry, redundant reconstruction, and data-carousel concepts. | Keep as future comms R&D track with physics constraints and no FTL claims. |

## L.O.D.E / RoomSense / BodyRig Features

| Feature | Status | Purpose | Next Step |
|---|---|---|---|
| L.O.D.E TV completion spec | specified | Define Lightcore Optical Display Endpoint as display, optical compositor, telemetry node, and room anchor. | Convert completion spec into measured sheets and vector diagrams. |
| L.O.D.E engineering completion map | active | Define reference dimensions, subassemblies, drawing sheets, telemetry schema, assembly sequence, graphics pack, and EVT/DVT/PVT plan. | Create controlled SVG/PDF sheets using vector text and measured callouts. |
| Photonic-native graphics pipeline | specified | Replace final HDMI/DP pipeline with optical render-state object in final Lightcore architecture. | Define transport packet/schema and receiver requirements. |
| Bidirectional display telemetry | specified | Make emitted frames auditable through brightness, colour, distortion, K-filter, timing, weak-zone, and frame-hash telemetry. | Create `LODE-TEL-300` validation fixture plan. |
| RoomSense spatial fabric | specified | Fuse L.O.D.E sensors, LiDAR/camera/RF towers, headset sensors, controller packets, and Lightcore inference. | Build sensor coordinate-frame and calibration specification. |
| Sentinel local security mode | specified | Use RoomSense for local-first presence, motion, anomaly, tamper, and familiarity detection. | Define privacy modes, event tiers, and local-only storage rules. |
| BodyRig markerless full-body tracking | specified | Generate full-body VR/XR virtual trackers from room/headset sensor fusion without body pucks or suit. | Define OpenXR/SteamVR/OSC tracker output contract and pose-confidence metrics. |
| Human-state reconstruction | conceptual | Track body sway, weight shift, balance, inertia, posture rhythm, anticipation, and follow-through. | Create relational skeleton graph and embodied-motion test set. |

## OASIS / Operative Interface Features

| Feature | Status | Purpose | Next Step |
|---|---|---|---|
| OASIS architecture spec | planned | Define outer digital environment for simulation, engineering, games, workspaces, R&D, and schematic workshops. | Create environment object model and simulation provenance schema. |
| Material/environment scan import | conceptual | Convert sensor scans and material maps into OASIS code/material/position states. | Define dataset, confidence maps, and material-property inference limits. |
| Operative Duplex AI spec | planned | Define the future action/metacognitive PC-control layer separate from Athena and OASIS. | Create permission/action trace/rollback contract. |
| Phone-to-local-agent control | planned | Let phone app send instructions to a local/network API controlling Codex/local work while user is away. | Design secure API, authentication, and task queue before implementation. |

## Operator Features

| Feature | Status | Purpose | Next Step |
|---|---|---|---|
| Athena operator console | planned | Make external-brain use ergonomic. | Design after intake workflow stabilizes. |
| Status dashboard | planned | Show context, tasks, risks, and next actions. | Define data contract first. |
| Local-only sync policy | clarified | Local-only rule applies to the user's local repo/manual code workflow; this plugin documentation workspace can update cloud mirrors when explicitly authorized. | Keep `GOVERNANCE_CLOUD_PUSH_EXCEPTION_2026-08-05.md` scoped to documentation sync, not blanket local/private upload permission. |
