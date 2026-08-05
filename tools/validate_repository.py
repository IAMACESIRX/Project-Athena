#!/usr/bin/env python3
"""Validate Project Athena's machine-readable structure and repository hygiene."""

from __future__ import annotations

import argparse
import csv
import json
import pathlib
import re
import sys
from dataclasses import dataclass, field
from typing import Any, Iterable

import yaml
from jsonschema import Draft202012Validator
from jsonschema.exceptions import SchemaError


REQUIRED_PATHS = (
    "AI-PORTAL.md",
    "README.md",
    "START-HERE.md",
    "context.md",
    "Plan/context.md",
    "manifests/system-manifest.json",
    "manifests/ingestion-order.yml",
    "memory/athena-memory-map.md",
    "engine/order-of-operations.md",
    "governance/absolutes.md",
    "governance/cloud-publication-policy.md",
    "cognition/anti-hallucination/anti-hallucination-protocol.md",
    "schemas/athena-task-intake.schema.json",
    "work/TODO.md",
    "council/roles.yml",
    ".gitignore",
    "LICENSE",
    ".github/workflows/repository-integrity.yml",
)

CANONICAL_DOCS = (
    "AI-PORTAL.md",
    "README.md",
    "START-HERE.md",
    "context.md",
    "memory/athena-memory-map.md",
)

PATH_TOKEN = re.compile(
    r"`((?:[A-Za-z0-9_. -]+/)+[A-Za-z0-9_.() -]+(?:\.[A-Za-z0-9]+)?)`"
)


@dataclass
class ValidationReport:
    root: pathlib.Path
    errors: list[str] = field(default_factory=list)
    warnings: list[str] = field(default_factory=list)
    counts: dict[str, int] = field(default_factory=dict)

    def error(self, message: str) -> None:
        self.errors.append(message)

    def warn(self, message: str) -> None:
        self.warnings.append(message)

    def write(self, path: pathlib.Path) -> None:
        path.parent.mkdir(parents=True, exist_ok=True)
        payload = {
            "schema": "project-athena.repository-integrity.v1",
            "root": str(self.root),
            "status": "FAIL" if self.errors else ("WARN" if self.warnings else "PASS"),
            "counts": self.counts,
            "errors": self.errors,
            "warnings": self.warnings,
        }
        path.write_text(json.dumps(payload, indent=2) + "\n", encoding="utf-8")


def iter_files(root: pathlib.Path, suffixes: Iterable[str]) -> Iterable[pathlib.Path]:
    ignored_parts = {".git", ".venv", "venv", "__pycache__", "obj_dir", "build"}
    for path in root.rglob("*"):
        if not path.is_file():
            continue
        if ignored_parts.intersection(path.parts):
            continue
        if path.suffix.lower() in suffixes:
            yield path


def relative(path: pathlib.Path, root: pathlib.Path) -> str:
    return path.relative_to(root).as_posix()


def validate_required_paths(report: ValidationReport) -> None:
    for item in REQUIRED_PATHS:
        if not (report.root / item).exists():
            report.error(f"Missing required path: {item}")


def validate_json(report: ValidationReport) -> None:
    count = 0
    schema_count = 0
    for path in iter_files(report.root, {".json"}):
        count += 1
        try:
            value = json.loads(path.read_text(encoding="utf-8-sig"))
        except (OSError, UnicodeError, json.JSONDecodeError) as exc:
            report.error(f"Invalid JSON {relative(path, report.root)}: {exc}")
            continue

        if path.name.endswith(".schema.json") or (
            isinstance(value, dict) and "$schema" in value and "$id" in value
        ):
            schema_count += 1
            try:
                Draft202012Validator.check_schema(value)
            except SchemaError as exc:
                report.error(
                    f"Invalid JSON Schema {relative(path, report.root)}: {exc.message}"
                )

    report.counts["json_files"] = count
    report.counts["json_schemas"] = schema_count


