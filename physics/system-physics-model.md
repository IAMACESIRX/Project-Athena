# System Physics Model

This is the conceptual model for how the project behaves.

## Entities

An entity is anything with identity and state:

- repo,
- file,
- module,
- database,
- container,
- script,
- command,
- user,
- AI agent,
- game client,
- server process.

## State

State is any value that can change:

- Git commit,
- file contents,
- SQL dump content,
- Docker container status,
- realm address,
- client realmlist,
- bot count,
- work item status,
- scan signal.

## Forces

Forces are things that push state to change:

- human request,
- AI edit,
- Git commit,
- Docker command,
- SQL import/export,
- client launch,
- server runtime,
- disk pressure,
- upstream update.

## Constraints

Constraints shape what changes are allowed:

- local-only hosting,
- storage limits,
- privacy,
- restore safety,
- nested repo pointer rules,
- runtime confirmation rules.

## Flows

### Git Flow

Child repo state changes -> child commit -> local push -> mega pointer update -> mega commit -> local push.

### Restore Flow

SQL dump -> database import -> service restart -> realm validation -> client login test.

### Observation Flow

Probe -> report -> signal -> issue/work item -> fix -> verification -> memory update.

### Feature Flow

Idea -> research -> module card -> work item -> implementation -> verification -> commit -> handoff.

## Failure Dynamics

- Small hidden drift becomes expensive context loss.
- Runtime changes without logs become irreproducible.
- Parent pointer updates without child commits break layer meaning.
- Full client snapshots without storage planning create disk pressure.

## Control Goal

Make every important state transition visible, reversible when possible, and attached to evidence.
