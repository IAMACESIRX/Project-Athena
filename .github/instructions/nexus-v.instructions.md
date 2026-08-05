---
applyTo: "Nexus V/**"
---

For Nexus-V changes:

- Treat `Nexus V/rtl`, `Nexus V/tb`, `Nexus V/scripts`, and `Nexus V/toolchain` as the active source surface.
- Treat `Nexus V/docs/**` mirrors as archival unless the task explicitly targets documentation synchronization.
- Do not claim SystemVerilog lint, synthesis, or simulation passed unless the required external tool exists and the exact command succeeds.
- Keep generated compiler or Verilator artifacts out of source changes unless the task explicitly asks to refresh them.
- Prefer static validation before broader edits:

```powershell
python -m compileall -q "Nexus V/scripts" "Nexus V/toolchain"
python "Nexus V/scripts/static_bringup_audit.py"
```
