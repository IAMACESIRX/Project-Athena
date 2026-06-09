// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See Vtb_nvisc_core_v02_with_mem_domains.h for the primary calling header

#include "Vtb_nvisc_core_v02_with_mem_domains__pch.h"


Vtb_nvisc_core_v02_with_mem_domains___024unit::Vtb_nvisc_core_v02_with_mem_domains___024unit() = default;
Vtb_nvisc_core_v02_with_mem_domains___024unit::~Vtb_nvisc_core_v02_with_mem_domains___024unit() = default;

void Vtb_nvisc_core_v02_with_mem_domains___024unit::ctor(Vtb_nvisc_core_v02_with_mem_domains__Syms* symsp, const char* namep) {
    vlSymsp = symsp;
    vlNamep = strdup(Verilated::catName(vlSymsp->name(), namep));
    // Reset structure values
}

void Vtb_nvisc_core_v02_with_mem_domains___024unit::__Vconfigure(bool first) {
    (void)first;  // Prevent unused variable warning
}

void Vtb_nvisc_core_v02_with_mem_domains___024unit::dtor() {
    VL_DO_DANGLING(std::free(const_cast<char*>(vlNamep)), vlNamep);
}
