# Programmatic API

This is the file-level API for external tools.

## Read API

- `manifests/system-manifest.json`
- `manifests/generated-ai-index.json`
- `registries/*.yml`
- `navigation/generated/project-map.json`
- `sensory/scans/latest-scan.json`
- `observability/reports/latest-live-probe.json`
- `work/*.yml`

## Write API

Tools may write:

- `sensory/scans/`
- `observability/reports/`
- `navigation/generated/`
- `manifests/generated-ai-index.json`
- `handoff/sessions/`
- `work/work-items/`

Tools should not write source-of-truth registries unless they are explicitly registry-management tools.

## Stability

Machine-readable files must keep a `schema` field.

When changing a schema, update:

- `schemas/`
- `manifests/system-manifest.json`
- affected tools.
