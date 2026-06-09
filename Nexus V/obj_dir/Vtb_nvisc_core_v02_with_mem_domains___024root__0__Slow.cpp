// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See Vtb_nvisc_core_v02_with_mem_domains.h for the primary calling header

#include "Vtb_nvisc_core_v02_with_mem_domains__pch.h"

VL_ATTR_COLD void Vtb_nvisc_core_v02_with_mem_domains___024root___eval_static(Vtb_nvisc_core_v02_with_mem_domains___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_nvisc_core_v02_with_mem_domains___024root___eval_static\n"); );
    Vtb_nvisc_core_v02_with_mem_domains__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    vlSelfRef.__Vtrigprevexpr___TOP__clk__0 = vlSelfRef.clk;
    vlSelfRef.__Vtrigprevexpr___TOP__rst_n__0 = vlSelfRef.rst_n;
}

VL_ATTR_COLD void Vtb_nvisc_core_v02_with_mem_domains___024root___eval_initial(Vtb_nvisc_core_v02_with_mem_domains___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_nvisc_core_v02_with_mem_domains___024root___eval_initial\n"); );
    Vtb_nvisc_core_v02_with_mem_domains__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
}

VL_ATTR_COLD void Vtb_nvisc_core_v02_with_mem_domains___024root___eval_final(Vtb_nvisc_core_v02_with_mem_domains___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_nvisc_core_v02_with_mem_domains___024root___eval_final\n"); );
    Vtb_nvisc_core_v02_with_mem_domains__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
}

#ifdef VL_DEBUG
VL_ATTR_COLD void Vtb_nvisc_core_v02_with_mem_domains___024root___dump_triggers__stl(const VlUnpacked<QData/*63:0*/, 1> &triggers, const std::string &tag);
#endif  // VL_DEBUG
VL_ATTR_COLD bool Vtb_nvisc_core_v02_with_mem_domains___024root___eval_phase__stl(Vtb_nvisc_core_v02_with_mem_domains___024root* vlSelf);

VL_ATTR_COLD void Vtb_nvisc_core_v02_with_mem_domains___024root___eval_settle(Vtb_nvisc_core_v02_with_mem_domains___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_nvisc_core_v02_with_mem_domains___024root___eval_settle\n"); );
    Vtb_nvisc_core_v02_with_mem_domains__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Locals
    IData/*31:0*/ __VstlIterCount;
    // Body
    __VstlIterCount = 0U;
    vlSelfRef.__VstlFirstIteration = 1U;
    do {
        if (VL_UNLIKELY(((0x00002710U < __VstlIterCount)))) {
#ifdef VL_DEBUG
            Vtb_nvisc_core_v02_with_mem_domains___024root___dump_triggers__stl(vlSelfRef.__VstlTriggered, "stl"s);
#endif
            VL_FATAL_MT("rtl/core_v02\\tb_nvisc_core_v02_with_mem_domains.sv", 5, "", "DIDNOTCONVERGE: Settle region did not converge after '--converge-limit' of 10000 tries");
        }
        __VstlIterCount = ((IData)(1U) + __VstlIterCount);
        vlSelfRef.__VstlPhaseResult = Vtb_nvisc_core_v02_with_mem_domains___024root___eval_phase__stl(vlSelf);
        vlSelfRef.__VstlFirstIteration = 0U;
    } while (vlSelfRef.__VstlPhaseResult);
}

VL_ATTR_COLD void Vtb_nvisc_core_v02_with_mem_domains___024root___eval_triggers_vec__stl(Vtb_nvisc_core_v02_with_mem_domains___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_nvisc_core_v02_with_mem_domains___024root___eval_triggers_vec__stl\n"); );
    Vtb_nvisc_core_v02_with_mem_domains__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    vlSelfRef.__VstlTriggered[0U] = ((0xfffffffffffffffeULL 
                                      & vlSelfRef.__VstlTriggered[0U]) 
                                     | (IData)((IData)(vlSelfRef.__VstlFirstIteration)));
}

VL_ATTR_COLD bool Vtb_nvisc_core_v02_with_mem_domains___024root___trigger_anySet__stl(const VlUnpacked<QData/*63:0*/, 1> &in);

#ifdef VL_DEBUG
VL_ATTR_COLD void Vtb_nvisc_core_v02_with_mem_domains___024root___dump_triggers__stl(const VlUnpacked<QData/*63:0*/, 1> &triggers, const std::string &tag) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_nvisc_core_v02_with_mem_domains___024root___dump_triggers__stl\n"); );
    // Body
    if ((1U & (~ (IData)(Vtb_nvisc_core_v02_with_mem_domains___024root___trigger_anySet__stl(triggers))))) {
        VL_DBG_MSGS("         No '" + tag + "' region triggers active\n");
    }
    if ((1U & (IData)(triggers[0U]))) {
        VL_DBG_MSGS("         '" + tag + "' region trigger index 0 is active: Internal 'stl' trigger - first iteration\n");
    }
}
#endif  // VL_DEBUG

VL_ATTR_COLD bool Vtb_nvisc_core_v02_with_mem_domains___024root___trigger_anySet__stl(const VlUnpacked<QData/*63:0*/, 1> &in) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_nvisc_core_v02_with_mem_domains___024root___trigger_anySet__stl\n"); );
    // Locals
    IData/*31:0*/ n;
    // Body
    n = 0U;
    do {
        if (in[n]) {
            return (1U);
        }
        n = ((IData)(1U) + n);
    } while ((1U > n));
    return (0U);
}

extern const VlWide<11>/*351:0*/ Vtb_nvisc_core_v02_with_mem_domains__ConstPool__CONST_h09c2fdcd_0;

