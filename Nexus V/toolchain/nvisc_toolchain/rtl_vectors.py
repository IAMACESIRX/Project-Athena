from __future__ import annotations
import json
from pathlib import Path

def export_rtl_vectors(nvir: dict, path: str | Path) -> None:
    vectors = []
    for inst in nvir.get("instructions", []):
        op = inst.get("op", "")
        if op.startswith(("B.", "S.", "A.", "G.", "T.", "Q.")):
            vectors.append({
                "id": inst["id"],
                "op": op,
                "state_in": inst.get("state_in"),
                "state_out": inst.get("state_out"),
                "branch": inst.get("branch"),
                "reads": inst.get("reads", []),
                "writes": inst.get("writes", []),
                "creates": inst.get("creates", []),
                "effects": inst.get("effects", [])
            })
    Path(path).write_text(json.dumps({"format":"nexus-v-rtl-vectors-v0.1","module":nvir.get("module"),"vectors":vectors}, indent=2))
