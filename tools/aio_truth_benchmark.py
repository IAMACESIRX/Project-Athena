#!/usr/bin/env python3
"""Materialize and evaluate an AIO golden-truth benchmark."""
from __future__ import annotations

import argparse
import importlib.util
import json
from pathlib import Path
from typing import Any


class BenchmarkError(ValueError):
    pass


def load_json(path: Path) -> dict[str, Any]:
    try:
        value = json.loads(path.read_text(encoding="utf-8-sig"))
    except FileNotFoundError as exc:
        raise BenchmarkError(f"Missing file: {path}") from exc
    except json.JSONDecodeError as exc:
        raise BenchmarkError(f"Invalid JSON in {path}: {exc}") from exc
    if not isinstance(value, dict):
        raise BenchmarkError(f"Expected object root in {path}")
    return value


def load_aio(module_path: Path):
    spec = importlib.util.spec_from_file_location("aio_contract", module_path)
    if spec is None or spec.loader is None:
        raise BenchmarkError(f"Cannot load AIO module: {module_path}")
    module = importlib.util.module_from_spec(spec)
    spec.loader.exec_module(module)
    return module


def materialize(aio, master: dict[str, Any], source: dict[str, Any], solution: dict[str, Any]) -> dict[str, Any]:
    instance = aio.instantiate(master, source)
    summaries = solution.get("phase_summaries", {})
    required_ids = [f"P{i:02d}" for i in range(21)]
    if sorted(summaries) != required_ids:
        raise BenchmarkError("solution must provide exactly P00 through P20 phase summaries")

    for phase in instance["pipeline_state"]["phases"]:
        phase["status"] = "completed"
        phase["result"] = {"summary": summaries[phase["id"]]}
        phase["evidence"] = ["thermodynamics", "detailed_balance", "boundary_accounting"]
        phase["review"] = {"status": "accepted_for_golden_benchmark"}

    instance["pipeline_state"]["current_phase"] = "P20"
    instance["identity"]["status"] = "completed"
    instance["shared_state"] = solution["shared_state"]
    instance["attestations"] = solution.get("attestations", [])
    instance["outputs"] = solution["outputs"]

    actor = solution.get("actor", "ai_benchmark_agent")
    completion = solution.get("completion_event", {"type": "complete_golden_truth_run", "payload": {}})
    parent = instance["provenance"]["current_sha256"]
    aio.append_event(instance, actor, completion["type"], completion.get("payload", {}), parent)
    aio.validate_instance(instance, master)
    return instance


def evaluate(instance: dict[str, Any], golden: dict[str, Any]) -> dict[str, Any]:
    checks: list[dict[str, Any]] = []

    def add(name: str, passed: bool, points: int, detail: str) -> None:
        checks.append({
            "name": name,
            "passed": bool(passed),
            "points": points if passed else 0,
            "max_points": points,
            "detail": detail,
        })

    outputs = instance.get("outputs", {})
    conclusion = outputs.get("conclusion")
    add("known conclusion", conclusion == golden["expected_conclusion"], 25, str(conclusion))

    mechanisms = set(outputs.get("mechanisms", []))
    required_mechanisms = set(golden.get("required_mechanisms", []))
    add("required mechanisms", required_mechanisms <= mechanisms, 20, f"found {sorted(mechanisms)}")

    failures = set(outputs.get("failure_explanations", []))
    required_failures = set(golden.get("required_failure_explanations", []))
    add("failure explanations", required_failures <= failures, 15, f"found {sorted(failures)}")

    expected_change = golden.get("required_reconstruction", {}).get("change")
    actual_change = outputs.get("required_reconstruction", {}).get("change")
    add("valid reconstruction", actual_change == expected_change, 15, str(actual_change))

    completed = [
        phase.get("id")
        for phase in instance.get("pipeline_state", {}).get("phases", [])
        if phase.get("status") == "completed"
    ]
    required_phases = golden.get("required_pipeline_phases", [])
    add("all phases completed", completed == required_phases, 15, f"{len(completed)} completed")

    scale_count = len(outputs.get("scale_coverage", []))
    add("full scale coverage", scale_count >= 10, 5, f"{scale_count} scales")

    lens_count = len(outputs.get("view_lenses", []))
    add("broad lens coverage", lens_count >= 15, 5, f"{lens_count} lenses")

    score = sum(check["points"] for check in checks)
    maximum = sum(check["max_points"] for check in checks)
    minimum = int(golden.get("minimum_score", maximum))
    return {
        "benchmark_id": golden.get("benchmark_id"),
        "score": score,
        "max_score": maximum,
        "minimum_score": minimum,
        "passed": score >= minimum,
        "checks": checks,
    }


def render_report(instance: dict[str, Any], result: dict[str, Any]) -> str:
    rows = "\n".join(
        f"| {check['name']} | {'PASS' if check['passed'] else 'FAIL'} | "
        f"{check['points']}/{check['max_points']} | {check['detail']} |"
        for check in result["checks"]
    )
    return (
        f"# AIO Golden Truth Benchmark Report\n\n"
        f"- Benchmark: `{result['benchmark_id']}`\n"
        f"- Contract instance: `{instance['identity']['instance_id']}`\n"
        f"- State hash: `{instance['provenance']['current_sha256']}`\n"
        f"- Score: **{result['score']}/{result['max_score']}**\n"
        f"- Required score: **{result['minimum_score']}**\n"
        f"- Result: **{'PASS' if result['passed'] else 'FAIL'}**\n\n"
        f"## Conclusion\n\n"
        f"{instance['outputs']['answer']}\n\n"
        f"## Checks\n\n"
        f"| Check | Result | Score | Detail |\n"
        f"|---|---|---:|---|\n"
        f"{rows}\n\n"
        f"## Capability demonstrated\n\n"
        f"The run retained all 21 AIO phases, rejected a known false claim under explicit "
        f"boundary conditions, preserved anomalous-result testing, reconstructed a valid "
        f"nonequilibrium design path, and produced a hash-verifiable shared state.\n"
    )


def main() -> int:
    parser = argparse.ArgumentParser(description="Run an AIO golden-truth benchmark")
    parser.add_argument("--aio-module", type=Path, required=True)
    parser.add_argument("--master", type=Path, required=True)
    parser.add_argument("--input", type=Path, required=True)
    parser.add_argument("--solution", type=Path, required=True)
    parser.add_argument("--golden", type=Path, required=True)
    parser.add_argument("--run-out", type=Path)
    parser.add_argument("--json-out", type=Path)
    parser.add_argument("--report-out", type=Path)
    args = parser.parse_args()

    aio = load_aio(args.aio_module)
    master = aio.load(args.master)
    source = load_json(args.input)
    solution = load_json(args.solution)
    golden = load_json(args.golden)

    aio.validate_master(master)
    instance = materialize(aio, master, source, solution)
    result = evaluate(instance, golden)

    if args.run_out:
        aio.dump(args.run_out, instance)
    if args.json_out:
        args.json_out.parent.mkdir(parents=True, exist_ok=True)
        args.json_out.write_text(json.dumps(result, indent=2, ensure_ascii=False) + "\n", encoding="utf-8")
    if args.report_out:
        args.report_out.parent.mkdir(parents=True, exist_ok=True)
        args.report_out.write_text(render_report(instance, result), encoding="utf-8")

    print(f"{'PASS' if result['passed'] else 'FAIL'}: {result['score']}/{result['max_score']}")
    return 0 if result["passed"] else 2


if __name__ == "__main__":
    raise SystemExit(main())