VL_ATTR_COLD void Vtb_nvisc_core_v02_with_mem_domains___024root___stl_sequent__TOP__0(Vtb_nvisc_core_v02_with_mem_domains___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_nvisc_core_v02_with_mem_domains___024root___stl_sequent__TOP__0\n"); );
    Vtb_nvisc_core_v02_with_mem_domains__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Locals
    CData/*0:0*/ tb_nvisc_core_v02_with_mem_domains__DOT__memsys_resp_write_ack_w;
    tb_nvisc_core_v02_with_mem_domains__DOT__memsys_resp_write_ack_w = 0;
    SData/*15:0*/ tb_nvisc_core_v02_with_mem_domains__DOT__memsys_fault_code_w;
    tb_nvisc_core_v02_with_mem_domains__DOT__memsys_fault_code_w = 0;
    CData/*0:0*/ tb_nvisc_core_v02_with_mem_domains__DOT__u_core__DOT__ctrl_trap_w;
    tb_nvisc_core_v02_with_mem_domains__DOT__u_core__DOT__ctrl_trap_w = 0;
    SData/*15:0*/ tb_nvisc_core_v02_with_mem_domains__DOT__u_core__DOT__ctrl_trap_code_w;
    tb_nvisc_core_v02_with_mem_domains__DOT__u_core__DOT__ctrl_trap_code_w = 0;
    CData/*6:0*/ tb_nvisc_core_v02_with_mem_domains__DOT__u_core__DOT__u_dec__DOT__opcode;
    tb_nvisc_core_v02_with_mem_domains__DOT__u_core__DOT__u_dec__DOT__opcode = 0;
    CData/*4:0*/ tb_nvisc_core_v02_with_mem_domains__DOT__u_core__DOT__u_dec__DOT__rd;
    tb_nvisc_core_v02_with_mem_domains__DOT__u_core__DOT__u_dec__DOT__rd = 0;
    CData/*4:0*/ tb_nvisc_core_v02_with_mem_domains__DOT__u_core__DOT__u_dec__DOT__rs1;
    tb_nvisc_core_v02_with_mem_domains__DOT__u_core__DOT__u_dec__DOT__rs1 = 0;
    CData/*4:0*/ tb_nvisc_core_v02_with_mem_domains__DOT__u_core__DOT__u_dec__DOT__rs2;
    tb_nvisc_core_v02_with_mem_domains__DOT__u_core__DOT__u_dec__DOT__rs2 = 0;
    CData/*2:0*/ tb_nvisc_core_v02_with_mem_domains__DOT__u_core__DOT__u_dec__DOT__funct3;
    tb_nvisc_core_v02_with_mem_domains__DOT__u_core__DOT__u_dec__DOT__funct3 = 0;
    CData/*6:0*/ tb_nvisc_core_v02_with_mem_domains__DOT__u_core__DOT__u_dec__DOT__funct7;
    tb_nvisc_core_v02_with_mem_domains__DOT__u_core__DOT__u_dec__DOT__funct7 = 0;
    SData/*11:0*/ tb_nvisc_core_v02_with_mem_domains__DOT__u_core__DOT__u_dec__DOT__imm12_i;
    tb_nvisc_core_v02_with_mem_domains__DOT__u_core__DOT__u_dec__DOT__imm12_i = 0;
    SData/*11:0*/ tb_nvisc_core_v02_with_mem_domains__DOT__u_core__DOT__u_dec__DOT__imm12_s;
    tb_nvisc_core_v02_with_mem_domains__DOT__u_core__DOT__u_dec__DOT__imm12_s = 0;
    SData/*11:0*/ tb_nvisc_core_v02_with_mem_domains__DOT__u_core__DOT__u_dec__DOT__imm12_selected;
    tb_nvisc_core_v02_with_mem_domains__DOT__u_core__DOT__u_dec__DOT__imm12_selected = 0;
    QData/*63:0*/ tb_nvisc_core_v02_with_mem_domains__DOT__u_core__DOT__u_dec__DOT__imm_ext;
    tb_nvisc_core_v02_with_mem_domains__DOT__u_core__DOT__u_dec__DOT__imm_ext = 0;
    CData/*0:0*/ tb_nvisc_core_v02_with_mem_domains__DOT__u_core__DOT__u_alu__DOT__overflow_c;
    tb_nvisc_core_v02_with_mem_domains__DOT__u_core__DOT__u_alu__DOT__overflow_c = 0;
    CData/*0:0*/ tb_nvisc_core_v02_with_mem_domains__DOT__u_core__DOT__u_alu__DOT__fault_c;
    tb_nvisc_core_v02_with_mem_domains__DOT__u_core__DOT__u_alu__DOT__fault_c = 0;
    SData/*15:0*/ tb_nvisc_core_v02_with_mem_domains__DOT__u_core__DOT__u_alu__DOT__fault_code_c;
    tb_nvisc_core_v02_with_mem_domains__DOT__u_core__DOT__u_alu__DOT__fault_code_c = 0;
    // Body
    vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_core__DOT__u_mmu__DOT__align_fault_c = 0U;
    if ((0x02000000U & vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_core__DOT__u_lsu__DOT__req_q[11U])) {
        vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_core__DOT__u_mmu__DOT__align_fault_c 
            = ((1U != (0x000000ffU & (vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_core__DOT__u_lsu__DOT__req_q[4U] 
                                      >> 0x0000000eU))) 
               && (1U & ((2U == (0x000000ffU & (vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_core__DOT__u_lsu__DOT__req_q[4U] 
                                                >> 0x0000000eU)))
                          ? (vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_core__DOT__u_lsu__DOT__req_q[8U] 
                             >> 0x00000016U) : ((4U 
                                                 == 
                                                 (0x000000ffU 
                                                  & (vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_core__DOT__u_lsu__DOT__req_q[4U] 
                                                     >> 0x0000000eU)))
                                                 ? 
                                                (0U 
                                                 != 
                                                 (3U 
                                                  & (vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_core__DOT__u_lsu__DOT__req_q[8U] 
                                                     >> 0x00000016U)))
                                                 : 
                                                ((8U 
                                                  != 
                                                  (0x000000ffU 
                                                   & (vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_core__DOT__u_lsu__DOT__req_q[4U] 
                                                      >> 0x0000000eU))) 
                                                 || (0U 
                                                     != 
                                                     (7U 
                                                      & (vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_core__DOT__u_lsu__DOT__req_q[8U] 
                                                         >> 0x00000016U))))))));
        if ((1U & (~ VL_ONEHOT_I(((((8U == (0x000000ffU 
                                            & (vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_core__DOT__u_lsu__DOT__req_q[4U] 
                                               >> 0x0000000eU))) 
                                    << 3U) | ((4U == 
                                               (0x000000ffU 
                                                & (vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_core__DOT__u_lsu__DOT__req_q[4U] 
                                                   >> 0x0000000eU))) 
                                              << 2U)) 
                                  | (((2U == (0x000000ffU 
                                              & (vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_core__DOT__u_lsu__DOT__req_q[4U] 
                                                 >> 0x0000000eU))) 
                                      << 1U) | (1U 
                                                == 
                                                (0x000000ffU 
                                                 & (vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_core__DOT__u_lsu__DOT__req_q[4U] 
                                                    >> 0x0000000eU))))))))) {
            if ((0U != ((((8U == (0x000000ffU & (vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_core__DOT__u_lsu__DOT__req_q[4U] 
                                                 >> 0x0000000eU))) 
                          << 3U) | ((4U == (0x000000ffU 
                                            & (vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_core__DOT__u_lsu__DOT__req_q[4U] 
                                               >> 0x0000000eU))) 
                                    << 2U)) | (((2U 
                                                 == 
                                                 (0x000000ffU 
                                                  & (vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_core__DOT__u_lsu__DOT__req_q[4U] 
                                                     >> 0x0000000eU))) 
                                                << 1U) 
                                               | (1U 
                                                  == 
                                                  (0x000000ffU 
                                                   & (vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_core__DOT__u_lsu__DOT__req_q[4U] 
                                                      >> 0x0000000eU))))))) {
                if (VL_UNLIKELY((vlSymsp->_vm_contextp__->assertOn()))) {
                    VL_WRITEF_NX("[%0t] %%Error: nvisc_mmu_tlb_stub.sv:49: Assertion failed in %m: unique case, but multiple matches found for '8'h%X'\n",4, 'M',vlSymsp->name(),"tb_nvisc_core_v02_with_mem_domains.u_core.u_mmu", 'T',-9
                                 , '#',64,VL_TIME_UNITED_Q(1000)
                                 , '#',8,(0x000000ffU 
                                          & (vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_core__DOT__u_lsu__DOT__req_q[4U] 
                                             >> 0x0000000eU)));
                    VL_STOP_MT("rtl/core_v02\\nvisc_mmu_tlb_stub.sv", 49, "");
                }
            }
        }
    }
    vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_core__DOT__u_lsu__DOT__bad_size_c 
        = (1U & (~ ((1U == (IData)(vlSelfRef.lsu_size_bytes_i)) 
                    | ((2U == (IData)(vlSelfRef.lsu_size_bytes_i)) 
                       | ((4U == (IData)(vlSelfRef.lsu_size_bytes_i)) 
                          | (8U == (IData)(vlSelfRef.lsu_size_bytes_i)))))));
    vlSelfRef.pc_valid_o = vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_core__DOT__u_pc__DOT__valid_q;
    vlSelfRef.mem_req_domain_o = vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_core__DOT__mmu_resp_mem_domain_w;
    vlSelfRef.imem_req_addr_o = vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_core__DOT__u_pc__DOT__pc_q;
    vlSelfRef.pc_o = vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_core__DOT__u_pc__DOT__pc_q;
    vlSelfRef.fetch_valid_o = (1U & (vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_core__DOT__u_if__DOT__fetch_q[7U] 
                                     >> 3U));
    vlSelfRef.fetch_instr_o = ((vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_core__DOT__u_if__DOT__fetch_q[5U] 
                                << 0x0000001dU) | (vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_core__DOT__u_if__DOT__fetch_q[4U] 
                                                   >> 3U));
    vlSelfRef.dbg_rf_r1_o = vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_core__DOT__u_rf__DOT__regs_q[1U];
    vlSelfRef.dbg_rf_r2_o = vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_core__DOT__u_rf__DOT__regs_q[2U];
    vlSelfRef.dbg_rf_r3_o = vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_core__DOT__u_rf__DOT__regs_q[3U];
    vlSelfRef.mem_req_valid_o = vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_core__DOT__mmu_resp_valid_w;
    vlSelfRef.mem_req_is_read_o = vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_core__DOT__mmu_resp_is_read_w;
    vlSelfRef.mem_req_is_write_o = vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_core__DOT__mmu_resp_is_write_w;
    vlSelfRef.mem_req_vaddr_o = vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_core__DOT__mmu_resp_vaddr_w;
    vlSelfRef.mem_req_paddr_o = vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_core__DOT__mmu_resp_paddr_w;
    vlSelfRef.mem_req_wdata_o = vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_core__DOT__mmu_resp_wdata_w;
    vlSelfRef.mem_req_size_bytes_o = vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_core__DOT__mmu_resp_size_bytes_w;
    vlSelfRef.dbg_data_route_valid_o = vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__data_req_valid_w;
    vlSelfRef.dbg_exec_route_valid_o = vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__exec_req_valid_w;
    vlSelfRef.dbg_livehot_route_valid_o = vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__livehot_req_valid_w;
    vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_execmem__DOT__in_range_c 
        = ((0x0000000000002000ULL <= vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__exec_req_paddr_w) 
           & (0x0000000000000100ULL > VL_SHIFTR_QQI(64,64,32, 
                                                    (vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__exec_req_paddr_w 
                                                     - 0x0000000000002000ULL), 3U)));
    vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_livehot__DOT__in_range_c 
        = ((0x0000000000003000ULL <= vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__livehot_req_paddr_w) 
           & (0x0000000000000100ULL > VL_SHIFTR_QQI(64,64,32, 
                                                    (vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__livehot_req_paddr_w 
                                                     - 0x0000000000003000ULL), 3U)));
    vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_core__DOT__u_mmu__DOT__page_fault_c 
        = (IData)(((0x003fffc0U == (0x003fffc0U & vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_core__DOT__u_lsu__DOT__req_q[10U])) 
                   & (vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_core__DOT__u_lsu__DOT__req_q[11U] 
                      >> 0x00000019U)));
    vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__effective_flush_data_l1d_w 
        = ((IData)(vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__cache_csr_flush_l1d_w) 
           | (IData)(vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__cache_csr_flush_hierarchy_w));
    vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_execmem__DOT__op_ok_c 
        = ((IData)(vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__exec_req_is_read_w) 
           ^ (IData)(vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__exec_req_is_write_w));
    vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_livehot__DOT__op_ok_c 
        = ((IData)(vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__livehot_req_is_read_w) 
           ^ (IData)(vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__livehot_req_is_write_w));
    vlSelfRef.imem_req_valid_o = ((~ ((IData)(vlSelfRef.stall_i) 
                                      | (IData)(vlSelfRef.flush_i))) 
                                  & (IData)(vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_core__DOT__u_pc__DOT__valid_q));
    vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__wrapper_override_domain_w 
        = ((IData)(vlSelfRef.mem_domain_override_valid_i)
            ? (IData)(vlSelfRef.mem_domain_override_i)
            : (IData)(vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_core__DOT__mmu_resp_mem_domain_w));
    vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__memsys_resp_valid_w = 0U;
    vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__memsys_resp_rdata_w = 0ULL;
    tb_nvisc_core_v02_with_mem_domains__DOT__memsys_resp_write_ack_w = 0U;
    vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__memsys_fault_w = 0U;
    tb_nvisc_core_v02_with_mem_domains__DOT__memsys_fault_code_w = 0U;
    if (vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__router_fault_w) {
        vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__memsys_fault_w = 1U;
        tb_nvisc_core_v02_with_mem_domains__DOT__memsys_fault_code_w 
            = vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__router_fault_code_w;
    } else {
        if ((1U == (IData)(vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__pending_domain_q))) {
            vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__memsys_resp_valid_w 
                = vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__data_resp_valid_w;
            vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__memsys_resp_rdata_w 
                = vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__data_resp_rdata_w;
            tb_nvisc_core_v02_with_mem_domains__DOT__memsys_resp_write_ack_w 
                = vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__data_resp_write_ack_w;
            vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__memsys_fault_w 
                = vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__data_fault_w;
            tb_nvisc_core_v02_with_mem_domains__DOT__memsys_fault_code_w 
                = vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__data_fault_code_w;
        } else if ((2U == (IData)(vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__pending_domain_q))) {
            vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__memsys_resp_valid_w 
                = vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__exec_resp_valid_w;
            vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__memsys_resp_rdata_w 
                = vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__exec_resp_rdata_w;
            tb_nvisc_core_v02_with_mem_domains__DOT__memsys_resp_write_ack_w 
                = vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__exec_resp_write_ack_w;
            vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__memsys_fault_w 
                = vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__exec_fault_w;
            tb_nvisc_core_v02_with_mem_domains__DOT__memsys_fault_code_w 
                = vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__exec_fault_code_w;
        } else if ((3U == (IData)(vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__pending_domain_q))) {
            vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__memsys_resp_valid_w 
                = vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__livehot_resp_valid_w;
            vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__memsys_resp_rdata_w 
                = vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__livehot_resp_rdata_w;
            tb_nvisc_core_v02_with_mem_domains__DOT__memsys_resp_write_ack_w 
                = vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__livehot_resp_write_ack_w;
            vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__memsys_fault_w 
                = vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__livehot_fault_w;
            tb_nvisc_core_v02_with_mem_domains__DOT__memsys_fault_code_w 
                = vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__livehot_fault_code_w;
        } else {
            vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__memsys_fault_w = 1U;
            tb_nvisc_core_v02_with_mem_domains__DOT__memsys_fault_code_w = 0x0801U;
        }
        if ((1U & (~ VL_ONEHOT_I((((3U == (IData)(vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__pending_domain_q)) 
                                   << 2U) | (((2U == (IData)(vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__pending_domain_q)) 
                                              << 1U) 
                                             | (1U 
                                                == (IData)(vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__pending_domain_q)))))))) {
            if ((0U != (((3U == (IData)(vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__pending_domain_q)) 
                         << 2U) | (((2U == (IData)(vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__pending_domain_q)) 
                                    << 1U) | (1U == (IData)(vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__pending_domain_q)))))) {
                if (VL_UNLIKELY((vlSymsp->_vm_contextp__->assertOn()))) {
                    VL_WRITEF_NX("[%0t] %%Error: tb_nvisc_memory_domain_subsystem.sv:316: Assertion failed in %m: unique case, but multiple matches found for '3'h%X'\n",4, 'M',vlSymsp->name(),"tb_nvisc_core_v02_with_mem_domains.u_memsys", 'T',-9
                                 , '#',64,VL_TIME_UNITED_Q(1000)
                                 , '#',3,(IData)(vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__pending_domain_q));
                    VL_STOP_MT("rtl/core_v02\\tb_nvisc_memory_domain_subsystem.sv", 316, "");
                }
            }
        }
    }
    tb_nvisc_core_v02_with_mem_domains__DOT__u_core__DOT__u_dec__DOT__opcode 
        = (0x0000007fU & (vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_core__DOT__u_if__DOT__fetch_q[4U] 
                          >> 3U));
    tb_nvisc_core_v02_with_mem_domains__DOT__u_core__DOT__u_dec__DOT__rd 
        = (0x0000001fU & (vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_core__DOT__u_if__DOT__fetch_q[4U] 
                          >> 0x0000000aU));
    tb_nvisc_core_v02_with_mem_domains__DOT__u_core__DOT__u_dec__DOT__funct3 
        = (7U & (vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_core__DOT__u_if__DOT__fetch_q[4U] 
                 >> 0x0000000fU));
    tb_nvisc_core_v02_with_mem_domains__DOT__u_core__DOT__u_dec__DOT__rs1 
        = (0x0000001fU & (vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_core__DOT__u_if__DOT__fetch_q[4U] 
                          >> 0x00000012U));
    tb_nvisc_core_v02_with_mem_domains__DOT__u_core__DOT__u_dec__DOT__rs2 
        = (0x0000001fU & (vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_core__DOT__u_if__DOT__fetch_q[4U] 
                          >> 0x00000017U));
    tb_nvisc_core_v02_with_mem_domains__DOT__u_core__DOT__u_dec__DOT__funct7 
        = (0x0000007fU & ((vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_core__DOT__u_if__DOT__fetch_q[5U] 
                           << 4U) | (vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_core__DOT__u_if__DOT__fetch_q[4U] 
                                     >> 0x0000001cU)));
    tb_nvisc_core_v02_with_mem_domains__DOT__u_core__DOT__u_dec__DOT__imm12_i 
        = (0x00000fffU & ((vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_core__DOT__u_if__DOT__fetch_q[5U] 
                           << 9U) | (vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_core__DOT__u_if__DOT__fetch_q[4U] 
                                     >> 0x00000017U)));
    tb_nvisc_core_v02_with_mem_domains__DOT__u_core__DOT__u_dec__DOT__imm12_s 
        = ((0x00000fe0U & ((vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_core__DOT__u_if__DOT__fetch_q[5U] 
                            << 9U) | (0x000001e0U & 
                                      (vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_core__DOT__u_if__DOT__fetch_q[4U] 
                                       >> 0x00000017U)))) 
           | (0x0000001fU & (vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_core__DOT__u_if__DOT__fetch_q[4U] 
                             >> 0x0000000aU)));
    tb_nvisc_core_v02_with_mem_domains__DOT__u_core__DOT__u_dec__DOT__imm12_selected 
        = tb_nvisc_core_v02_with_mem_domains__DOT__u_core__DOT__u_dec__DOT__imm12_i;
    if (((3U == (IData)(tb_nvisc_core_v02_with_mem_domains__DOT__u_core__DOT__u_dec__DOT__opcode)) 
         | (4U == (IData)(tb_nvisc_core_v02_with_mem_domains__DOT__u_core__DOT__u_dec__DOT__opcode)))) {
        tb_nvisc_core_v02_with_mem_domains__DOT__u_core__DOT__u_dec__DOT__imm12_selected 
            = tb_nvisc_core_v02_with_mem_domains__DOT__u_core__DOT__u_dec__DOT__imm12_s;
    }
    tb_nvisc_core_v02_with_mem_domains__DOT__u_core__DOT__u_dec__DOT__imm_ext 
        = (((- (QData)((IData)((1U & ((IData)(tb_nvisc_core_v02_with_mem_domains__DOT__u_core__DOT__u_dec__DOT__imm12_selected) 
                                      >> 0x0bU))))) 
            << 0x0000000cU) | (QData)((IData)(tb_nvisc_core_v02_with_mem_domains__DOT__u_core__DOT__u_dec__DOT__imm12_selected)));
    VL_ASSIGN_W(335, vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_core__DOT__u_dec__DOT__dec, Vtb_nvisc_core_v02_with_mem_domains__ConstPool__CONST_h09c2fdcd_0);
    vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_core__DOT__u_dec__DOT__dec[7U] 
        = ((0x00003fffU & vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_core__DOT__u_dec__DOT__dec[7U]) 
           | (0xffffc000U & (vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_core__DOT__u_if__DOT__fetch_q[4U] 
                             << 0x0000000bU)));
    vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_core__DOT__u_dec__DOT__dec[8U] 
        = (((0x00003800U & (vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_core__DOT__u_if__DOT__fetch_q[5U] 
                            << 0x0000000bU)) | (vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_core__DOT__u_if__DOT__fetch_q[4U] 
                                                >> 0x00000015U)) 
           | (0xffffc000U & (vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_core__DOT__u_if__DOT__fetch_q[5U] 
                             << 0x0000000bU)));
    vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_core__DOT__u_dec__DOT__dec[9U] 
        = (((0x00003800U & (vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_core__DOT__u_if__DOT__fetch_q[6U] 
                            << 0x0000000bU)) | (vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_core__DOT__u_if__DOT__fetch_q[5U] 
                                                >> 0x00000015U)) 
           | (0xffffc000U & (vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_core__DOT__u_if__DOT__fetch_q[6U] 
                             << 0x0000000bU)));
    vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_core__DOT__u_dec__DOT__dec[10U] 
        = (0x00007fffU & (((0x00003800U & (vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_core__DOT__u_if__DOT__fetch_q[7U] 
                                           << 0x0000000bU)) 
                           | (vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_core__DOT__u_if__DOT__fetch_q[6U] 
                              >> 0x00000015U)) | (0x00004000U 
                                                  & (vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_core__DOT__u_if__DOT__fetch_q[7U] 
                                                     << 0x0000000bU))));
    vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_core__DOT__u_dec__DOT__dec[6U] 
        = ((0x00001fffU & vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_core__DOT__u_dec__DOT__dec[6U]) 
           | (0xffffe000U & (((IData)(tb_nvisc_core_v02_with_mem_domains__DOT__u_core__DOT__u_dec__DOT__opcode) 
                              << 0x0000001cU) | (((IData)(tb_nvisc_core_v02_with_mem_domains__DOT__u_core__DOT__u_dec__DOT__rd) 
                                                  << 0x00000017U) 
                                                 | (((IData)(tb_nvisc_core_v02_with_mem_domains__DOT__u_core__DOT__u_dec__DOT__rs1) 
                                                     << 0x00000012U) 
                                                    | ((IData)(tb_nvisc_core_v02_with_mem_domains__DOT__u_core__DOT__u_dec__DOT__rs2) 
                                                       << 0x0000000dU))))));
    vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_core__DOT__u_dec__DOT__dec[7U] 
        = ((0xfffffff8U & vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_core__DOT__u_dec__DOT__dec[7U]) 
           | (0x00001fffU & ((0x00001fffU & ((IData)(tb_nvisc_core_v02_with_mem_domains__DOT__u_core__DOT__u_dec__DOT__opcode) 
                                             >> 4U)) 
                             | ((0x00001fffU & ((IData)(tb_nvisc_core_v02_with_mem_domains__DOT__u_core__DOT__u_dec__DOT__rd) 
                                                >> 9U)) 
                                | ((0x00001fffU & ((IData)(tb_nvisc_core_v02_with_mem_domains__DOT__u_core__DOT__u_dec__DOT__rs1) 
                                                   >> 0x0000000eU)) 
                                   | ((IData)(tb_nvisc_core_v02_with_mem_domains__DOT__u_core__DOT__u_dec__DOT__rs2) 
                                      >> 0x00000013U))))));
    vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_core__DOT__u_dec__DOT__dec[4U] 
        = ((0x00001fffU & vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_core__DOT__u_dec__DOT__dec[4U]) 
           | ((IData)(tb_nvisc_core_v02_with_mem_domains__DOT__u_core__DOT__u_dec__DOT__imm_ext) 
              << 0x0000000dU));
    vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_core__DOT__u_dec__DOT__dec[5U] 
        = (((IData)(tb_nvisc_core_v02_with_mem_domains__DOT__u_core__DOT__u_dec__DOT__imm_ext) 
            >> 0x00000013U) | ((IData)((tb_nvisc_core_v02_with_mem_domains__DOT__u_core__DOT__u_dec__DOT__imm_ext 
                                        >> 0x00000020U)) 
                               << 0x0000000dU));
    vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_core__DOT__u_dec__DOT__dec[6U] 
        = ((0xffffe000U & vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_core__DOT__u_dec__DOT__dec[6U]) 
           | ((IData)((tb_nvisc_core_v02_with_mem_domains__DOT__u_core__DOT__u_dec__DOT__imm_ext 
                       >> 0x00000020U)) >> 0x00000013U));
    vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_core__DOT__u_dec__DOT__dec[0U] 
        = vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_core__DOT__u_if__DOT__fetch_q[0U];
    vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_core__DOT__u_dec__DOT__dec[1U] 
        = vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_core__DOT__u_if__DOT__fetch_q[1U];
    vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_core__DOT__u_dec__DOT__dec[2U] 
        = vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_core__DOT__u_if__DOT__fetch_q[2U];
    vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_core__DOT__u_dec__DOT__dec[3U] 
        = vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_core__DOT__u_if__DOT__fetch_q[3U];
    vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_core__DOT__u_dec__DOT__dec[4U] 
        = (8U | ((0xffffffc0U & vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_core__DOT__u_dec__DOT__dec[4U]) 
                 | (7U & vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_core__DOT__u_if__DOT__fetch_q[4U])));
    vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_core__DOT__u_dec__DOT__dec[7U] 
        = (0xffffffc7U & vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_core__DOT__u_dec__DOT__dec[7U]);
    if ((0x00000040U & (IData)(tb_nvisc_core_v02_with_mem_domains__DOT__u_core__DOT__u_dec__DOT__opcode))) {
        vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_core__DOT__u_dec__DOT__dec[7U] 
            = (0x00003fc0U | vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_core__DOT__u_dec__DOT__dec[7U]);
        vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_core__DOT__u_dec__DOT__dec[4U] 
            = ((0xffffffbfU & vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_core__DOT__u_dec__DOT__dec[4U]) 
               | (0x00000040U & (vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_core__DOT__u_if__DOT__fetch_q[7U] 
                                 << 3U)));
    } else if ((0x00000020U & (IData)(tb_nvisc_core_v02_with_mem_domains__DOT__u_core__DOT__u_dec__DOT__opcode))) {
        vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_core__DOT__u_dec__DOT__dec[7U] 
            = (0x00003fc0U | vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_core__DOT__u_dec__DOT__dec[7U]);
        vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_core__DOT__u_dec__DOT__dec[4U] 
            = ((0xffffffbfU & vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_core__DOT__u_dec__DOT__dec[4U]) 
               | (0x00000040U & (vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_core__DOT__u_if__DOT__fetch_q[7U] 
                                 << 3U)));
    } else if ((0x00000010U & (IData)(tb_nvisc_core_v02_with_mem_domains__DOT__u_core__DOT__u_dec__DOT__opcode))) {
        vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_core__DOT__u_dec__DOT__dec[7U] 
            = (0x00003fc0U | vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_core__DOT__u_dec__DOT__dec[7U]);
        vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_core__DOT__u_dec__DOT__dec[4U] 
            = ((0xffffffbfU & vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_core__DOT__u_dec__DOT__dec[4U]) 
               | (0x00000040U & (vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_core__DOT__u_if__DOT__fetch_q[7U] 
                                 << 3U)));
    } else if ((8U & (IData)(tb_nvisc_core_v02_with_mem_domains__DOT__u_core__DOT__u_dec__DOT__opcode))) {
        vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_core__DOT__u_dec__DOT__dec[7U] 
            = (0x00003fc0U | vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_core__DOT__u_dec__DOT__dec[7U]);
        vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_core__DOT__u_dec__DOT__dec[4U] 
            = ((0xffffffbfU & vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_core__DOT__u_dec__DOT__dec[4U]) 
               | (0x00000040U & (vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_core__DOT__u_if__DOT__fetch_q[7U] 
                                 << 3U)));
    } else if ((4U & (IData)(tb_nvisc_core_v02_with_mem_domains__DOT__u_core__DOT__u_dec__DOT__opcode))) {
        if ((2U & (IData)(tb_nvisc_core_v02_with_mem_domains__DOT__u_core__DOT__u_dec__DOT__opcode))) {
            vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_core__DOT__u_dec__DOT__dec[7U] 
                = (0x00003fc0U | vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_core__DOT__u_dec__DOT__dec[7U]);
            vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_core__DOT__u_dec__DOT__dec[4U] 
                = ((0xffffffbfU & vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_core__DOT__u_dec__DOT__dec[4U]) 
                   | (0x00000040U & (vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_core__DOT__u_if__DOT__fetch_q[7U] 
                                     << 3U)));
        } else if ((1U & (IData)(tb_nvisc_core_v02_with_mem_domains__DOT__u_core__DOT__u_dec__DOT__opcode))) {
            vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_core__DOT__u_dec__DOT__dec[7U] 
                = (0x00000140U | (0xffffc03fU & vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_core__DOT__u_dec__DOT__dec[7U]));
            vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_core__DOT__u_dec__DOT__dec[4U] 
                = (0x00000200U | vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_core__DOT__u_dec__DOT__dec[4U]);
            vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_core__DOT__u_dec__DOT__dec[4U] 
                = (0x00001000U | vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_core__DOT__u_dec__DOT__dec[4U]);
        } else {
            vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_core__DOT__u_dec__DOT__dec[7U] 
                = (0x00000100U | (0xffffc03fU & vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_core__DOT__u_dec__DOT__dec[7U]));
            vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_core__DOT__u_dec__DOT__dec[4U] 
                = (0x00000080U | vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_core__DOT__u_dec__DOT__dec[4U]);
        }
    } else if ((2U & (IData)(tb_nvisc_core_v02_with_mem_domains__DOT__u_core__DOT__u_dec__DOT__opcode))) {
        if ((1U & (IData)(tb_nvisc_core_v02_with_mem_domains__DOT__u_core__DOT__u_dec__DOT__opcode))) {
            vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_core__DOT__u_dec__DOT__dec[7U] 
                = (0x000000c0U | (0xffffc03fU & vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_core__DOT__u_dec__DOT__dec[7U]));
            vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_core__DOT__u_dec__DOT__dec[4U] 
                = (0x00000400U | vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_core__DOT__u_dec__DOT__dec[4U]);
            vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_core__DOT__u_dec__DOT__dec[4U] 
                = (8U | (0xffffffc7U & vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_core__DOT__u_dec__DOT__dec[4U]));
            vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_core__DOT__u_dec__DOT__dec[7U] 
                = (0xffffffc7U & vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_core__DOT__u_dec__DOT__dec[7U]);
        } else {
            vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_core__DOT__u_dec__DOT__dec[7U] 
                = (0x00000080U | (0xffffc03fU & vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_core__DOT__u_dec__DOT__dec[7U]));
            vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_core__DOT__u_dec__DOT__dec[4U] 
                = (0x00001800U | vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_core__DOT__u_dec__DOT__dec[4U]);
            vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_core__DOT__u_dec__DOT__dec[4U] 
                = (8U | (0xffffffc7U & vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_core__DOT__u_dec__DOT__dec[4U]));
            vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_core__DOT__u_dec__DOT__dec[7U] 
                = (0xffffffc7U & vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_core__DOT__u_dec__DOT__dec[7U]);
        }
    } else if ((1U & (IData)(tb_nvisc_core_v02_with_mem_domains__DOT__u_core__DOT__u_dec__DOT__opcode))) {
        vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_core__DOT__u_dec__DOT__dec[7U] 
            = (0x00000040U | (0xffffc03fU & vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_core__DOT__u_dec__DOT__dec[7U]));
        vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_core__DOT__u_dec__DOT__dec[4U] 
            = (0x00001000U | vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_core__DOT__u_dec__DOT__dec[4U]);
        if ((4U & (IData)(tb_nvisc_core_v02_with_mem_domains__DOT__u_core__DOT__u_dec__DOT__funct3))) {
            if ((2U & (IData)(tb_nvisc_core_v02_with_mem_domains__DOT__u_core__DOT__u_dec__DOT__funct3))) {
                vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_core__DOT__u_dec__DOT__dec[7U] 
                    = ((0xffffffc7U & vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_core__DOT__u_dec__DOT__dec[7U]) 
                       | (((1U & (IData)(tb_nvisc_core_v02_with_mem_domains__DOT__u_core__DOT__u_dec__DOT__funct3))
                            ? 2U : 3U) << 3U));
            } else if ((1U & (IData)(tb_nvisc_core_v02_with_mem_domains__DOT__u_core__DOT__u_dec__DOT__funct3))) {
                vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_core__DOT__u_dec__DOT__dec[7U] 
                    = (0x00003fc0U | vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_core__DOT__u_dec__DOT__dec[7U]);
                vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_core__DOT__u_dec__DOT__dec[4U] 
                    = (0xffffefffU & vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_core__DOT__u_dec__DOT__dec[4U]);
                vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_core__DOT__u_dec__DOT__dec[4U] 
                    = ((0xffffffbfU & vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_core__DOT__u_dec__DOT__dec[4U]) 
                       | (0x00000040U & (vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_core__DOT__u_if__DOT__fetch_q[7U] 
                                         << 3U)));
            } else {
                vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_core__DOT__u_dec__DOT__dec[7U] 
                    = (0x00000020U | (0xffffffc7U & vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_core__DOT__u_dec__DOT__dec[7U]));
            }
        } else if ((2U & (IData)(tb_nvisc_core_v02_with_mem_domains__DOT__u_core__DOT__u_dec__DOT__funct3))) {
            if ((1U & (IData)(tb_nvisc_core_v02_with_mem_domains__DOT__u_core__DOT__u_dec__DOT__funct3))) {
                vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_core__DOT__u_dec__DOT__dec[7U] 
                    = (0x00003fc0U | vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_core__DOT__u_dec__DOT__dec[7U]);
                vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_core__DOT__u_dec__DOT__dec[4U] 
                    = (0xffffefffU & vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_core__DOT__u_dec__DOT__dec[4U]);
                vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_core__DOT__u_dec__DOT__dec[4U] 
                    = ((0xffffffbfU & vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_core__DOT__u_dec__DOT__dec[4U]) 
                       | (0x00000040U & (vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_core__DOT__u_if__DOT__fetch_q[7U] 
                                         << 3U)));
            } else {
                vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_core__DOT__u_dec__DOT__dec[7U] 
                    = (0x00000028U | (0xffffffc7U & vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_core__DOT__u_dec__DOT__dec[7U]));
            }
        } else if ((1U & (IData)(tb_nvisc_core_v02_with_mem_domains__DOT__u_core__DOT__u_dec__DOT__funct3))) {
            vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_core__DOT__u_dec__DOT__dec[7U] 
                = (0x00003fc0U | vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_core__DOT__u_dec__DOT__dec[7U]);
            vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_core__DOT__u_dec__DOT__dec[4U] 
                = (0xffffefffU & vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_core__DOT__u_dec__DOT__dec[4U]);
            vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_core__DOT__u_dec__DOT__dec[4U] 
                = ((0xffffffbfU & vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_core__DOT__u_dec__DOT__dec[4U]) 
                   | (0x00000040U & (vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_core__DOT__u_if__DOT__fetch_q[7U] 
                                     << 3U)));
        } else {
            vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_core__DOT__u_dec__DOT__dec[7U] 
                = ((0xffffffc7U & vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_core__DOT__u_dec__DOT__dec[7U]) 
                   | (((0x20U == (IData)(tb_nvisc_core_v02_with_mem_domains__DOT__u_core__DOT__u_dec__DOT__funct7))
                        ? 1U : 0U) << 3U));
        }
    } else {
        vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_core__DOT__u_dec__DOT__dec[7U] 
            = (0xffffc03fU & vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_core__DOT__u_dec__DOT__dec[7U]);
    }
    if ((1U & (~ (vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_core__DOT__u_if__DOT__fetch_q[7U] 
                  >> 3U)))) {
        vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_core__DOT__u_dec__DOT__dec[10U] 
            = (0x00003fffU & vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_core__DOT__u_dec__DOT__dec[10U]);
        vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_core__DOT__u_dec__DOT__dec[4U] 
            = (0xffffffbfU & vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_core__DOT__u_dec__DOT__dec[4U]);
    }
    vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_memdom_csr__DOT__effective_domain_c 
        = ((IData)(vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_memdom_csr__DOT__mem_domain_override_enable_q)
            ? (IData)(vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_memdom_csr__DOT__mem_domain_select_q)
            : (IData)(vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__wrapper_override_domain_w));
    vlSelfRef.memsys_resp_write_ack_o = tb_nvisc_core_v02_with_mem_domains__DOT__memsys_resp_write_ack_w;
    vlSelfRef.memsys_resp_rdata_o = vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__memsys_resp_rdata_w;
    vlSelfRef.load_wb_data_o = vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__memsys_resp_rdata_w;
    vlSelfRef.memsys_fault_code_o = tb_nvisc_core_v02_with_mem_domains__DOT__memsys_fault_code_w;
    vlSelfRef.memsys_resp_valid_o = vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__memsys_resp_valid_w;
    vlSelfRef.memsys_fault_o = vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__memsys_fault_w;
    vlSelfRef.load_wb_valid_o = ((IData)(vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__memsys_resp_valid_w) 
                                 & ((~ (IData)(vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__memsys_fault_w)) 
                                    & (IData)(vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_core__DOT__load_pending_q)));
    vlSelfRef.decode_class_o = (0x000000ffU & (vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_core__DOT__u_dec__DOT__dec[7U] 
                                               >> 6U));
    vlSelfRef.branch_target_internal_o = ((((QData)((IData)(vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_core__DOT__u_dec__DOT__dec[10U])) 
                                            << 0x00000032U) 
                                           | (((QData)((IData)(vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_core__DOT__u_dec__DOT__dec[9U])) 
                                               << 0x00000012U) 
                                              | ((QData)((IData)(vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_core__DOT__u_dec__DOT__dec[8U])) 
                                                 >> 0x0000000eU))) 
                                          + (((QData)((IData)(vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_core__DOT__u_dec__DOT__dec[6U])) 
                                              << 0x00000033U) 
                                             | (((QData)((IData)(vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_core__DOT__u_dec__DOT__dec[5U])) 
                                                 << 0x00000013U) 
                                                | ((QData)((IData)(vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_core__DOT__u_dec__DOT__dec[4U])) 
                                                   >> 0x0000000dU))));
    vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_core__DOT__rs1_data_w 
        = ((0U == (0x0000001fU & (vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_core__DOT__u_dec__DOT__dec[6U] 
                                  >> 0x00000012U)))
            ? 0ULL : vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_core__DOT__u_rf__DOT__regs_q
           [(0x0000001fU & (vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_core__DOT__u_dec__DOT__dec[6U] 
                            >> 0x00000012U))]);
    vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_core__DOT__rs2_data_w 
        = ((0U == (0x0000001fU & (vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_core__DOT__u_dec__DOT__dec[6U] 
                                  >> 0x0000000dU)))
            ? 0ULL : vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_core__DOT__u_rf__DOT__regs_q
           [(0x0000001fU & (vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_core__DOT__u_dec__DOT__dec[6U] 
                            >> 0x0000000dU))]);
    vlSelfRef.alu_valid_o = 0U;
    vlSelfRef.lsu_valid_o = 0U;
    vlSelfRef.csr_valid_o = 0U;
    vlSelfRef.branch_valid_o = 0U;
    vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_core__DOT__ctrl_reg_write_w = 0U;
    vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_core__DOT__ctrl_mem_read_w = 0U;
    vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_core__DOT__ctrl_mem_write_w = 0U;
    tb_nvisc_core_v02_with_mem_domains__DOT__u_core__DOT__ctrl_trap_w = 0U;
    tb_nvisc_core_v02_with_mem_domains__DOT__u_core__DOT__ctrl_trap_code_w = 0U;
    if ((0x00004000U & vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_core__DOT__u_dec__DOT__dec[10U])) {
        if ((0U != (0x000000ffU & (vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_core__DOT__u_dec__DOT__dec[7U] 
                                   >> 6U)))) {
            if ((1U == (0x000000ffU & (vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_core__DOT__u_dec__DOT__dec[7U] 
                                       >> 6U)))) {
                vlSelfRef.alu_valid_o = 1U;
                vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_core__DOT__ctrl_reg_write_w 
                    = (1U & (vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_core__DOT__u_dec__DOT__dec[4U] 
                             >> 0x0000000cU));
            } else if ((2U == (0x000000ffU & (vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_core__DOT__u_dec__DOT__dec[7U] 
                                              >> 6U)))) {
                vlSelfRef.lsu_valid_o = 1U;
                vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_core__DOT__ctrl_mem_read_w 
                    = (1U & (vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_core__DOT__u_dec__DOT__dec[4U] 
                             >> 0x0000000bU));
                vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_core__DOT__ctrl_reg_write_w 
                    = (1U & (vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_core__DOT__u_dec__DOT__dec[4U] 
                             >> 0x0000000cU));
            } else if ((3U == (0x000000ffU & (vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_core__DOT__u_dec__DOT__dec[7U] 
                                              >> 6U)))) {
                vlSelfRef.lsu_valid_o = 1U;
                vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_core__DOT__ctrl_mem_write_w 
                    = (1U & (vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_core__DOT__u_dec__DOT__dec[4U] 
                             >> 0x0000000aU));
            } else if ((4U == (0x000000ffU & (vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_core__DOT__u_dec__DOT__dec[7U] 
                                              >> 6U)))) {
                vlSelfRef.branch_valid_o = 1U;
            } else if ((5U == (0x000000ffU & (vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_core__DOT__u_dec__DOT__dec[7U] 
                                              >> 6U)))) {
                vlSelfRef.csr_valid_o = 1U;
                vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_core__DOT__ctrl_reg_write_w 
                    = (1U & (vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_core__DOT__u_dec__DOT__dec[4U] 
                             >> 0x0000000cU));
            } else {
                tb_nvisc_core_v02_with_mem_domains__DOT__u_core__DOT__ctrl_trap_w = 1U;
                tb_nvisc_core_v02_with_mem_domains__DOT__u_core__DOT__ctrl_trap_code_w = 1U;
            }
        }
        if ((1U & (~ VL_ONEHOT_I(((((5U == (0x000000ffU 
                                            & (vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_core__DOT__u_dec__DOT__dec[7U] 
                                               >> 6U))) 
                                    << 5U) | (((4U 
                                                == 
                                                (0x000000ffU 
                                                 & (vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_core__DOT__u_dec__DOT__dec[7U] 
                                                    >> 6U))) 
                                               << 4U) 
                                              | ((3U 
                                                  == 
                                                  (0x000000ffU 
                                                   & (vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_core__DOT__u_dec__DOT__dec[7U] 
                                                      >> 6U))) 
                                                 << 3U))) 
                                  | (((2U == (0x000000ffU 
                                              & (vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_core__DOT__u_dec__DOT__dec[7U] 
                                                 >> 6U))) 
                                      << 2U) | (((1U 
                                                  == 
                                                  (0x000000ffU 
                                                   & (vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_core__DOT__u_dec__DOT__dec[7U] 
                                                      >> 6U))) 
                                                 << 1U) 
                                                | (0U 
                                                   == 
                                                   (0x000000ffU 
                                                    & (vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_core__DOT__u_dec__DOT__dec[7U] 
                                                       >> 6U)))))))))) {
            if ((0U != ((((5U == (0x000000ffU & (vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_core__DOT__u_dec__DOT__dec[7U] 
                                                 >> 6U))) 
                          << 5U) | (((4U == (0x000000ffU 
                                             & (vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_core__DOT__u_dec__DOT__dec[7U] 
                                                >> 6U))) 
                                     << 4U) | ((3U 
                                                == 
                                                (0x000000ffU 
                                                 & (vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_core__DOT__u_dec__DOT__dec[7U] 
                                                    >> 6U))) 
                                               << 3U))) 
                        | (((2U == (0x000000ffU & (vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_core__DOT__u_dec__DOT__dec[7U] 
                                                   >> 6U))) 
                            << 2U) | (((1U == (0x000000ffU 
                                               & (vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_core__DOT__u_dec__DOT__dec[7U] 
                                                  >> 6U))) 
                                       << 1U) | (0U 
                                                 == 
                                                 (0x000000ffU 
                                                  & (vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_core__DOT__u_dec__DOT__dec[7U] 
                                                     >> 6U)))))))) {
                if (VL_UNLIKELY((vlSymsp->_vm_contextp__->assertOn()))) {
                    VL_WRITEF_NX("[%0t] %%Error: nvisc_control_unit.sv:67: Assertion failed in %m: unique case, but multiple matches found for '8'h%X'\n",4, 'M',vlSymsp->name(),"tb_nvisc_core_v02_with_mem_domains.u_core.u_ctrl", 'T',-9
                                 , '#',64,VL_TIME_UNITED_Q(1000)
                                 , '#',8,(0x000000ffU 
                                          & (vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_core__DOT__u_dec__DOT__dec[7U] 
                                             >> 6U)));
                    VL_STOP_MT("rtl/core_v02\\nvisc_control_unit.sv", 67, "");
                }
            }
        }
        if ((0x00000040U & vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_core__DOT__u_dec__DOT__dec[4U])) {
            tb_nvisc_core_v02_with_mem_domains__DOT__u_core__DOT__ctrl_trap_w = 1U;
            tb_nvisc_core_v02_with_mem_domains__DOT__u_core__DOT__ctrl_trap_code_w = 1U;
        }
    }
    vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_core__DOT__branch_taken_w = 0U;
    if (vlSelfRef.branch_valid_o) {
        if ((vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_core__DOT__rs1_data_w 
             == vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_core__DOT__rs2_data_w)) {
            vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_core__DOT__branch_taken_w = 1U;
        }
    }
    vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_core__DOT__u_lsu__DOT__both_read_write_c 
        = ((IData)(vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_core__DOT__ctrl_mem_read_w) 
           & (IData)(vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_core__DOT__ctrl_mem_write_w));
    vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_core__DOT__u_lsu__DOT__no_op_c 
        = (1U & (~ ((IData)(vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_core__DOT__ctrl_mem_read_w) 
                    | (IData)(vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_core__DOT__ctrl_mem_write_w))));
    tb_nvisc_core_v02_with_mem_domains__DOT__u_core__DOT__u_alu__DOT__fault_code_c = 0U;
    vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_core__DOT__u_alu__DOT__result_c = 0ULL;
    tb_nvisc_core_v02_with_mem_domains__DOT__u_core__DOT__u_alu__DOT__overflow_c = 0U;
    tb_nvisc_core_v02_with_mem_domains__DOT__u_core__DOT__u_alu__DOT__fault_c = 0U;
    if (vlSelfRef.alu_valid_o) {
        if ((0x00000020U & vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_core__DOT__u_dec__DOT__dec[7U])) {
            if ((0x00000010U & vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_core__DOT__u_dec__DOT__dec[7U])) {
                tb_nvisc_core_v02_with_mem_domains__DOT__u_core__DOT__u_alu__DOT__fault_code_c = 0x0201U;
                tb_nvisc_core_v02_with_mem_domains__DOT__u_core__DOT__u_alu__DOT__fault_c = 1U;
            }
            if ((1U & (~ (vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_core__DOT__u_dec__DOT__dec[7U] 
                          >> 4U)))) {
                vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_core__DOT__u_alu__DOT__result_c 
                    = ((8U & vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_core__DOT__u_dec__DOT__dec[7U])
                        ? (VL_LTS_IQQ(64, vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_core__DOT__rs1_data_w, vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_core__DOT__rs2_data_w)
                            ? 1ULL : 0ULL) : (vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_core__DOT__rs1_data_w 
                                              ^ vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_core__DOT__rs2_data_w));
            }
        } else if ((0x00000010U & vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_core__DOT__u_dec__DOT__dec[7U])) {
            vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_core__DOT__u_alu__DOT__result_c 
                = ((8U & vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_core__DOT__u_dec__DOT__dec[7U])
                    ? (vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_core__DOT__rs1_data_w 
                       | vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_core__DOT__rs2_data_w)
                    : (vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_core__DOT__rs1_data_w 
                       & vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_core__DOT__rs2_data_w));
        } else if ((8U & vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_core__DOT__u_dec__DOT__dec[7U])) {
            vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_core__DOT__u_alu__DOT__result_c 
                = (vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_core__DOT__rs1_data_w 
                   - vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_core__DOT__rs2_data_w);
            tb_nvisc_core_v02_with_mem_domains__DOT__u_core__DOT__u_alu__DOT__overflow_c 
                = (1U & (((IData)((vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_core__DOT__rs1_data_w 
                                   >> 0x3fU)) ^ (IData)(
                                                        (vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_core__DOT__rs2_data_w 
                                                         >> 0x3fU))) 
                         & ((IData)((vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_core__DOT__u_alu__DOT__result_c 
                                     >> 0x3fU)) ^ (IData)(
                                                          (vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_core__DOT__rs1_data_w 
                                                           >> 0x3fU)))));
        } else {
            vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_core__DOT__u_alu__DOT__result_c 
                = (vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_core__DOT__rs1_data_w 
                   + vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_core__DOT__rs2_data_w);
            tb_nvisc_core_v02_with_mem_domains__DOT__u_core__DOT__u_alu__DOT__overflow_c 
                = (1U & ((~ ((IData)((vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_core__DOT__rs1_data_w 
                                      >> 0x3fU)) ^ (IData)(
                                                           (vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_core__DOT__rs2_data_w 
                                                            >> 0x3fU)))) 
                         & ((IData)((vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_core__DOT__u_alu__DOT__result_c 
                                     >> 0x3fU)) ^ (IData)(
                                                          (vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_core__DOT__rs1_data_w 
                                                           >> 0x3fU)))));
        }
    }
    vlSelfRef.branch_taken_internal_o = vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_core__DOT__branch_taken_w;
    vlSelfRef.alu_result_o = vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_core__DOT__u_alu__DOT__result_c;
    vlSelfRef.core_fault_o = 0U;
    vlSelfRef.core_fault_code_o = 0U;
    if (vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_core__DOT__u_if__DOT__fault_q) {
        vlSelfRef.core_fault_o = 1U;
        vlSelfRef.core_fault_code_o = vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_core__DOT__u_if__DOT__fault_code_q;
    } else if (tb_nvisc_core_v02_with_mem_domains__DOT__u_core__DOT__ctrl_trap_w) {
        vlSelfRef.core_fault_o = 1U;
        vlSelfRef.core_fault_code_o = tb_nvisc_core_v02_with_mem_domains__DOT__u_core__DOT__ctrl_trap_code_w;
    } else if (tb_nvisc_core_v02_with_mem_domains__DOT__u_core__DOT__u_alu__DOT__fault_c) {
        vlSelfRef.core_fault_o = 1U;
        vlSelfRef.core_fault_code_o = tb_nvisc_core_v02_with_mem_domains__DOT__u_core__DOT__u_alu__DOT__fault_code_c;
    } else if (vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_core__DOT__mmu_fault_w) {
        vlSelfRef.core_fault_o = 1U;
        vlSelfRef.core_fault_code_o = vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_core__DOT__mmu_fault_code_w;
    } else if (vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__memsys_fault_w) {
        vlSelfRef.core_fault_o = 1U;
        vlSelfRef.core_fault_code_o = tb_nvisc_core_v02_with_mem_domains__DOT__memsys_fault_code_w;
    } else if (vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_core__DOT__lsu_fault_w) {
        vlSelfRef.core_fault_o = 1U;
        vlSelfRef.core_fault_code_o = vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_core__DOT__lsu_fault_code_w;
    } else if (vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_core__DOT__csr_fault_w) {
        vlSelfRef.core_fault_o = 1U;
        vlSelfRef.core_fault_code_o = vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_core__DOT__csr_fault_code_w;
    }
    vlSelfRef.alu_result_valid_o = ((~ (IData)(tb_nvisc_core_v02_with_mem_domains__DOT__u_core__DOT__u_alu__DOT__fault_c)) 
                                    & (IData)(vlSelfRef.alu_valid_o));
    vlSelfRef.alu_zero_o = ((0ULL == vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_core__DOT__u_alu__DOT__result_c) 
                            & (IData)(vlSelfRef.alu_result_valid_o));
    vlSelfRef.alu_negative_o = ((IData)((vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_core__DOT__u_alu__DOT__result_c 
                                         >> 0x0000003fU)) 
                                & (IData)(vlSelfRef.alu_result_valid_o));
    vlSelfRef.alu_overflow_o = ((IData)(tb_nvisc_core_v02_with_mem_domains__DOT__u_core__DOT__u_alu__DOT__overflow_c) 
                                & (IData)(vlSelfRef.alu_result_valid_o));
    vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_core__DOT__rf_we_w 
        = vlSelfRef.dbg_rf_we_i;
    vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_core__DOT__rf_waddr_w 
        = vlSelfRef.dbg_rf_waddr_i;
    if (((~ (IData)(vlSelfRef.dbg_rf_we_i)) & (IData)(vlSelfRef.load_wb_valid_o))) {
        vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_core__DOT__rf_we_w = 1U;
        vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_core__DOT__rf_waddr_w 
            = vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_core__DOT__load_rd_q;
        vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_core__DOT__rf_wdata_w 
            = vlSelfRef.dbg_rf_wdata_i;
        vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_core__DOT__rf_wdata_w 
            = vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__memsys_resp_rdata_w;
    } else {
        vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_core__DOT__rf_wdata_w 
            = vlSelfRef.dbg_rf_wdata_i;
    }
    if (((((~ (IData)(vlSelfRef.dbg_rf_we_i)) & (~ (IData)(vlSelfRef.load_wb_valid_o))) 
          & (IData)(vlSelfRef.alu_result_valid_o)) 
         & (IData)(vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_core__DOT__ctrl_reg_write_w))) {
        vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_core__DOT__rf_we_w = 1U;
        vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_core__DOT__rf_waddr_w 
            = (0x0000001fU & (vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_core__DOT__u_dec__DOT__dec[6U] 
                              >> 0x00000017U));
        vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_core__DOT__rf_wdata_w 
            = vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_core__DOT__u_alu__DOT__result_c;
    }
}

