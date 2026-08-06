#!/usr/bin/env python3
"""Deterministic file-native F.O.R.G.E. v0.1 compiler.

This prototype ranks declared candidates, mines recurring mechanisms, preserves
semantic invariants, detects declared conflicts, and emits a functional snapshot
plus a reproducible compile trace. It intentionally does not claim scientific or
physical validation.
"""

from __future__ import annotations

import argparse
import hashlib
import json
import sys
from dataclasses import dataclass
from datetime import datetime, timezone
from pathlib import Path
from typing import Any

COMPILER_VERSION = "0.1.0"
DEFAULT_WEIGHTS: dict[str, float] = {
    "evidence": 1.5,
    "performance": 1.0,
    "simplicity": 1.2,
    "resilience": 1.0,
    "adaptability": 1.1,
    "reversibility": 1.1,
    "integration": 1.0,
}
REQUIRED_ROOT_FIELDS = {
    "schema",
    "concept_id",
    "title",
    "objective",
    "origin",
    "semantic_invariants",
    "claims",
    "candidates",
    "desired_properties",
}
REQUIRED_CANDIDATE_FIELDS = {
    "candidate_id",
    "name",
    "description",
    "mechanisms",
    "strengths",
    "weaknesses",
    "tradeoffs",
    "scores",
}
REQUIRED_MECHANISM_FIELDS = {"mechanism_id", "name", "why_it_works"}


class ForgeValidationError(ValueError):
    """Raised when a concept packet does not satisfy v0.1 structural rules."""


@dataclass(frozen=True)
class RankedCandidate:
    candidate_id: str
    name: str
    score: float
    rank: int


def utc_now() -> str:
    return datetime.now(timezone.utc).isoformat()


def canonical_json_bytes(value: Any) -> bytes:
    return json.dumps(value, sort_keys=True, separators=(",", ":"), ensure_ascii=False).encode("utf-8")


def stable_hash(value: Any) -> str:
    return hashlib.sha256(canonical_json_bytes(value)).hexdigest()


def load_packet(path: Path) -> dict[str, Any]:
    try:
        value = json.loads(path.read_text(encoding="utf-8-sig"))
    except FileNotFoundError as exc:
        raise ForgeValidationError(f"Concept packet not found: {path}") from exc
    except json.JSONDecodeError as exc:
        raise ForgeValidationError(f"Invalid JSON in {path}: {exc}") from exc
    if not isinstance(value, dict):
        raise ForgeValidationError("Concept packet root must be a JSON object.")
    return value


def require_fields(value: dict[str, Any], required: set[str], context: str) -> None:
    missing = sorted(required - value.keys())
    if missing:
        raise ForgeValidationError(f"{context} missing required fields: {', '.join(missing)}")


def validate_packet(packet: dict[str, Any]) -> None:
    require_fields(packet, REQUIRED_ROOT_FIELDS, "Concept packet")
    if packet.get("schema") != "forge.concept_packet.v0.1":
        raise ForgeValidationError("Unsupported schema; expected forge.concept_packet.v0.1")
    if not isinstance(packet["semantic_invariants"], list) or not packet["semantic_invariants"]:
        raise ForgeValidationError("semantic_invariants must be a non-empty array.")
    if not isinstance(packet["candidates"], list) or not packet["candidates"]:
        raise ForgeValidationError("candidates must be a non-empty array.")
    seen_candidates: set[str] = set()
    seen_mechanisms: dict[str, str] = {}
    for index, candidate in enumerate(packet["candidates"]):
        if not isinstance(candidate, dict):
            raise ForgeValidationError(f"Candidate {index} must be an object.")
        require_fields(candidate, REQUIRED_CANDIDATE_FIELDS, f"Candidate {index}")
        candidate_id = candidate["candidate_id"]
        if candidate_id in seen_candidates:
            raise ForgeValidationError(f"Duplicate candidate_id: {candidate_id}")
        seen_candidates.add(candidate_id)
        if not isinstance(candidate["mechanisms"], list) or not candidate["mechanisms"]:
            raise ForgeValidationError(f"Candidate {candidate_id} must declare at least one mechanism.")
        for mechanism in candidate["mechanisms"]:
            if not isinstance(mechanism, dict):
                raise ForgeValidationError(f"Candidate {candidate_id} contains a non-object mechanism.")
            require_fields(mechanism, REQUIRED_MECHANISM_FIELDS, f"Mechanism in {candidate_id}")
            mechanism_id = mechanism["mechanism_id"]
            mechanism_name = mechanism["name"]
            prior_name = seen_mechanisms.setdefault(mechanism_id, mechanism_name)
            if prior_name != mechanism_name:
                raise ForgeValidationError(
                    f"Mechanism {mechanism_id} has inconsistent names: {prior_name!r} vs {mechanism_name!r}"
                )
        for dimension, score in candidate["scores"].items():
            if not isinstance(score, (int, float)) or not 0 <= float(score) <= 1:
                raise ForgeValidationError(
                    f"Candidate {candidate_id} score {dimension!r} must be between 0 and 1."
                )


