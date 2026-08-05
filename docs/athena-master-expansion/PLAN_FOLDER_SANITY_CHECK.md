# Plan Folder Sanity Check

Generated: 2026-08-05

## 1. Result

The `Plan/` folder remains the strongest architecture-authority location for Project Athena.

Current interpretation:

```text
root docs = current operating state
Plan/ = design authority and architecture intent
Nexus V/ = implementation-heavy branch for Nexus-V hardware/toolchain work
```

Do not treat `Plan/` as old notes. Treat it as the architecture backlog and canonical design-intent vault.

## 2. Inventory accounted for from `Plan/context.md`

The current Plan context reports:

- 64 files total,
- 25 Markdown files,
- 24 `.docx` Word specifications,
- 13 `.zip` source archives,
- 2 `.txt` raw notes.

Validation already recorded in the repository context:

- all `.docx` files open structurally as OOXML and contain readable text,
- all `.zip` archives open structurally,
- Markdown/text files were read directly,
- zip entries were counted and categorized by dominant source type,
- Word files were summarized from extracted text runs rather than fully rewritten.

## 3. Authority files

### Highest priority

1. `Plan/context.md`
2. `Plan/AI-OS-v13.0-Unified-Encyclopedia.md`
3. `Plan/Project-Athena-Cognitive-Orchestrator-Specification-v1.0.md`
4. `Plan/Odysseus-Nexus-Ontology-Extraction-and-Unification-Specification.md`
5. `Plan/AI-OS-v8.0-Constitution-and-Identity-Charter.md`
6. `Plan/AI-OS-v10.0-Knowledge-and-Memory-Constitution.md`
7. `Plan/AI-OS-v11.0-Agent-Species-Catalog.md`
8. `Plan/AI-OS-v12.0-Federation-and-Civilization-Framework.md`
9. `Plan/Hardware plan.md`
10. `Plan/define.txt`
11. `Plan/NVISC.txt`
12. Nexus-V Word specs in phase order.

### Key thesis from Plan/context

`Plan/` defines Athena as:

> an institutional AI operating system intended to coordinate cognition, agents, memory, governance, evidence, runtime work, and future Nexus-V semantic execution.

## 4. Plan-domain map

| Domain | Plan source | What it contributes |
|---|---|---|
| AI-OS artificial organization | AI-OS v1-v7, v13 | Institutional intelligence, artificial organization, federation/civilization pathway. |
| Constitution/identity | AI-OS v8 | Mission, values, human authority, identity, evolution rules. |
| Knowledge/memory | AI-OS v10, Athena Memory Architecture | Fact/assumption/hypothesis/prediction/opinion classes, memory layers, project brain standard. |
| Agents | AI-OS v11, agents/org/orchestration root folders | Agent species, reasoning council, capability agents, specialist agents. |
| Federation/civilization | AI-OS v12-v13 | Expansion from agent → multi-agent → organization → institution → federation → civilization. |
| Cognitive orchestration | Project Athena Cognitive Orchestrator | Senate model, task classification, scheduling, confidence, disagreement handling. |
| Ontology unification | Odysseus Nexus v14 | Canonical ontology extraction, deduplication, domain mapping, gap analysis. |
| Nexus-V hardware | Hardware plan, define.txt, Nexus-V docs | Versioned state compute, CPU completeness, Aegis, RSM, topology, tensor, quantum bridge. |
| ISA/toolchain | NVISC, NVASM, NVIR, NVVM specs | N-dimensional versioned ISA, semantic parser, lowering, object model, VM/routing. |
| Source lineage | Zip archives | Phase source snapshots and hardware/toolchain lineage. |

## 5. Sanity findings

### Finding A — Plan is broader than current implementation

The current repo implements/scaffolds major pieces of the file-native control plane, but Plan describes a much larger institutional/runtime/hardware future.

Action: Keep a clear state distinction:

```text
implemented
scaffolded
specified
conceptual
speculative
blocked
```

### Finding B — Root docs and Plan can drift

Root docs describe operating state. Plan describes intended architecture. The correct workflow is to convert Plan intent into root docs, schemas, tasks, tools, and implementation artifacts explicitly.

Action: maintain an ontology map and implementation matrix.

### Finding C — Odysseus Nexus should become the unification engine

