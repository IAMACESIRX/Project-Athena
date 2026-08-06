#!/usr/bin/env python3
"""CLI and local HTTP blind-solver service for AIO-OMEGA-001."""
from __future__ import annotations
import argparse, json, sys
from http import HTTPStatus
from http.server import BaseHTTPRequestHandler,ThreadingHTTPServer
from pathlib import Path
from typing import Any
TOOLS=Path(__file__).resolve().parent
if str(TOOLS) not in sys.path: sys.path.insert(0,str(TOOLS))
from aio_omega_common import *
from aio_omega_world import OmegaWorld
from aio_omega_session import OmegaSession
class OmegaHTTPHandler(BaseHTTPRequestHandler):
    session: OmegaSession
    token: str | None = None

    def _authorized(self) -> bool:
        return self.token is None or self.headers.get("Authorization") == f"Bearer {self.token}"

    def _json(self, status: int, payload: Any) -> None:
        body = json.dumps(payload, indent=2, ensure_ascii=False).encode("utf-8")
        self.send_response(status)
        self.send_header("Content-Type", "application/json")
        self.send_header("Content-Length", str(len(body)))
        self.end_headers()
        self.wfile.write(body)

    def do_GET(self) -> None:
        if not self._authorized():
            self._json(HTTPStatus.UNAUTHORIZED, {"error": "unauthorized"})
            return
        routes = {
            "/snapshot": self.session.public_snapshot,
            "/brief": lambda: read_json(self.session.paths.brief),
            "/evidence": lambda: read_json(self.session.paths.evidence),
            "/diagnostics": lambda: read_json(self.session.paths.diagnostic_catalog),
            "/state": lambda: read_json(self.session.paths.public / "state.json"),
            "/events": lambda: read_json(self.session.paths.event_stream),
        }
        try:
            if self.path not in routes:
                self._json(HTTPStatus.NOT_FOUND, {"error": "not_found"})
            else:
                self._json(HTTPStatus.OK, routes[self.path]())
        except OmegaRuntimeError as exc:
            self._json(HTTPStatus.BAD_REQUEST, {"error": str(exc)})

    def do_POST(self) -> None:
        if not self._authorized():
            self._json(HTTPStatus.UNAUTHORIZED, {"error": "unauthorized"})
            return
        length = int(self.headers.get("Content-Length", "0"))
        raw = self.rfile.read(length) if length else b"{}"
        try:
            payload = json.loads(raw)
            if self.path.startswith("/diagnostics/"):
                result = self.session.execute_diagnostic(self.path.rsplit("/", 1)[-1])
            elif self.path == "/freeze":
                result = self.session.freeze_architecture(str(payload["architecture_sha256"]))
            elif self.path.startswith("/reveal/"):
                result = self.session.reveal(self.path.rsplit("/", 1)[-1])
            elif self.path == "/score":
                result = self.session.score_submission(payload)
            else:
                self._json(HTTPStatus.NOT_FOUND, {"error": "not_found"})
                return
            self._json(HTTPStatus.OK, result)
        except (OmegaRuntimeError, KeyError, json.JSONDecodeError) as exc:
            self._json(HTTPStatus.BAD_REQUEST, {"error": str(exc)})

    def log_message(self, fmt: str, *args: Any) -> None:
        sys.stderr.write("OMEGA HTTP: " + fmt % args + "\n")


def serve(session: OmegaSession, host: str, port: int, token: str | None) -> None:
    handler = type("BoundOmegaHTTPHandler", (OmegaHTTPHandler,), {"session": session, "token": token})
    server = ThreadingHTTPServer((host, port), handler)
    print(json.dumps({"host": host, "port": port, "token_required": token is not None}))
    try:
        server.serve_forever()
    except KeyboardInterrupt:
        pass
    finally:
        server.server_close()


def main() -> int:
    parser = argparse.ArgumentParser(description="AIO OMEGA seeded closed-world benchmark runtime")
    parser.add_argument("--model", type=Path, default=Path("benchmarks/aio/omega/yggdrasil-habitat/scenario-model.json"))
    sub = parser.add_subparsers(dest="command", required=True)

    create = sub.add_parser("create")
    create.add_argument("--session", type=Path, required=True)
    create.add_argument("--seed")

    snapshot = sub.add_parser("snapshot")
    snapshot.add_argument("--session", type=Path, required=True)

    diagnostic = sub.add_parser("diagnostic")
    diagnostic.add_argument("--session", type=Path, required=True)
    diagnostic.add_argument("--id", required=True)

    freeze = sub.add_parser("freeze")
    freeze.add_argument("--session", type=Path, required=True)
    freeze.add_argument("--architecture", type=Path, required=True)

    reveal = sub.add_parser("reveal")
    reveal.add_argument("--session", type=Path, required=True)
    reveal.add_argument("--round", choices=["R4", "R5", "R6"], required=True)

    score = sub.add_parser("score")
    score.add_argument("--session", type=Path, required=True)
    score.add_argument("--submission", type=Path, required=True)
    score.add_argument("--out", type=Path)

    server = sub.add_parser("serve")
    server.add_argument("--session", type=Path, required=True)
    server.add_argument("--host", default="127.0.0.1")
    server.add_argument("--port", type=int, default=8765)
    server.add_argument("--token")

    args = parser.parse_args()
    try:
        world = OmegaWorld.load(args.model)
        if args.command == "create":
            session = OmegaSession.create(args.session, world, args.seed)
            print(json.dumps(session.public_snapshot(), indent=2))
        else:
            session = OmegaSession(args.session, world)
            if args.command == "snapshot":
                print(json.dumps(session.public_snapshot(), indent=2))
            elif args.command == "diagnostic":
                print(json.dumps(session.execute_diagnostic(args.id), indent=2))
            elif args.command == "freeze":
                print(json.dumps(session.freeze_architecture(digest(read_json(args.architecture))), indent=2))
            elif args.command == "reveal":
                print(json.dumps(session.reveal(args.round), indent=2))
            elif args.command == "score":
                result = session.score_submission(read_json(args.submission))
                if args.out:
                    write_json(args.out, result)
                print(json.dumps(result, indent=2))
                return 0 if result["passed"] else 3
            elif args.command == "serve":
                serve(session, args.host, args.port, args.token)
        return 0
    except OmegaRuntimeError as exc:
        print(f"FAIL: {exc}", file=sys.stderr)
        return 2


if __name__ == "__main__":
    raise SystemExit(main())
