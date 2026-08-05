# Plugin Action Register

Generated: 2026-08-05

Purpose: define what should be run through each plugin/tool surface for Project Athena, and what must remain repo-local or local-machine-only.

## Operating rule

```text
GitHub repository = canonical source of truth
Asana = execution queue
Notion = planning dashboard / mirror
Gamma = communication artifact generator
Consensus/SciSpace = research sanity-check surfaces
Local Athena tools = verification authority for local state
```

Plugins should not override the repository. They should produce tasks, mirrors, summaries, research anchors, or commits that are traceable back to repo files.

## GitHub register

| Action | Priority | Input | Output | Gate |
|---|---:|---|---|---|
| Push A.E.S.I.R. full project review | P0 | User method + expansion pack | `AESIR_FULL_PROJECT_ACTION_REVIEW_2026-08-05.md` | No raw private screenshots. |
| Push ontology | P0 | Expansion pack + concept map | `ATHENA_MASTER_ONTOLOGY.yml` | No secrets/private runtime. |
| Push capability matrix | P0 | Repo + toolchain state | `CAPABILITY_STATE_MATRIX.md` | Label uncertainty. |
| Push plugin action register | P0 | Available plugin/tool surfaces | `PLUGIN_ACTION_REGISTER.md` | Repo remains canonical. |
| Push governance exception | P0 | Explicit user cloud-push instruction | `GOVERNANCE_CLOUD_PUSH_EXCEPTION_2026-08-05.md` | Documentation-only exception. |
| Comment issue #3 | P0 | New action files | Issue comment | Confirm current queue. |
| Create bridge specs | P1 | Ontology + matrix | OASIS / Operative / Nexus-V / L.O.D.E specs | P0 complete first. |
| Push local verification outputs | P2 | Local tool outputs | Scan/manifest/map/cycle reports | Privacy review required. |

## Asana register

| Action | Priority | Target project | Output |
|---|---:|---|---|
| Add P0 tasks | P0 | Project Athena A.E.S.I.R. Push Queue | Ontology, matrix, plugin register, governance exception, cycle report tasks. |
| Add P1 architecture tasks | P1 | Same | OASIS, Operative Duplex, Nexus-V bridge, L.O.D.E/RoomSense/BodyRig, Lightcore profile, adapter SDK. |
| Add P2 local verification tasks | P2 | Same | Local command checklist and sanitized-push gate. |
| Add research plugin tasks | P1 | Same | Consensus/SciSpace queries by topic. |
| Add plugin sync review | P1 | Same | Notion/Gamma/GitHub issue sync checks. |

## Notion register

| Action | Priority | Output | Rule |
|---|---:|---|---|
| Create/update A.E.S.I.R. dashboard mirror | P0 | Notion page | Mirror only; repo canonical. |
| Add current action queue | P0 | P0/P1/P2 sections | Link back to GitHub files. |
| Maintain human-readable project view | P1 | Dashboard | Do not store secrets/private logs. |
| Convert stable specs into wiki pages | P2 | Notion docs | Only after repo docs stabilize. |

## Gamma register

| Action | Priority | Output | Rule |
|---|---:|---|---|
| Master architecture dossier | Optional | Gamma document/deck | Use after repo docs stabilize. |
| L.O.D.E / RoomSense public-facing concept deck | Optional | Presentation | Must preserve caveats. |
| ACES public-facing summary | Optional | Short deck/site | Do not include private project governance details. |
| Investor/technical overview | Later | Deck | Only if requested. |

Gamma is not a source of truth. It is a communication layer.

## Consensus register