VL_ATTR_COLD void Vtb_nvisc_core_v02_with_mem_domains___024root___eval_stl(Vtb_nvisc_core_v02_with_mem_domains___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_nvisc_core_v02_with_mem_domains___024root___eval_stl\n"); );
    Vtb_nvisc_core_v02_with_mem_domains__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    if ((1ULL & vlSelfRef.__VstlTriggered[0U])) {
        Vtb_nvisc_core_v02_with_mem_domains___024root___stl_sequent__TOP__0(vlSelf);
    }
}

VL_ATTR_COLD bool Vtb_nvisc_core_v02_with_mem_domains___024root___eval_phase__stl(Vtb_nvisc_core_v02_with_mem_domains___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_nvisc_core_v02_with_mem_domains___024root___eval_phase__stl\n"); );
    Vtb_nvisc_core_v02_with_mem_domains__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Locals
    CData/*0:0*/ __VstlExecute;
    // Body
    Vtb_nvisc_core_v02_with_mem_domains___024root___eval_triggers_vec__stl(vlSelf);
#ifdef VL_DEBUG
    if (VL_UNLIKELY(vlSymsp->_vm_contextp__->debug())) {
        Vtb_nvisc_core_v02_with_mem_domains___024root___dump_triggers__stl(vlSelfRef.__VstlTriggered, "stl"s);
    }
#endif
    __VstlExecute = Vtb_nvisc_core_v02_with_mem_domains___024root___trigger_anySet__stl(vlSelfRef.__VstlTriggered);
    if (__VstlExecute) {
        Vtb_nvisc_core_v02_with_mem_domains___024root___eval_stl(vlSelf);
    }
    return (__VstlExecute);
}

