# F.O.R.G.E.

**F.O.R.G.E.** means **First-Principles Ontological Reconstruction and Generational Evolution**.

F.O.R.G.E. is the cognitive-synthesis system that encodes the human owner's recurring method for developing ideas: preserve intent, separate claims from evidence, generate competing architectures, challenge positives and negatives symmetrically, vary assumptions, mine the strongest mechanisms, reconstruct a native design, simplify the usable result, and preserve the complete lineage.

## System boundary

```text
A.E.S.I.R. discovers and expands the evidence/candidate space.
F.O.R.G.E. compares, challenges, reconstructs and compiles candidate systems.
ATHENA preserves institutional memory, provenance, governance and continuity.
OASIS/simulators/prototypes test candidate systems against modelled or physical reality.
Nexus-V/Aegis is a future versioned and attested execution substrate.
```

F.O.R.G.E. is not another ATHENA identity and does not own ATHENA, A.E.S.I.R., OASIS, JARVIS or JANUS. It is an independent cognitive-development system that collaborates with them through explicit contracts.

## Capability state

- **Specified:** complete v0.1 system boundary, workflow and interfaces.
- **Implemented:** deterministic file-native compiler prototype, JSON Schemas, sample concept packet and unit tests.
- **Not yet implemented:** AI council orchestration, external research adapters, graph database, simulation execution, autonomous method evolution and production service runtime.

## Quick start

Validate the example packet:

```bash
python forge/compiler/forge_compiler.py validate forge/examples/concept-packet.example.json
```

Compile it into a functional snapshot and compile trace:

```bash
python forge/compiler/forge_compiler.py compile \
  forge/examples/concept-packet.example.json \
  --out forge/examples/generated
```

Run the v0.1 unit tests:

```bash
python -m unittest discover -s forge/tests -p "test_*.py"
```

## v0.1 output

The compiler produces:

- `functional-snapshot.json`: current best reconstruction of the concept;
- `compile-trace.json`: input hash, ranking, mechanism selection, conflicts and pass history.

The compiler does not claim that a generated architecture is scientifically true or physically validated. It structures the reasoning state so A.E.S.I.R., ATHENA, human reviewers and later simulations can test it.

## Read order

1. `forge/FORGE-PORTAL.md`
2. `forge/architecture/FORGE-SYSTEM-SPEC-v0.1.md`
3. `forge/engine/pipeline.yml`
4. `forge/engine/promotion-gates.yml`
5. `forge/adapters/AESIR-CONTRACT.md`
6. `forge/adapters/ATHENA-CONTRACT.md`
7. `forge/schemas/concept-packet.schema.json`
8. `forge/compiler/forge_compiler.py`
