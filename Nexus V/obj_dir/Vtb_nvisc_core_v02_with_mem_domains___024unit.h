// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design internal header
// See Vtb_nvisc_core_v02_with_mem_domains.h for the primary calling header

#ifndef VERILATED_VTB_NVISC_CORE_V02_WITH_MEM_DOMAINS___024UNIT_H_
#define VERILATED_VTB_NVISC_CORE_V02_WITH_MEM_DOMAINS___024UNIT_H_  // guard

#include "verilated.h"


class Vtb_nvisc_core_v02_with_mem_domains__Syms;

class alignas(VL_CACHE_LINE_BYTES) Vtb_nvisc_core_v02_with_mem_domains___024unit final {
  public:

    // INTERNAL VARIABLES
    Vtb_nvisc_core_v02_with_mem_domains__Syms* vlSymsp;
    const char* vlNamep;

    // CONSTRUCTORS
    Vtb_nvisc_core_v02_with_mem_domains___024unit();
    ~Vtb_nvisc_core_v02_with_mem_domains___024unit();
    void ctor(Vtb_nvisc_core_v02_with_mem_domains__Syms* symsp, const char* namep);
    void dtor();
    VL_UNCOPYABLE(Vtb_nvisc_core_v02_with_mem_domains___024unit);

    // INTERNAL METHODS
    void __Vconfigure(bool first);
};


#endif  // guard