bool Vtb_nvisc_core_v02_with_mem_domains___024root___trigger_anySet__ico(const VlUnpacked<QData/*63:0*/, 1> &in);

#ifdef VL_DEBUG
VL_ATTR_COLD void Vtb_nvisc_core_v02_with_mem_domains___024root___dump_triggers__ico(const VlUnpacked<QData/*63:0*/, 1> &triggers, const std::string &tag) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_nvisc_core_v02_with_mem_domains___024root___dump_triggers__ico\n"); );
    // Body
    if ((1U & (~ (IData)(Vtb_nvisc_core_v02_with_mem_domains___024root___trigger_anySet__ico(triggers))))) {
        VL_DBG_MSGS("         No '" + tag + "' region triggers active\n");
    }
    if ((1U & (IData)(triggers[0U]))) {
        VL_DBG_MSGS("         '" + tag + "' region trigger index 0 is active: Internal 'ico' trigger - first iteration\n");
    }
}
#endif  // VL_DEBUG

bool Vtb_nvisc_core_v02_with_mem_domains___024root___trigger_anySet__act(const VlUnpacked<QData/*63:0*/, 1> &in);

#ifdef VL_DEBUG
VL_ATTR_COLD void Vtb_nvisc_core_v02_with_mem_domains___024root___dump_triggers__act(const VlUnpacked<QData/*63:0*/, 1> &triggers, const std::string &tag) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_nvisc_core_v02_with_mem_domains___024root___dump_triggers__act\n"); );
    // Body
    if ((1U & (~ (IData)(Vtb_nvisc_core_v02_with_mem_domains___024root___trigger_anySet__act(triggers))))) {
        VL_DBG_MSGS("         No '" + tag + "' region triggers active\n");
    }
    if ((1U & (IData)(triggers[0U]))) {
        VL_DBG_MSGS("         '" + tag + "' region trigger index 0 is active: @(posedge clk)\n");
    }
    if ((1U & (IData)((triggers[0U] >> 1U)))) {
        VL_DBG_MSGS("         '" + tag + "' region trigger index 1 is active: @(negedge rst_n)\n");
    }
}
#endif  // VL_DEBUG