The Plan folder already contains an ontology extraction/unification blueprint. It should be used to deduplicate Athena, AI-OS, Nexus-V, Lightcore, L.O.D.E, RoomSense, OASIS, and Operative Duplex AI concepts into one canonical graph.

Action: create an ontology extraction backlog.

### Finding D — L.O.D.E/RoomSense are currently outside the older Plan inventory

The L.O.D.E/RoomSense/BodyRig concepts are strong project-chat architecture, but not fully represented in the older Plan folder.

Action: this expansion pack adds them as an applied R&D track under the Athena/Nexus-V/Lightcore stack.

### Finding E — Lightcore should remain a future physical execution profile

Lightcore is valid as a design direction, but should not be treated as implemented hardware.

Action: keep Lightcore docs in future execution profile / R&D state until physical prototypes or formal simulations exist.

### Finding F — Governance mismatch remains explicit

The repo says local-only/no cloud push by default, while the repository now has GitHub planning artifacts. Because the user explicitly requested these docs be pushed, this documentation pack is allowed as a user-directed exception.

Action: add a cloud-push exception record for documentation-only publishing if needed.

## 6. Conversion priorities

### Priority 1 — Ontology and term dictionary

Create canonical definitions for:

- Athena,
- AI-OS,
- A.E.S.I.R.,
- OASIS,
- Local Athena Adapter,
- Operative Duplex AI,
- Nexus-V,
- NVISC,
- NVASM,
- NVIR,
- NVOBJ,
- NVVM,
- RSM,
- Aegis,
- MINREP,
- Lightcore,
- L.O.D.E,
- RoomSense,
- BodyRig,
- Sentinel,
- Human-State Reconstruction,
- Embodied Motion Fidelity.

### Priority 2 — Module dependency matrix

Convert the conceptual feed map into a machine-readable file later:

```text
source_module,target_module,feed_type,benefit,status,evidence_path
```

### Priority 3 — Capability state matrix

Each capability needs a status:

```text
implemented / scaffolded / specified / conceptual / speculative / blocked
```

### Priority 4 — Evidence/provenance schema alignment

Align Athena evidence registers, cycle reports, audit events, and task intake with provenance-aware agent workflows.

### Priority 5 — Adapter SDK

Define how Codex/Jarvis/GPT/local models/Operative Duplex act through Athena without becoming separate project brains.

### Priority 6 — L.O.D.E/RoomSense applied track

Create applied R&D work packages for:

- L.O.D.E display endpoint,
- RoomSense room sensors,
- BodyRig markerless VR tracking,
- Sentinel security mode,
- privacy/local processing,
- and VRChat/OpenXR/SteamVR bridge.

## 7. What was not fully completed in this remote pass

This sanity check used the GitHub-connected repository view plus the existing `Plan/context.md` inventory and selected authority-file reads. It did not locally unzip every `.zip`, re-extract every `.docx`, compile RTL, run PowerShell scripts, or execute local project tooling. Those checks require the local checkout/runtime environment.

Therefore:

- source-derived Plan inventory is considered repo-grounded,
- binary/archive deep verification is considered pending local rerun,
- hardware/toolchain compile status is not claimed,
- and implementation completeness is not asserted beyond observed docs and prior generated context.

## 8. Local follow-up commands

Run these locally from the Project Athena root when available:

```powershell
powershell -NoProfile -ExecutionPolicy Bypass -File .\tools\Invoke-AIIntegrityCheck.ps1
powershell -NoProfile -ExecutionPolicy Bypass -File .\tools\Invoke-AIProjectScan.ps1
powershell -NoProfile -ExecutionPolicy Bypass -File .\tools\Export-ProjectMap.ps1
powershell -NoProfile -ExecutionPolicy Bypass -File .\tools\Export-AISystemManifest.ps1
powershell -NoProfile -ExecutionPolicy Bypass -File .\tools\Invoke-AIForensicVerification.ps1
powershell -NoProfile -ExecutionPolicy Bypass -File .\tools\Invoke-AIOperationCycle.ps1 -SkipLiveProbe
```

## 9. Bottom line

`Plan/` is not a passive archive. It is the canonical Athena architecture vault. This expansion pack updates it by adding the newer project-chat concepts around Lightcore, L.O.D.E, RoomSense, BodyRig, OASIS, and Operative Duplex AI into the same system map.
