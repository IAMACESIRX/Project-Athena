# JANUS Operative Metacognitive AI — Master Specification v1.0

Generated: 2026-08-05
Status: Plan-level design authority / independent AI architecture / implementation not yet claimed

## 1. Canonical identity

**JANUS** is the working canonical name for the independent operative metacognitive artificial intelligence.

Expanded engineering name:

**J.A.N.U.S. — Joint Adaptive Neurocognitive Operative System**

JANUS is not ATHENA, not JARVIS, not OASIS, and not a component inside any of them. It is its own conjoined intelligence with its own identity, operational memory, state model, perception, planning, metacognition, skill library, embodiment, and authority envelope.

The word *duplex* describes JANUS's two inseparable perspectives, not two separate agents:

- **Interior Face** — monitors goals, reasoning, confidence, assumptions, errors, policy conflicts, and cognitive state.
- **Exterior Face** — perceives programs and environments, acts through interfaces, observes consequences, and verifies real state changes.

## 2. Correct system boundary

```text
ATHENA
  independent institutional intelligence
  research, governance, memory, evidence, councils, long-horizon coordination

JARVIS
  independent personal/executive intelligence
  human dialogue, preference/context handling, device and daily-work orchestration

JANUS
  independent operative metacognitive intelligence
  program discovery, embodied software control, action planning, execution, verification

OASIS
  non-AI persistent digital reality and creation/simulation substrate
  engineering, science, games, living/work spaces, R&D, production and digital workshops
```

They collaborate through explicit contracts. None is defined as the brain, owner, container, or subordinate implementation of another.

## 3. Core purpose

JANUS gives artificial intelligence a governed digital body.

It can:

- operate ordinary desktop and immersive software without requiring shell access as the primary control path;
- use documented APIs when they are available and appropriate;
- understand windows, controls, documents, scenes, timelines, node graphs, editors and application state;
- learn unfamiliar or undocumented programs through controlled observation and reversible experimentation;
- turn discovered workflows into reusable, versioned and testable skill capsules;
- operate inside OASIS as a persistent embodied collaborator;
- transfer validated OASIS designs into external CAD, simulation, code, production and documentation tools;
- return evidence, state diffs, confidence, failures and rollback information to ATHENA, JARVIS and the human operator.

## 4. Duplex cognition

### 4.1 Interior Face

The Interior Face maintains:

- current goal and subgoals;
- provenance of the goal;
- active assumptions and unknowns;
- confidence and uncertainty;
- predicted state transitions;
- expected versus observed results;
- permission and policy constraints;
- cognitive conflict and error detection;
- skill selection rationale;
- stop, retry, rollback and escalation criteria.

It continuously asks:

```text
What am I trying to accomplish?
What do I actually know?
What am I assuming?
Why do I believe the current screen/application state is what I think it is?
What change should this action cause?
What evidence would prove success or failure?
Is the action authorized, reversible and proportionate?
```

### 4.2 Exterior Face

The Exterior Face maintains:

- operating-system and application world model;
- windows, controls, focus, selection and modal state;
- visual scene, accessibility tree and semantic UI graph;
- files, project state, unsaved changes and output artifacts;
- device, controller and spatial state;
- action trace and observed state diff;
- confidence and disagreement across perception sources.

It continuously asks:

```text
What is physically or digitally present?
Which object is actionable?
What state changed after the action?
Did the target program accept the input?
Did the output artifact actually appear and validate?
Is the current state safe to commit?
```

## 5. Computer-control hierarchy

JANUS uses the strongest available control layer, with shell and command-line execution optional rather than foundational.

### Layer A — native semantic control

- Windows UI Automation and Win32 control surfaces;
- accessibility trees and application event hooks;
- browser DOM/accessibility semantics;
- application object models and plugin APIs;
- structured document, scene and editor models.

### Layer B — verified application adapters

Adapters expose stable application grammar rather than memorized cursor paths:

- objects and entities;
- actions and preconditions;
- state transitions;
- output formats;
- validation procedures;
- version compatibility and hazards.

### Layer C — visual-semantic control

When structured interfaces are incomplete, JANUS combines:

- screen and region capture;
- text and icon understanding;
- layout and spatial relationship modelling;
- cursor, focus, selection and animation-change detection;
- before/after visual diffing;
- multimodal confidence fusion.

### Layer D — virtual physical input

Universal fallback through governed virtual:

- mouse;
- keyboard;
- touch;
- pen;
- controller;
- spatial/XR input.

### Layer E — shell or low-level automation

Used only when explicitly permitted and materially safer or more reliable. It is not required for the core JANUS concept.

