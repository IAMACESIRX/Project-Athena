from __future__ import annotations
import argparse, json
from pathlib import Path
from .parser import NVASMParser
from .lowering import SemanticLowerer
from .nvobj import write_nvobj
from .rtl_vectors import export_rtl_vectors

def main(argv=None):
    ap = argparse.ArgumentParser(prog="nvisc-bridge", description="Compile NVASM to NVIR/NVOBJ and RTL vectors")
    ap.add_argument("source", help="input .nvasm file")
    ap.add_argument("--nvir", help="output .nvir.json path")
    ap.add_argument("--nvobj", help="output .nvobj path")
    ap.add_argument("--vectors", help="output RTL vectors JSON path")
    args = ap.parse_args(argv)

    parsed = NVASMParser().parse_file(args.source)
    nvir = SemanticLowerer().lower(parsed).to_dict()

    if args.nvir:
        Path(args.nvir).write_text(json.dumps(nvir, indent=2))
    if args.nvobj:
        write_nvobj(nvir, args.nvobj)
    if args.vectors:
        export_rtl_vectors(nvir, args.vectors)
    if not any([args.nvir, args.nvobj, args.vectors]):
        print(json.dumps(nvir, indent=2))

if __name__ == "__main__":
    main()