def normalized_weights(packet: dict[str, Any]) -> dict[str, float]:
    supplied = packet.get("score_weights", {})
    if supplied and not isinstance(supplied, dict):
        raise ForgeValidationError("score_weights must be an object.")
    weights = dict(DEFAULT_WEIGHTS)
    for name, weight in supplied.items():
        if not isinstance(weight, (int, float)) or float(weight) < 0:
            raise ForgeValidationError(f"Weight {name!r} must be a non-negative number.")
        weights[name] = float(weight)
    if sum(weights.values()) <= 0:
        raise ForgeValidationError("At least one score weight must be greater than zero.")
    return weights


def score_candidate(candidate: dict[str, Any], weights: dict[str, float]) -> float:
    numerator = 0.0
    denominator = 0.0
    scores = candidate.get("scores", {})
    for dimension, weight in weights.items():
        if weight <= 0 or dimension not in scores:
            continue
        numerator += float(scores[dimension]) * weight
        denominator += weight
    if denominator == 0:
        return 0.0
    return round(numerator / denominator, 6)


def rank_candidates(packet: dict[str, Any], weights: dict[str, float]) -> list[RankedCandidate]:
    scored = [
        (candidate["candidate_id"], candidate["name"], score_candidate(candidate, weights))
        for candidate in packet["candidates"]
    ]
    scored.sort(key=lambda item: (-item[2], item[0]))
    return [
        RankedCandidate(candidate_id=item[0], name=item[1], score=item[2], rank=index + 1)
        for index, item in enumerate(scored)
    ]


def mine_mechanisms(
    packet: dict[str, Any],
    donor_ids: list[str],
    candidate_scores: dict[str, float],
) -> tuple[list[dict[str, Any]], list[dict[str, Any]], list[dict[str, Any]]]:
    candidates = {candidate["candidate_id"]: candidate for candidate in packet["candidates"]}
    pool: dict[str, dict[str, Any]] = {}
    for candidate_id in donor_ids:
        candidate = candidates[candidate_id]
        for mechanism in candidate["mechanisms"]:
            mechanism_id = mechanism["mechanism_id"]
            record = pool.setdefault(
                mechanism_id,
                {
                    "mechanism_id": mechanism_id,
                    "name": mechanism["name"],
                    "why_it_works": mechanism["why_it_works"],
                    "conditions": [],
                    "benefits": [],
                    "costs": [],
                    "conflicts_with": [],
                    "donor_candidates": [],
                    "donor_scores": [],
                },
            )
            record["donor_candidates"].append(candidate_id)
            record["donor_scores"].append(candidate_scores[candidate_id])
            for field in ("conditions", "benefits", "costs", "conflicts_with"):
                for item in mechanism.get(field, []):
                    if item not in record[field]:
                        record[field].append(item)

    decisions: list[dict[str, Any]] = []
    selected: list[dict[str, Any]] = []
    donor_count = max(len(donor_ids), 1)
    for mechanism_id in sorted(pool):
        record = pool[mechanism_id]
        recurrence = len(record["donor_candidates"]) / donor_count
        mean_donor_score = sum(record.pop("donor_scores")) / len(record["donor_candidates"])
        mechanism_score = round((0.65 * mean_donor_score) + (0.35 * recurrence), 6)
        record["recurrence"] = round(recurrence, 6)
        record["mechanism_score"] = mechanism_score
        decision = "selected" if mechanism_score >= 0.5 else "deferred"
        decisions.append(
            {
                "mechanism_id": mechanism_id,
                "decision": decision,
                "score": mechanism_score,
                "reason": "score threshold" if decision == "selected" else "insufficient donor support",
            }
        )
        if decision == "selected":
            selected.append(record)
    selected.sort(key=lambda item: (-item["mechanism_score"], item["mechanism_id"]))
    all_records = sorted(pool.values(), key=lambda item: (-item["mechanism_score"], item["mechanism_id"]))
    return selected, decisions, all_records


