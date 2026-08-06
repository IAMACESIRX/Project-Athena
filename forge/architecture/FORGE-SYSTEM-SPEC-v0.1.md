# F.O.R.G.E. System Specification v0.1

## 1. Purpose

F.O.R.G.E. operationalises a human-originated development methodology for high-uncertainty ideas and architectures. It converts loosely expressed intent and research into an inspectable candidate space, extracts the causal mechanisms behind strong candidates, and produces a simplified native reconstruction with full lineage.

## 2. Separation of responsibilities

| System | Responsibility |
|---|---|
| A.E.S.I.R. | Research, source discovery, cross-domain exploration, hypothesis generation and evidence packets |
| F.O.R.G.E. | Candidate generation, symmetric challenge, mechanism mining, reverse reconstruction and functional snapshot compilation |
| ATHENA | Institutional memory, project state, governance, provenance, authority, audit and long-term continuity |
| OASIS / simulation tools | Behavioural simulation, digital twins, experimental environments and discrepancy production |
| Nexus-V / Aegis | Future versioned-state execution, provenance, attestation and commit gating |

## 3. Human-AI operating model

The human owner supplies direction, original concept formation, semantic correction, architectural judgement and risk acceptance. AI systems provide parallel research, candidate generation, adversarial review, formalisation, code, documentation and repetitive comparison. Evidence—not confidence—determines what is supported.

F.O.R.G.E. records conceptual provenance using contribution modes:

- `human_originated`;
- `human_directed`;
- `co_developed`;
- `ai_proposed_human_selected`;
- `external_adapted`;
- `independently_reconstructed`.

## 4. Core data objects

### Intent Genome

Preserves the objective, semantic invariants, flexible variables, success criteria and prohibited reinterpretations.

### Claim Record

Separates facts, observations, assumptions, hypotheses, speculation, predictions, contradictions and unresolved questions.

### Candidate Architecture

Represents one possible solution, including mechanisms, strengths, weaknesses, trade-offs, evidence and multidimensional scores.

### Mechanism Record

Captures why a candidate works, conditions required, benefits, costs, portability and conflicts.

### Compile Trace

Records the exact input hash, compiler version, passes, candidate ranking, mechanism decisions, unresolved conflicts and output references.

### Functional Snapshot

Represents what the concept should currently be, given the selected objective, evidence, constraints and compatible mechanisms.

## 5. Candidate tournament

Candidates are not simply voted on. Each candidate is scored across dimensions such as evidence, performance, simplicity, resilience, adaptability, reversibility and integration cost. The leading set becomes a mechanism donor pool.

The compiler asks:

1. What produces each candidate's strength?
2. Under what conditions does the mechanism work?
3. Which costs are intrinsic and which are implementation accidents?
4. Can the mechanism be separated from the donor architecture?
5. Which mechanisms conflict?
6. What native architecture could produce the compatible strengths together?

## 6. Reconstruction rule

F.O.R.G.E. does not merge donor implementations directly. It merges validated knowledge and reconstructs a new architecture around the combined mechanism set.

```text
observed strengths
→ causal mechanisms
→ required invariants
→ compatibility graph
→ native primitives
→ simplified architecture
```

## 7. Temporal model

Every meaningful state remains addressable:

- original concept;
- temporary additions;
- candidate branches;
- failed hypotheses;
- simulations;
- reconstructed concepts;
- functional snapshots;
- method versions.

The active snapshot is therefore not the whole project. It is the current compiled view of a four-dimensional project history.

## 8. v0.1 compiler boundary

The v0.1 compiler is deterministic and file-native. It:

- validates required concept-packet structure;
- calculates a stable input hash;
- ranks candidates using configurable weighted dimensions;
- selects the leading donor set;
- scores recurring mechanisms;
- detects declared mechanism conflicts;
- preserves semantic invariants;
- emits a functional snapshot and compile trace.

It does not yet:

- verify scientific sources;
- run external simulations;
- infer mechanisms from unstructured prose;
- use an LLM council automatically;
- prove that selected mechanisms can coexist physically;
- autonomously modify the canonical ATHENA project.

## 9. Promotion rule

A compiled snapshot is **scaffolded output**, not canonical truth. Promotion requires the gates in `forge/engine/promotion-gates.yml`, relevant A.E.S.I.R. evidence and ATHENA governance.

## 10. Success criteria for v0.1

- one machine-readable concept packet;
- deterministic ranking and mechanism mining;
- preserved semantic invariants;
- explicit unresolved conflicts;
- reproducible compile trace;
- unit-tested output generation;
- clear ATHENA and A.E.S.I.R. interfaces.
