#!/usr/bin/env python3
"""Validate Project Athena's machine-readable structure and repository hygiene."""

from __future__ import annotations

import argparse
import csv
import fnmatch
import json
import pathlib
import re
import sys
from dataclasses import dataclass, field
from typing import Any, Iterable

import yaml
from jsonschema import Draft202012Validator
from jsonschema.exceptions import SchemaError, ValidationError


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
    "governance/publication-gate.yml",
    "cognition/anti-hallucination/anti-hallucination-protocol.md",
    "schemas/publication-gate.schema.json",
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

PUBLICATION_GATE_PATH = "governance/publication-gate.yml"
PUBLICATION_GATE_SCHEMA_PATH = "schemas/publication-gate.schema.json"

DEFAULT_IGNORED_PATH_PATTERNS = (
    "artifacts/",
    "continuity/transcript-inbox/imports/",
    "continuity/chat-repository-sync/generated/",
    "continuity/chat-repository-sync/cache/",
    "continuity/chat-repository-sync/exports/",
    "continuity/chat-repository-sync/source-bundles/",
)

TEXT_SCAN_SUFFIXES = {
    ".bat",
    ".cmd",
    ".conf",
    ".csv",
    ".css",
    ".f",
    ".html",
    ".ini",
    ".js",
    ".json",
    ".jsonl",
    ".md",
    ".ps1",
    ".py",
    ".sh",
    ".sv",
    ".toml",
    ".ts",
    ".txt",
    ".v",
    ".xml",
    ".yaml",
    ".yml",
}


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


def relative(path: pathlib.Path, root: pathlib.Path) -> str:
    return path.relative_to(root).as_posix()


def matches_path_pattern(rel_path: str, pattern: str) -> bool:
    pattern = pattern.replace("\\", "/")
    if pattern.endswith("/"):
        prefix = pattern.rstrip("/") + "/"
        return rel_path == pattern.rstrip("/") or rel_path.startswith(prefix)
    return rel_path == pattern or fnmatch.fnmatch(rel_path, pattern)


def is_ignored_path(
    path: pathlib.Path,
    root: pathlib.Path,
    extra_patterns: Iterable[str] = (),
) -> bool:
    ignored_parts = {".git", ".venv", "venv", "__pycache__", "obj_dir", "build"}
    if ignored_parts.intersection(path.parts):
        return True
    rel_path = relative(path, root)
    return any(
        matches_path_pattern(rel_path, pattern)
        for pattern in (*DEFAULT_IGNORED_PATH_PATTERNS, *extra_patterns)
    )


def iter_files(root: pathlib.Path, suffixes: Iterable[str]) -> Iterable[pathlib.Path]:
    for path in root.rglob("*"):
        if not path.is_file():
            continue
        if is_ignored_path(path, root):
            continue
        if path.suffix.lower() in suffixes:
            yield path


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
            if any(marker in token for marker in ("*", "{", "}", "<", ">", "...")):
                continue
            if token.startswith(("http://", "https://", ".")):
                continue
            checked += 1
            candidates = (
                report.root / token,
                report.root / "Nexus V" / token,
                path.parent / token,
            )
            if not any(candidate.exists() for candidate in candidates):
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

    gate_path = project.get("publication_gate")
    if gate_path != PUBLICATION_GATE_PATH:
        report.error(
            f"Manifest project.publication_gate must be {PUBLICATION_GATE_PATH}."
        )
    elif not (report.root / str(gate_path)).exists():
        report.error(f"Manifest publication gate does not exist: {gate_path}")


def load_publication_gate(report: ValidationReport) -> dict[str, Any] | None:
    gate_path = report.root / PUBLICATION_GATE_PATH
    schema_path = report.root / PUBLICATION_GATE_SCHEMA_PATH
    if not gate_path.exists() or not schema_path.exists():
        return None

    try:
        gate = yaml.safe_load(gate_path.read_text(encoding="utf-8-sig"))
    except (OSError, UnicodeError, yaml.YAMLError) as exc:
        report.error(f"Invalid publication gate YAML: {exc}")
        return None

    try:
        schema = json.loads(schema_path.read_text(encoding="utf-8-sig"))
    except (OSError, UnicodeError, json.JSONDecodeError) as exc:
        report.error(f"Invalid publication gate schema JSON: {exc}")
        return None

    try:
        Draft202012Validator(schema).validate(gate)
    except ValidationError as exc:
        report.error(f"Publication gate does not match schema: {exc.message}")
        return None

    if not isinstance(gate, dict):
        report.error("Publication gate must be a mapping.")
        return None
    return gate


