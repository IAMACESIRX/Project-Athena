from __future__ import annotations
from dataclasses import asdict
from typing import Dict, List, Tuple
from .schema import NvirModule, NvirInstruction, DependencyEdge, NvirValue

class SemanticLowerer:
    def __init__(self):
        self.next_id = 1
        self.state_counter = {"@branch.main": 0}
        self.active_branch = "@branch.main"
        self.active_state = "%state#0@main"
        self.last_audit_token = None
        self.last_audit_subject = None
        self.edges: List[DependencyEdge] = []
        self.instructions: List[NvirInstruction] = []
        self.values: List[NvirValue] = []
        self.branch_heads = {"@branch.main": self.active_state}

    def _new_state(self, branch: str) -> str:
        short = branch.split('.')[-1] if '.' in branch else branch.replace('@branch.', '')
        self.state_counter[branch] = self.state_counter.get(branch, 0) + 1
        return f"%state#{self.state_counter[branch]}@{short}"

    def _emit(self, **kwargs) -> NvirInstruction:
        inst = NvirInstruction(id=self.next_id, **kwargs)
        self.instructions.append(inst)
        self.next_id += 1
        return inst

    def lower(self, parsed: Dict) -> NvirModule:
        mod = NvirModule(module=parsed["module"], arch=parsed["arch"], entry=parsed["entry"])
        mod.symbols = [asdict(s) for s in parsed["symbols"]]
        mod.state_graph["branches"].append({"branch_id": "@branch.main", "parent_branch": None, "head_state": self.active_state, "status": "active"})
        for inst in parsed["instructions"]:
            self.lower_instruction(inst)
        mod.instructions = [asdict(i) for i in self.instructions]
        mod.edges = [asdict(e) for e in self.edges]
        mod.values = [asdict(v) for v in self.values]
        mod.debug = {"source_model": "NVASM semantic mutation graph lowered to VSSA NVIR", "toolchain": "nvisc-toolchain-bridge-v0.1"}
        return mod

    def lower_instruction(self, inst):
        op = f"{inst.family}.{inst.opcode}"
        src = {"file": inst.loc.file if inst.loc else "", "line": inst.loc.line if inst.loc else 0, "raw": inst.raw}
        state_in = self.active_state
        state_out = state_in
        effects = []
        reads = []
        writes = []
        creates = []
        requires = []
        attrs = dict(inst.attrs)
        domain = "BIN"

        if inst.family == "B":
            if inst.opcode in {"ADD","SUB","MUL","DIV","AND","OR","XOR","CMP","LOAD","STORE","MOV"}:
                reads = inst.operands[1:] if len(inst.operands) > 1 else inst.operands
                if inst.operands: writes = [inst.operands[0]] if inst.opcode != "STORE" else []
                state_out = self._new_state(self.active_branch)
                effects = ["writes_register"] if inst.opcode != "STORE" else ["writes_memory"]
            elif inst.opcode in {"JMP","CALL","RET","HALT"}:
                effects = ["control_flow"]
        elif inst.family == "S":
            if inst.opcode == "SNAP":
                state_out = self._new_state(self.active_branch)
                writes = inst.operands[:1]
                effects = ["creates_snapshot", "writes_state_graph"]
            elif inst.opcode == "BRANCH":
                branch = inst.operands[0] if inst.operands else f"@branch.auto{self.next_id}"
                creates = [branch]
                self.active_branch = branch
                self.state_counter[branch] = 0
                state_out = self._new_state(branch)
                self.branch_heads[branch] = state_out
                effects = ["creates_branch", "writes_state_graph"]
            elif inst.opcode == "CHECKOUT":
                target = inst.operands[0] if inst.operands else "@branch.main"
                if target.startswith("@branch"):
                    self.active_branch = target
                    state_out = self.branch_heads.get(target, self.active_state)
                effects = ["checkout_branch_or_state"]
            elif inst.opcode == "SCORE":
                reads = inst.operands
                effects = ["scores_branch"]
            elif inst.opcode in {"RANK","SELECT"}:
                effects = ["merge_candidate_selection"]
                if inst.opcode == "SELECT":
                    state_out = f"%state#merged@main"
                    writes = [inst.dest] if inst.dest else []
            elif inst.opcode == "COMMIT":
                reads = inst.operands
                if self.last_audit_token:
                    requires = [self.last_audit_token]
                    self.edges.append(DependencyEdge(self.next_id-1, self.next_id, "audit_dependency", "S.COMMIT requires previous A.AUDIT token"))
                state_out = "%state#committed@main"
                effects = ["commits_state", "requires_audit"]
            elif inst.opcode == "ROLLBACK":
                reads = inst.operands
                state_out = self._new_state(self.active_branch)
                effects = ["rollback_state", "invalidates_descendants"]
        elif inst.family == "A":
            if inst.opcode in {"AUDIT","VERIFY"}:
                reads = inst.operands
                writes = [inst.dest] if inst.dest else []
                token = f"%audit_token#{self.next_id}"
                creates = [token]
                self.last_audit_token = token
                self.last_audit_subject = inst.operands[0] if inst.operands else None
                effects = ["aegis_audit", "creates_audit_token"]
                domain = "AEGIS"
        elif inst.family == "G":
            reads = inst.operands
            token = f"%topology.route#{self.next_id}"
            creates = [token]
            state_out = self._new_state(self.active_branch)
            effects = ["uses_topology", "creates_topology_token"]
            domain = "TOPOLOGY"
        elif inst.family == "T":
            reads = inst.operands
            writes = [inst.dest] if inst.dest else []
            state_out = self._new_state(self.active_branch)
            effects = ["tensor_operation", "writes_tensor_state"]
            domain = "TENSOR"
        elif inst.family == "Q":
            reads = inst.operands
            writes = [inst.dest] if inst.dest else []
            token = f"%quantum_token#{self.next_id}"
            creates = [token]
            state_out = self._new_state(self.active_branch)
            effects = ["quantum_step", "creates_quantum_token"]
            domain = "QSIM"
        elif inst.family == "D":
            reads = inst.operands[1:] if len(inst.operands) > 1 else inst.operands
            writes = [inst.operands[0]] if inst.operands else []
            state_out = self._new_state(self.active_branch)
            effects = ["decimal_operation"]
            domain = "DEC"
        elif inst.family == "FPERR":
            reads = inst.operands
            writes = [inst.dest] if inst.dest else []
            effects = ["numeric_integrity_check"]
            domain = "FPERR"
        elif inst.family == "M":
            reads = inst.operands
            writes = [inst.operands[0]] if inst.operands else []
            state_out = self._new_state(self.active_branch)
            effects = ["multi_valued_operation"]
            domain = "MVL"

        nvi = self._emit(op=op, reads=reads, writes=writes, creates=creates, requires=requires,
                         state_in=state_in, state_out=state_out, branch=self.active_branch,
                         domain=domain, effects=effects, attrs=attrs, source=src)
        self.active_state = state_out
        self.branch_heads[self.active_branch] = state_out
