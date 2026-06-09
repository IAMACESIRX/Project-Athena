# NVISC Compiler Bridge v0.1

Pipeline:

```text
NVASM -> parser AST -> semantic lowering -> NVIR JSON -> NVOBJ container -> RTL vectors
```

Run:

```bash
./nvisc-bridge examples/branch_route_tensor_quantum.nvasm --nvir out.nvir.json --nvobj out.nvobj --vectors out.rtl_vectors.json
```

This is an implementation scaffold, not a final optimizing compiler.