def validate_yaml(report: ValidationReport) -> None:
    count = 0
    for path in iter_files(report.root, {".yml", ".yaml"}):
        count += 1
        try:
            list(yaml.safe_load_all(path.read_text(encoding="utf-8-sig")))
        except (OSError, UnicodeError, yaml.YAMLError) as exc:
            report.error(f"Invalid YAML {relative(path, report.root)}: {exc}")
    report.counts["yaml_files"] = count


def validate_csv_headers(report: ValidationReport) -> None:
    targets = (
        "forensics/evidence-register.csv",
        "forensics/claim-catalog.csv",
        "forensics/evidence-claim-map.csv",
    )
    checked = 0
    for item in targets:
        path = report.root / item
        if not path.exists():
            report.warn(f"Expected forensic ledger is missing: {item}")
            continue
        try:
            with path.open("r", encoding="utf-8-sig", newline="") as handle:
                reader = csv.reader(handle)
                header = next(reader, [])
        except (OSError, UnicodeError, csv.Error) as exc:
            report.error(f"Unreadable CSV {item}: {exc}")
            continue
        checked += 1
        if not header or any(not cell.strip() for cell in header):
            report.error(f"CSV has an empty or invalid header: {item}")
    report.counts["forensic_csv_ledgers_checked"] = checked


def validate_canonical_path_references(report: ValidationReport) -> None:
    checked = 0
    for item in CANONICAL_DOCS:
        path = report.root / item
        if not path.exists():
            continue
        text = path.read_text(encoding="utf-8-sig")
        for match in PATH_TOKEN.finditer(text):
            token = match.group(1)
            if any(marker in token for marker in ("*", "{", "}", "<", ">")):
                continue
            if token.startswith(("http://", "https://")):
                continue
            checked += 1
            candidate = report.root / token
            if not candidate.exists():
                report.warn(f"Unresolved path reference in {item}: {token}")
    report.counts["canonical_path_references_checked"] = checked


def validate_manifest_policy(report: ValidationReport) -> None:
    path = report.root / "manifests/system-manifest.json"
    if not path.exists():
        return
    try:
        manifest: dict[str, Any] = json.loads(path.read_text(encoding="utf-8-sig"))
    except (OSError, UnicodeError, json.JSONDecodeError):
        return

    project = manifest.get("project", {})
    if project.get("cloud_push_allowed") is not False:
        report.error("Manifest must preserve default-deny cloud_push_allowed=false.")

    policy_path = project.get("cloud_publication_policy")
    if not policy_path:
        report.error("Manifest does not declare project.cloud_publication_policy.")
    elif not (report.root / str(policy_path)).exists():
        report.error(f"Manifest cloud publication policy does not exist: {policy_path}")


def main() -> int:
    parser = argparse.ArgumentParser()
    parser.add_argument("--root", default=".")
    parser.add_argument(
        "--report",
        default="artifacts/repository-integrity.json",
        help="Path relative to root unless absolute.",
    )
    args = parser.parse_args()

    root = pathlib.Path(args.root).resolve()
    report_path = pathlib.Path(args.report)
    if not report_path.is_absolute():
        report_path = root / report_path

    report = ValidationReport(root=root)
    validate_required_paths(report)
    validate_json(report)
    validate_yaml(report)
    validate_csv_headers(report)
    validate_canonical_path_references(report)
    validate_manifest_policy(report)
    report.write(report_path)

    for warning in report.warnings:
        print(f"WARNING: {warning}", file=sys.stderr)
    for error in report.errors:
        print(f"ERROR: {error}", file=sys.stderr)

    print(
        json.dumps(
            {
                "status": "FAIL" if report.errors else "PASS",
                "errors": len(report.errors),
                "warnings": len(report.warnings),
                "report": str(report_path),
            },
            indent=2,
        )
    )
    return 1 if report.errors else 0


if __name__ == "__main__":
    raise SystemExit(main())
