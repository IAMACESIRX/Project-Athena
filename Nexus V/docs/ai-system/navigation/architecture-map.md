# Architecture Map

## Layer Architecture

```text
Human / AI / Tools
        |
        v
ai-system governance, maps, memory, work, sensors
        |
        v
Mega repo child pointers
        |
        +--> Game client repo
        +--> Server live-state repo
        +--> WoW server project repo
                  |
                  +--> FastAPI command hub
                  +--> WoW scripts
                  +--> AzerothCore clean repo
                  +--> AzerothCore Playerbots repo
                              |
                              +--> mod-playerbots repo
```

## Runtime Architecture Target

```text
AI agent
  -> reads ai-system manifests
  -> runs read-only probes
  -> updates work/risk/handoff
  -> uses command hub for controlled actions
  -> command hub logs action
  -> module executes only allowed operation
  -> observability captures result
```

## Design Intent

The AI system is not just documentation. It is the control plane from which future tooling can read, reason, act, verify, and remember.
