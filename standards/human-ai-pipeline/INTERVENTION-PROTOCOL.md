# Intervention Protocol

## Purpose

Intervention is a normal control path, not an exceptional failure. Human and authorised-system intervention must be possible without destroying the run's history.

## Required intervention fields

- stable intervention ID;
- timestamp;
- actor and authority;
- stage and state before intervention;
- action taken;
- reason;
- fields or artifacts changed;
- expected state difference;
- validation required;
- rollback or branch reference.

## Allowed actions

`pause`, `edit`, `override`, `branch`, `reject`, `resume`, `rollback`, `change_mode`, `change_mitigation`, `request_evidence`, `request_review`.

## Rules

1. Never silently overwrite the prior state.
2. An override records the rejected recommendation and why it was rejected.
3. A branch preserves the parent run identifier.
4. A mode change does not erase human or machine contributions.
5. High-risk actions still follow ATHENA authority and governance.
6. An intervention can itself be challenged, revised, or reversed.