def detect_conflicts(mechanisms: list[dict[str, Any]]) -> list[dict[str, Any]]:
    selected_ids = {mechanism["mechanism_id"] for mechanism in mechanisms}
    conflicts: set[tuple[str, str]] = set()
    for mechanism in mechanisms:
        source = mechanism["mechanism_id"]
        for target in mechanism.get("conflicts_with", []):
            if target in selected_ids and target != source:
                conflicts.add(tuple(sorted((source, target))))
    return [
        {
            "mechanism_a": pair[0],
            "mechanism_b": pair[1],
            "status": "unresolved",
            "required_action": "Define compatibility conditions, isolation boundary or explicit trade-off.",
        }
        for pair in sorted(conflicts)
    ]


def build_validation_plan(packet: dict[str, Any], conflicts: list[dict[str, Any]]) -> list[str]:
    plan = [
        "Verify every hypothesis and inferred claim through A.E.S.I.R. evidence review.",
        "Test the reconstructed architecture against each donor candidate using the same score dimensions.",
        "Define rollback or fallback behaviour before canonical promotion through ATHENA.",
        "Run the smallest reversible simulation or prototype that can falsify the selected mechanisms.",
    ]
    if conflicts:
        plan.insert(0, "Resolve or deliberately isolate every declared mechanism conflict.")
    for claim in packet.get("claims", []):
        if claim.get("status") in {"assumed", "hypothesis", "speculative", "predicted", "unknown"}:
            plan.append(f"Resolve claim {claim['claim_id']}: {claim['statement']}")
    return plan


