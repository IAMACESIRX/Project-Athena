#!/usr/bin/env python3
"""Shared primitives for AIO-OMEGA-001."""
from __future__ import annotations
import hashlib, json
from dataclasses import dataclass
from pathlib import Path
from typing import Any, Iterable
BENCHMARK_ID="AIO-OMEGA-001"
SESSION_SCHEMA="project-athena.aio.omega.session.v0.1"
HIDDEN_SCHEMA="project-athena.aio.omega.hidden_truth.v0.1"
SUBMISSION_SCHEMA="project-athena.aio.omega.submission.v0.1"
FAULT_THRESHOLD=0.5
class OmegaRuntimeError(ValueError): pass
def canonical(value:Any)->bytes: return json.dumps(value,sort_keys=True,separators=(",",":"),ensure_ascii=False).encode("utf-8")
def digest(value:Any)->str: return hashlib.sha256(canonical(value)).hexdigest()
def stable_seed(*parts:Any)->int: return int(hashlib.sha256("|".join(str(p) for p in parts).encode()).hexdigest()[:16],16)
def read_json(path:Path)->dict[str,Any]:
    try: value=json.loads(path.read_text(encoding="utf-8-sig"))
    except FileNotFoundError as exc: raise OmegaRuntimeError(f"Missing file: {path}") from exc
    except json.JSONDecodeError as exc: raise OmegaRuntimeError(f"Invalid JSON in {path}: {exc}") from exc
    if not isinstance(value,dict): raise OmegaRuntimeError(f"Root must be an object: {path}")
    return value
def write_json(path:Path,value:Any)->None:
    path.parent.mkdir(parents=True,exist_ok=True); path.write_text(json.dumps(value,indent=2,ensure_ascii=False)+"\n",encoding="utf-8")
def clamp(value:float,low:float=0.0,high:float=1.0)->float: return max(low,min(high,value))
def require(value:dict[str,Any],fields:Iterable[str],context:str)->None:
    missing=[f for f in fields if f not in value]
    if missing: raise OmegaRuntimeError(f"{context} missing: {', '.join(missing)}")
@dataclass(frozen=True)
class SessionPaths:
    root:Path
    @property
    def private(self)->Path:return self.root/".private"
    @property
    def public(self)->Path:return self.root/"public"
    @property
    def hidden(self)->Path:return self.private/"hidden-truth.json"
    @property
    def state(self)->Path:return self.private/"session-state.json"
    @property
    def brief(self)->Path:return self.public/"brief.json"
    @property
    def evidence(self)->Path:return self.public/"evidence.json"
    @property
    def diagnostic_catalog(self)->Path:return self.public/"diagnostics.json"
    @property
    def event_stream(self)->Path:return self.public/"events.json"
    @property
    def score(self)->Path:return self.root/"score.json"
