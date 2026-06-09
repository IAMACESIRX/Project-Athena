# Review Gates

Use these gates before crossing risk boundaries.

## Gate: Local Git

- Are remotes local?
- Is the correct layer active?
- Are child repos committed before parent pointer updates?

## Gate: Live Server

- Is the operation read-only?
- If not read-only, did the human explicitly ask for it?
- Is there a backup or rollback plan?
- Which containers/databases will be touched?

## Gate: Client Payload

- Is this a config-only commit?
- Is disk capacity enough?
- Are large MPQ/exe/dll files intentionally included?

## Gate: AI Execution Capability

- Is the command logged?
- Is risk level classified?
- Does it require confirmation?
- Is output captured?
- Is there a failure path?
