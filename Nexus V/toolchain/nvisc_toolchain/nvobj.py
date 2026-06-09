from __future__ import annotations
import json, struct, zlib
from pathlib import Path

MAGIC = b"NVOBJ\x00\x01"

def write_nvobj(nvir_dict: dict, path: str | Path) -> None:
    payload = json.dumps(nvir_dict, indent=2, sort_keys=True).encode("utf-8")
    comp = zlib.compress(payload)
    header = MAGIC + struct.pack("<II", len(payload), len(comp))
    Path(path).write_bytes(header + comp)

def read_nvobj(path: str | Path) -> dict:
    data = Path(path).read_bytes()
    if not data.startswith(MAGIC):
        raise ValueError("not an NVOBJ v0.1 file")
    off = len(MAGIC)
    raw_len, comp_len = struct.unpack("<II", data[off:off+8])
    comp = data[off+8:off+8+comp_len]
    payload = zlib.decompress(comp)
    if len(payload) != raw_len:
        raise ValueError("NVOBJ payload length mismatch")
    return json.loads(payload.decode("utf-8"))