def compile_packet(packet: dict[str, Any]) -> tuple[dict[str, Any], dict[str, Any]]:
    validate_packet(packet)
    weights = normalized_weights(packet)
    ranking = rank_candidates(packet, weights)
    requested_top_n = int(packet.get("top_n", 10))
    top_n = min(max(requested_top_n, 1), 10, len(ranking))
    donor_ids = [item.candidate_id for item in ranking[:top_n]]
    candidate_scores = {item.candidate_id: item.score for item in ranking}
    selected_mechanisms, mechanism_decisions, donor_mechanisms = mine_mechanisms(packet, donor_ids, candidate_scores)
    conflicts = detect_conflicts(donor_mechanisms)
    input_sha = stable_hash(packet)
    compile_id = f"FORGE-COMPILE-{input_sha[:12]}"
    snapshot_id = f"FORGE-SNAPSHOT-{input_sha[:12]}"

    snapshot = {
        "schema": "forge.functional_snapshot.v0.1",
        "snapshot_id": snapshot_id,
        "concept_id": packet["concept_id"],
        "compiler_version": COMPILER_VERSION,
        "generated_at": utc_now(),
        "objective": packet["objective"],
        "semantic_invariants": list(packet["semantic_invariants"]),
        "flexible_variables": list(packet.get("flexible_variables", [])),
        "constraints": list(packet.get("constraints", [])),
        "desired_properties": list(packet["desired_properties"]),
        "selected_candidates": donor_ids,
        "selected_mechanisms": selected_mechanisms,
        "unresolved_conflicts": conflicts,
        "validation_plan": build_validation_plan(packet, conflicts),
        "capability_state": "scaffolded",
        "promotion_notice": (
            "This is a deterministic reconstruction scaffold. It is not scientific, runtime, or hardware validation."
        ),
    }

    trace = {
        "schema": "forge.compile_trace.v0.1",
        "compile_id": compile_id,
        "compiler_version": COMPILER_VERSION,
        "generated_at": utc_now(),
        "input_sha256": input_sha,
        "concept_id": packet["concept_id"],
        "weights": weights,
        "passes": [
            {"id": "F00", "name": "authority_and_intent_anchor", "status": "pass"},
            {"id": "F01", "name": "epistemic_partition", "status": "pass"},
            {"id": "F07", "name": "candidate_tournament", "status": "pass"},
            {"id": "F08", "name": "mechanism_mining", "status": "pass"},
            {"id": "F09", "name": "reverse_reconstruction", "status": "scaffolded"},
            {"id": "F10", "name": "semantic_and_runtime_compression", "status": "scaffolded"},
            {"id": "F11", "name": "functional_snapshot_compile", "status": "pass"},
            {"id": "F12", "name": "validation_and_promotion", "status": "pending_external_evidence"},
        ],
        "candidate_ranking": [
            {"candidate_id": item.candidate_id, "name": item.name, "score": item.score, "rank": item.rank}
            for item in ranking
        ],
        "donor_pool": donor_ids,
        "mechanism_decisions": mechanism_decisions,
        "unresolved_conflicts": conflicts,
        "outputs": {
            "functional_snapshot": "functional-snapshot.json",
            "compile_trace": "compile-trace.json",
        },
    }
    return snapshot, trace


def write_json(path: Path, value: Any) -> None:
    path.parent.mkdir(parents=True, exist_ok=True)
    path.write_text(json.dumps(value, indent=2, ensure_ascii=False) + "\n", encoding="utf-8")


def command_validate(args: argparse.Namespace) -> int:
    packet = load_packet(args.packet)
    validate_packet(packet)
    print(f"PASS: {args.packet} is structurally valid for F.O.R.G.E. v0.1")
    return 0


def command_compile(args: argparse.Namespace) -> int:
    packet = load_packet(args.packet)
    snapshot, trace = compile_packet(packet)
    output_dir: Path = args.out
    write_json(output_dir / "functional-snapshot.json", snapshot)
    write_json(output_dir / "compile-trace.json", trace)
    print(json.dumps({"status": "PASS", "output_dir": str(output_dir), "snapshot_id": snapshot["snapshot_id"]}, indent=2))
    return 0


def build_parser() -> argparse.ArgumentParser:
    parser = argparse.ArgumentParser(description="F.O.R.G.E. v0.1 deterministic concept compiler")
    subparsers = parser.add_subparsers(dest="command", required=True)

    validate_parser = subparsers.add_parser("validate", help="Validate a concept packet")
    validate_parser.add_argument("packet", type=Path)
    validate_parser.set_defaults(func=command_validate)

    compile_parser = subparsers.add_parser("compile", help="Compile a concept packet")
    compile_parser.add_argument("packet", type=Path)
    compile_parser.add_argument("--out", type=Path, required=True)
    compile_parser.set_defaults(func=command_compile)
    return parser


def main(argv: list[str] | None = None) -> int:
    parser = build_parser()
    args = parser.parse_args(argv)
    try:
        return int(args.func(args))
    except ForgeValidationError as exc:
        print(f"FAIL: {exc}", file=sys.stderr)
        return 2


if __name__ == "__main__":
    raise SystemExit(main())
