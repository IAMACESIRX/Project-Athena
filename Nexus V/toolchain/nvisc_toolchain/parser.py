from __future__ import annotations
import re
from pathlib import Path
from typing import Dict, List, Tuple
from .schema import Instruction, SourceLoc, Symbol

DIRECTIVE_RE = re.compile(r"^\.(\w+)(?:\s+(.*))?$")
LABEL_RE = re.compile(r"^([@%]?[A-Za-z_][\w\.]*):$")
INSTR_RE = re.compile(r"^([A-Za-z][\w]*)(?:\.([A-Za-z_][\w]*))?\s*(.*)$")

class NVASMParseError(Exception):
    pass

def _strip_comment(line: str) -> str:
    if ';' in line:
        return line.split(';', 1)[0]
    return line

def _split_operands(text: str) -> Tuple[List[str], str | None]:
    text = text.strip()
    dest = None
    if '->' in text:
        left, right = text.split('->', 1)
        text = left.strip()
        dest = right.strip()
    if not text:
        return [], dest
    parts = []
    cur = []
    depth = 0
    for ch in text:
        if ch in '([{<': depth += 1
        elif ch in ')]}>': depth = max(0, depth - 1)
        if ch == ',' and depth == 0:
            parts.append(''.join(cur).strip())
            cur = []
        else:
            cur.append(ch)
    if cur:
        parts.append(''.join(cur).strip())
    return parts, dest

class NVASMParser:
    def parse_file(self, path: str | Path) -> Dict:
        path = Path(path)
        return self.parse_text(path.read_text(), str(path))

    def parse_text(self, text: str, filename: str = "<memory>") -> Dict:
        module = "unnamed"
        arch = "NVISC-v0.1"
        entry = "main"
        section = ".text"
        instructions: List[Instruction] = []
        symbols: List[Symbol] = []
        directives: List[Dict] = []
        pending_attrs: Dict = {}

        block_depth = 0
        block_name = None

        for line_no, raw in enumerate(text.splitlines(), start=1):
            line = _strip_comment(raw).strip()
            if not line:
                continue

            # Directive blocks such as .policy name { ... } are metadata for later
            # toolchain passes. The v0.1 bridge records the opening directive and
            # skips the block body so full-system programs can lower to NVIR before
            # policy-body semantics are implemented.
            if block_depth > 0:
                block_depth += line.count('{')
                block_depth -= line.count('}')
                if block_depth <= 0:
                    block_depth = 0
                    block_name = None
                continue
            if line.startswith('@') and not line.endswith(':') and '(' in line and line.endswith(')'):
                name, rest = line[1:].split('(', 1)
                pending_attrs[name.strip()] = rest[:-1].strip()
                continue
            m = DIRECTIVE_RE.match(line)
            if m:
                name, arg = m.group(1), (m.group(2) or "").strip()
                directives.append({"name": name, "arg": arg, "line": line_no})
                if name == "module": module = arg.strip('"')
                elif name == "arch": arch = arg.strip('"')
                elif name == "entry": entry = arg
                elif name == "section": section = arg
                if '{' in line and not line.rstrip().endswith('}'):
                    block_depth = line.count('{') - line.count('}')
                    block_name = name
                continue
            m = LABEL_RE.match(line)
            if m:
                symbols.append(Symbol(m.group(1), section, len(instructions)))
                continue
            m = INSTR_RE.match(line)
            if not m:
                raise NVASMParseError(f"{filename}:{line_no}: cannot parse line: {raw}")
            fam_or_op, maybe_op, opers = m.groups()
            if maybe_op is None:
                family, opcode = "B", fam_or_op.upper()
            else:
                family, opcode = fam_or_op.upper(), maybe_op.upper()
            operands, dest = _split_operands(opers)
            instructions.append(Instruction(
                family=family, opcode=opcode, operands=operands, dest=dest,
                attrs=pending_attrs, loc=SourceLoc(filename, line_no), raw=raw.rstrip()
            ))
            pending_attrs = {}
        return {"module": module, "arch": arch, "entry": entry, "directives": directives, "symbols": symbols, "instructions": instructions}
