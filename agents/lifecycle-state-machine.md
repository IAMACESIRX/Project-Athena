# Agent Lifecycle State Machine

## States

1. `created`
2. `idle`
3. `assigned`
4. `planning`
5. `executing`
6. `waiting`
7. `review`
8. `completed`
9. `escalated`
10. `failed`
11. `archived`

## Rules

- Agents cannot execute before assignment.
- High-risk tasks enter `review` before execution.
- Blocked agents enter `waiting` with a named blocker.
- Failed agents produce a failure report and lesson candidate.
- Retired agents keep their audit history.

