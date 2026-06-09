// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See Vtb_nvisc_core_v02_with_mem_domains.h for the primary calling header

#include "Vtb_nvisc_core_v02_with_mem_domains__pch.h"

void Vtb_nvisc_core_v02_with_mem_domains___024root___ctor_var_reset(Vtb_nvisc_core_v02_with_mem_domains___024root* vlSelf);

Vtb_nvisc_core_v02_with_mem_domains___024root::Vtb_nvisc_core_v02_with_mem_domains___024root(Vtb_nvisc_core_v02_with_mem_domains__Syms* symsp, const char* namep)
 {
    vlSymsp = symsp;
    vlNamep = strdup(namep);
    // Reset structure values
    Vtb_nvisc_core_v02_with_mem_domains___024root___ctor_var_reset(this);
}

void Vtb_nvisc_core_v02_with_mem_domains___024root::__Vconfigure(bool first) {
    (void)first;  // Prevent unused variable warning
}

Vtb_nvisc_core_v02_with_mem_domains___024root::~Vtb_nvisc_core_v02_with_mem_domains___024root() {
    VL_DO_DANGLING(std::free(const_cast<char*>(vlNamep)), vlNamep);
}
