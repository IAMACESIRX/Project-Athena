// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Symbol table internal header
//
// Internal details; most calling programs do not need this header,
// unless using verilator public meta comments.

#ifndef VERILATED_VTB_NVISC_CORE_V02_WITH_MEM_DOMAINS__SYMS_H_
#define VERILATED_VTB_NVISC_CORE_V02_WITH_MEM_DOMAINS__SYMS_H_  // guard

#include "verilated.h"

// INCLUDE MODEL CLASS

#include "Vtb_nvisc_core_v02_with_mem_domains.h"

// INCLUDE MODULE CLASSES
#include "Vtb_nvisc_core_v02_with_mem_domains___024root.h"
#include "Vtb_nvisc_core_v02_with_mem_domains___024unit.h"

// SYMS CLASS (contains all model state)
class alignas(VL_CACHE_LINE_BYTES) Vtb_nvisc_core_v02_with_mem_domains__Syms final : public VerilatedSyms {
  public:
    // INTERNAL STATE
    Vtb_nvisc_core_v02_with_mem_domains* const __Vm_modelp;
    VlDeleter __Vm_deleter;
    bool __Vm_didInit = false;

    // MODULE INSTANCE STATE
    Vtb_nvisc_core_v02_with_mem_domains___024root TOP;

    // CONSTRUCTORS
    Vtb_nvisc_core_v02_with_mem_domains__Syms(VerilatedContext* contextp, const char* namep, Vtb_nvisc_core_v02_with_mem_domains* modelp);
    ~Vtb_nvisc_core_v02_with_mem_domains__Syms();

    // METHODS
    const char* name() const { return TOP.vlNamep; }
};

#endif  // guard
