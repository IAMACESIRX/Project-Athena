# Athena Memory

This directory defines Athena's durable memory architecture and writeback rules.

## Primary entrypoint

Read `athena-memory-map.md` first. It classifies repository memory into identity,
architecture, working, evidence, capability, runtime, and implementation layers,
then defines when verified information should be written to each layer.

## Operating rule

Store information in the narrowest durable location that preserves its meaning:

- identity changes belong in root context and `identity/`;
- architecture intent belongs in `Plan/`;
- current task state belongs in `work/`, `handoff/`, or `continuity/`;
- evidence and decisions belong in `forensics/`, `audit/`, or cycle reports;
- capability and routing changes belong in manifests, registries, agents, and
  orchestration;
- runtime observations belong in sensory, observability, and tool reports;
- source implementation belongs in code, schemas, templates, and Nexus-V.

Do not promote assumptions, speculative concepts, stale generated reports, or
unmerged feature branches into canonical memory without an explicit truth-state
label.
