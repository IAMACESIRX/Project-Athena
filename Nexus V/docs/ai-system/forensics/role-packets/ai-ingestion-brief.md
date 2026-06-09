# AI Ingestion Brief

Use this order when an AI needs a structured project-facts pass:

1. `ai-system/AI-PORTAL.md`
2. `ai-system/manifests/system-manifest.json`
3. `ai-system/engine/order-of-operations.md`
4. `ai-system/engine/routine-catalog.yml`
5. `ai-system/forensics/evidence-register.csv`
6. `ai-system/forensics/claim-catalog.csv`
7. `ai-system/forensics/evidence-claim-map.csv`
8. `ai-system/forensics/event-timeline.csv`
9. `ai-system/forensics/known-unknowns.csv`
10. `ai-system/sensory/scans/latest-scan.json`
11. `ai-system/observability/reports/latest-log-intelligence.json`
12. `ai-system/forensics/verification-reports/latest-forensic-verification.json`

Rules:

- Treat evidence IDs as stable keys.
- Preserve uncertainty labels.
- Do not turn old generated reports into current facts without refreshing them.
- Cite evidence IDs when adding new claims.