| Research pass | Priority | Output file candidate | Notes |
|---|---:|---|---|
| Agent execution provenance / evidence tracing | P1 | `RESEARCH_ANCHORS_AGENT_PROVENANCE.md` | Supports Athena evidence/cycle/audit model. |
| Agentic governance / accountability | P1 | `RESEARCH_ANCHORS_AGENT_GOVERNANCE.md` | Supports AI-OS governance/council model. |
| Photonic computing / silicon photonics | P1 | `RESEARCH_ANCHORS_PHOTONIC_COMPUTE.md` | Supports Lightcore subdomains only. |
| CNT optoelectronics / 3D CNT integration | P1 | `RESEARCH_ANCHORS_CNT_OPTOELECTRONICS.md` | Do not claim full Lightcore implementation. |
| Full-body VR / markerless motion reconstruction | P1 | `RESEARCH_ANCHORS_BODYRIG_XR.md` | Supports BodyRig plausibility, not product readiness. |

## SciSpace register

| Research pass | Priority | Output file candidate | Notes |
|---|---:|---|---|
| Multi-view markerless pose estimation | P1 | `RESEARCH_ANCHORS_MULTIVIEW_POSE.md` | BodyRig and RoomSense. |
| LiDAR + IMU/camera sensor fusion | P1 | `RESEARCH_ANCHORS_SENSOR_FUSION.md` | RoomSense tracking. |
| RF/mmWave/UWB human sensing | P1 | `RESEARCH_ANCHORS_RF_SENSING.md` | RoomSense occlusion/intent support. |
| XR embodiment / full-body avatars | P1 | `RESEARCH_ANCHORS_XR_EMBODIMENT.md` | Embodied motion fidelity claims. |
| Local-first AI memory/provenance | P2 | `RESEARCH_ANCHORS_LOCAL_AI_MEMORY.md` | Athena memory/evidence design. |

## Local Athena tools register

These must be run on the user's machine, not remotely through plugins:

```powershell
powershell -NoProfile -ExecutionPolicy Bypass -File .\tools\Invoke-AIIntegrityCheck.ps1
powershell -NoProfile -ExecutionPolicy Bypass -File .\tools\Invoke-AIProjectScan.ps1
powershell -NoProfile -ExecutionPolicy Bypass -File .\tools\Export-ProjectMap.ps1
powershell -NoProfile -ExecutionPolicy Bypass -File .\tools\Export-AISystemManifest.ps1
powershell -NoProfile -ExecutionPolicy Bypass -File .\tools\Invoke-AIForensicVerification.ps1
powershell -NoProfile -ExecutionPolicy Bypass -File .\tools\Invoke-AIWatchedState.ps1
powershell -NoProfile -ExecutionPolicy Bypass -File .\tools\Invoke-AIOperationCycle.ps1 -SkipLiveProbe
```

Push local outputs only after a privacy pass for:

- credentials,
- tokens,
- IP addresses,
- hostnames,
- account files,
- SQL dumps,
- raw private chats,
- local runtime dumps,
- private sensor data,
- absolute local paths if sensitive.

## Routing decision table

| Work type | Use plugin/tool | Push to repo? |
|---|---|---|
| Permanent architecture spec | GitHub | Yes, if sanitized. |
| Task execution / due dates | Asana | Link/summarize only. |
| Planning dashboard | Notion | Mirror only. |
| Presentation / public deck | Gamma | Optional export/link. |
| Peer-reviewed research check | Consensus/SciSpace | Push summarized anchor file only. |
| Local verification | Local Athena tools | Push sanitized generated outputs only. |
| Private raw memory/screenshots | None | No. |
| Secrets/runtime/account state | None | No. |

## Immediate plugin run queue

1. GitHub: add P0 control files.
2. GitHub: update expansion README index.
3. GitHub: comment issue #3 with new file list and action queue.
4. Asana: add tasks for P0 files and P1 bridge specs.
5. Notion: create/update mirror page for this A.E.S.I.R. full review.
6. Consensus/SciSpace: run targeted research passes only for the open evidence gaps.
7. Local machine: run Athena verification commands before P2 outputs.

## Final rule

A plugin output is valid only if it can be traced back into:

```text
repo file → issue/task → evidence/provenance note → capability status → next action
```
