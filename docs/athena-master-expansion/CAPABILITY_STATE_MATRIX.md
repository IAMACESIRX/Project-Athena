# Capability State Matrix

Generated: 2026-08-05

This matrix prevents overclaiming by separating what is implemented, scaffolded, specified, conceptual, speculative, and blocked.

## State labels

| Label | Meaning |
|---|---|
| Implemented | Working artifact exists and has been verified in the repo or local runtime. |
| Scaffolded | Structure, placeholder, or partial implementation exists, but not complete. |
| Specified | Documented enough to guide implementation. |
| Conceptual | Coherent concept exists, but needs formal spec or prototype plan. |
| Speculative | Future R&D / science / hardware direction; do not claim implementation. |
| Blocked | Requires missing verification, local tool output, component choice, data, or explicit approval. |

## Master capability matrix

| Capability / subsystem | State | Evidence location | Next action | Plugin / tool route |
|---|---|---|---|---|
| Athena repo as project brain | Specified | Root docs + expansion pack | Keep repo as source of truth | GitHub |
| Plan folder as design-authority vault | Specified | `Plan/context.md` + sanity check | Convert Plan intent into ontology and specs | GitHub + local tools |
| A.E.S.I.R. method | Specified | Saved-memory screenshots + derived repo doc | Use as canonical complex-investigation workflow | GitHub + Notion mirror |
| Master expansion pack | Implemented | `docs/athena-master-expansion/` | Maintain index and traceability | GitHub |
| Athena / AI-OS architecture | Specified | Expansion pack + Plan docs | Build ontology and implementation matrix | GitHub |
| Cognitive Orchestrator | Specified | Plan source docs | Create adapter/runtime bridge spec | GitHub |
| Evidence/provenance layer | Scaffolded | Research anchors + repo folders | Create schema alignment doc | GitHub + Consensus/SciSpace |
| Nexus-V architecture | Specified | Plan + Nexus V folder | Create Athena/Nexus-V bridge spec | GitHub + local build tools |
| Nexus-V implementation/toolchain | Scaffolded / Blocked | `Nexus V/` branch/folder | Run local lint/smoke/regression/Verilator where available | Local tools + GitHub |
| Aegis commit/proof layer | Specified | Nexus-V/Aegis docs and expansion mapping | Define Aegis event/proof schema for Athena tasks | GitHub |
| Lightcore | Speculative | Lightcore expansion docs | Create physical execution profile; keep R&D label | GitHub + Consensus/SciSpace |
| L.O.D.E TV | Specified | `LODE_TV_COMPLETION_SPEC.md` | Create interface spec with RoomSense/BodyRig | GitHub |
| L.O.D.E engineering blueprints | Conceptual / prototype-doc | Generated blueprint PDFs outside repo unless pushed later | Only push sanitized final artifacts if intended public | GitHub after review |
| RoomSense | Conceptual | Expansion pack | Formalize sensor/fusion/privacy spec | GitHub + SciSpace |
| RoomSense Sentinel security | Conceptual | Project-chat concepts | Formalize local-first security threat model | GitHub + Notion |
| BodyRig markerless FBT | Conceptual | Expansion pack | Define OpenXR/SteamVR/OSC/VRChat interface path | GitHub + SciSpace |
| OASIS | Conceptual | Expansion pack | Create formal architecture/environment spec | GitHub + Gamma later |
| Operative Duplex AI | Conceptual | Expansion pack | Create permissions/action/audit/UI-control spec | GitHub + Asana |
| Adapter SDK | Blocked until specified | Missing as standalone spec | Create `ADAPTER_SDK_CONTRACT.md` | GitHub |
| Plugin action routing | Implemented by this matrix + register | `PLUGIN_ACTION_REGISTER.md` | Keep updated as tools change | GitHub + Asana |
| Notion dashboard | Scaffolded | Existing Notion pages | Mirror repo docs; do not make canonical | Notion |
| Asana execution queue | Scaffolded | Existing Asana project | Add tasks for P0/P1/P2 and local verification | Asana |
| Gamma communication docs | Optional | Existing Gamma | Generate only after repo truth stabilizes | Gamma |
| Research anchors | Scaffolded | `RESEARCH_ANCHORS.md` | Add targeted research update files | Consensus + SciSpace |
| Local verification outputs | Blocked | Not run in remote pass | Run local PowerShell/forensics/project-map tools | Local machine |
| Cloud-push governance exception | Implemented | `GOVERNANCE_CLOUD_PUSH_EXCEPTION_2026-08-05.md` | Keep exceptions narrow and explicit | GitHub |

## Required promotion gates

### Conceptual → Specified

Requires:

- definition,
- subsystem boundary,
- inputs/outputs,
- dependencies,
- failure modes,
- privacy/governance implications,
- plugin route,
- validation plan.

### Specified → Scaffolded

Requires:

- repo folder/file structure,
- schema or interface draft,
- example object/dataflow,
- issue/task link,
- owner/tool route.

### Scaffolded → Implemented

Requires:

- working code/tool/doc artifact,
- local or CI verification,
- cycle report,
- privacy review if pushed,
- evidence/provenance record.

### Speculative → R&D validated

Requires:

- literature anchors,
- equations/models,
- simulation plan,
- component assumptions,
- prototype path,
- explicit caveats.

## Immediate judgement

The project should not promote Lightcore, L.O.D.E hardware, RoomSense, BodyRig, or Operative Duplex AI to implementation status until real prototype, code, simulation, or local verification outputs exist.

The next implemented layer should be the **control layer**:

```text
ontology + capability matrix + plugin register + governance exception + cycle report
```