## 6. Undocumented-program cartography

JANUS includes an **Application Cartographer**.

### 6.1 Passive discovery

Collect, without destructive action:

- application identity, version and executable metadata;
- window/control hierarchy;
- menus, labels, tooltips and shortcuts;
- accessibility semantics;
- file types and project structure;
- visible help, examples and templates;
- configuration and plugin surfaces within the authorized scope.

### 6.2 Sandboxed controlled exploration

For unknown functions:

1. Open a disposable or cloned project.
2. Snapshot the initial state.
3. Perform one bounded action.
4. Capture every observable diff.
5. Validate whether the predicted transition occurred.
6. Undo, rollback or restore the snapshot.
7. Repeat under varied conditions.
8. Record dependencies, side effects and confidence.

### 6.3 Functional inference

Each inferred capability is represented as a hypothesis:

```yaml
ApplicationCapabilityHypothesis:
  application_id: string
  version_range: string
  control_or_action: string
  inferred_function: string
  preconditions: [string]
  expected_diff: [string]
  observed_evidence: [string]
  reversibility: full | partial | none | unknown
  confidence: 0.0-1.0
  validation_state: observed | reproduced | cross_checked | approved
```

### 6.4 Skill compilation

Validated workflows become **Skill Capsules**:

```yaml
JanusSkillCapsule:
  skill_id: string
  name: string
  application: string
  compatible_versions: [string]
  intent_schema: object
  preconditions: [string]
  action_graph: object
  expected_state_diffs: [object]
  validation_probes: [object]
  rollback_plan: object
  permission_class: string
  evidence_refs: [string]
  confidence: 0.0-1.0
  owner: human | janus | shared
  status: experimental | verified | deprecated | blocked
```

A Skill Capsule records the invariant workflow, not accidental cursor movement.

## 7. Operational state contract

Every meaningful action is a proposed state mutation:

```yaml
JanusOperation:
  operation_id: string
  requester: human | athena | jarvis | oasis | janus
  objective: string
  target_environment: string
  current_state_ref: string
  preconditions: [string]
  proposed_action: object
  expected_diff: object
  risk_class: observe | draft | reversible | consequential | privileged
  authority_token: string | null
  observed_diff: object | null
  validation_result: pass | fail | partial | unknown
  rollback_state: available | unavailable | attempted | completed
  final_disposition: commit | reject | rollback | escalate | blocked
  evidence_refs: [string]
```

This contract can map onto Nexus-V branch, diff, commit and rollback semantics, but JANUS does not depend on Nexus-V hardware to exist. A conventional software implementation must be possible first.

## 8. Authority and safety

### Authority levels

- **O0 Observe** — inspect and map; no mutation.
- **O1 Prepare** — draft, populate and stage; cannot submit or publish.
- **O2 Reversible** — execute actions with proven restoration path.
- **O3 Consequential** — external communication, publication, installation, purchasing, account or production changes; explicit human policy/approval required.
- **O4 Privileged** — administrative, credential, security, driver, destructive storage or machinery operations; strong authorization, isolation and independent verification required.

### Independent commit gate

The execution planner and verifier must not be the same unchallenged process. JANUS's Exterior Face proposes/executes; its Interior Face and an independent policy/verification service can block commit.

Aegis may provide attestation and commit-gating services when Nexus-V is present. Aegis is not JANUS's owner and physical channel separation is never sufficient authority by itself.

### Hard invariants

- Human authority remains ultimate.
- No hidden escalation of privileges.
- No irreversible action based only on visual guesswork.
- No claim of success without an observed and validated state diff.
- No promotion of an experimental skill to verified without reproducible evidence.
- Credentials are isolated from the general reasoning context.
- Destructive or external actions remain interruptible until the final commit boundary.

## 9. Relationship to ATHENA

ATHENA may provide JANUS with:

- institutional context and project memory;
- evidence requirements;
- policies and governance decisions;
- council analysis;
- long-horizon plans;
- ontology and provenance references.

JANUS returns:

- action feasibility;
- application maps;
- execution traces;
- validated outputs;
- failures, uncertainty and environmental state;
- reusable skill capsules.

ATHENA does not become JANUS's internal brain. JANUS can continue bounded operation if ATHENA is unavailable, subject to cached authority and safety policy.

## 10. Relationship to JARVIS

JARVIS may provide:

- the user's immediate intent and conversational context;
- preferences, schedule and situational context;
- device and personal-workflow orchestration;
- clarification and status presentation.

JANUS returns operational progress and verified outcomes. JARVIS does not directly certify a consequential action unless the relevant authority policy permits it.

