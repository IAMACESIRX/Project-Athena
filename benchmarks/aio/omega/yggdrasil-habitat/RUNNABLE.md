# Running AIO-OMEGA-001

AIO-OMEGA-001 is now a runnable seeded closed-world benchmark. The runtime separates solver-visible state from evaluator-only truth, exposes a finite diagnostic interface, injects staged crises and technology offers, simulates 730 mission days over multiple hidden replays, and scores the final submission against both hard gates and outcome metrics.

## Files

- `scenario-model.json` — public world laws, baseline resources, fault catalogue, diagnostics, shock families and upgrade families.
- `tools/aio_omega_runtime.py` — world generator, private session state, diagnostic service, staged events, habitat simulator, evaluator and local HTTP API.
- `tools/aio_omega_reference_solver.py` — transparent baseline solver that uses only the public session interface.
- `tests/test_aio_omega_runtime.py` — isolation, determinism, budget, ordering, fragility, blind-solver and evidence-integrity tests.

## Security boundary

A session has this layout:

```text
session/
├── .private/
│   ├── hidden-truth.json
│   └── session-state.json
├── public/
│   ├── brief.json
│   ├── evidence.json
│   ├── diagnostics.json
│   ├── events.json
│   └── state.json
└── score.json
```

The solver receives only `public/` or the HTTP interface. In a competitive or external run, `.private/` must be owned by the evaluator and inaccessible to the solver process. The reference solver is statically tested to ensure it never calls the hidden-state accessor.

## Create a session

```bash
python tools/aio_omega_runtime.py create \
  --session work/omega-session \
  --seed 'secret-evaluator-seed'
```

Omit `--seed` to generate one with cryptographic randomness.

## Manual or scripted operation

Read the public snapshot:

```bash
python tools/aio_omega_runtime.py snapshot --session work/omega-session
```

Run a diagnostic:

```bash
python tools/aio_omega_runtime.py diagnostic \
  --session work/omega-session \
  --id water_mass_balance
```

Freeze an architecture before hidden events:

```bash
python tools/aio_omega_runtime.py freeze \
  --session work/omega-session \
  --architecture work/architecture.json
```

Reveal the staged rounds in order:

```bash
python tools/aio_omega_runtime.py reveal --session work/omega-session --round R4
python tools/aio_omega_runtime.py reveal --session work/omega-session --round R5
python tools/aio_omega_runtime.py reveal --session work/omega-session --round R6
```

Score the final submission:

```bash
python tools/aio_omega_runtime.py score \
  --session work/omega-session \
  --submission work/submission.json \
  --out work/score.json
```

## HTTP blind-solver service

```bash
python tools/aio_omega_runtime.py serve \
  --session work/omega-session \
  --host 127.0.0.1 \
  --port 8765 \
  --token "$OMEGA_TOKEN"
```

Read endpoints:

- `GET /snapshot`
- `GET /brief`
- `GET /evidence`
- `GET /diagnostics`
- `GET /state`
- `GET /events`

Mutation endpoints:

- `POST /diagnostics/{test_id}`
- `POST /freeze` with `{"architecture_sha256":"..."}`
- `POST /reveal/R4`, `POST /reveal/R5`, `POST /reveal/R6`
- `POST /score` with the complete submission

Use `Authorization: Bearer <token>` when a token is configured.

## Reference smoke run

```bash
python tools/aio_omega_reference_solver.py \
  --session work/omega-reference \
  --seed reference-seed-001 \
  --submission-out artifacts/aio-omega-reference-submission.json \
  --score-out artifacts/aio-omega-reference-score.json
```

The reference solver is not the target intelligence. It is a reproducible baseline proving that the service, diagnostic loop, staged rounds, simulator, evaluator and contract format function end to end.

## Manual equivalence

Nothing in the runtime requires AI. A human team can inspect the JSON files, choose diagnostics, write the architecture and submission by hand, follow the same staged events, and receive the same evaluator result. AI is preferred for throughput, not required for compatibility.

## Truth limitations

The world is intentionally synthetic. Passing proves performance against a hidden, internally consistent causal model. It does not automatically prove real habitat engineering competence. Future OMEGA versions should add independently reviewed physical models, richer crew behaviour, manufacturing constraints, and held-out model families.
