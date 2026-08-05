# JANUS Research and Safety Validation Notes — 2026-08-05

Status: research anchors and architecture sanity check; not implementation evidence

## Purpose

This note tests the JANUS architecture against current computer-use-agent research. It separates supported primitives from extrapolated Project Athena design intent.

## Findings

### 1. GUI operation without application-specific APIs is a valid research direction

Visual GUI agents can operate through screenshots and ordinary click/type action spaces rather than requiring application internals. Research systems and benchmarks support visual grounding, cross-platform action spaces and hierarchical planning.

This supports JANUS's use of visual-semantic control and virtual physical input as universal fallback layers.

It does **not** prove reliable control of every program.

### 2. Professional software remains substantially harder than general web/mobile tasks

ScreenSpot-Pro reports severe grounding difficulty in professional high-resolution interfaces, with the best baseline in that study at 18.9% and its cascaded search method at 48.1%.

Architectural implication:

- JANUS must narrow the active search region;
- combine application grammar with vision;
- maintain selection/focus/modal state;
- never treat a single visual guess as sufficient for consequential action;
- validate professional applications individually and by version.

Reference:

- Kaixin Li et al., 2025, *Proceedings of the 33rd ACM International Conference on Multimedia*, [ScreenSpot-Pro: GUI Grounding for Professional High-Resolution Computer Use](https://consensus.app/papers/screenspotpro-gui-grounding-for-professional-li-meng/f753ec8c3be7559488931422429035fa/?utm_source=chatgpt).

### 3. Independent pre-action verification is a security requirement

The Visual Confused Deputy work formalizes failures where an agent acts on the wrong target because of perception errors, adversarial screen manipulation or time-of-check/time-of-use races. It reports improved blocking when visual target evidence and the agent's stated reasoning are checked independently.

This directly supports:

- JANUS Interior/Exterior separation;
- an external commit/verification service;
- pre-dispatch re-observation;
- target identity checks;
- prohibition on irreversible actions based only on stale screenshots;
- explicit expected-versus-observed state diffs.

Reference:

- Xunzhuo Liu et al., 2026, *arXiv abs/2603.14707*, [Visual Confused Deputy: Exploiting and Defending Perception Failures in Computer-Using Agents](https://consensus.app/papers/visual-confused-deputy-exploiting-and-defending-liu-he/bf2716ecd81a5914b61af826daf87844/?utm_source=chatgpt).

### 4. Hierarchical planning, specialized grounding and recovery are supported design patterns

Independent SciSpace search results identify recurring patterns across Agent S, Surfer 2 and professional-software benchmarks:

- decoupled planning and execution;
- hierarchical task/subtask planning;
- experience retrieval;
- self-verification;
- adaptive recovery;
- execution-based evaluation;
- human-in-the-loop gates for difficult professional workflows.

This supports JANUS's split between objective planning, application-specific Skill Capsules, action execution and independent verification.

Research also reports that professional multi-software workflows remain weak. JANUS's generalized undocumented-program competence must therefore remain a staged research target.

Representative references:

- Saaket Agashe et al., 2024, *arXiv*, DOI `10.48550/arxiv.2410.08164`, Agent S: An Open Agentic Framework that Uses Computers Like a Human.
- Jiaxin Ai et al., 2025/2026 preprint, DOI `10.48550/arxiv.2601.02399`, ProSoftArena: Benchmarking Hierarchical Capabilities of Multimodal Agents in Professional Software Environments.
- Mathieu Andreux et al., 2025, DOI `10.48550/arxiv.2510.19949`, Surfer 2: The Next Generation of Cross-Platform Computer Use Agents.

## Architecture verdict

| JANUS element | Evidence state | Verdict |
|---|---|---|
| Visual control of ordinary software | research-supported primitive | valid, but accuracy is application-dependent |
| Native semantic/accessibility control | established platform capability | should be preferred where trustworthy |
| Multi-source semantic + visual fusion | research-supported | required for robustness |
| Interior/Exterior duplex | architecture inference supported by independent-verification findings | retain |
| Application Cartographer | plausible systems architecture | requires controlled experiments and benchmark design |
| Skill Capsules | consistent with experience retrieval and reusable hierarchical plans | retain and test per version |
| Universal undocumented-program competence | not established | long-horizon research target |
| Consequential autonomous action | unsafe without independent verification/authority gates | human/policy commit required |
| OASIS simulation before external action | reasonable safety/design pattern | useful but simulation mismatch must be measured |
| Nexus-V/Aegis native integration | Project-specific future architecture | optional after conventional reference implementation |

## Required test additions

1. Pre-action screenshot and semantic-tree refresh.
2. Window, process, focus and target-control identity check.
3. Stale-state and overlay/notification attack suite.
4. Time-of-check/time-of-use race tests.
5. Professional high-resolution small-target grounding tests.
6. Application version-drift suite.
7. Long-horizon failure recovery and partial-completion tests.
8. Cross-application transfer tests.
9. Independent verifier disagreement tests.
10. Human emergency-stop latency and reliability tests.

## Claim boundary

The research supports component patterns, not the complete JANUS system. The repository must continue to label JANUS as specified/planned until a conventional local implementation passes named benchmarks and application-specific acceptance tests.