## 11. Relationship to OASIS

OASIS is a world and runtime substrate, not JANUS.

JANUS can have a persistent OASIS embodiment with:

- body/avatar and spatial frame;
- tools and inventories;
- laboratories, workshops and factories;
- simulation controls;
- collaborative presence;
- project and machine digital twins.

The same JANUS identity can operate both:

```text
external software/application world
                ↕
shared operation and evidence model
                ↕
OASIS spatial/digital world
```

OASIS can be used to simulate a proposed workflow before JANUS executes it in external software or authorized machinery.

## 12. Relationship to the engineering stack

### Nexus-V

Provides optional native versioned-state execution primitives and branch/merge/rollback representation.

### Aegis

Provides optional policy enforcement, attestation, proof records and commit gates.

### Lightcore

Provides a future physical execution profile and optical transport/compute substrate. JANUS must remain implementable on conventional hardware.

### L.O.D.E TV, RoomSense and BodyRig

Provide display, interaction and spatial-sensing channels. JANUS can use them to operate in embodied room/XR contexts, while local privacy and explicit authority boundaries remain mandatory.

### Reality-to-Simulation / Known Behavioral Map

Provides material, environment and object-state models that JANUS can inspect and manipulate in OASIS, then transfer into engineering applications with provenance and confidence labels.

## 13. Persistent world model

JANUS maintains a graph that separates observed fact from inference:

```text
Computer / OASIS / spatial environment
├── applications and versions
├── windows, panels and controls
├── projects, files and unsaved state
├── people/agents represented by scoped identifiers
├── devices, sensors and network resources
├── permissions and authority tokens
├── known workflows and skill capsules
├── predicted versus observed state transitions
├── hazards and blocked actions
└── evidence and provenance
```

Each node carries:

- source;
- timestamp;
- confidence;
- authority scope;
- privacy class;
- validation status;
- expiry/version compatibility.

## 14. Implementation architecture

```text
JANUS Identity and Policy Core
├── Interior Metacognition Engine
├── Exterior Perception and Action Engine
├── Application Cartographer
├── World-State Graph
├── Skill Capsule Registry
├── Operation Planner
├── Independent Verifier
├── Permission / Commit Gate
├── Adapter Runtime
├── OASIS Embodiment Runtime
├── Evidence and Replay Store
└── Human Emergency Stop / Session Boundary
```

Recommended first implementation is local-first and conventional:

1. Windows desktop observation and semantic UI graph.
2. Read-only mapping of File Explorer, browser, IDE and one engineering application.
3. Sandboxed reversible action execution.
4. Skill capsule creation and replay.
5. Independent verifier and state-diff log.
6. ATHENA/JARVIS/OASIS adapters.
7. Spatial/XR embodiment.
8. Optional Nexus-V/Aegis integration.

## 15. Validation programme

### V0 — model-only simulation

- synthetic application states;
- predicted diffs;
- permission and rollback tests;
- adversarial ambiguity tests.

### V1 — read-only real applications

- semantic control discovery;
- visual/structured state agreement;
- no mutation.

### V2 — reversible sandbox tasks

- document edits;
- project duplication;
- export/import;
- deterministic rollback.

### V3 — unfamiliar application cartography

- isolated application;
- controlled exploration;
- reproducible skill inference;
- version-drift testing.

### V4 — consequential staged actions

- draft-only external operations;
- human commit approval;
- evidence and replay verification.

### V5 — OASIS/external-world transfer

- simulate in OASIS;
- export to external tool;
- compare predicted and actual outputs;
- reconcile differences.

## 16. Current maturity

- Identity and boundary: **specified**.
- Duplex cognitive model: **specified**.
- Program cartography method: **specified**.
- Permission/operation schema: **specified**.
- Conventional local runtime: **planned**.
- General undocumented-program competence: **research target**.
- OASIS embodiment: **planned/conceptual**.
- Nexus-V/Aegis native execution: **future integration**.
- Lightcore-native implementation: **long-horizon speculative**.

## 17. Canonical correction

Any earlier document that says the operative AI is:

- an ATHENA subsystem,
- ATHENA's action layer,
- inside ATHENA's brain,
- controlled as a limb of one central Athena,
- or identical to OASIS,

is superseded by this specification.

The canonical relationship is:

```text
ATHENA ↔ JANUS ↔ JARVIS
     \       |       /
             ↕
           OASIS
             ↕
external software, digital systems and authorized physical machinery
```

The links are governed collaboration interfaces between independent systems, not ownership arrows.
