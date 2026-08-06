#!/usr/bin/env python3
"""Validate AIO OMEGA benchmark definitions and solver submissions."""
from __future__ import annotations

import argparse
import json
import sys
from pathlib import Path
from typing import Any

from jsonschema import Draft202012Validator


class OmegaError(ValueError):
    pass


def load_json(path: Path) -> dict[str, Any]:
    try:
        value = json.loads(path.read_text(encoding="utf-8-sig"))
    except FileNotFoundError as exc:
        raise OmegaError(f"Missing file: {path}") from exc
    except json.JSONDecodeError as exc:
        raise OmegaError(f"Invalid JSON in {path}: {exc}") from exc
    if not isinstance(value, dict):
        raise OmegaError(f"Root must be an object: {path}")
    return value


def require(value: dict[str, Any], fields: list[str], context: str) -> None:
    missing = [field for field in fields if field not in value]
    if missing:
        raise OmegaError(f"{context} missing fields: {', '.join(missing)}")


def validate_definition(
    challenge: dict[str, Any], scoring: dict[str, Any], schema: dict[str, Any]
) -> None:
    require(
        challenge,
        [
            "schema",
            "benchmark_id",
            "name",
            "mode",
            "objective",
            "rounds",
            "public_system",
            "hidden_generation",
            "hard_gates",
            "score_domains",
            "pass_thresholds",
        ],
        "challenge",
    )
    if challenge["schema"] != "project-athena.aio.omega.challenge.v0.1":
        raise OmegaError("Unsupported challenge schema")
    if challenge["benchmark_id"] != "AIO-OMEGA-001":
        raise OmegaError("Unexpected benchmark id")

    expected_rounds = [f"R{i}" for i in range(9)]
    round_ids = [round_def.get("id") for round_def in challenge["rounds"]]
    if round_ids != expected_rounds:
        raise OmegaError(f"Rounds must be ordered {expected_rounds}")
    if not all(round_def.get("required") is True for round_def in challenge["rounds"]):
        raise OmegaError("Every OMEGA round must be required")
    if challenge["public_system"].get("minimum_candidates", 0) < 10:
        raise OmegaError("OMEGA requires at least ten candidates")
    if challenge["hidden_generation"].get("solver_access") != "forbidden":
        raise OmegaError("Hidden truth must be inaccessible to the solver")

    required_gates = {
        "no_hidden_truth_access",
        "no_evidence_fabrication",
        "all_21_aio_phases_nonzero",
        "valid_parent_hashes",
        "human_authority_preserved",
        "rollback_for_consequential_changes",
        "manual_operating_path",
        "explicit_new_branch_when_assumptions_change",
    }
    gates = set(challenge["hard_gates"])
    if not required_gates <= gates:
        raise OmegaError(f"Missing hard gates: {sorted(required_gates - gates)}")

    require(
        scoring,
        ["schema", "benchmark_id", "total_points", "hard_gates", "domains", "metrics", "anti_gaming"],
        "scoring",
    )
    if scoring["schema"] != "project-athena.aio.omega.scoring.v0.1":
        raise OmegaError("Unsupported scoring schema")
    if scoring["benchmark_id"] != challenge["benchmark_id"]:
        raise OmegaError("Scoring benchmark id mismatch")
    total = sum(int(domain.get("points", 0)) for domain in scoring["domains"])
    if total != int(scoring["total_points"]) or total != 100:
        raise OmegaError(f"Score domains must total 100, got {total}")
    if set(scoring["hard_gates"]) != gates:
        raise OmegaError("Challenge and scoring hard gates differ")

    anti_gaming = scoring["anti_gaming"]
    for key in (
        "secret_seeds",
        "held_out_scenario_families",
        "outcome_scoring_not_exact_text",
        "solver_cannot_read_hidden_pack",
        "multiple_stochastic_replays",
    ):
        if anti_gaming.get(key) is not True:
            raise OmegaError(f"Anti-gaming control must be enabled: {key}")

    Draft202012Validator.check_schema(schema)
    if schema.get("$id") != "project-athena.aio.omega.submission.schema.v0.1":
        raise OmegaError("Unexpected submission schema id")


def validate_submission(submission: dict[str, Any], schema: dict[str, Any]) -> None:
    Draft202012Validator(schema).validate(submission)
    phases = submission.get("aio_instance", {}).get("pipeline_state", {}).get("phases", [])
    if [phase.get("id") for phase in phases] != [f"P{i:02d}" for i in range(21)]:
        raise OmegaError("Submission must preserve all ordered AIO phases P00-P20")
    if any(float(phase.get("effective_depth", 0)) <= 0 for phase in phases):
        raise OmegaError("No AIO phase may have zero depth")
    if len(submission["candidate_lattice"]["candidates"]) < 10:
        raise OmegaError("Submission must include at least ten candidates")
    if submission["human_intervention"].get("rejected_branch_preserved") is not True:
        raise OmegaError("Human intervention must preserve the rejected branch")
    if not submission["technology_adoption"].get("archived_path"):
        raise OmegaError("Technology adoption must preserve the archived path")


def main() -> int:
    parser = argparse.ArgumentParser(description="AIO OMEGA benchmark validator")
    sub = parser.add_subparsers(dest="command", required=True)

    definition = sub.add_parser("validate-definition")
    definition.add_argument("--challenge", type=Path, required=True)
    definition.add_argument("--scoring", type=Path, required=True)
    definition.add_argument("--schema", type=Path, required=True)

    submission_parser = sub.add_parser("validate-submission")
    submission_parser.add_argument("--submission", type=Path, required=True)
    submission_parser.add_argument("--schema", type=Path, required=True)

    args = parser.parse_args()
    try:
        schema = load_json(args.schema)
        if args.command == "validate-definition":
            validate_definition(load_json(args.challenge), load_json(args.scoring), schema)
            print("PASS: AIO OMEGA benchmark definition valid")
        else:
            validate_submission(load_json(args.submission), schema)
            print("PASS: AIO OMEGA submission structurally valid")
        return 0
    except Exception as exc:
        print(f"FAIL: {exc}", file=sys.stderr)
        return 2


if __name__ == "__main__":
    raise SystemExit(main())
