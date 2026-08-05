# System Identity and Authority Correction — 2026-08-05

Status: canonical correction to the Project Athena master-expansion pack

## Correction

The prior expansion pack incorrectly collapsed the wider architecture into an ATHENA-centred hierarchy. In particular, it described the Operative Duplex AI as an action layer under ATHENA and sometimes treated OASIS as the outer container that contains ATHENA.

That model is superseded.

## Canonical entities

| Entity | Type | Canonical role | Explicitly not |
|---|---|---|---|
| ATHENA | independent institutional intelligence | research, evidence, governance, durable memory, councils, project coordination | JANUS's brain or owner |
| JARVIS | independent personal/executive intelligence | human dialogue, personal context, device/daily-work orchestration | an ATHENA adapter by definition |
| JANUS | independent operative metacognitive intelligence | perceives, learns and operates programs/environments; verifies real state changes | ATHENA subsystem, OASIS, or simple automation tool |
| OASIS | persistent digital reality and simulation/creation substrate | engineering, science, games, living/work, R&D, digital production and workshops | an AI, JANUS, or a container that owns ATHENA |
| Nexus-V | semantic/versioned execution architecture | branchable state, rollback, merge, provenance and execution semantics | the identity of any AI |
| Aegis | trust/attestation/commit-gate architecture | policy enforcement and proof of authorized state transition | owner of ATHENA/JARVIS/JANUS |
| Lightcore | future physical execution profile | optoelectronic/CNT/photonic compute and transport | replacement for Nexus-V semantics or RSM/Aegis truth |
| L.O.D.E TV | Lightcore Optical Display Endpoint | display, optical endpoint, telemetry and room-sensing anchor | the complete OASIS or complete RoomSense system |

## Correct relationship

```text
                       HUMAN AUTHORITY
                             │
       ┌─────────────────────┼─────────────────────┐
       │                     │                     │
    ATHENA                JARVIS                 JANUS
institutional AI     personal/executive AI   operative metacognitive AI
       │                     │                     │
       └──────────── governed collaboration ──────┘
                             │
                         OASIS API
                             │
          persistent digital reality / simulation substrate
                             │
        engineering · science · games · living/work · R&D
        digital twins · production · schematic workshops
                             │
           external software and authorized machinery
```

Arrows indicate information or action contracts, not ownership.

## JANUS naming

Working canonical name: **JANUS**

Expansion: **Joint Adaptive Neurocognitive Operative System**

The duplex is internal to JANUS:

- Interior Face: metacognition, confidence, error detection and authority checks.
- Exterior Face: perception, program cartography, action and state verification.

## OASIS correction

OASIS is broader than a game or conventional metaverse. It is a persistent programmable digital-world substrate for:

- engineering and digital twins;
- scientific and multiphysics simulation;
- games and fictional worlds;
- virtual living and social spaces;
- offices, laboratories, universities and collaborative workspaces;
- R&D think tanks and evidence rooms;
- production planning, CAD/schematic workshops and manufacturing handoff;
- AI and human embodiment.

It hosts environments and interoperable runtime services. It is not itself the operative AI.

## Repository impact

The following documents require or receive correction:

- `JANUS_OPERATIVE_METACOGNITIVE_AI_MASTER_SPEC.md` — new canonical JANUS authority.
- `OPERATIVE_DUPLEX_AI_SPEC.md` — retained as a compatibility/legacy title, corrected to point to JANUS.
- `OASIS_ARCHITECTURE_SPEC.md` — revised as a non-AI substrate.
- `ATHENA_FULL_SYSTEM_MAP.md` — revised from hierarchy to peer-intelligence/system-of-systems map.
- `ATHENA_MASTER_ONTOLOGY.yml` — JANUS node and non-ownership relationships.
- `Plan/OASIS_ATHENA_AGENT_MODEL.md` — legacy model marked superseded where it conflates JARVIS/JANUS with adapters.
- root `README.md` and `AI-PORTAL.md` — first-read correction.

## Authority rule

No AI gains authority over another merely because it supplied a goal, context or analysis. Every cross-system request carries:

- requester identity;
- objective;
- evidence/provenance;
- requested authority scope;
- privacy class;
- expected state diff;
- validation and rollback requirements.

Human authority remains ultimate.
