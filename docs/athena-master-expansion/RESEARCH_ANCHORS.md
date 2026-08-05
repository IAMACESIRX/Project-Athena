# Research Anchors

Generated: 2026-08-05

This document records external research anchors used as a sanity check for Project Athena, Nexus-V, Lightcore, L.O.D.E, RoomSense, and BodyRig.

The anchors do not prove the full architecture exists. They identify real research domains that support parts of the concept.

## 1. Agentic AI, governance, provenance, and auditability

### Evidence tracing and execution provenance

Paper:

- **From Agent Traces to Trust: A Survey of Evidence Tracing and Execution Provenance in LLM Agents**
- Authors: Yiqi Wang, Jiaqi Zhang, Taotao Cai, Zirui Liu, Qingqiang Sun, Zequn Sun, Zhangkai Wu, Manqing Dong, Mingkai Zhang, Xuefei Yin, Yanmin Zhu
- Year: 2026
- URL: https://consensus.app/papers/from-agent-traces-to-trust-a-survey-of-evidence-tracing-and-wang-zhang/aac67a6ecc345004adeea568093c6227/?utm_source=chatgpt

Relevance to Athena:

- supports typed execution traces,
- evidence-support relationships,
- retrieval grounding,
- tool-use provenance,
- memory lineage,
- observability,
- debugging,
- audit,
- and recovery.

Athena mapping:

```text
agent trace → cycle report
evidence trace → evidence register / claim map
memory lineage → Athena memory map
failure diagnosis → diagnostics / correction queue
runtime guardrail → governance / Aegis-style commit gate
```

### Agentic systems and governance

Paper:

- **AI Agents and Agentic Systems: A Multi-Expert Analysis**
- Authors: Laurie Hughes, Yogesh K. Dwivedi, Tegwen Malik, Mazen Shawosh, M. Albashrawi, Il Jeon, Vincent Dutot, Mandanna Appanderanda, Tom Crick, Rahul De', Mark Fenwick, Senali Madugoda Gunaratnege, Paulius Jurcys, A. Kar, N. Kshetri, Keyao Li, S. Mutasa, Spyridon Samothrakis, Michael Wade, Paul Walton
- Year: 2025
- Journal: Journal of Computer Information Systems
- URL: https://consensus.app/papers/ai-agents-and-agentic-systems-a-multiexpert-analysis-hughes-dwivedi/a94aa09c85635c31b40f2c57d9a79d71/?utm_source=chatgpt

Relevance to Athena:

- supports the idea that agentic systems need governance,
- attribution,
- shared accountability,
- compatibility with legacy systems,
- bias controls,
- and interdisciplinary ethical/scalable deployment methods.

Athena mapping:

```text
multi-agent work → organization / agents / orchestration
accountability → audit / forensics / governance
legacy compatibility → adapters / local runtime bridge
bias and safety → verification senate / anti-hallucination
```

### PROV-AGENT provenance model

Paper:

- **PROV-AGENT: Unified Provenance for Tracking AI Agent Interactions in Agentic Workflows**
- Authors: Renan Souza, Amal Gueroudji, Stephen DeWitt, Daniel Rosendo, Tirthankar Ghosal, Robert B. Ross, Prasanna Balaprakash, Rafael Ferreira da Silva
- Year: 2025
- Venue: IEEE eScience
- URL: https://consensus.app/papers/provagent-unified-provenance-for-tracking-ai-agent-souza-gueroudji/5b969fd368015c8fbac1d8d80976a981/?utm_source=chatgpt

Relevance to Athena:

- supports end-to-end provenance for agent workflows,
- relates prompts, responses, decisions, tools, workflow context, and downstream outputs,
- and aligns with MCP/data observability.

Athena mapping:

```text
prompt / response / tool / decision provenance
→ Athena evidence record
→ claim support link
→ action/audit event
→ cycle report
→ memory writeback
```

## 2. Markerless VR, RoomSense, and BodyRig

### Full-body motion reconstruction in VR

Paper:

- **A Survey of Full-Body Motion Reconstruction in Immersive Virtual Reality Applications**
- Authors: Polona Caserman, Augusto Garcia-Agundez, Stefan Goebel
- Year: 2020
- Journal: IEEE Transactions on Visualization and Computer Graphics
- URL: https://consensus.app/papers/a-survey-of-fullbody-motion-reconstruction-in-immersive-caserman-garcia-agundez/0f34cc520c1956f2840ceec0db2f4ef5/?utm_source=chatgpt

Relevance to BodyRig:

- full-body avatars enhance embodiment and immersion,
- Kinect and marker-based systems were common in the research base,
- robust multiplayer/full-body tracking remains difficult.

RoomSense implication:

```text
A single Kinect-like camera is not enough for the target system.
RoomSense needs multi-view, inside-out/outside-in tracking, sensor fusion, and confidence-aware reconstruction.
```

### Real-time multi-view markerless motion capture

Paper:

- **A Comprehensive Review of Real-Time Multi-View Multi-Person Markerless Motion Capture**
- Authors: Pierre Nagorny, Bart Kevelham, S. Chagué, C. Charbonnier
- Year: 2025
- Journal: ACM Computing Surveys
- URL: https://consensus.app/papers/a-comprehensive-review-of-realtime-multiview-multiperson-nagorny-kevelham/7259656b54cf5397a1c973ac888c8de7/?utm_source=chatgpt

Relevance to RoomSense:

- validates multi-view markerless tracking as an active research direction,
- highlights accuracy, latency, and compute efficiency as the major metrics,
- supports architectural focus on sensor viewpoint count, scalability, and tracked individuals.

RoomSense implication:

```text
more viewpoints help, but only if calibration, latency, compute, and skeleton fusion are designed properly.
```

### Multi-camera sensor fusion

Paper:

- **Hi-ROS: Open-source multi-camera sensor fusion for real-time people tracking**
- Authors: Mattia Guidolin, L. Tagliapietra, E. Menegatti, M. Reggiani
- Year: 2023
- Journal: Computer Vision and Image Understanding
- URL: https://consensus.app/papers/hiros-opensource-multicamera-sensor-fusion-for-realtime-guidolin-tagliapietra/abc09598a98e5e86b684af4fa085f544/?utm_source=chatgpt

Relevance to BodyRig:

- supports calibrated camera networks,
- skeleton tracking,
- skeleton merging,
- limb-length consistency,
- filtering/smoothing,
- and robust multi-person tracking.

RoomSense implication:

```text
RoomSense BodyRig should implement skeleton tracker + skeleton merger + skeleton optimizer + skeleton filter concepts.
```

### LiDAR-assisted human motion capture

Paper:

- **LiDAR-aid Inertial Poser: Large-scale Human Motion Capture by Sparse Inertial and LiDAR Sensors**
- Authors: Yiming Ren, Chengfeng Zhao, Yannan He, Peishan Cong, Hanming Liang, Jingyi Yu, Lan Xu, Yuexin Ma
- Year: 2022
- Journal: IEEE Transactions on Visualization and Computer Graphics
- URL: https://consensus.app/papers/lidaraid-inertial-poser-largescale-human-motion-capture-ren-zhao/7339bb5233e75c73bcdabbda0743740c/?utm_source=chatgpt

Relevance to RoomSense:

- supports LiDAR + inertial fusion for body pose and global trajectory,
- shows why point clouds are useful for coarse body shape,
- and why local dynamic sensors improve fine motion.

RoomSense implication:

```text
LiDAR towers + headset/controller IMUs + cameras/RF can form a stronger solver than any one sensor alone.
```

### Wireless / RF sensing for non-intrusive 4D human perception

SciSpace result:

- **MM-Fi: Multi-Modal Non-Intrusive 4D Human Dataset for Versatile Wireless Sensing**
- Year: 2023
- DOI: 10.48550/arXiv.2305.10345

Relevance to RoomSense:

- supports the broad idea that LiDAR, mmWave radar, Wi-Fi/wireless signals, and multimodal sensing can contribute to non-intrusive human perception.

RoomSense implication:

```text
RF/mmWave/UWB should be an occlusion-support and motion-confidence layer, not the only high-resolution body tracker.
```

## 3. Lightcore and photonic/CNT compute

Previously identified anchors from the Lightcore pass:

### CNT + silicon waveguide optoelectronics

- **Silicon-Waveguide-Integrated Carbon Nanotube Optoelectronic System on a Single Chip**
- Year: 2020
- Field relevance: CNT photodetectors and CNT logic interaction integrated with silicon waveguides.

Lightcore implication:

```text
CNT electro-photonic integration is a real research direction, but Lightcore's full compute fabric remains future R&D.
```

### 3D CNT transistor integration

- **Monolithic three-dimensional integration of aligned carbon nanotube transistors for high-performance integrated circuits**
- Year: 2023
- Field relevance: M3D CNT transistors and low-temperature integration constraints.

Lightcore implication:

```text
3D CNT electronics can be treated as an enabling research domain for Lightcore's XYZ compute concept.
```

### High-bandwidth CNT photodetectors

- **Silicon Waveguide-Integrated Carbon Nanotube Photodetector with Low Dark Current and 48 GHz Bandwidth**
- Year: 2023
- Field relevance: CNT photodetectors for optical interconnect potential.

Lightcore implication:

```text
photonic interconnects and CNT optoelectronic detection are plausible component-level anchors.
```

## 4. Research-to-architecture sanity classification

| Claim | Support level | Notes |
|---|---:|---|
| Agentic systems need governance/audit/provenance | Strong | Multiple papers support this directly. |
| Athena evidence/provenance model is conceptually aligned with research | Strong | External literature supports evidence tracing and provenance-aware agent workflows. |
| Full-body VR avatars improve embodiment | Strong | Directly supported by VR motion reconstruction review. |
| Markerless multi-view body tracking is viable research direction | Strong | Supported, but with latency/accuracy/compute constraints. |
| LiDAR can support human motion capture | Strong | Supported by LiDAR-human mocap work. |
| RF/mmWave/wireless sensing can help non-intrusive human perception | Moderate | Strong as research direction; product reliability depends heavily on hardware/data/model design. |
| RoomSense can beat Kinect-style single-sensor tracking | Plausible | Supported by multi-view and sensor fusion principles; needs prototype validation. |
| L.O.D.E as bidirectional photonic display endpoint | Speculative but architecturally coherent | Requires optical hardware prototyping and safety validation. |
| Lightcore full CNT-silicon-photonic compute fabric | Speculative R&D | Component fields exist; full architecture requires major invention and validation. |

## 5. Next research work packages

1. Create a formal BodyRig literature review.
2. Create a Lightcore component feasibility matrix.
3. Create a L.O.D.E optical path validation plan.
4. Create a RoomSense privacy/legal/regulatory review.
5. Create a Nexus-V provenance schema alignment paper.
6. Create an Athena institutional-intelligence architecture paper.