def validate_gitignore_covers_local_only_paths(
    report: ValidationReport, local_only_paths: list[str]
) -> None:
    gitignore_path = report.root / ".gitignore"
    if not gitignore_path.exists():
        return
    text = gitignore_path.read_text(encoding="utf-8-sig")
    entries = {
        line.strip().replace("\\", "/")
        for line in text.splitlines()
        if line.strip() and not line.lstrip().startswith("#")
    }
    for item in local_only_paths:
        normalized = item.replace("\\", "/")
        if normalized not in entries:
            report.error(f".gitignore does not cover local-only path: {normalized}")


def validate_required_publication_review(report: ValidationReport, gate: dict[str, Any]) -> None:
    required_review = gate.get("required_review", {})
    checklist_path = report.root / str(required_review.get("checklist_file", ""))
    heading = str(required_review.get("checklist_heading", ""))
    if not checklist_path.exists():
        report.error(f"Publication review checklist file is missing: {checklist_path}")
        return
    text = checklist_path.read_text(encoding="utf-8-sig")
    if heading not in text:
        report.error(f"Publication review checklist heading is missing: {heading}")


def iter_secret_scan_files(
    report: ValidationReport,
    local_only_paths: list[str],
) -> Iterable[pathlib.Path]:
    for path in report.root.rglob("*"):
        if not path.is_file():
            continue
        if is_ignored_path(path, report.root, local_only_paths):
            continue
        if path.name == ".gitignore" or path.suffix.lower() in TEXT_SCAN_SUFFIXES:
            yield path


def validate_secret_patterns(report: ValidationReport, gate: dict[str, Any]) -> None:
    local_only_paths = [
        str(item.get("path", ""))
        for item in gate.get("local_only_paths", [])
        if isinstance(item, dict)
    ]
    compiled: list[tuple[str, re.Pattern[str]]] = []
    for item in gate.get("secret_patterns", []):
        pattern_id = str(item.get("id", "unknown"))
        try:
            compiled.append((pattern_id, re.compile(str(item.get("regex", "")))))
        except re.error as exc:
            report.error(f"Invalid secret pattern {pattern_id}: {exc}")

    checked = 0
    matches = 0
    for path in iter_secret_scan_files(report, local_only_paths):
        rel_path = relative(path, report.root)
        try:
            text = path.read_text(encoding="utf-8-sig")
        except (OSError, UnicodeError):
            continue
        checked += 1
        for pattern_id, pattern in compiled:
            for match in pattern.finditer(text):
                line_no = text.count("\n", 0, match.start()) + 1
                matches += 1
                report.error(
                    f"Potential credential pattern {pattern_id} in {rel_path}:{line_no}"
                )

    report.counts["publication_secret_scan_files"] = checked
    report.counts["publication_secret_pattern_matches"] = matches


def validate_publication_gate(report: ValidationReport) -> None:
    gate = load_publication_gate(report)
    if gate is None:
        return

    canonical_policy = gate.get("canonical_policy")
    if not canonical_policy or not (report.root / str(canonical_policy)).exists():
        report.error(f"Publication gate canonical policy is missing: {canonical_policy}")

    local_only_paths = [
        str(item.get("path", ""))
        for item in gate.get("local_only_paths", [])
        if isinstance(item, dict)
    ]
    validate_gitignore_covers_local_only_paths(report, local_only_paths)
    validate_required_publication_review(report, gate)
    validate_secret_patterns(report, gate)
    report.counts["publication_local_only_paths"] = len(local_only_paths)


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
    validate_publication_gate(report)
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
