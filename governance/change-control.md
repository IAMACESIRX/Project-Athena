# Change Control

## Change Classes

### Class 0: Documentation And Maps

Low risk. Commit in mega repo.

### Class 1: AI System Tooling

Medium risk. Run tool after edit and commit result if it generates useful state.

### Class 2: Project Code Or Scripts

Medium risk. Inspect, edit, run targeted verification, commit in child repo, update mega pointer.

### Class 3: Live State Or Runtime

High risk. Requires explicit intent, backup awareness, and post-change verification.

### Class 4: Destructive Or Public Exposure

Critical risk. Requires explicit human approval and a rollback plan.

## Required Fields For Significant Changes

- layer,
- purpose,
- files changed,
- verification,
- risks,
- rollback path,
- next action.
