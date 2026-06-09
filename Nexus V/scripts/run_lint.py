#!/usr/bin/env python3
import argparse
import pathlib
import subprocess
import sys

parser = argparse.ArgumentParser(description="Run SystemVerilog lint for the Nexus-V canonical tree.")
parser.add_argument("--root", default=".", help="Repository root")
parser.add_argument("--top", default="tb_nexus_v_soc_smoke", help="Top module")
parser.add_argument("--verilator", default="verilator", help="Verilator executable")
args = parser.parse_args()

root = pathlib.Path(args.root)
rtl_files = sorted(str(p) for p in (root / "rtl").rglob("*.sv"))
tb_files = sorted(str(p) for p in (root / "tb").rglob("*.sv"))
files = rtl_files + tb_files

if not files:
    print("No SystemVerilog files found under rtl/ or tb/", file=sys.stderr)
    sys.exit(2)

cmd = [args.verilator, "--lint-only", "-sv", "--top-module", args.top] + files
print(" ".join(cmd))
result = subprocess.run(cmd)
sys.exit(result.returncode)
