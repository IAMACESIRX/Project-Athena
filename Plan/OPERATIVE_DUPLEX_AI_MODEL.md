# Operative Duplex AI Model

Updated: 2026-08-01
Status: Human design intent; independent AI not implemented.

## Identity Boundary

The Operative Duplex is an independent operative metacognitive AI. It is not
Athena, Jarvis, or OASIS, and none of those systems is automatically its owner
or brain.

It may collaborate with:

- Athena for institutional research, governance, evidence, and durable memory;
- Jarvis for human-facing context, personal assistance, and immediate intent;
- OASIS for simulation, digital embodiment, construction, and validation;
- conventional applications, networks, and authorized physical machinery for
  real execution.

The independent system requires its own identity, memory, goals, reasoning,
perception, skills, authority, embodiment, and learning policy.

## Provisional Name

`JANUS - Joint Adaptive Neurocognitive Operative System` was proposed in the
recovered chat because the architecture looks inward at its own cognition and
outward at the environment.

This name is provisional. The chat contains no later human confirmation, so
`Operative Duplex` remains the canonical functional name until a naming
decision is recorded.

## Duplex Structure

The system contains two conjoined but independently accountable loops.

### Interior Loop

The interior loop handles:

- metacognition and self-evaluation;
- intent modeling;
- planning and candidate generation;
- confidence and uncertainty tracking;
- memory inspection;
- cognitive conflict detection;
- error prediction;
- authority and risk interpretation.

### Exterior Loop

The exterior loop handles:

- application and environment perception;
- live-state modeling;
- software and tool operation;
- unfamiliar-program discovery;
- digital embodiment in OASIS;
- authorized physical-system interfaces;
- independent result verification;
- observed-state reporting.

The interior may predict that an action will work. The exterior must determine
what actually happened. Predicted state never becomes observed state merely
because the action was attempted.

## Pilot And Witness Roles

An initial implementation can express the duplex as two roles:

- Pilot: translates goals into candidate actions and executes approved steps.
- Witness: maintains authoritative observed state, detects unexpected effects,
  and verifies completion independently.

They share a versioned live-state model but must keep prediction, command,
observation, and verification records distinct.

## Control Hierarchy

Use the highest-semantic and most verifiable authorized control surface first:

1. Native semantic control: accessibility trees, UI Automation, DOM, structured
   application state, and documented operating-system interfaces.
2. Application adapter: a versioned model of objects, commands, state
   transitions, storage, and validation for a known application.
3. Visual-semantic control: screen state, OCR, icon and layout recognition,
   spatial relationships, and change detection.
4. Virtual physical input: mouse, keyboard, touch, pen, or controller as a
   fallback when higher-level control is unavailable.
5. Authorized hardware interface: only through a separately reviewed runtime
   adapter and safety boundary.

"No shell required" means shell access is not a dependency for universal
operation. It does not prohibit structured APIs or command tools when they are
safer and easier to verify.

## Application Cartographer

The Cartographer constructs empirical operational models for undocumented or
poorly documented programs.

### Stage 0: Admission

- confirm legal and user authority;
- classify the application's trust and consequence level;
- define read, write, network, file, credential, and runtime boundaries;
- prepare an isolated test project or disposable environment;
- establish an emergency stop and recovery path.

### Stage 1: Passive Inspection

Observe metadata, version, windows, menus, accessibility labels, shortcuts,
tooltips, help text, file extensions, configuration locations, plugins, and
visible workspace structure without changing state.

### Stage 2: Controlled Exploration

For each bounded experiment:

1. Capture a known starting state.
2. Perform one low-risk action.
3. Observe all accessible state changes.
4. Compare files, UI, logs, and side effects.
5. Undo or restore.
6. Repeat to test consistency.

### Stage 3: Functional Inference

Build labeled hypotheses from controls, context, observed changes, saved-state
diffs, repeated tests, similar programs, and human demonstrations.

Every inferred function records:

- confidence;
- preconditions;
- expected transition;
- observed transition;
- side effects;
- rollback behavior;
- version and environment;
- evidence references.

### Stage 4: Skill Compilation

A reusable application skill contains:

- application identity and supported versions;
- objective and preconditions;
- semantic action sequence;
- fallback control paths;
- expected intermediate states;
- validation checks;
- side effects and consequence class;
- failure detection;
- rollback or containment;
- evidence and demonstration provenance.

Learning one program version does not authorize or guarantee operation of every
version.

## Operative Action Protocol

