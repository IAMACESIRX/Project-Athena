# Mitigation and Offset Framework

## Principle

A weakness is rarely isolated from the mechanism that creates value. Controls must therefore answer two questions simultaneously:

1. What negative effect are we reducing?
2. What useful capability must survive the control?

The framework rejects controls that merely suppress activity, complexity, creativity, challenge, speed, plasticity, or exploration without measuring what is lost.

## Required weakness record

Each weakness states:

- the observed or predicted weakness;
- triggers and operating conditions;
- harms or failure modes;
- benefits associated with the same behaviour or mechanism;
- evidence and confidence;
- current disposition.

## Required mitigation record

Each mitigation states:

- weakness IDs addressed;
- control or offset mechanism;
- benefits that must be preserved;
- activation trigger and execution mode;
- trade-offs and new risks introduced;
- manual and machine verification;
- review, adaptation, and removal conditions;
- owner and authority.

## Offset strategies

- **Boundary:** isolate a harmful effect without removing the useful mechanism.
- **Rate limit:** reduce overload while retaining burst capacity.
- **Staging:** keep exploration broad but delay canonical commitment.
- **Parallel path:** preserve a high-speed path and a high-assurance path.
- **Compiler displacement:** move complexity upstream to keep runtime simple.
- **Redundancy:** add independent review where correlated failure is dangerous.
- **Counterweight:** pair a bias or strength with an opposing role or test.
- **Progressive disclosure:** hide complexity from routine users while preserving full detail.
- **Reversibility:** permit aggressive experimentation within recoverable boundaries.
- **Dynamic configuration:** switch trade-offs based on context instead of fixing one compromise.

## Control quality test

A mitigation is incomplete when it lacks any of the following:

- a named benefit to preserve;
- a measurable or inspectable verification method;
- declared trade-offs;
- new-risk analysis;
- a review condition;
- a condition for changing or removing the control.

## Examples

| Weakness | Benefit to preserve | Offset |
|---|---|---|
| Concept proliferation | Broad design-space search | Sandbox branches, stage gates, and ranked promotion rather than restricting ideation |
| Endless reconstruction | Native integration and low technical debt | Evidence threshold and reconstruction trigger; freeze stable versions for operational learning |
| AI agreement loops | High research throughput | Independent adversarial roles, source diversity, and human challenge checkpoints |
| Historical overload | Complete lineage | Tiered active context, semantic indexes, and archive retrieval rather than deletion |
| Rapid adoption instability | Responsiveness to improvement | Shadow deployment, rollback, compatibility tests, and retained prior candidates |
| Process plasticity drift | Adaptability | Version the method, preserve baseline metrics, and compare process generations |
