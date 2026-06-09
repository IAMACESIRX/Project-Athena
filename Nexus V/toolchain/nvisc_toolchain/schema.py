from __future__ import annotations
from dataclasses import dataclass, field, asdict
from typing import Any, Dict, List, Optional

@dataclass
class SourceLoc:
    file: str
    line: int
    column: int = 1

@dataclass
class Instruction:
    family: str
    opcode: str
    operands: List[str]
    dest: Optional[str] = None
    attrs: Dict[str, Any] = field(default_factory=dict)
    loc: Optional[SourceLoc] = None
    raw: str = ""

@dataclass
class Symbol:
    name: str
    section: str
    index: int

@dataclass
class NvirValue:
    value_id: str
    type: str
    domain: str
    branch: str
    state_version: str
    provenance: List[str] = field(default_factory=list)
    safety: str = "LOCAL"
    audit_status: str = "unaudited"

@dataclass
class NvirInstruction:
    id: int
    op: str
    reads: List[str] = field(default_factory=list)
    writes: List[str] = field(default_factory=list)
    creates: List[str] = field(default_factory=list)
    requires: List[str] = field(default_factory=list)
    guard: Optional[str] = None
    state_in: Optional[str] = None
    state_out: Optional[str] = None
    branch: str = "@branch.main"
    domain: str = "BIN"
    effects: List[str] = field(default_factory=list)
    attrs: Dict[str, Any] = field(default_factory=dict)
    source: Dict[str, Any] = field(default_factory=dict)

@dataclass
class DependencyEdge:
    from_id: int
    to_id: int
    type: str
    reason: str

@dataclass
class NvirModule:
    nvir_version: str = "0.2"
    module: str = "unnamed"
    arch: str = "NVISC-v0.1"
    representation: str = "VSSA"
    features: List[str] = field(default_factory=list)
    entry: str = "main"
    sections: Dict[str, Any] = field(default_factory=dict)
    symbols: List[Dict[str, Any]] = field(default_factory=list)
    types: Dict[str, Any] = field(default_factory=dict)
    policies: List[Dict[str, Any]] = field(default_factory=list)
    topologies: List[Dict[str, Any]] = field(default_factory=list)
    state_graph: Dict[str, Any] = field(default_factory=lambda: {"branches": [], "commits": [], "snapshots": [], "rollback_points": []})
    values: List[Dict[str, Any]] = field(default_factory=list)
    instructions: List[Dict[str, Any]] = field(default_factory=list)
    edges: List[Dict[str, Any]] = field(default_factory=list)
    diagnostics: List[Dict[str, Any]] = field(default_factory=list)
    debug: Dict[str, Any] = field(default_factory=dict)

    def to_dict(self) -> Dict[str, Any]:
        return asdict(self)
