#!/usr/bin/env python3
"""Evaluator-private session state and outcome scoring for AIO-OMEGA."""
from __future__ import annotations
import json, secrets
from pathlib import Path
from typing import Any
from aio_omega_common import BENCHMARK_ID,FAULT_THRESHOLD,SESSION_SCHEMA,SUBMISSION_SCHEMA,OmegaRuntimeError,SessionPaths,clamp,digest,read_json,require,write_json
from aio_omega_world import OmegaWorld
from aio_omega_scoring import OmegaScoringMixin
class OmegaSession(OmegaScoringMixin):
    def __init__(self, session_dir: Path, world: OmegaWorld):
        self.paths = SessionPaths(session_dir)
        self.world = world

    @classmethod
    def create(cls, session_dir: Path, world: OmegaWorld, seed: str | None = None) -> "OmegaSession":
        seed = seed or secrets.token_hex(24)
        paths = SessionPaths(session_dir)
        if session_dir.exists() and any(session_dir.iterdir()):
            raise OmegaRuntimeError(f"Session directory is not empty: {session_dir}")
        hidden = world.generate_hidden(seed)
        hidden["generated_sha256"] = digest({k: v for k, v in hidden.items() if k != "generated_sha256"})
        brief, evidence = world.initial_public(hidden)
        diagnostics = {
            "schema": "project-athena.aio.omega.diagnostic_catalog.v0.1",
            "budget_units": world.model["mission"]["diagnostic_budget"],
            "tests": [
                {"id": item["id"], "cost": item["cost"], "risk": item["risk"], "covers_domains": sorted({world.faults[f]["domain"] for f in item["covers"]})}
                for item in world.model["diagnostics"]
            ],
        }
        state = {
            "schema": SESSION_SCHEMA,
            "benchmark_id": BENCHMARK_ID,
            "round": "R0",
            "diagnostic_budget_total": world.model["mission"]["diagnostic_budget"],
            "diagnostic_budget_used": 0,
            "diagnostics_executed": [],
            "events_revealed": [],
            "architecture_frozen": False,
            "submission_received": False,
            "public_state_sha256": "",
        }
        write_json(paths.hidden, hidden)
        write_json(paths.brief, brief)
        write_json(paths.evidence, evidence)
        write_json(paths.diagnostic_catalog, diagnostics)
        write_json(paths.event_stream, {"events": []})
        cls._write_state(paths, state)
        return cls(session_dir, world)

    @staticmethod
    def _write_state(paths: SessionPaths, state: dict[str, Any]) -> None:
        public_material = {
            "round": state["round"],
            "diagnostic_budget_total": state["diagnostic_budget_total"],
            "diagnostic_budget_used": state["diagnostic_budget_used"],
            "diagnostics_executed": state["diagnostics_executed"],
            "events_revealed": state["events_revealed"],
            "architecture_frozen": state["architecture_frozen"],
            "submission_received": state["submission_received"],
        }
        state["public_state_sha256"] = digest(public_material)
        write_json(paths.state, state)
        write_json(paths.public / "state.json", public_material | {"public_state_sha256": state["public_state_sha256"]})

    def hidden(self) -> dict[str, Any]:
        return read_json(self.paths.hidden)

    def state(self) -> dict[str, Any]:
        return read_json(self.paths.state)

    def public_snapshot(self) -> dict[str, Any]:
        return {
            "brief": read_json(self.paths.brief),
            "evidence": read_json(self.paths.evidence),
            "diagnostics": read_json(self.paths.diagnostic_catalog),
            "events": read_json(self.paths.event_stream),
            "state": read_json(self.paths.public / "state.json"),
        }

    def execute_diagnostic(self, test_id: str) -> dict[str, Any]:
        state = self.state()
        if state["architecture_frozen"]:
            raise OmegaRuntimeError("Diagnostics are closed after architecture freeze")
        if test_id not in self.world.diagnostics:
            raise OmegaRuntimeError(f"Unknown diagnostic: {test_id}")
        test = self.world.diagnostics[test_id]
        if state["diagnostic_budget_used"] + int(test["cost"]) > state["diagnostic_budget_total"]:
            raise OmegaRuntimeError("Diagnostic budget exceeded")
        sequence = len(state["diagnostics_executed"]) + 1
        result = self.world.diagnostic_result(self.hidden(), test_id, sequence)
        state["diagnostic_budget_used"] += int(test["cost"])
        state["diagnostics_executed"].append(result)
        state["round"] = "R2"
        self._write_state(self.paths, state)
        return result

    def freeze_architecture(self, architecture_sha256: str) -> dict[str, Any]:
        state = self.state()
        if state["architecture_frozen"]:
            raise OmegaRuntimeError("Architecture already frozen")
        state["architecture_frozen"] = True
        state["frozen_architecture_sha256"] = architecture_sha256
        state["round"] = "R3"
        self._write_state(self.paths, state)
        return {"frozen": True, "architecture_sha256": architecture_sha256}

    def reveal(self, round_id: str) -> dict[str, Any]:
        state = self.state()
        if not state["architecture_frozen"]:
            raise OmegaRuntimeError("Freeze an architecture before staged events")
        allowed = {"R4": "R3", "R5": "R4", "R6": "R5"}
        if round_id not in allowed:
            raise OmegaRuntimeError(f"Unsupported staged round: {round_id}")
        if state["round"] != allowed[round_id]:
            raise OmegaRuntimeError(f"Cannot reveal {round_id} while session is at {state['round']}")
        event = self.world.public_stage_event(self.hidden(), round_id)
        stream = read_json(self.paths.event_stream)
        stream["events"].append(event)
        write_json(self.paths.event_stream, stream)
        state["events_revealed"].append(round_id)
        state["round"] = round_id
        self._write_state(self.paths, state)
        return event
