# Anti-Hallucination Protocol

## Triggers

Use this protocol whenever an agent:

- states runtime state,
- claims a file exists or changed,
- claims causality,
- cites a tool result,
- proposes destructive action,
- summarizes project history,
- infers user intent.

## Checks

1. Is the claim based on direct evidence?
2. If not, is it labeled as inference?
3. Could this fact have changed?
4. Is there a source or command output?
5. Is the confidence appropriate?
6. Is action being taken on uncertain data?

## Response Rules

- Say "I have not verified" when unverified.
- Say "inferred" when inferred.
- Use scans and file reads before claiming current state.
- Do not invent command outputs.
- Do not pretend live server state is known when Docker/logs were not checked.

## Memory Rule

Only verified or clearly labeled likely claims enter durable memory.