Every action proposal should be representable as:

```text
GOAL
CURRENT_OBSERVED_STATE
ASSUMPTIONS
PROPOSED_ACTION
EXPECTED_STATE_TRANSITION
AUTHORITY
CONSEQUENCE_CLASS
PRECONDITIONS
VALIDATION
ROLLBACK_OR_CONTAINMENT
EVIDENCE
```

After execution, append:

```text
OBSERVED_RESULT
STATE_DIFF
VALIDATION_RESULT
UNEXPECTED_EFFECTS
CONFIDENCE
AUDIT_REFERENCE
LEARNING_CANDIDATE
```

## Authority Levels

| Level | Name | Examples | Default Gate |
|---:|---|---|---|
| 0 | Observe | inspect UI, map controls, explain state | allowed within read scope |
| 1 | Prepare | fill fields, stage drafts, prepare export | stop before consequential commit |
| 2 | Reversible | edit documents, configure ordinary apps | require verified rollback |
| 3 | Consequential | send, publish, purchase, install, account change | explicit human confirmation |
| 4 | Privileged | admin, drivers, credentials, security, destructive storage | explicit confirmation plus elevated controls |

Project and application policy may make a lower-numbered action more
restrictive. The table is a ceiling, not an entitlement.

## OASIS Embodiment

The OASIS-side embodiment can construct and operate:

- engineering and scientific workspaces;
- digital twins and simulations;
- prototype and production-planning environments;
- laboratories, factories, vehicles, and test chambers;
- shared project rooms and navigable knowledge structures;
- fictional, educational, game, and social environments.

OASIS objects require a reality class:

- fictional;
- conceptual;
- approximate;
- simulated;
- validated;
- production-qualified.

Visual realism cannot raise an object's reality class. Evidence and
qualification do.

## Cross-System Cycle

```text
human goal or internally authorized goal
  -> Jarvis resolves immediate human context when relevant
  -> Athena supplies research, constraints, evidence, and governance
  -> Operative Duplex creates candidate plans
  -> OASIS simulates or constructs candidates when useful
  -> Witness observes and tests results
  -> approved plan executes in real software or machinery
  -> real result is compared with prediction
  -> each system receives only the memory appropriate to its scope
```

No collaborator silently inherits another system's authority.

## Safety Invariants

- The Witness can veto or stop the Pilot on state mismatch.
- Unknown application state defaults to observation, not mutation.
- Exploration occurs in disposable or recoverable state.
- Credentials are isolated from learned workflows and visual logs.
- CAPTCHAs, human-verification gates, anti-cheat, DRM, and protected desktops
  are boundaries, not obstacles to bypass.
- Privileged, financial, publishing, communication, account, and destructive
  actions require explicit authority.
- Learning from demonstration removes accidental motion and preserves the
  demonstrated intent, validation, and constraints.
- Skills expire or require review when application versions or environments
  change materially.
- Physical operation requires a distinct hazard analysis and fail-safe design.

## Current Repository Mapping

| Requirement | Current Precursor | Gap |
|---|---|---|
| Windows semantic control | `runtime/agent-platform/windows-agent-platform.md` | no independent duplex runtime |
| Adapter contracts | `integration/adapter-contract.md`, `integration/adapter-registry.yml` | fields too small for learned application models |
| Message envelope | `schemas/message.schema.json`, `orchestration/message-protocol.md` | no action-transition schema |
| Evidence and audit | `forensics/`, `audit/`, `truth/` | not connected to UI actions |
| Restore and rollback | `restore/`, `drift/` | no application sandbox controller |
| Model routing | `orchestration/model-router.yml` | no Pilot/Witness separation |
| OASIS world model | Plan documents only | no runtime or object schema |

## First Build Slice

1. Record the final name and identity boundary.
2. Define action, observation, application-model, and skill schemas.
3. Implement a read-only Windows Cartographer for one test application.
4. Add a Pilot that proposes actions without executing them.
5. Add a Witness that verifies manually executed actions from independent
   observations.
6. Enable one reversible action in a disposable test project.
7. Test state mismatch, unexpected dialog, failed undo, version drift, and
   emergency stop.

## Success Criteria

- The system distinguishes desired, predicted, commanded, observed, and
  verified state.
- It can learn one bounded workflow without undocumented destructive effects.
- Replacing the Pilot does not erase the application model or audit history.
- The Witness detects false completion and blocks unsafe continuation.
- Authority remains explicit from goal through observed result.