VL_ATTR_COLD void Vtb_nvisc_core_v02_with_mem_domains___024root___ctor_var_reset(Vtb_nvisc_core_v02_with_mem_domains___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_nvisc_core_v02_with_mem_domains___024root___ctor_var_reset\n"); );
    Vtb_nvisc_core_v02_with_mem_domains__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    const uint64_t __VscopeHash = VL_MURMUR64_HASH(vlSelf->vlNamep);
    vlSelf->clk = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 16707436170211756652ull);
    vlSelf->rst_n = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 1638864771569018232ull);
    vlSelf->imem_resp_valid_i = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 16638698067570457990ull);
    vlSelf->imem_resp_instr_i = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 16968054974070884669ull);
    vlSelf->imem_resp_fault_i = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 17697440477334768216ull);
    vlSelf->imem_resp_fault_code_i = VL_SCOPED_RAND_RESET_I(16, __VscopeHash, 12223516124430957681ull);
    vlSelf->thread_id_i = VL_SCOPED_RAND_RESET_I(8, __VscopeHash, 14491746936754564230ull);
    vlSelf->branch_id_i = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 8755824948894417277ull);
    vlSelf->state_id_i = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 15678071621078952526ull);
    vlSelf->commit_id_i = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 517556249703001847ull);
    vlSelf->privilege_i = VL_SCOPED_RAND_RESET_I(3, __VscopeHash, 5860785198612651058ull);
    vlSelf->aegis_policy_id_i = VL_SCOPED_RAND_RESET_I(16, __VscopeHash, 17668345155559506627ull);
    vlSelf->lsu_base_value_i = VL_SCOPED_RAND_RESET_Q(64, __VscopeHash, 334750963891327010ull);
    vlSelf->lsu_store_data_i = VL_SCOPED_RAND_RESET_Q(64, __VscopeHash, 5767665728978274330ull);
    vlSelf->lsu_size_bytes_i = VL_SCOPED_RAND_RESET_I(8, __VscopeHash, 16739217472377482601ull);
    vlSelf->dbg_rf_we_i = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 10289339781363864045ull);
    vlSelf->dbg_rf_waddr_i = VL_SCOPED_RAND_RESET_I(5, __VscopeHash, 6191477237130370102ull);
    vlSelf->dbg_rf_wdata_i = VL_SCOPED_RAND_RESET_Q(64, __VscopeHash, 4719366851184750190ull);
    vlSelf->stall_i = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 6422829819824836280ull);
    vlSelf->flush_i = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 12823618135036147526ull);
    vlSelf->redirect_valid_i = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 9921512748266401153ull);
    vlSelf->redirect_pc_i = VL_SCOPED_RAND_RESET_Q(64, __VscopeHash, 8483376357496056553ull);
    vlSelf->branch_taken_i = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 2194808769932859071ull);
    vlSelf->branch_target_i = VL_SCOPED_RAND_RESET_Q(64, __VscopeHash, 17149295761068401404ull);
    vlSelf->trap_valid_i = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 17674465530870728177ull);
    vlSelf->trap_vector_i = VL_SCOPED_RAND_RESET_Q(64, __VscopeHash, 15587047278558901619ull);
    vlSelf->rollback_redirect_i = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 5829100977624310036ull);
    vlSelf->rollback_pc_i = VL_SCOPED_RAND_RESET_Q(64, __VscopeHash, 832766564151712205ull);
    vlSelf->mem_domain_override_valid_i = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 12475944428482012537ull);
    vlSelf->mem_domain_override_i = VL_SCOPED_RAND_RESET_I(3, __VscopeHash, 2718549825093296335ull);
    vlSelf->memdom_csr_valid_i = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 16692769941482742679ull);
    vlSelf->memdom_csr_write_i = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 9822346547652421025ull);
    vlSelf->memdom_csr_read_i = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 16040337463830392626ull);
    vlSelf->memdom_csr_addr_i = VL_SCOPED_RAND_RESET_I(12, __VscopeHash, 14943485100534420902ull);
    vlSelf->memdom_csr_wdata_i = VL_SCOPED_RAND_RESET_Q(64, __VscopeHash, 17767980387651045991ull);
    vlSelf->memdom_csr_resp_valid_o = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 8045545332231549293ull);
    vlSelf->memdom_csr_rdata_o = VL_SCOPED_RAND_RESET_Q(64, __VscopeHash, 1141602721551224175ull);
    vlSelf->memdom_csr_fault_o = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 6904721835646295847ull);
    vlSelf->memdom_csr_fault_code_o = VL_SCOPED_RAND_RESET_I(16, __VscopeHash, 13084971655358262594ull);
    vlSelf->imem_req_valid_o = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 11566933197308787897ull);
    vlSelf->imem_req_addr_o = VL_SCOPED_RAND_RESET_Q(64, __VscopeHash, 1395739073743930077ull);
    vlSelf->pc_o = VL_SCOPED_RAND_RESET_Q(64, __VscopeHash, 12049352105174271456ull);
    vlSelf->pc_valid_o = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 783514939669681687ull);
    vlSelf->fetch_valid_o = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 4351242466155816649ull);
    vlSelf->fetch_instr_o = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 13301149240284153373ull);
    vlSelf->decode_class_o = VL_SCOPED_RAND_RESET_I(8, __VscopeHash, 7374639534792209528ull);
    vlSelf->dbg_rf_r1_o = VL_SCOPED_RAND_RESET_Q(64, __VscopeHash, 10340362236902051114ull);
    vlSelf->dbg_rf_r2_o = VL_SCOPED_RAND_RESET_Q(64, __VscopeHash, 9421668802662609781ull);
    vlSelf->dbg_rf_r3_o = VL_SCOPED_RAND_RESET_Q(64, __VscopeHash, 14989097336297585196ull);
    vlSelf->alu_result_valid_o = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 6234226699728058059ull);
    vlSelf->alu_result_o = VL_SCOPED_RAND_RESET_Q(64, __VscopeHash, 16474669768512604924ull);
    vlSelf->alu_zero_o = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 15759345831680215118ull);
    vlSelf->alu_negative_o = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 9630094875556141371ull);
    vlSelf->alu_overflow_o = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 14843974399233313188ull);
    vlSelf->branch_taken_internal_o = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 6372717577535688537ull);
    vlSelf->branch_target_internal_o = VL_SCOPED_RAND_RESET_Q(64, __VscopeHash, 301404983845926270ull);
    vlSelf->alu_valid_o = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 17846802122589891230ull);
    vlSelf->lsu_valid_o = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 4879334220471641836ull);
    vlSelf->csr_valid_o = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 4005406974490887882ull);
    vlSelf->branch_valid_o = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 16291574195784206795ull);
    vlSelf->mem_req_valid_o = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 15939682335504899554ull);
    vlSelf->mem_req_is_read_o = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 3486757219916037115ull);
    vlSelf->mem_req_is_write_o = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 11336626877148348927ull);
    vlSelf->mem_req_vaddr_o = VL_SCOPED_RAND_RESET_Q(64, __VscopeHash, 716957763697864033ull);
    vlSelf->mem_req_paddr_o = VL_SCOPED_RAND_RESET_Q(64, __VscopeHash, 8322224779004021789ull);
    vlSelf->mem_req_wdata_o = VL_SCOPED_RAND_RESET_Q(64, __VscopeHash, 9637553956413752883ull);
    vlSelf->mem_req_size_bytes_o = VL_SCOPED_RAND_RESET_I(8, __VscopeHash, 13340449774381197835ull);
    vlSelf->mem_req_domain_o = VL_SCOPED_RAND_RESET_I(3, __VscopeHash, 17625156055120178086ull);
    vlSelf->memsys_resp_valid_o = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 8465615882432232654ull);
    vlSelf->memsys_resp_rdata_o = VL_SCOPED_RAND_RESET_Q(64, __VscopeHash, 17427973010546307403ull);
    vlSelf->memsys_resp_write_ack_o = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 533323022146849115ull);
    vlSelf->memsys_fault_o = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 5383532667709372648ull);
    vlSelf->memsys_fault_code_o = VL_SCOPED_RAND_RESET_I(16, __VscopeHash, 5629752620061614481ull);
    vlSelf->dbg_data_route_valid_o = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 18317900487392794846ull);
    vlSelf->dbg_exec_route_valid_o = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 14398515772693165808ull);
    vlSelf->dbg_livehot_route_valid_o = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 6835561494755167707ull);
    vlSelf->load_wb_valid_o = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 10918508971267472976ull);
    vlSelf->load_wb_data_o = VL_SCOPED_RAND_RESET_Q(64, __VscopeHash, 4030588292749206829ull);
    vlSelf->core_fault_o = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 3976923580098010762ull);
    vlSelf->core_fault_code_o = VL_SCOPED_RAND_RESET_I(16, __VscopeHash, 13289095538541318757ull);
    vlSelf->tb_nvisc_core_v02_with_mem_domains__DOT__wrapper_override_domain_w = VL_SCOPED_RAND_RESET_I(3, __VscopeHash, 3498567118215365860ull);
    vlSelf->tb_nvisc_core_v02_with_mem_domains__DOT__memsys_resp_valid_w = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 12380250601509602163ull);
    vlSelf->tb_nvisc_core_v02_with_mem_domains__DOT__memsys_resp_rdata_w = VL_SCOPED_RAND_RESET_Q(64, __VscopeHash, 13230470714520002919ull);
    vlSelf->tb_nvisc_core_v02_with_mem_domains__DOT__memsys_fault_w = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 13658630712501711046ull);
    vlSelf->tb_nvisc_core_v02_with_mem_domains__DOT__u_memdom_csr__DOT__mem_domain_select_q = VL_SCOPED_RAND_RESET_I(3, __VscopeHash, 12591011050856108350ull);
    vlSelf->tb_nvisc_core_v02_with_mem_domains__DOT__u_memdom_csr__DOT__mem_domain_override_enable_q = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 17121480334565217691ull);
    vlSelf->tb_nvisc_core_v02_with_mem_domains__DOT__u_memdom_csr__DOT__effective_domain_c = VL_SCOPED_RAND_RESET_I(3, __VscopeHash, 4772887260852988416ull);
    vlSelf->tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__data_req_valid_w = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 15626708625565751258ull);
    vlSelf->tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__data_req_is_read_w = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 1729450005951985968ull);
    vlSelf->tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__data_req_is_write_w = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 6240028708694064973ull);
    vlSelf->tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__data_req_paddr_w = VL_SCOPED_RAND_RESET_Q(64, __VscopeHash, 11748879703247680527ull);
    vlSelf->tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__data_req_wdata_w = VL_SCOPED_RAND_RESET_Q(64, __VscopeHash, 7767854328589963440ull);
    vlSelf->tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__data_req_size_bytes_w = VL_SCOPED_RAND_RESET_I(8, __VscopeHash, 1706264576698218011ull);
    VL_SCOPED_RAND_RESET_W(131, vlSelf->tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__data_req_id_w, __VscopeHash, 8344034110716770267ull);
    vlSelf->tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__exec_req_valid_w = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 47913932911941407ull);
    vlSelf->tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__exec_req_is_read_w = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 11425176249180605921ull);
    vlSelf->tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__exec_req_is_write_w = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 15026976493117312529ull);
    vlSelf->tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__exec_req_paddr_w = VL_SCOPED_RAND_RESET_Q(64, __VscopeHash, 17324894757909892023ull);
    vlSelf->tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__exec_req_wdata_w = VL_SCOPED_RAND_RESET_Q(64, __VscopeHash, 6138350054110898414ull);
    vlSelf->tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__exec_req_size_bytes_w = VL_SCOPED_RAND_RESET_I(8, __VscopeHash, 4200570867727181983ull);
    vlSelf->tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__livehot_req_valid_w = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 1114403237844788359ull);
    vlSelf->tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__livehot_req_is_read_w = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 1620875797475084433ull);
    vlSelf->tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__livehot_req_is_write_w = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 3580748342836715807ull);
    vlSelf->tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__livehot_req_paddr_w = VL_SCOPED_RAND_RESET_Q(64, __VscopeHash, 14063184115699323746ull);
    vlSelf->tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__livehot_req_wdata_w = VL_SCOPED_RAND_RESET_Q(64, __VscopeHash, 9137490752149773244ull);
    vlSelf->tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__livehot_req_size_bytes_w = VL_SCOPED_RAND_RESET_I(8, __VscopeHash, 15597425336928425310ull);
    vlSelf->tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__router_fault_w = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 4047204015328633374ull);
    vlSelf->tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__router_fault_code_w = VL_SCOPED_RAND_RESET_I(16, __VscopeHash, 1956808981622201917ull);
    vlSelf->tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__data_resp_valid_w = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 10770517877135710363ull);
    vlSelf->tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__data_resp_rdata_w = VL_SCOPED_RAND_RESET_Q(64, __VscopeHash, 11077382961413512059ull);
    vlSelf->tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__data_resp_write_ack_w = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 14150967680599425384ull);
    vlSelf->tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__data_fault_w = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 12009650756477001557ull);
    vlSelf->tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__data_fault_code_w = VL_SCOPED_RAND_RESET_I(16, __VscopeHash, 18264030359014888572ull);
    vlSelf->tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__cache_csr_flush_l1d_w = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 10256896003031795856ull);
    vlSelf->tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__cache_csr_flush_3d_w = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 7714242553352136060ull);
    vlSelf->tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__cache_csr_flush_hierarchy_w = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 13046194585299386483ull);
    vlSelf->tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__effective_flush_data_l1d_w = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 11009608369193304567ull);
    vlSelf->tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__exec_resp_valid_w = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 2890668455789496356ull);
    vlSelf->tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__exec_resp_rdata_w = VL_SCOPED_RAND_RESET_Q(64, __VscopeHash, 11502997801682310343ull);
    vlSelf->tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__exec_resp_write_ack_w = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 1184515062734475582ull);
    vlSelf->tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__exec_fault_w = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 5889075403644463868ull);
    vlSelf->tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__exec_fault_code_w = VL_SCOPED_RAND_RESET_I(16, __VscopeHash, 12452147969180561308ull);
    vlSelf->tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__livehot_resp_valid_w = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 5443285360866922198ull);
    vlSelf->tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__livehot_resp_rdata_w = VL_SCOPED_RAND_RESET_Q(64, __VscopeHash, 3837831509211041109ull);
    vlSelf->tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__livehot_resp_write_ack_w = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 4385342761059439999ull);
    vlSelf->tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__livehot_fault_w = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 16985424192703116963ull);
    vlSelf->tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__livehot_fault_code_w = VL_SCOPED_RAND_RESET_I(16, __VscopeHash, 10187433180998459074ull);
    vlSelf->tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__pending_domain_q = VL_SCOPED_RAND_RESET_I(3, __VscopeHash, 7427124210102572733ull);
    vlSelf->tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_data_lane__DOT__l1d_mem_req_valid_w = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 3347153735285852733ull);
    vlSelf->tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_data_lane__DOT__l1d_mem_req_is_read_w = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 11293433512948831378ull);
    vlSelf->tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_data_lane__DOT__l1d_mem_req_is_write_w = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 15929388886975851905ull);
    vlSelf->tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_data_lane__DOT__l1d_mem_req_paddr_w = VL_SCOPED_RAND_RESET_Q(64, __VscopeHash, 11897403889609943025ull);
    vlSelf->tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_data_lane__DOT__l1d_mem_req_wdata_w = VL_SCOPED_RAND_RESET_Q(64, __VscopeHash, 4421465575333135680ull);
    vlSelf->tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_data_lane__DOT__l1d_mem_req_size_bytes_w = VL_SCOPED_RAND_RESET_I(8, __VscopeHash, 10270772496869569865ull);
    vlSelf->tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_data_lane__DOT__cache3d_resp_valid_w = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 9649998937832665618ull);
    vlSelf->tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_data_lane__DOT__cache3d_resp_rdata_w = VL_SCOPED_RAND_RESET_Q(64, __VscopeHash, 4855460945300510331ull);
    vlSelf->tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_data_lane__DOT__cache3d_resp_write_ack_w = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 7523139946057024400ull);
    vlSelf->tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_data_lane__DOT__cache3d_fault_w = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 2124376521529505846ull);
    vlSelf->tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_data_lane__DOT__cache3d_fault_code_w = VL_SCOPED_RAND_RESET_I(16, __VscopeHash, 17224773251547406130ull);
    vlSelf->tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_data_lane__DOT__u_l1d__DOT__state_q = VL_SCOPED_RAND_RESET_I(2, __VscopeHash, 1042880020887522260ull);
    vlSelf->tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_data_lane__DOT__u_l1d__DOT__valid_q = VL_SCOPED_RAND_RESET_I(16, __VscopeHash, 8643192871927256265ull);
    for (int __Vi0 = 0; __Vi0 < 16; ++__Vi0) {
        vlSelf->tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_data_lane__DOT__u_l1d__DOT__tag_q[__Vi0] = VL_SCOPED_RAND_RESET_Q(64, __VscopeHash, 13443592051407660940ull);
    }
    for (int __Vi0 = 0; __Vi0 < 16; ++__Vi0) {
        vlSelf->tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_data_lane__DOT__u_l1d__DOT__data_q[__Vi0] = VL_SCOPED_RAND_RESET_Q(64, __VscopeHash, 13023801429552955128ull);
    }
    vlSelf->tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_data_lane__DOT__u_l1d__DOT__miss_index_q = VL_SCOPED_RAND_RESET_I(4, __VscopeHash, 2410288742181765561ull);
    vlSelf->tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_data_lane__DOT__u_l1d__DOT__miss_tag_q = VL_SCOPED_RAND_RESET_Q(64, __VscopeHash, 6805296481614289086ull);
    vlSelf->tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_data_lane__DOT__u_l1d__DOT__flush_q = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 13790057931302429950ull);
    vlSelf->tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_data_lane__DOT__u_3d_dram__DOT__cache_mem_req_valid_w = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 15503900627891408854ull);
    vlSelf->tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_data_lane__DOT__u_3d_dram__DOT__cache_mem_req_is_read_w = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 5430978120909729194ull);
    vlSelf->tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_data_lane__DOT__u_3d_dram__DOT__cache_mem_req_is_write_w = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 18250050822956290490ull);
    vlSelf->tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_data_lane__DOT__u_3d_dram__DOT__cache_mem_req_paddr_w = VL_SCOPED_RAND_RESET_Q(64, __VscopeHash, 11910294332974833284ull);
    vlSelf->tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_data_lane__DOT__u_3d_dram__DOT__cache_mem_req_wdata_w = VL_SCOPED_RAND_RESET_Q(64, __VscopeHash, 16098685159959797119ull);
    vlSelf->tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_data_lane__DOT__u_3d_dram__DOT__cache_mem_req_size_bytes_w = VL_SCOPED_RAND_RESET_I(8, __VscopeHash, 3043734620232812919ull);
    vlSelf->tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_data_lane__DOT__u_3d_dram__DOT__cache_mem_req_id_w = VL_SCOPED_RAND_RESET_I(8, __VscopeHash, 10453776507546020490ull);
    vlSelf->tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_data_lane__DOT__u_3d_dram__DOT__dram_resp_valid_w = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 6965038316203330670ull);
    vlSelf->tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_data_lane__DOT__u_3d_dram__DOT__dram_resp_rdata_w = VL_SCOPED_RAND_RESET_Q(64, __VscopeHash, 4162337687005496495ull);
    vlSelf->tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_data_lane__DOT__u_3d_dram__DOT__dram_resp_write_ack_w = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 13737886820746907969ull);
    vlSelf->tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_data_lane__DOT__u_3d_dram__DOT__dram_fault_w = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 17267763847660881997ull);
    vlSelf->tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_data_lane__DOT__u_3d_dram__DOT__dram_fault_code_w = VL_SCOPED_RAND_RESET_I(16, __VscopeHash, 7512949939578705831ull);
    vlSelf->tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_data_lane__DOT__u_3d_dram__DOT__u_3d_cache__DOT__state_q = VL_SCOPED_RAND_RESET_I(2, __VscopeHash, 17242771253450895884ull);
    for (int __Vi0 = 0; __Vi0 < 16; ++__Vi0) {
        vlSelf->tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_data_lane__DOT__u_3d_dram__DOT__u_3d_cache__DOT__valid_q[__Vi0] = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 2704304701705121948ull);
    }
    for (int __Vi0 = 0; __Vi0 < 16; ++__Vi0) {
        vlSelf->tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_data_lane__DOT__u_3d_dram__DOT__u_3d_cache__DOT__tag_q[__Vi0] = VL_SCOPED_RAND_RESET_Q(64, __VscopeHash, 5126138245094786273ull);
    }
    for (int __Vi0 = 0; __Vi0 < 16; ++__Vi0) {
        vlSelf->tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_data_lane__DOT__u_3d_dram__DOT__u_3d_cache__DOT__data_q[__Vi0] = VL_SCOPED_RAND_RESET_Q(64, __VscopeHash, 16563990139714286065ull);
    }
    vlSelf->tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_data_lane__DOT__u_3d_dram__DOT__u_3d_cache__DOT__pending_index_q = VL_SCOPED_RAND_RESET_I(4, __VscopeHash, 13422812057520310716ull);
    vlSelf->tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_data_lane__DOT__u_3d_dram__DOT__u_3d_cache__DOT__pending_tag_q = VL_SCOPED_RAND_RESET_Q(64, __VscopeHash, 13394625344714107415ull);
    for (int __Vi0 = 0; __Vi0 < 1024; ++__Vi0) {
        vlSelf->tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_data_lane__DOT__u_3d_dram__DOT__u_dram__DOT__mem_q[__Vi0] = VL_SCOPED_RAND_RESET_Q(64, __VscopeHash, 1696118565022115371ull);
    }
    vlSelf->tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_data_lane__DOT__u_3d_dram__DOT__u_dram__DOT__busy_q = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 4702091542789847722ull);
    vlSelf->tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_data_lane__DOT__u_3d_dram__DOT__u_dram__DOT__latency_q = VL_SCOPED_RAND_RESET_I(3, __VscopeHash, 7850727929089023795ull);
    vlSelf->tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_data_lane__DOT__u_3d_dram__DOT__u_dram__DOT__pending_read_q = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 13143451700945444501ull);
    vlSelf->tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_data_lane__DOT__u_3d_dram__DOT__u_dram__DOT__pending_write_q = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 10639468518184149254ull);
    vlSelf->tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_data_lane__DOT__u_3d_dram__DOT__u_dram__DOT__pending_wdata_q = VL_SCOPED_RAND_RESET_Q(64, __VscopeHash, 8071996019790585621ull);
    vlSelf->tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_data_lane__DOT__u_3d_dram__DOT__u_dram__DOT__pending_index_q = VL_SCOPED_RAND_RESET_I(10, __VscopeHash, 6067816187344463453ull);
    vlSelf->tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_data_lane__DOT__u_3d_dram__DOT__u_dram__DOT__pending_id_q = VL_SCOPED_RAND_RESET_I(8, __VscopeHash, 1797972491781527747ull);
    vlSelf->tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_data_lane__DOT__u_3d_dram__DOT__u_dram__DOT__i = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 11591770029861248615ull);
    for (int __Vi0 = 0; __Vi0 < 256; ++__Vi0) {
        vlSelf->tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_execmem__DOT__mem_q[__Vi0] = VL_SCOPED_RAND_RESET_Q(64, __VscopeHash, 13399944855224299737ull);
    }
    vlSelf->tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_execmem__DOT__in_range_c = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 10284488607901826293ull);
    vlSelf->tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_execmem__DOT__op_ok_c = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 5421198400563072971ull);
    vlSelf->tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_execmem__DOT__i = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 8494660355983453672ull);
    for (int __Vi0 = 0; __Vi0 < 256; ++__Vi0) {
        vlSelf->tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_livehot__DOT__mem_q[__Vi0] = VL_SCOPED_RAND_RESET_Q(64, __VscopeHash, 8947287690875252166ull);
    }
    vlSelf->tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_livehot__DOT__in_range_c = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 10404980049035084114ull);
    vlSelf->tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_livehot__DOT__op_ok_c = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 11477495073299673959ull);
    vlSelf->tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_livehot__DOT__i = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 526608603081902666ull);
    vlSelf->tb_nvisc_core_v02_with_mem_domains__DOT__u_core__DOT__mmu_resp_valid_w = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 9411217424561642328ull);
    vlSelf->tb_nvisc_core_v02_with_mem_domains__DOT__u_core__DOT__mmu_resp_is_read_w = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 15175600066457615395ull);
    vlSelf->tb_nvisc_core_v02_with_mem_domains__DOT__u_core__DOT__mmu_resp_is_write_w = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 4798630950131791385ull);
    vlSelf->tb_nvisc_core_v02_with_mem_domains__DOT__u_core__DOT__mmu_resp_vaddr_w = VL_SCOPED_RAND_RESET_Q(64, __VscopeHash, 16998695847324500895ull);
    vlSelf->tb_nvisc_core_v02_with_mem_domains__DOT__u_core__DOT__mmu_resp_paddr_w = VL_SCOPED_RAND_RESET_Q(64, __VscopeHash, 3007546472027252217ull);
    vlSelf->tb_nvisc_core_v02_with_mem_domains__DOT__u_core__DOT__mmu_resp_wdata_w = VL_SCOPED_RAND_RESET_Q(64, __VscopeHash, 5880185287923546691ull);
    vlSelf->tb_nvisc_core_v02_with_mem_domains__DOT__u_core__DOT__mmu_resp_size_bytes_w = VL_SCOPED_RAND_RESET_I(8, __VscopeHash, 3365041711723423236ull);
    vlSelf->tb_nvisc_core_v02_with_mem_domains__DOT__u_core__DOT__mmu_resp_mem_domain_w = VL_SCOPED_RAND_RESET_I(3, __VscopeHash, 14376587704042946239ull);
    vlSelf->tb_nvisc_core_v02_with_mem_domains__DOT__u_core__DOT__mmu_fault_w = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 1570902626433694053ull);
    vlSelf->tb_nvisc_core_v02_with_mem_domains__DOT__u_core__DOT__mmu_fault_code_w = VL_SCOPED_RAND_RESET_I(16, __VscopeHash, 14777555600748776313ull);
    vlSelf->tb_nvisc_core_v02_with_mem_domains__DOT__u_core__DOT__rs1_data_w = VL_SCOPED_RAND_RESET_Q(64, __VscopeHash, 12017037722729981284ull);
    vlSelf->tb_nvisc_core_v02_with_mem_domains__DOT__u_core__DOT__rs2_data_w = VL_SCOPED_RAND_RESET_Q(64, __VscopeHash, 14710626199278643981ull);
    vlSelf->tb_nvisc_core_v02_with_mem_domains__DOT__u_core__DOT__branch_taken_w = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 9952458116704172991ull);
    vlSelf->tb_nvisc_core_v02_with_mem_domains__DOT__u_core__DOT__rf_we_w = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 6088561199430216088ull);
    vlSelf->tb_nvisc_core_v02_with_mem_domains__DOT__u_core__DOT__rf_waddr_w = VL_SCOPED_RAND_RESET_I(5, __VscopeHash, 9753258326268771293ull);
    vlSelf->tb_nvisc_core_v02_with_mem_domains__DOT__u_core__DOT__rf_wdata_w = VL_SCOPED_RAND_RESET_Q(64, __VscopeHash, 13666403511000772641ull);
    vlSelf->tb_nvisc_core_v02_with_mem_domains__DOT__u_core__DOT__load_pending_q = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 10289281905154327731ull);
    vlSelf->tb_nvisc_core_v02_with_mem_domains__DOT__u_core__DOT__load_rd_q = VL_SCOPED_RAND_RESET_I(5, __VscopeHash, 3373838458594591169ull);
    vlSelf->tb_nvisc_core_v02_with_mem_domains__DOT__u_core__DOT__ctrl_reg_write_w = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 9971243597233423352ull);
    vlSelf->tb_nvisc_core_v02_with_mem_domains__DOT__u_core__DOT__ctrl_mem_read_w = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 3136444136934267201ull);
    vlSelf->tb_nvisc_core_v02_with_mem_domains__DOT__u_core__DOT__ctrl_mem_write_w = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 13065959553587590182ull);
    vlSelf->tb_nvisc_core_v02_with_mem_domains__DOT__u_core__DOT__lsu_fault_w = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 2428608197384465766ull);
    vlSelf->tb_nvisc_core_v02_with_mem_domains__DOT__u_core__DOT__lsu_fault_code_w = VL_SCOPED_RAND_RESET_I(16, __VscopeHash, 8121770712037970376ull);
    vlSelf->tb_nvisc_core_v02_with_mem_domains__DOT__u_core__DOT__csr_fault_w = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 6351691317927089509ull);
    vlSelf->tb_nvisc_core_v02_with_mem_domains__DOT__u_core__DOT__csr_fault_code_w = VL_SCOPED_RAND_RESET_I(16, __VscopeHash, 18265634249974391865ull);
    vlSelf->tb_nvisc_core_v02_with_mem_domains__DOT__u_core__DOT__u_csr__DOT__core_id_q = VL_SCOPED_RAND_RESET_I(8, __VscopeHash, 16414704676166729108ull);
    vlSelf->tb_nvisc_core_v02_with_mem_domains__DOT__u_core__DOT__u_csr__DOT__thread_id_q = VL_SCOPED_RAND_RESET_I(8, __VscopeHash, 9361783571251235007ull);
    vlSelf->tb_nvisc_core_v02_with_mem_domains__DOT__u_core__DOT__u_csr__DOT__branch_id_q = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 11555750173902660372ull);
    vlSelf->tb_nvisc_core_v02_with_mem_domains__DOT__u_core__DOT__u_csr__DOT__state_id_q = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 1231043216616552973ull);
    vlSelf->tb_nvisc_core_v02_with_mem_domains__DOT__u_core__DOT__u_csr__DOT__commit_id_q = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 4519519840485416317ull);
    vlSelf->tb_nvisc_core_v02_with_mem_domains__DOT__u_core__DOT__u_csr__DOT__privilege_q = VL_SCOPED_RAND_RESET_I(3, __VscopeHash, 6218714653865137017ull);
    vlSelf->tb_nvisc_core_v02_with_mem_domains__DOT__u_core__DOT__u_csr__DOT__aegis_policy_id_q = VL_SCOPED_RAND_RESET_I(16, __VscopeHash, 11593018064816436989ull);
    vlSelf->tb_nvisc_core_v02_with_mem_domains__DOT__u_core__DOT__u_pc__DOT__pc_q = VL_SCOPED_RAND_RESET_Q(64, __VscopeHash, 710461044581977530ull);
    vlSelf->tb_nvisc_core_v02_with_mem_domains__DOT__u_core__DOT__u_pc__DOT__valid_q = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 14892034316218787909ull);
    VL_SCOPED_RAND_RESET_W(228, vlSelf->tb_nvisc_core_v02_with_mem_domains__DOT__u_core__DOT__u_if__DOT__fetch_q, __VscopeHash, 16880476819374417932ull);
    vlSelf->tb_nvisc_core_v02_with_mem_domains__DOT__u_core__DOT__u_if__DOT__fault_q = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 11167319771317782496ull);
    vlSelf->tb_nvisc_core_v02_with_mem_domains__DOT__u_core__DOT__u_if__DOT__fault_code_q = VL_SCOPED_RAND_RESET_I(16, __VscopeHash, 1137977074862991034ull);
    VL_SCOPED_RAND_RESET_W(335, vlSelf->tb_nvisc_core_v02_with_mem_domains__DOT__u_core__DOT__u_dec__DOT__dec, __VscopeHash, 4351162135010196269ull);
    for (int __Vi0 = 0; __Vi0 < 32; ++__Vi0) {
        vlSelf->tb_nvisc_core_v02_with_mem_domains__DOT__u_core__DOT__u_rf__DOT__regs_q[__Vi0] = VL_SCOPED_RAND_RESET_Q(64, __VscopeHash, 16470594687615188793ull);
    }
    vlSelf->tb_nvisc_core_v02_with_mem_domains__DOT__u_core__DOT__u_alu__DOT__result_c = VL_SCOPED_RAND_RESET_Q(64, __VscopeHash, 10037390490620437827ull);
    VL_SCOPED_RAND_RESET_W(378, vlSelf->tb_nvisc_core_v02_with_mem_domains__DOT__u_core__DOT__u_lsu__DOT__req_q, __VscopeHash, 15864171927719738481ull);
    vlSelf->tb_nvisc_core_v02_with_mem_domains__DOT__u_core__DOT__u_lsu__DOT__bad_size_c = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 6777815143721625321ull);
    vlSelf->tb_nvisc_core_v02_with_mem_domains__DOT__u_core__DOT__u_lsu__DOT__both_read_write_c = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 11023345003058618082ull);
    vlSelf->tb_nvisc_core_v02_with_mem_domains__DOT__u_core__DOT__u_lsu__DOT__no_op_c = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 4380558638825849621ull);
    vlSelf->tb_nvisc_core_v02_with_mem_domains__DOT__u_core__DOT__u_mmu__DOT__page_fault_c = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 2837720385847404387ull);
    vlSelf->tb_nvisc_core_v02_with_mem_domains__DOT__u_core__DOT__u_mmu__DOT__align_fault_c = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 8146297162001049827ull);
    for (int __Vi0 = 0; __Vi0 < 1; ++__Vi0) {
        vlSelf->__VstlTriggered[__Vi0] = 0;
    }
    for (int __Vi0 = 0; __Vi0 < 1; ++__Vi0) {
        vlSelf->__VicoTriggered[__Vi0] = 0;
    }
    for (int __Vi0 = 0; __Vi0 < 1; ++__Vi0) {
        vlSelf->__VactTriggered[__Vi0] = 0;
    }
    vlSelf->__Vtrigprevexpr___TOP__clk__0 = 0;
    vlSelf->__Vtrigprevexpr___TOP__rst_n__0 = 0;
    for (int __Vi0 = 0; __Vi0 < 1; ++__Vi0) {
        vlSelf->__VnbaTriggered[__Vi0] = 0;
    }
}
