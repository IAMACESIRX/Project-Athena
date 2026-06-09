// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See Vtb_nvisc_core_v02_with_mem_domains.h for the primary calling header

#include "Vtb_nvisc_core_v02_with_mem_domains__pch.h"

void Vtb_nvisc_core_v02_with_mem_domains___024root___eval_triggers_vec__ico(Vtb_nvisc_core_v02_with_mem_domains___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_nvisc_core_v02_with_mem_domains___024root___eval_triggers_vec__ico\n"); );
    Vtb_nvisc_core_v02_with_mem_domains__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    vlSelfRef.__VicoTriggered[0U] = ((0xfffffffffffffffeULL 
                                      & vlSelfRef.__VicoTriggered[0U]) 
                                     | (IData)((IData)(vlSelfRef.__VicoFirstIteration)));
}

bool Vtb_nvisc_core_v02_with_mem_domains___024root___trigger_anySet__ico(const VlUnpacked<QData/*63:0*/, 1> &in) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_nvisc_core_v02_with_mem_domains___024root___trigger_anySet__ico\n"); );
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

void Vtb_nvisc_core_v02_with_mem_domains___024root___ico_sequent__TOP__0(Vtb_nvisc_core_v02_with_mem_domains___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_nvisc_core_v02_with_mem_domains___024root___ico_sequent__TOP__0\n"); );
    Vtb_nvisc_core_v02_with_mem_domains__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_core__DOT__u_lsu__DOT__bad_size_c 
        = (1U & (~ ((1U == (IData)(vlSelfRef.lsu_size_bytes_i)) 
                    | ((2U == (IData)(vlSelfRef.lsu_size_bytes_i)) 
                       | ((4U == (IData)(vlSelfRef.lsu_size_bytes_i)) 
                          | (8U == (IData)(vlSelfRef.lsu_size_bytes_i)))))));
    vlSelfRef.imem_req_valid_o = ((~ ((IData)(vlSelfRef.stall_i) 
                                      | (IData)(vlSelfRef.flush_i))) 
                                  & (IData)(vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_core__DOT__u_pc__DOT__valid_q));
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
    vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__wrapper_override_domain_w 
        = ((IData)(vlSelfRef.mem_domain_override_valid_i)
            ? (IData)(vlSelfRef.mem_domain_override_i)
            : (IData)(vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_core__DOT__mmu_resp_mem_domain_w));
    vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_memdom_csr__DOT__effective_domain_c 
        = ((IData)(vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_memdom_csr__DOT__mem_domain_override_enable_q)
            ? (IData)(vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_memdom_csr__DOT__mem_domain_select_q)
            : (IData)(vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__wrapper_override_domain_w));
}

void Vtb_nvisc_core_v02_with_mem_domains___024root___eval_ico(Vtb_nvisc_core_v02_with_mem_domains___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_nvisc_core_v02_with_mem_domains___024root___eval_ico\n"); );
    Vtb_nvisc_core_v02_with_mem_domains__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    if ((1ULL & vlSelfRef.__VicoTriggered[0U])) {
        vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_core__DOT__u_lsu__DOT__bad_size_c 
            = (1U & (~ ((1U == (IData)(vlSelfRef.lsu_size_bytes_i)) 
                        | ((2U == (IData)(vlSelfRef.lsu_size_bytes_i)) 
                           | ((4U == (IData)(vlSelfRef.lsu_size_bytes_i)) 
                              | (8U == (IData)(vlSelfRef.lsu_size_bytes_i)))))));
        vlSelfRef.imem_req_valid_o = ((~ ((IData)(vlSelfRef.stall_i) 
                                          | (IData)(vlSelfRef.flush_i))) 
                                      & (IData)(vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_core__DOT__u_pc__DOT__valid_q));
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
        if (((((~ (IData)(vlSelfRef.dbg_rf_we_i)) & 
               (~ (IData)(vlSelfRef.load_wb_valid_o))) 
              & (IData)(vlSelfRef.alu_result_valid_o)) 
             & (IData)(vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_core__DOT__ctrl_reg_write_w))) {
            vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_core__DOT__rf_we_w = 1U;
            vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_core__DOT__rf_waddr_w 
                = (0x0000001fU & (vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_core__DOT__u_dec__DOT__dec[6U] 
                                  >> 0x00000017U));
            vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_core__DOT__rf_wdata_w 
                = vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_core__DOT__u_alu__DOT__result_c;
        }
        vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__wrapper_override_domain_w 
            = ((IData)(vlSelfRef.mem_domain_override_valid_i)
                ? (IData)(vlSelfRef.mem_domain_override_i)
                : (IData)(vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_core__DOT__mmu_resp_mem_domain_w));
        vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_memdom_csr__DOT__effective_domain_c 
            = ((IData)(vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_memdom_csr__DOT__mem_domain_override_enable_q)
                ? (IData)(vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_memdom_csr__DOT__mem_domain_select_q)
                : (IData)(vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__wrapper_override_domain_w));
    }
}

#ifdef VL_DEBUG
VL_ATTR_COLD void Vtb_nvisc_core_v02_with_mem_domains___024root___dump_triggers__ico(const VlUnpacked<QData/*63:0*/, 1> &triggers, const std::string &tag);
#endif  // VL_DEBUG

bool Vtb_nvisc_core_v02_with_mem_domains___024root___eval_phase__ico(Vtb_nvisc_core_v02_with_mem_domains___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_nvisc_core_v02_with_mem_domains___024root___eval_phase__ico\n"); );
    Vtb_nvisc_core_v02_with_mem_domains__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Locals
    CData/*0:0*/ __VicoExecute;
    // Body
    Vtb_nvisc_core_v02_with_mem_domains___024root___eval_triggers_vec__ico(vlSelf);
#ifdef VL_DEBUG
    if (VL_UNLIKELY(vlSymsp->_vm_contextp__->debug())) {
        Vtb_nvisc_core_v02_with_mem_domains___024root___dump_triggers__ico(vlSelfRef.__VicoTriggered, "ico"s);
    }
#endif
    __VicoExecute = Vtb_nvisc_core_v02_with_mem_domains___024root___trigger_anySet__ico(vlSelfRef.__VicoTriggered);
    if (__VicoExecute) {
        Vtb_nvisc_core_v02_with_mem_domains___024root___eval_ico(vlSelf);
    }
    return (__VicoExecute);
}

void Vtb_nvisc_core_v02_with_mem_domains___024root___eval_triggers_vec__act(Vtb_nvisc_core_v02_with_mem_domains___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_nvisc_core_v02_with_mem_domains___024root___eval_triggers_vec__act\n"); );
    Vtb_nvisc_core_v02_with_mem_domains__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    vlSelfRef.__VactTriggered[0U] = (QData)((IData)(
                                                    ((((~ (IData)(vlSelfRef.rst_n)) 
                                                       & (IData)(vlSelfRef.__Vtrigprevexpr___TOP__rst_n__0)) 
                                                      << 1U) 
                                                     | ((IData)(vlSelfRef.clk) 
                                                        & (~ (IData)(vlSelfRef.__Vtrigprevexpr___TOP__clk__0))))));
    vlSelfRef.__Vtrigprevexpr___TOP__clk__0 = vlSelfRef.clk;
    vlSelfRef.__Vtrigprevexpr___TOP__rst_n__0 = vlSelfRef.rst_n;
}

bool Vtb_nvisc_core_v02_with_mem_domains___024root___trigger_anySet__act(const VlUnpacked<QData/*63:0*/, 1> &in) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_nvisc_core_v02_with_mem_domains___024root___trigger_anySet__act\n"); );
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

extern const VlWide<8>/*255:0*/ Vtb_nvisc_core_v02_with_mem_domains__ConstPool__CONST_hee3372ac_0;
extern const VlWide<12>/*383:0*/ Vtb_nvisc_core_v02_with_mem_domains__ConstPool__CONST_h3a0f6b6a_0;
extern const VlUnpacked<CData/*0:0*/, 2> Vtb_nvisc_core_v02_with_mem_domains__ConstPool__TABLE_h8cec2904_0;
extern const VlWide<11>/*351:0*/ Vtb_nvisc_core_v02_with_mem_domains__ConstPool__CONST_h09c2fdcd_0;

void Vtb_nvisc_core_v02_with_mem_domains___024root___nba_sequent__TOP__0(Vtb_nvisc_core_v02_with_mem_domains___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_nvisc_core_v02_with_mem_domains___024root___nba_sequent__TOP__0\n"); );
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
    CData/*0:0*/ __Vtableidx1;
    __Vtableidx1 = 0;
    CData/*2:0*/ __Vdly__tb_nvisc_core_v02_with_mem_domains__DOT__u_memdom_csr__DOT__mem_domain_select_q;
    __Vdly__tb_nvisc_core_v02_with_mem_domains__DOT__u_memdom_csr__DOT__mem_domain_select_q = 0;
    CData/*0:0*/ __Vdly__tb_nvisc_core_v02_with_mem_domains__DOT__u_memdom_csr__DOT__mem_domain_override_enable_q;
    __Vdly__tb_nvisc_core_v02_with_mem_domains__DOT__u_memdom_csr__DOT__mem_domain_override_enable_q = 0;
    SData/*15:0*/ __Vdly__tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_data_lane__DOT__u_l1d__DOT__valid_q;
    __Vdly__tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_data_lane__DOT__u_l1d__DOT__valid_q = 0;
    CData/*1:0*/ __Vdly__tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_data_lane__DOT__u_l1d__DOT__state_q;
    __Vdly__tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_data_lane__DOT__u_l1d__DOT__state_q = 0;
    CData/*3:0*/ __Vdly__tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_data_lane__DOT__u_l1d__DOT__miss_index_q;
    __Vdly__tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_data_lane__DOT__u_l1d__DOT__miss_index_q = 0;
    QData/*63:0*/ __Vdly__tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_data_lane__DOT__u_l1d__DOT__miss_tag_q;
    __Vdly__tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_data_lane__DOT__u_l1d__DOT__miss_tag_q = 0;
    CData/*0:0*/ __Vdly__tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_data_lane__DOT__cache3d_resp_valid_w;
    __Vdly__tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_data_lane__DOT__cache3d_resp_valid_w = 0;
    QData/*63:0*/ __Vdly__tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_data_lane__DOT__cache3d_resp_rdata_w;
    __Vdly__tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_data_lane__DOT__cache3d_resp_rdata_w = 0;
    CData/*0:0*/ __Vdly__tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_data_lane__DOT__cache3d_resp_write_ack_w;
    __Vdly__tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_data_lane__DOT__cache3d_resp_write_ack_w = 0;
    CData/*0:0*/ __Vdly__tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_data_lane__DOT__cache3d_fault_w;
    __Vdly__tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_data_lane__DOT__cache3d_fault_w = 0;
    SData/*15:0*/ __Vdly__tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_data_lane__DOT__cache3d_fault_code_w;
    __Vdly__tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_data_lane__DOT__cache3d_fault_code_w = 0;
    CData/*3:0*/ __Vdly__tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_data_lane__DOT__u_3d_dram__DOT__u_3d_cache__DOT__pending_index_q;
    __Vdly__tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_data_lane__DOT__u_3d_dram__DOT__u_3d_cache__DOT__pending_index_q = 0;
    QData/*63:0*/ __Vdly__tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_data_lane__DOT__u_3d_dram__DOT__u_3d_cache__DOT__pending_tag_q;
    __Vdly__tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_data_lane__DOT__u_3d_dram__DOT__u_3d_cache__DOT__pending_tag_q = 0;
    CData/*1:0*/ __Vdly__tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_data_lane__DOT__u_3d_dram__DOT__u_3d_cache__DOT__state_q;
    __Vdly__tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_data_lane__DOT__u_3d_dram__DOT__u_3d_cache__DOT__state_q = 0;
    CData/*0:0*/ __Vdly__tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_data_lane__DOT__u_3d_dram__DOT__dram_resp_valid_w;
    __Vdly__tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_data_lane__DOT__u_3d_dram__DOT__dram_resp_valid_w = 0;
    QData/*63:0*/ __Vdly__tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_data_lane__DOT__u_3d_dram__DOT__dram_resp_rdata_w;
    __Vdly__tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_data_lane__DOT__u_3d_dram__DOT__dram_resp_rdata_w = 0;
    CData/*0:0*/ __Vdly__tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_data_lane__DOT__u_3d_dram__DOT__dram_resp_write_ack_w;
    __Vdly__tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_data_lane__DOT__u_3d_dram__DOT__dram_resp_write_ack_w = 0;
    CData/*0:0*/ __Vdly__tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_data_lane__DOT__u_3d_dram__DOT__dram_fault_w;
    __Vdly__tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_data_lane__DOT__u_3d_dram__DOT__dram_fault_w = 0;
    SData/*15:0*/ __Vdly__tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_data_lane__DOT__u_3d_dram__DOT__dram_fault_code_w;
    __Vdly__tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_data_lane__DOT__u_3d_dram__DOT__dram_fault_code_w = 0;
    CData/*0:0*/ __Vdly__tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_data_lane__DOT__u_3d_dram__DOT__u_dram__DOT__busy_q;
    __Vdly__tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_data_lane__DOT__u_3d_dram__DOT__u_dram__DOT__busy_q = 0;
    CData/*2:0*/ __Vdly__tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_data_lane__DOT__u_3d_dram__DOT__u_dram__DOT__latency_q;
    __Vdly__tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_data_lane__DOT__u_3d_dram__DOT__u_dram__DOT__latency_q = 0;
    CData/*0:0*/ __Vdly__tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_data_lane__DOT__u_3d_dram__DOT__u_dram__DOT__pending_read_q;
    __Vdly__tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_data_lane__DOT__u_3d_dram__DOT__u_dram__DOT__pending_read_q = 0;
    CData/*0:0*/ __Vdly__tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_data_lane__DOT__u_3d_dram__DOT__u_dram__DOT__pending_write_q;
    __Vdly__tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_data_lane__DOT__u_3d_dram__DOT__u_dram__DOT__pending_write_q = 0;
    QData/*63:0*/ __Vdly__tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_data_lane__DOT__u_3d_dram__DOT__u_dram__DOT__pending_wdata_q;
    __Vdly__tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_data_lane__DOT__u_3d_dram__DOT__u_dram__DOT__pending_wdata_q = 0;
    SData/*9:0*/ __Vdly__tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_data_lane__DOT__u_3d_dram__DOT__u_dram__DOT__pending_index_q;
    __Vdly__tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_data_lane__DOT__u_3d_dram__DOT__u_dram__DOT__pending_index_q = 0;
    CData/*7:0*/ __Vdly__tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_data_lane__DOT__u_3d_dram__DOT__u_dram__DOT__pending_id_q;
    __Vdly__tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_data_lane__DOT__u_3d_dram__DOT__u_dram__DOT__pending_id_q = 0;
    QData/*63:0*/ __Vdly__tb_nvisc_core_v02_with_mem_domains__DOT__u_core__DOT__u_pc__DOT__pc_q;
    __Vdly__tb_nvisc_core_v02_with_mem_domains__DOT__u_core__DOT__u_pc__DOT__pc_q = 0;
    CData/*0:0*/ __VdlySet__tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_data_lane__DOT__u_l1d__DOT__tag_q__v0;
    __VdlySet__tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_data_lane__DOT__u_l1d__DOT__tag_q__v0 = 0;
    CData/*0:0*/ __VdlySet__tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_data_lane__DOT__u_l1d__DOT__tag_q__v1;
    __VdlySet__tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_data_lane__DOT__u_l1d__DOT__tag_q__v1 = 0;
    QData/*63:0*/ __VdlyVal__tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_data_lane__DOT__u_l1d__DOT__data_q__v16;
    __VdlyVal__tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_data_lane__DOT__u_l1d__DOT__data_q__v16 = 0;
    CData/*3:0*/ __VdlyDim0__tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_data_lane__DOT__u_l1d__DOT__data_q__v16;
    __VdlyDim0__tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_data_lane__DOT__u_l1d__DOT__data_q__v16 = 0;
    CData/*0:0*/ __VdlySet__tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_data_lane__DOT__u_l1d__DOT__data_q__v16;
    __VdlySet__tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_data_lane__DOT__u_l1d__DOT__data_q__v16 = 0;
    QData/*63:0*/ __VdlyVal__tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_data_lane__DOT__u_l1d__DOT__tag_q__v16;
    __VdlyVal__tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_data_lane__DOT__u_l1d__DOT__tag_q__v16 = 0;
    CData/*3:0*/ __VdlyDim0__tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_data_lane__DOT__u_l1d__DOT__tag_q__v16;
    __VdlyDim0__tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_data_lane__DOT__u_l1d__DOT__tag_q__v16 = 0;
    CData/*0:0*/ __VdlySet__tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_data_lane__DOT__u_l1d__DOT__tag_q__v16;
    __VdlySet__tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_data_lane__DOT__u_l1d__DOT__tag_q__v16 = 0;
    QData/*63:0*/ __VdlyVal__tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_data_lane__DOT__u_l1d__DOT__data_q__v17;
    __VdlyVal__tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_data_lane__DOT__u_l1d__DOT__data_q__v17 = 0;
    CData/*3:0*/ __VdlyDim0__tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_data_lane__DOT__u_l1d__DOT__data_q__v17;
    __VdlyDim0__tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_data_lane__DOT__u_l1d__DOT__data_q__v17 = 0;
    CData/*0:0*/ __VdlySet__tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_data_lane__DOT__u_l1d__DOT__tag_q__v17;
    __VdlySet__tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_data_lane__DOT__u_l1d__DOT__tag_q__v17 = 0;
    CData/*0:0*/ __VdlySet__tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_data_lane__DOT__u_l1d__DOT__tag_q__v18;
    __VdlySet__tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_data_lane__DOT__u_l1d__DOT__tag_q__v18 = 0;
    CData/*0:0*/ __VdlySet__tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_data_lane__DOT__u_l1d__DOT__tag_q__v19;
    __VdlySet__tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_data_lane__DOT__u_l1d__DOT__tag_q__v19 = 0;
    CData/*0:0*/ __VdlySet__tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_data_lane__DOT__u_3d_dram__DOT__u_3d_cache__DOT__valid_q__v0;
    __VdlySet__tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_data_lane__DOT__u_3d_dram__DOT__u_3d_cache__DOT__valid_q__v0 = 0;
    CData/*3:0*/ __VdlyDim0__tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_data_lane__DOT__u_3d_dram__DOT__u_3d_cache__DOT__valid_q__v16;
    __VdlyDim0__tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_data_lane__DOT__u_3d_dram__DOT__u_3d_cache__DOT__valid_q__v16 = 0;
    CData/*0:0*/ __VdlySet__tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_data_lane__DOT__u_3d_dram__DOT__u_3d_cache__DOT__valid_q__v16;
    __VdlySet__tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_data_lane__DOT__u_3d_dram__DOT__u_3d_cache__DOT__valid_q__v16 = 0;
    QData/*63:0*/ __VdlyVal__tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_data_lane__DOT__u_3d_dram__DOT__u_3d_cache__DOT__tag_q__v0;
    __VdlyVal__tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_data_lane__DOT__u_3d_dram__DOT__u_3d_cache__DOT__tag_q__v0 = 0;
    CData/*3:0*/ __VdlyDim0__tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_data_lane__DOT__u_3d_dram__DOT__u_3d_cache__DOT__tag_q__v0;
    __VdlyDim0__tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_data_lane__DOT__u_3d_dram__DOT__u_3d_cache__DOT__tag_q__v0 = 0;
    QData/*63:0*/ __VdlyVal__tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_data_lane__DOT__u_3d_dram__DOT__u_3d_cache__DOT__data_q__v0;
    __VdlyVal__tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_data_lane__DOT__u_3d_dram__DOT__u_3d_cache__DOT__data_q__v0 = 0;
    CData/*3:0*/ __VdlyDim0__tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_data_lane__DOT__u_3d_dram__DOT__u_3d_cache__DOT__data_q__v0;
    __VdlyDim0__tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_data_lane__DOT__u_3d_dram__DOT__u_3d_cache__DOT__data_q__v0 = 0;
    CData/*3:0*/ __VdlyDim0__tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_data_lane__DOT__u_3d_dram__DOT__u_3d_cache__DOT__valid_q__v17;
    __VdlyDim0__tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_data_lane__DOT__u_3d_dram__DOT__u_3d_cache__DOT__valid_q__v17 = 0;
    CData/*0:0*/ __VdlySet__tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_data_lane__DOT__u_3d_dram__DOT__u_3d_cache__DOT__valid_q__v17;
    __VdlySet__tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_data_lane__DOT__u_3d_dram__DOT__u_3d_cache__DOT__valid_q__v17 = 0;
    QData/*63:0*/ __VdlyVal__tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_data_lane__DOT__u_3d_dram__DOT__u_3d_cache__DOT__tag_q__v1;
    __VdlyVal__tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_data_lane__DOT__u_3d_dram__DOT__u_3d_cache__DOT__tag_q__v1 = 0;
    CData/*3:0*/ __VdlyDim0__tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_data_lane__DOT__u_3d_dram__DOT__u_3d_cache__DOT__tag_q__v1;
    __VdlyDim0__tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_data_lane__DOT__u_3d_dram__DOT__u_3d_cache__DOT__tag_q__v1 = 0;
    CData/*0:0*/ __VdlySet__tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_data_lane__DOT__u_3d_dram__DOT__u_3d_cache__DOT__tag_q__v1;
    __VdlySet__tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_data_lane__DOT__u_3d_dram__DOT__u_3d_cache__DOT__tag_q__v1 = 0;
    QData/*63:0*/ __VdlyVal__tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_data_lane__DOT__u_3d_dram__DOT__u_3d_cache__DOT__data_q__v1;
    __VdlyVal__tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_data_lane__DOT__u_3d_dram__DOT__u_3d_cache__DOT__data_q__v1 = 0;
    CData/*3:0*/ __VdlyDim0__tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_data_lane__DOT__u_3d_dram__DOT__u_3d_cache__DOT__data_q__v1;
    __VdlyDim0__tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_data_lane__DOT__u_3d_dram__DOT__u_3d_cache__DOT__data_q__v1 = 0;
    CData/*0:0*/ __VdlySet__tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_data_lane__DOT__u_3d_dram__DOT__u_3d_cache__DOT__valid_q__v18;
    __VdlySet__tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_data_lane__DOT__u_3d_dram__DOT__u_3d_cache__DOT__valid_q__v18 = 0;
    CData/*0:0*/ __VdlySet__tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_data_lane__DOT__u_3d_dram__DOT__u_3d_cache__DOT__tag_q__v3;
    __VdlySet__tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_data_lane__DOT__u_3d_dram__DOT__u_3d_cache__DOT__tag_q__v3 = 0;
    QData/*63:0*/ __VdlyVal__tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_data_lane__DOT__u_3d_dram__DOT__u_dram__DOT__mem_q__v0;
    __VdlyVal__tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_data_lane__DOT__u_3d_dram__DOT__u_dram__DOT__mem_q__v0 = 0;
    SData/*9:0*/ __VdlyDim0__tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_data_lane__DOT__u_3d_dram__DOT__u_dram__DOT__mem_q__v0;
    __VdlyDim0__tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_data_lane__DOT__u_3d_dram__DOT__u_dram__DOT__mem_q__v0 = 0;
    SData/*9:0*/ __VdlyDim0__tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_data_lane__DOT__u_3d_dram__DOT__u_dram__DOT__mem_q__v1;
    __VdlyDim0__tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_data_lane__DOT__u_3d_dram__DOT__u_dram__DOT__mem_q__v1 = 0;
    QData/*63:0*/ __VdlyVal__tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_execmem__DOT__mem_q__v0;
    __VdlyVal__tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_execmem__DOT__mem_q__v0 = 0;
    CData/*7:0*/ __VdlyDim0__tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_execmem__DOT__mem_q__v0;
    __VdlyDim0__tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_execmem__DOT__mem_q__v0 = 0;
    CData/*7:0*/ __VdlyDim0__tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_execmem__DOT__mem_q__v1;
    __VdlyDim0__tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_execmem__DOT__mem_q__v1 = 0;
    QData/*63:0*/ __VdlyVal__tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_livehot__DOT__mem_q__v0;
    __VdlyVal__tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_livehot__DOT__mem_q__v0 = 0;
    CData/*7:0*/ __VdlyDim0__tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_livehot__DOT__mem_q__v0;
    __VdlyDim0__tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_livehot__DOT__mem_q__v0 = 0;
    CData/*7:0*/ __VdlyDim0__tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_livehot__DOT__mem_q__v1;
    __VdlyDim0__tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_livehot__DOT__mem_q__v1 = 0;
    CData/*0:0*/ __VdlySet__tb_nvisc_core_v02_with_mem_domains__DOT__u_core__DOT__u_rf__DOT__regs_q__v0;
    __VdlySet__tb_nvisc_core_v02_with_mem_domains__DOT__u_core__DOT__u_rf__DOT__regs_q__v0 = 0;
    QData/*63:0*/ __VdlyVal__tb_nvisc_core_v02_with_mem_domains__DOT__u_core__DOT__u_rf__DOT__regs_q__v1;
    __VdlyVal__tb_nvisc_core_v02_with_mem_domains__DOT__u_core__DOT__u_rf__DOT__regs_q__v1 = 0;
    CData/*4:0*/ __VdlyDim0__tb_nvisc_core_v02_with_mem_domains__DOT__u_core__DOT__u_rf__DOT__regs_q__v1;
    __VdlyDim0__tb_nvisc_core_v02_with_mem_domains__DOT__u_core__DOT__u_rf__DOT__regs_q__v1 = 0;
    CData/*0:0*/ __VdlySet__tb_nvisc_core_v02_with_mem_domains__DOT__u_core__DOT__u_rf__DOT__regs_q__v1;
    __VdlySet__tb_nvisc_core_v02_with_mem_domains__DOT__u_core__DOT__u_rf__DOT__regs_q__v1 = 0;
    CData/*0:0*/ __VdlySet__tb_nvisc_core_v02_with_mem_domains__DOT__u_core__DOT__u_rf__DOT__regs_q__v2;
    __VdlySet__tb_nvisc_core_v02_with_mem_domains__DOT__u_core__DOT__u_rf__DOT__regs_q__v2 = 0;
    // Body
    __Vdly__tb_nvisc_core_v02_with_mem_domains__DOT__u_core__DOT__u_pc__DOT__pc_q 
        = vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_core__DOT__u_pc__DOT__pc_q;
    __Vdly__tb_nvisc_core_v02_with_mem_domains__DOT__u_memdom_csr__DOT__mem_domain_select_q 
        = vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_memdom_csr__DOT__mem_domain_select_q;
    __Vdly__tb_nvisc_core_v02_with_mem_domains__DOT__u_memdom_csr__DOT__mem_domain_override_enable_q 
        = vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_memdom_csr__DOT__mem_domain_override_enable_q;
    __VdlySet__tb_nvisc_core_v02_with_mem_domains__DOT__u_core__DOT__u_rf__DOT__regs_q__v0 = 0U;
    __VdlySet__tb_nvisc_core_v02_with_mem_domains__DOT__u_core__DOT__u_rf__DOT__regs_q__v1 = 0U;
    __VdlySet__tb_nvisc_core_v02_with_mem_domains__DOT__u_core__DOT__u_rf__DOT__regs_q__v2 = 0U;
    __Vdly__tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_data_lane__DOT__u_l1d__DOT__valid_q 
        = vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_data_lane__DOT__u_l1d__DOT__valid_q;
    __Vdly__tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_data_lane__DOT__u_l1d__DOT__state_q 
        = vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_data_lane__DOT__u_l1d__DOT__state_q;
    __Vdly__tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_data_lane__DOT__u_l1d__DOT__miss_index_q 
        = vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_data_lane__DOT__u_l1d__DOT__miss_index_q;
    __Vdly__tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_data_lane__DOT__u_l1d__DOT__miss_tag_q 
        = vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_data_lane__DOT__u_l1d__DOT__miss_tag_q;
    __VdlySet__tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_data_lane__DOT__u_l1d__DOT__data_q__v16 = 0U;
    __VdlySet__tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_data_lane__DOT__u_l1d__DOT__tag_q__v0 = 0U;
    __VdlySet__tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_data_lane__DOT__u_l1d__DOT__tag_q__v1 = 0U;
    __VdlySet__tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_data_lane__DOT__u_l1d__DOT__tag_q__v16 = 0U;
    __VdlySet__tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_data_lane__DOT__u_l1d__DOT__tag_q__v17 = 0U;
    __VdlySet__tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_data_lane__DOT__u_l1d__DOT__tag_q__v18 = 0U;
    __VdlySet__tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_data_lane__DOT__u_l1d__DOT__tag_q__v19 = 0U;
    __Vdly__tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_data_lane__DOT__cache3d_resp_valid_w 
        = vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_data_lane__DOT__cache3d_resp_valid_w;
    __Vdly__tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_data_lane__DOT__cache3d_resp_rdata_w 
        = vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_data_lane__DOT__cache3d_resp_rdata_w;
    __Vdly__tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_data_lane__DOT__cache3d_resp_write_ack_w 
        = vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_data_lane__DOT__cache3d_resp_write_ack_w;
    __Vdly__tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_data_lane__DOT__cache3d_fault_w 
        = vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_data_lane__DOT__cache3d_fault_w;
    __Vdly__tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_data_lane__DOT__cache3d_fault_code_w 
        = vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_data_lane__DOT__cache3d_fault_code_w;
    __Vdly__tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_data_lane__DOT__u_3d_dram__DOT__u_3d_cache__DOT__pending_index_q 
        = vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_data_lane__DOT__u_3d_dram__DOT__u_3d_cache__DOT__pending_index_q;
    __Vdly__tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_data_lane__DOT__u_3d_dram__DOT__u_3d_cache__DOT__pending_tag_q 
        = vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_data_lane__DOT__u_3d_dram__DOT__u_3d_cache__DOT__pending_tag_q;
    __Vdly__tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_data_lane__DOT__u_3d_dram__DOT__u_3d_cache__DOT__state_q 
        = vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_data_lane__DOT__u_3d_dram__DOT__u_3d_cache__DOT__state_q;
    __VdlySet__tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_data_lane__DOT__u_3d_dram__DOT__u_3d_cache__DOT__valid_q__v0 = 0U;
    __VdlySet__tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_data_lane__DOT__u_3d_dram__DOT__u_3d_cache__DOT__valid_q__v17 = 0U;
    __VdlySet__tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_data_lane__DOT__u_3d_dram__DOT__u_3d_cache__DOT__tag_q__v1 = 0U;
    __VdlySet__tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_data_lane__DOT__u_3d_dram__DOT__u_3d_cache__DOT__valid_q__v16 = 0U;
    __VdlySet__tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_data_lane__DOT__u_3d_dram__DOT__u_3d_cache__DOT__valid_q__v18 = 0U;
    __VdlySet__tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_data_lane__DOT__u_3d_dram__DOT__u_3d_cache__DOT__tag_q__v3 = 0U;
    __Vdly__tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_data_lane__DOT__u_3d_dram__DOT__dram_resp_valid_w 
        = vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_data_lane__DOT__u_3d_dram__DOT__dram_resp_valid_w;
    __Vdly__tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_data_lane__DOT__u_3d_dram__DOT__dram_resp_rdata_w 
        = vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_data_lane__DOT__u_3d_dram__DOT__dram_resp_rdata_w;
    __Vdly__tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_data_lane__DOT__u_3d_dram__DOT__dram_resp_write_ack_w 
        = vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_data_lane__DOT__u_3d_dram__DOT__dram_resp_write_ack_w;
    __Vdly__tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_data_lane__DOT__u_3d_dram__DOT__dram_fault_w 
        = vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_data_lane__DOT__u_3d_dram__DOT__dram_fault_w;
    __Vdly__tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_data_lane__DOT__u_3d_dram__DOT__dram_fault_code_w 
        = vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_data_lane__DOT__u_3d_dram__DOT__dram_fault_code_w;
    __Vdly__tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_data_lane__DOT__u_3d_dram__DOT__u_dram__DOT__busy_q 
        = vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_data_lane__DOT__u_3d_dram__DOT__u_dram__DOT__busy_q;
    __Vdly__tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_data_lane__DOT__u_3d_dram__DOT__u_dram__DOT__latency_q 
        = vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_data_lane__DOT__u_3d_dram__DOT__u_dram__DOT__latency_q;
    __Vdly__tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_data_lane__DOT__u_3d_dram__DOT__u_dram__DOT__pending_read_q 
        = vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_data_lane__DOT__u_3d_dram__DOT__u_dram__DOT__pending_read_q;
    __Vdly__tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_data_lane__DOT__u_3d_dram__DOT__u_dram__DOT__pending_write_q 
        = vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_data_lane__DOT__u_3d_dram__DOT__u_dram__DOT__pending_write_q;
    __Vdly__tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_data_lane__DOT__u_3d_dram__DOT__u_dram__DOT__pending_wdata_q 
        = vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_data_lane__DOT__u_3d_dram__DOT__u_dram__DOT__pending_wdata_q;
    __Vdly__tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_data_lane__DOT__u_3d_dram__DOT__u_dram__DOT__pending_index_q 
        = vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_data_lane__DOT__u_3d_dram__DOT__u_dram__DOT__pending_index_q;
    __Vdly__tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_data_lane__DOT__u_3d_dram__DOT__u_dram__DOT__pending_id_q 
        = vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_data_lane__DOT__u_3d_dram__DOT__u_dram__DOT__pending_id_q;
    if (vlSelfRef.rst_n) {
        if (vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__exec_req_valid_w) {
            if (vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_execmem__DOT__op_ok_c) {
                if ((8U == (IData)(vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__exec_req_size_bytes_w))) {
                    if ((0U == (7U & (IData)(vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__exec_req_paddr_w)))) {
                        if (vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_execmem__DOT__in_range_c) {
                            if (vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__exec_req_is_write_w) {
                                __VdlyVal__tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_execmem__DOT__mem_q__v0 
                                    = vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__exec_req_wdata_w;
                                __VdlyDim0__tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_execmem__DOT__mem_q__v0 
                                    = (0x000000ffU 
                                       & (IData)(((vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__exec_req_paddr_w 
                                                   - 0x0000000000002000ULL) 
                                                  >> 3U)));
                                vlSelfRef.__VdlyCommitQueuetb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_execmem__DOT__mem_q.enqueue(__VdlyVal__tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_execmem__DOT__mem_q__v0, (IData)(__VdlyDim0__tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_execmem__DOT__mem_q__v0));
                            }
                        }
                    }
                }
            }
        }
    } else {
        vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_execmem__DOT__i = 0U;
        while (VL_GTS_III(32, 0x00000100U, vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_execmem__DOT__i)) {
            __VdlyDim0__tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_execmem__DOT__mem_q__v1 
                = (0x000000ffU & vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_execmem__DOT__i);
            vlSelfRef.__VdlyCommitQueuetb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_execmem__DOT__mem_q.enqueue(0ULL, (IData)(__VdlyDim0__tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_execmem__DOT__mem_q__v1));
            vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_execmem__DOT__i 
                = ((IData)(1U) + vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_execmem__DOT__i);
        }
    }
    if (vlSelfRef.rst_n) {
        if (vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__livehot_req_valid_w) {
            if (vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_livehot__DOT__op_ok_c) {
                if ((8U == (IData)(vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__livehot_req_size_bytes_w))) {
                    if ((0U == (7U & (IData)(vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__livehot_req_paddr_w)))) {
                        if (vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_livehot__DOT__in_range_c) {
                            if (vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__livehot_req_is_write_w) {
                                __VdlyVal__tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_livehot__DOT__mem_q__v0 
                                    = vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__livehot_req_wdata_w;
                                __VdlyDim0__tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_livehot__DOT__mem_q__v0 
                                    = (0x000000ffU 
                                       & (IData)(((vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__livehot_req_paddr_w 
                                                   - 0x0000000000003000ULL) 
                                                  >> 3U)));
                                vlSelfRef.__VdlyCommitQueuetb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_livehot__DOT__mem_q.enqueue(__VdlyVal__tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_livehot__DOT__mem_q__v0, (IData)(__VdlyDim0__tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_livehot__DOT__mem_q__v0));
                            }
                        }
                    }
                }
            }
        }
    } else {
        vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_livehot__DOT__i = 0U;
        while (VL_GTS_III(32, 0x00000100U, vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_livehot__DOT__i)) {
            __VdlyDim0__tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_livehot__DOT__mem_q__v1 
                = (0x000000ffU & vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_livehot__DOT__i);
            vlSelfRef.__VdlyCommitQueuetb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_livehot__DOT__mem_q.enqueue(0ULL, (IData)(__VdlyDim0__tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_livehot__DOT__mem_q__v1));
            vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_livehot__DOT__i 
                = ((IData)(1U) + vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_livehot__DOT__i);
        }
    }
    vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_core__DOT__csr_fault_code_w = 0U;
    vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_core__DOT__csr_fault_w = 0U;
    vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_core__DOT__u_pc__DOT__valid_q 
        = vlSelfRef.rst_n;
    if (vlSelfRef.rst_n) {
        if ((1U & (~ (IData)(vlSelfRef.stall_i)))) {
            __Vdly__tb_nvisc_core_v02_with_mem_domains__DOT__u_core__DOT__u_pc__DOT__pc_q 
                = ((IData)(vlSelfRef.rollback_redirect_i)
                    ? vlSelfRef.rollback_pc_i : ((IData)(vlSelfRef.trap_valid_i)
                                                  ? vlSelfRef.trap_vector_i
                                                  : 
                                                 ((IData)(vlSelfRef.redirect_valid_i)
                                                   ? vlSelfRef.redirect_pc_i
                                                   : 
                                                  (((IData)(vlSelfRef.branch_taken_i) 
                                                    | (IData)(vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_core__DOT__branch_taken_w))
                                                    ? 
                                                   ((IData)(vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_core__DOT__branch_taken_w)
                                                     ? vlSelfRef.branch_target_internal_o
                                                     : vlSelfRef.branch_target_i)
                                                    : 
                                                   (4ULL 
                                                    + vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_core__DOT__u_pc__DOT__pc_q)))));
        }
        __VdlySet__tb_nvisc_core_v02_with_mem_domains__DOT__u_core__DOT__u_rf__DOT__regs_q__v0 = 1U;
        if (((IData)(vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_core__DOT__rf_we_w) 
             & (0U != (IData)(vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_core__DOT__rf_waddr_w)))) {
            __VdlyVal__tb_nvisc_core_v02_with_mem_domains__DOT__u_core__DOT__u_rf__DOT__regs_q__v1 
                = vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_core__DOT__rf_wdata_w;
            __VdlyDim0__tb_nvisc_core_v02_with_mem_domains__DOT__u_core__DOT__u_rf__DOT__regs_q__v1 
                = vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_core__DOT__rf_waddr_w;
            __VdlySet__tb_nvisc_core_v02_with_mem_domains__DOT__u_core__DOT__u_rf__DOT__regs_q__v1 = 1U;
        }
        if (vlSelfRef.flush_i) {
            vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_core__DOT__u_if__DOT__fault_code_q = 0U;
            vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_core__DOT__u_if__DOT__fault_q = 0U;
            VL_ASSIGN_W(228, vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_core__DOT__u_if__DOT__fetch_q, Vtb_nvisc_core_v02_with_mem_domains__ConstPool__CONST_hee3372ac_0);
        } else if ((1U & (~ (IData)(vlSelfRef.stall_i)))) {
            if (vlSelfRef.imem_resp_valid_i) {
                vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_core__DOT__u_if__DOT__fault_code_q 
                    = vlSelfRef.imem_resp_fault_code_i;
                vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_core__DOT__u_if__DOT__fetch_q[0U] 
                    = ((vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_core__DOT__u_csr__DOT__commit_id_q 
                        << 0x00000013U) | (((IData)(vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_core__DOT__u_csr__DOT__privilege_q) 
                                            << 0x00000010U) 
                                           | (IData)(vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_core__DOT__u_csr__DOT__aegis_policy_id_q)));
                vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_core__DOT__u_if__DOT__fetch_q[1U] 
                    = ((vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_core__DOT__u_csr__DOT__commit_id_q 
                        >> 0x0000000dU) | ((IData)(
                                                   (((QData)((IData)(vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_core__DOT__u_csr__DOT__branch_id_q)) 
                                                     << 0x00000020U) 
                                                    | (QData)((IData)(vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_core__DOT__u_csr__DOT__state_id_q)))) 
                                           << 0x00000013U));
                vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_core__DOT__u_if__DOT__fetch_q[2U] 
                    = (((IData)((((QData)((IData)(vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_core__DOT__u_csr__DOT__branch_id_q)) 
                                  << 0x00000020U) | (QData)((IData)(vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_core__DOT__u_csr__DOT__state_id_q)))) 
                        >> 0x0000000dU) | ((IData)(
                                                   ((((QData)((IData)(vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_core__DOT__u_csr__DOT__branch_id_q)) 
                                                      << 0x00000020U) 
                                                     | (QData)((IData)(vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_core__DOT__u_csr__DOT__state_id_q))) 
                                                    >> 0x00000020U)) 
                                           << 0x00000013U));
                vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_core__DOT__u_if__DOT__fetch_q[3U] 
                    = ((0xfff80000U & vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_core__DOT__u_if__DOT__fetch_q[3U]) 
                       | ((IData)(((((QData)((IData)(vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_core__DOT__u_csr__DOT__branch_id_q)) 
                                     << 0x00000020U) 
                                    | (QData)((IData)(vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_core__DOT__u_csr__DOT__state_id_q))) 
                                   >> 0x00000020U)) 
                          >> 0x0000000dU));
                vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_core__DOT__u_if__DOT__fetch_q[3U] 
                    = ((0x0007ffffU & vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_core__DOT__u_if__DOT__fetch_q[3U]) 
                       | (((IData)(vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_core__DOT__u_csr__DOT__core_id_q) 
                           << 0x0000001bU) | ((IData)(vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_core__DOT__u_csr__DOT__thread_id_q) 
                                              << 0x00000013U)));
                vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_core__DOT__u_if__DOT__fetch_q[4U] 
                    = (((0x0007fff8U & (vlSelfRef.imem_resp_instr_i 
                                        << 3U)) | (
                                                   (0x0007ffffU 
                                                    & ((IData)(vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_core__DOT__u_csr__DOT__core_id_q) 
                                                       >> 5U)) 
                                                   | ((IData)(vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_core__DOT__u_csr__DOT__thread_id_q) 
                                                      >> 0x0000000dU))) 
                       | (0xfff80000U & (vlSelfRef.imem_resp_instr_i 
                                         << 3U)));
                vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_core__DOT__u_if__DOT__fetch_q[5U] 
                    = (((vlSelfRef.imem_resp_instr_i 
                         >> 0x0000001dU) | (0x0007fff8U 
                                            & ((IData)(vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_core__DOT__u_pc__DOT__pc_q) 
                                               << 3U))) 
                       | (0xfff80000U & ((IData)(vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_core__DOT__u_pc__DOT__pc_q) 
                                         << 3U)));
                vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_core__DOT__u_if__DOT__fetch_q[6U] 
                    = ((((IData)(vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_core__DOT__u_pc__DOT__pc_q) 
                         >> 0x0000001dU) | (0x0007fff8U 
                                            & ((IData)(
                                                       (vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_core__DOT__u_pc__DOT__pc_q 
                                                        >> 0x00000020U)) 
                                               << 3U))) 
                       | (((0x00010000U & ((~ (IData)(vlSelfRef.imem_resp_fault_i)) 
                                           << 0x00000010U)) 
                           | ((IData)((vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_core__DOT__u_pc__DOT__pc_q 
                                       >> 0x00000020U)) 
                              >> 0x00000010U)) << 0x00000013U));
                vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_core__DOT__u_if__DOT__fetch_q[7U] 
                    = (0x0000000fU & (((0x00010000U 
                                        & ((~ (IData)(vlSelfRef.imem_resp_fault_i)) 
                                           << 0x00000010U)) 
                                       | ((IData)((vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_core__DOT__u_pc__DOT__pc_q 
                                                   >> 0x00000020U)) 
                                          >> 0x00000010U)) 
                                      >> 0x0000000dU));
            } else {
                vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_core__DOT__u_if__DOT__fault_code_q = 0U;
                vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_core__DOT__u_if__DOT__fetch_q[7U] 
                    = (7U & vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_core__DOT__u_if__DOT__fetch_q[7U]);
            }
            vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_core__DOT__u_if__DOT__fault_q 
                = ((IData)(vlSelfRef.imem_resp_valid_i) 
                   && (IData)(vlSelfRef.imem_resp_fault_i));
        }
        vlSelfRef.memdom_csr_resp_valid_o = 0U;
        vlSelfRef.memdom_csr_rdata_o = 0ULL;
        vlSelfRef.memdom_csr_fault_o = 0U;
        vlSelfRef.memdom_csr_fault_code_o = 0U;
        if (vlSelfRef.memdom_csr_valid_i) {
            vlSelfRef.memdom_csr_resp_valid_o = 1U;
            if (((IData)(vlSelfRef.memdom_csr_write_i) 
                 & (IData)(vlSelfRef.memdom_csr_read_i))) {
                vlSelfRef.memdom_csr_fault_o = 1U;
                vlSelfRef.memdom_csr_fault_code_o = 0x0b01U;
            } else if (vlSelfRef.memdom_csr_write_i) {
                if ((1U & (~ VL_ONEHOT_I((((0x0344U 
                                            == (IData)(vlSelfRef.memdom_csr_addr_i)) 
                                           << 1U) | 
                                          (0x0340U 
                                           == (IData)(vlSelfRef.memdom_csr_addr_i))))))) {
                    if ((0U != (((0x0344U == (IData)(vlSelfRef.memdom_csr_addr_i)) 
                                 << 1U) | (0x0340U 
                                           == (IData)(vlSelfRef.memdom_csr_addr_i))))) {
                        if (VL_UNLIKELY((vlSymsp->_vm_contextp__->assertOn()))) {
                            VL_WRITEF_NX("[%0t] %%Error: nvisc_mem_domain_csr_bridge.sv:82: Assertion failed in %m: unique case, but multiple matches found for '12'h%X'\n",4, 'M',vlSymsp->name(),"tb_nvisc_core_v02_with_mem_domains.u_memdom_csr", 'T',-9
                                         , '#',64,VL_TIME_UNITED_Q(1000)
                                         , '#',12,(IData)(vlSelfRef.memdom_csr_addr_i));
                            VL_STOP_MT("rtl/core_v02\\nvisc_mem_domain_csr_bridge.sv", 82, "");
                        }
                    }
                }
                if ((0x0340U == (IData)(vlSelfRef.memdom_csr_addr_i))) {
                    if (((1U == (7U & (IData)(vlSelfRef.memdom_csr_wdata_i))) 
                         | ((2U == (7U & (IData)(vlSelfRef.memdom_csr_wdata_i))) 
                            | (3U == (7U & (IData)(vlSelfRef.memdom_csr_wdata_i)))))) {
                        __Vdly__tb_nvisc_core_v02_with_mem_domains__DOT__u_memdom_csr__DOT__mem_domain_select_q 
                            = (7U & (IData)(vlSelfRef.memdom_csr_wdata_i));
                    } else {
                        vlSelfRef.memdom_csr_fault_o = 1U;
                        vlSelfRef.memdom_csr_fault_code_o = 0x0b02U;
                    }
                } else if ((0x0344U == (IData)(vlSelfRef.memdom_csr_addr_i))) {
                    __Vdly__tb_nvisc_core_v02_with_mem_domains__DOT__u_memdom_csr__DOT__mem_domain_override_enable_q 
                        = (1U & (IData)(vlSelfRef.memdom_csr_wdata_i));
                } else {
                    vlSelfRef.memdom_csr_fault_o = 1U;
                    vlSelfRef.memdom_csr_fault_code_o = 0x0b03U;
                }
            } else if (vlSelfRef.memdom_csr_read_i) {
                if ((1U & (~ VL_ONEHOT_I((((0x0348U 
                                            == (IData)(vlSelfRef.memdom_csr_addr_i)) 
                                           << 2U) | 
                                          (((0x0344U 
                                             == (IData)(vlSelfRef.memdom_csr_addr_i)) 
                                            << 1U) 
                                           | (0x0340U 
                                              == (IData)(vlSelfRef.memdom_csr_addr_i)))))))) {
                    if ((0U != (((0x0348U == (IData)(vlSelfRef.memdom_csr_addr_i)) 
                                 << 2U) | (((0x0344U 
                                             == (IData)(vlSelfRef.memdom_csr_addr_i)) 
                                            << 1U) 
                                           | (0x0340U 
                                              == (IData)(vlSelfRef.memdom_csr_addr_i)))))) {
                        if (VL_UNLIKELY((vlSymsp->_vm_contextp__->assertOn()))) {
                            VL_WRITEF_NX("[%0t] %%Error: nvisc_mem_domain_csr_bridge.sv:104: Assertion failed in %m: unique case, but multiple matches found for '12'h%X'\n",4, 'M',vlSymsp->name(),"tb_nvisc_core_v02_with_mem_domains.u_memdom_csr", 'T',-9
                                         , '#',64,VL_TIME_UNITED_Q(1000)
                                         , '#',12,(IData)(vlSelfRef.memdom_csr_addr_i));
                            VL_STOP_MT("rtl/core_v02\\nvisc_mem_domain_csr_bridge.sv", 104, "");
                        }
                    }
                }
                if ((0x0340U == (IData)(vlSelfRef.memdom_csr_addr_i))) {
                    vlSelfRef.memdom_csr_rdata_o = (QData)((IData)(vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_memdom_csr__DOT__mem_domain_select_q));
                } else if ((0x0344U == (IData)(vlSelfRef.memdom_csr_addr_i))) {
                    vlSelfRef.memdom_csr_rdata_o = (QData)((IData)(vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_memdom_csr__DOT__mem_domain_override_enable_q));
                } else if ((0x0348U == (IData)(vlSelfRef.memdom_csr_addr_i))) {
                    vlSelfRef.memdom_csr_rdata_o = (QData)((IData)(
                                                                   (((IData)(vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_memdom_csr__DOT__effective_domain_c) 
                                                                     << 5U) 
                                                                    | (((IData)(vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__wrapper_override_domain_w) 
                                                                        << 2U) 
                                                                       | ((IData)(vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_memdom_csr__DOT__mem_domain_override_enable_q) 
                                                                          << 1U)))));
                } else {
                    vlSelfRef.memdom_csr_fault_o = 1U;
                    vlSelfRef.memdom_csr_fault_code_o = 0x0b03U;
                }
            } else {
                vlSelfRef.memdom_csr_fault_o = 1U;
                vlSelfRef.memdom_csr_fault_code_o = 0x0b04U;
            }
        }
        vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_core__DOT__lsu_fault_code_w = 0U;
        vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_core__DOT__lsu_fault_w = 0U;
        if (vlSelfRef.lsu_valid_o) {
            if (vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_core__DOT__u_lsu__DOT__bad_size_c) {
                vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_core__DOT__lsu_fault_code_w = 0x0101U;
                vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_core__DOT__lsu_fault_w = 1U;
            } else if (vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_core__DOT__u_lsu__DOT__both_read_write_c) {
                vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_core__DOT__lsu_fault_code_w = 0x0102U;
                vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_core__DOT__lsu_fault_w = 1U;
            } else if (vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_core__DOT__u_lsu__DOT__no_op_c) {
                vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_core__DOT__lsu_fault_code_w = 0x0103U;
                vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_core__DOT__lsu_fault_w = 1U;
            }
        }
        if ((((IData)(vlSelfRef.lsu_valid_o) & (IData)(vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_core__DOT__ctrl_mem_read_w)) 
             & (IData)(vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_core__DOT__ctrl_reg_write_w))) {
            vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_core__DOT__load_pending_q = 1U;
            vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_core__DOT__load_rd_q 
                = (0x0000001fU & (vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_core__DOT__u_dec__DOT__dec[6U] 
                                  >> 0x00000017U));
        }
        if (((IData)(vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__memsys_resp_valid_w) 
             | (IData)(vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__memsys_fault_w))) {
            vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_core__DOT__load_pending_q = 0U;
        }
        vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_core__DOT__mmu_resp_vaddr_w = 0ULL;
        vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_core__DOT__mmu_resp_mem_domain_w = 1U;
        vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_core__DOT__mmu_fault_code_w = 0U;
        vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_core__DOT__mmu_fault_w = 0U;
        if ((0x02000000U & vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_core__DOT__u_lsu__DOT__req_q[11U])) {
            if ((1U & (~ (IData)(vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_core__DOT__u_mmu__DOT__page_fault_c)))) {
                if ((1U & (~ (IData)(vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_core__DOT__u_mmu__DOT__align_fault_c)))) {
                    vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_core__DOT__mmu_resp_vaddr_w 
                        = (((QData)((IData)(vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_core__DOT__u_lsu__DOT__req_q[10U])) 
                            << 0x0000002aU) | (((QData)((IData)(vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_core__DOT__u_lsu__DOT__req_q[9U])) 
                                                << 0x0000000aU) 
                                               | ((QData)((IData)(vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_core__DOT__u_lsu__DOT__req_q[8U])) 
                                                  >> 0x00000016U)));
                    vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_core__DOT__mmu_resp_mem_domain_w 
                        = (7U & (vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_core__DOT__u_lsu__DOT__req_q[4U] 
                                 >> 3U));
                }
            }
            if (vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_core__DOT__u_mmu__DOT__page_fault_c) {
                vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_core__DOT__mmu_fault_code_w = 0x0301U;
                vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_core__DOT__mmu_fault_w = 1U;
            } else if (vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_core__DOT__u_mmu__DOT__align_fault_c) {
                vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_core__DOT__mmu_fault_code_w = 0x0302U;
                vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_core__DOT__mmu_fault_w = 1U;
            }
        }
        if (vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_core__DOT__mmu_resp_valid_w) {
            vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__pending_domain_q 
                = vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_memdom_csr__DOT__effective_domain_c;
        }
        vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__exec_fault_code_w = 0U;
        vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__exec_fault_w = 0U;
        vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__livehot_fault_code_w = 0U;
        vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__livehot_fault_w = 0U;
        vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__exec_resp_write_ack_w = 0U;
        vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__livehot_resp_write_ack_w = 0U;
        vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__exec_resp_valid_w = 0U;
        vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__livehot_resp_valid_w = 0U;
        vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__exec_resp_rdata_w = 0ULL;
        if (vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__exec_req_valid_w) {
            if (vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_execmem__DOT__op_ok_c) {
                if ((8U == (IData)(vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__exec_req_size_bytes_w))) {
                    if ((0U == (7U & (IData)(vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__exec_req_paddr_w)))) {
                        if ((1U & (~ (IData)(vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_execmem__DOT__in_range_c)))) {
                            vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__exec_fault_code_w = 0x0904U;
                            vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__exec_fault_w = 1U;
                        }
                        if (vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_execmem__DOT__in_range_c) {
                            if (vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__exec_req_is_write_w) {
                                vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__exec_resp_write_ack_w = 1U;
                                vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__exec_resp_valid_w = 1U;
                            } else if (vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__exec_req_is_read_w) {
                                vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__exec_resp_valid_w = 1U;
                            }
                            if ((1U & (~ (IData)(vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__exec_req_is_write_w)))) {
                                if (vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__exec_req_is_read_w) {
                                    vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__exec_resp_rdata_w 
                                        = vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_execmem__DOT__mem_q
                                        [(0x000000ffU 
                                          & (IData)(
                                                    ((vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__exec_req_paddr_w 
                                                      - 0x0000000000002000ULL) 
                                                     >> 3U)))];
                                }
                            }
                        }
                    } else {
                        vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__exec_fault_code_w = 0x0903U;
                        vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__exec_fault_w = 1U;
                    }
                } else {
                    vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__exec_fault_code_w = 0x0902U;
                    vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__exec_fault_w = 1U;
                }
            } else {
                vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__exec_fault_code_w = 0x0901U;
                vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__exec_fault_w = 1U;
            }
        }
        vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__livehot_resp_rdata_w = 0ULL;
        if (vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__livehot_req_valid_w) {
            if (vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_livehot__DOT__op_ok_c) {
                if ((8U == (IData)(vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__livehot_req_size_bytes_w))) {
                    if ((0U == (7U & (IData)(vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__livehot_req_paddr_w)))) {
                        if ((1U & (~ (IData)(vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_livehot__DOT__in_range_c)))) {
                            vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__livehot_fault_code_w = 0x0a04U;
                            vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__livehot_fault_w = 1U;
                        }
                        if (vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_livehot__DOT__in_range_c) {
                            if (vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__livehot_req_is_write_w) {
                                vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__livehot_resp_write_ack_w = 1U;
                                vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__livehot_resp_valid_w = 1U;
                            } else if (vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__livehot_req_is_read_w) {
                                vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__livehot_resp_valid_w = 1U;
                            }
                            if ((1U & (~ (IData)(vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__livehot_req_is_write_w)))) {
                                if (vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__livehot_req_is_read_w) {
                                    vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__livehot_resp_rdata_w 
                                        = vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_livehot__DOT__mem_q
                                        [(0x000000ffU 
                                          & (IData)(
                                                    ((vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__livehot_req_paddr_w 
                                                      - 0x0000000000003000ULL) 
                                                     >> 3U)))];
                                }
                            }
                        }
                    } else {
                        vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__livehot_fault_code_w = 0x0a03U;
                        vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__livehot_fault_w = 1U;
                    }
                } else {
                    vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__livehot_fault_code_w = 0x0a02U;
                    vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__livehot_fault_w = 1U;
                }
            } else {
                vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__livehot_fault_code_w = 0x0a01U;
                vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__livehot_fault_w = 1U;
            }
        }
    } else {
        __Vdly__tb_nvisc_core_v02_with_mem_domains__DOT__u_core__DOT__u_pc__DOT__pc_q = 0ULL;
        __VdlySet__tb_nvisc_core_v02_with_mem_domains__DOT__u_core__DOT__u_rf__DOT__regs_q__v2 = 1U;
        vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_core__DOT__u_if__DOT__fault_code_q = 0U;
        vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_core__DOT__u_if__DOT__fault_q = 0U;
        __Vdly__tb_nvisc_core_v02_with_mem_domains__DOT__u_memdom_csr__DOT__mem_domain_select_q = 1U;
        __Vdly__tb_nvisc_core_v02_with_mem_domains__DOT__u_memdom_csr__DOT__mem_domain_override_enable_q = 0U;
        vlSelfRef.memdom_csr_resp_valid_o = 0U;
        vlSelfRef.memdom_csr_rdata_o = 0ULL;
        vlSelfRef.memdom_csr_fault_o = 0U;
        vlSelfRef.memdom_csr_fault_code_o = 0U;
        vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_core__DOT__lsu_fault_code_w = 0U;
        vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_core__DOT__lsu_fault_w = 0U;
        vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_core__DOT__load_pending_q = 0U;
        vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_core__DOT__load_rd_q = 0U;
        vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_core__DOT__mmu_resp_vaddr_w = 0ULL;
        vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_core__DOT__mmu_resp_mem_domain_w = 1U;
        vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_core__DOT__mmu_fault_code_w = 0U;
        vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_core__DOT__mmu_fault_w = 0U;
        VL_ASSIGN_W(228, vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_core__DOT__u_if__DOT__fetch_q, Vtb_nvisc_core_v02_with_mem_domains__ConstPool__CONST_hee3372ac_0);
        vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__pending_domain_q = 1U;
        vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__exec_fault_code_w = 0U;
        vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__exec_fault_w = 0U;
        vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__livehot_fault_code_w = 0U;
        vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__livehot_fault_w = 0U;
        vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__exec_resp_write_ack_w = 0U;
        vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__livehot_resp_write_ack_w = 0U;
        vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__exec_resp_valid_w = 0U;
        vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__livehot_resp_valid_w = 0U;
        vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__exec_resp_rdata_w = 0ULL;
        vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__livehot_resp_rdata_w = 0ULL;
    }
    if (vlSelfRef.rst_n) {
        __Vdly__tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_data_lane__DOT__u_3d_dram__DOT__dram_resp_valid_w = 0U;
        __Vdly__tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_data_lane__DOT__u_3d_dram__DOT__dram_resp_rdata_w = 0ULL;
        __Vdly__tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_data_lane__DOT__u_3d_dram__DOT__dram_resp_write_ack_w = 0U;
        __Vdly__tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_data_lane__DOT__u_3d_dram__DOT__dram_fault_w = 0U;
        __Vdly__tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_data_lane__DOT__u_3d_dram__DOT__dram_fault_code_w = 0U;
        if (((IData)(vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_data_lane__DOT__u_3d_dram__DOT__cache_mem_req_valid_w) 
             & (~ (IData)(vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_data_lane__DOT__u_3d_dram__DOT__u_dram__DOT__busy_q)))) {
            if (((0x0000000080000000ULL <= vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_data_lane__DOT__u_3d_dram__DOT__cache_mem_req_paddr_w) 
                 & (0x0000000000000400ULL > VL_SHIFTR_QQI(64,64,32, 
                                                          (vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_data_lane__DOT__u_3d_dram__DOT__cache_mem_req_paddr_w 
                                                           - 0x0000000080000000ULL), 3U)))) {
                if ((0U == (7U & (IData)(vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_data_lane__DOT__u_3d_dram__DOT__cache_mem_req_paddr_w)))) {
                    if ((8U == (IData)(vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_data_lane__DOT__u_3d_dram__DOT__cache_mem_req_size_bytes_w))) {
                        if (((IData)(vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_data_lane__DOT__u_3d_dram__DOT__cache_mem_req_is_read_w) 
                             ^ (IData)(vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_data_lane__DOT__u_3d_dram__DOT__cache_mem_req_is_write_w))) {
                            __Vdly__tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_data_lane__DOT__u_3d_dram__DOT__u_dram__DOT__busy_q = 1U;
                            __Vdly__tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_data_lane__DOT__u_3d_dram__DOT__u_dram__DOT__latency_q = 3U;
                            __Vdly__tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_data_lane__DOT__u_3d_dram__DOT__u_dram__DOT__pending_read_q 
                                = vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_data_lane__DOT__u_3d_dram__DOT__cache_mem_req_is_read_w;
                            __Vdly__tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_data_lane__DOT__u_3d_dram__DOT__u_dram__DOT__pending_write_q 
                                = vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_data_lane__DOT__u_3d_dram__DOT__cache_mem_req_is_write_w;
                            __Vdly__tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_data_lane__DOT__u_3d_dram__DOT__u_dram__DOT__pending_wdata_q 
                                = vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_data_lane__DOT__u_3d_dram__DOT__cache_mem_req_wdata_w;
                            __Vdly__tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_data_lane__DOT__u_3d_dram__DOT__u_dram__DOT__pending_index_q 
                                = (0x000003ffU & (IData)(
                                                         ((vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_data_lane__DOT__u_3d_dram__DOT__cache_mem_req_paddr_w 
                                                           - 0x0000000080000000ULL) 
                                                          >> 3U)));
                            __Vdly__tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_data_lane__DOT__u_3d_dram__DOT__u_dram__DOT__pending_id_q 
                                = vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_data_lane__DOT__u_3d_dram__DOT__cache_mem_req_id_w;
                        } else {
                            __Vdly__tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_data_lane__DOT__u_3d_dram__DOT__dram_fault_w = 1U;
                            __Vdly__tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_data_lane__DOT__u_3d_dram__DOT__dram_fault_code_w = 0x0d04U;
                        }
                    } else {
                        __Vdly__tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_data_lane__DOT__u_3d_dram__DOT__dram_fault_w = 1U;
                        __Vdly__tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_data_lane__DOT__u_3d_dram__DOT__dram_fault_code_w = 0x0d03U;
                    }
                } else {
                    __Vdly__tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_data_lane__DOT__u_3d_dram__DOT__dram_fault_w = 1U;
                    __Vdly__tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_data_lane__DOT__u_3d_dram__DOT__dram_fault_code_w = 0x0d02U;
                }
            } else {
                __Vdly__tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_data_lane__DOT__u_3d_dram__DOT__dram_fault_w = 1U;
                __Vdly__tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_data_lane__DOT__u_3d_dram__DOT__dram_fault_code_w = 0x0d01U;
            }
        } else if (vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_data_lane__DOT__u_3d_dram__DOT__u_dram__DOT__busy_q) {
            if ((0U != (IData)(vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_data_lane__DOT__u_3d_dram__DOT__u_dram__DOT__latency_q))) {
                __Vdly__tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_data_lane__DOT__u_3d_dram__DOT__u_dram__DOT__latency_q 
                    = (7U & ((IData)(vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_data_lane__DOT__u_3d_dram__DOT__u_dram__DOT__latency_q) 
                             - (IData)(1U)));
            } else {
                __Vdly__tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_data_lane__DOT__u_3d_dram__DOT__u_dram__DOT__busy_q = 0U;
                __Vdly__tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_data_lane__DOT__u_3d_dram__DOT__dram_resp_valid_w = 1U;
                if (vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_data_lane__DOT__u_3d_dram__DOT__u_dram__DOT__pending_write_q) {
                    __VdlyVal__tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_data_lane__DOT__u_3d_dram__DOT__u_dram__DOT__mem_q__v0 
                        = vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_data_lane__DOT__u_3d_dram__DOT__u_dram__DOT__pending_wdata_q;
                    __VdlyDim0__tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_data_lane__DOT__u_3d_dram__DOT__u_dram__DOT__mem_q__v0 
                        = vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_data_lane__DOT__u_3d_dram__DOT__u_dram__DOT__pending_index_q;
                    vlSelfRef.__VdlyCommitQueuetb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_data_lane__DOT__u_3d_dram__DOT__u_dram__DOT__mem_q.enqueue(__VdlyVal__tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_data_lane__DOT__u_3d_dram__DOT__u_dram__DOT__mem_q__v0, (IData)(__VdlyDim0__tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_data_lane__DOT__u_3d_dram__DOT__u_dram__DOT__mem_q__v0));
                    __Vdly__tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_data_lane__DOT__u_3d_dram__DOT__dram_resp_write_ack_w = 1U;
                }
                if (vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_data_lane__DOT__u_3d_dram__DOT__u_dram__DOT__pending_read_q) {
                    __Vdly__tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_data_lane__DOT__u_3d_dram__DOT__dram_resp_rdata_w 
                        = vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_data_lane__DOT__u_3d_dram__DOT__u_dram__DOT__mem_q
                        [vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_data_lane__DOT__u_3d_dram__DOT__u_dram__DOT__pending_index_q];
                }
            }
        }
    } else {
        vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_data_lane__DOT__u_3d_dram__DOT__u_dram__DOT__i = 0U;
        while (VL_GTS_III(32, 0x00000400U, vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_data_lane__DOT__u_3d_dram__DOT__u_dram__DOT__i)) {
            __VdlyDim0__tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_data_lane__DOT__u_3d_dram__DOT__u_dram__DOT__mem_q__v1 
                = (0x000003ffU & vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_data_lane__DOT__u_3d_dram__DOT__u_dram__DOT__i);
            vlSelfRef.__VdlyCommitQueuetb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_data_lane__DOT__u_3d_dram__DOT__u_dram__DOT__mem_q.enqueue(0ULL, (IData)(__VdlyDim0__tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_data_lane__DOT__u_3d_dram__DOT__u_dram__DOT__mem_q__v1));
            vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_data_lane__DOT__u_3d_dram__DOT__u_dram__DOT__i 
                = ((IData)(1U) + vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_data_lane__DOT__u_3d_dram__DOT__u_dram__DOT__i);
        }
        __Vdly__tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_data_lane__DOT__u_3d_dram__DOT__dram_resp_valid_w = 0U;
        __Vdly__tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_data_lane__DOT__u_3d_dram__DOT__dram_resp_rdata_w = 0ULL;
        __Vdly__tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_data_lane__DOT__u_3d_dram__DOT__dram_resp_write_ack_w = 0U;
        __Vdly__tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_data_lane__DOT__u_3d_dram__DOT__dram_fault_w = 0U;
        __Vdly__tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_data_lane__DOT__u_3d_dram__DOT__dram_fault_code_w = 0U;
        __Vdly__tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_data_lane__DOT__u_3d_dram__DOT__u_dram__DOT__busy_q = 0U;
        __Vdly__tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_data_lane__DOT__u_3d_dram__DOT__u_dram__DOT__latency_q = 0U;
        __Vdly__tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_data_lane__DOT__u_3d_dram__DOT__u_dram__DOT__pending_read_q = 0U;
        __Vdly__tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_data_lane__DOT__u_3d_dram__DOT__u_dram__DOT__pending_write_q = 0U;
        __Vdly__tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_data_lane__DOT__u_3d_dram__DOT__u_dram__DOT__pending_wdata_q = 0ULL;
        __Vdly__tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_data_lane__DOT__u_3d_dram__DOT__u_dram__DOT__pending_index_q = 0U;
        __Vdly__tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_data_lane__DOT__u_3d_dram__DOT__u_dram__DOT__pending_id_q = 0U;
    }
    if (__VdlySet__tb_nvisc_core_v02_with_mem_domains__DOT__u_core__DOT__u_rf__DOT__regs_q__v0) {
        vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_core__DOT__u_rf__DOT__regs_q[0U] = 0ULL;
    }
    if (__VdlySet__tb_nvisc_core_v02_with_mem_domains__DOT__u_core__DOT__u_rf__DOT__regs_q__v1) {
        vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_core__DOT__u_rf__DOT__regs_q[__VdlyDim0__tb_nvisc_core_v02_with_mem_domains__DOT__u_core__DOT__u_rf__DOT__regs_q__v1] 
            = __VdlyVal__tb_nvisc_core_v02_with_mem_domains__DOT__u_core__DOT__u_rf__DOT__regs_q__v1;
    }
    if (__VdlySet__tb_nvisc_core_v02_with_mem_domains__DOT__u_core__DOT__u_rf__DOT__regs_q__v2) {
        vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_core__DOT__u_rf__DOT__regs_q[0U] = 0ULL;
        vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_core__DOT__u_rf__DOT__regs_q[1U] = 0ULL;
        vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_core__DOT__u_rf__DOT__regs_q[2U] = 0ULL;
        vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_core__DOT__u_rf__DOT__regs_q[3U] = 0ULL;
        vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_core__DOT__u_rf__DOT__regs_q[4U] = 0ULL;
        vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_core__DOT__u_rf__DOT__regs_q[5U] = 0ULL;
        vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_core__DOT__u_rf__DOT__regs_q[6U] = 0ULL;
        vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_core__DOT__u_rf__DOT__regs_q[7U] = 0ULL;
        vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_core__DOT__u_rf__DOT__regs_q[8U] = 0ULL;
        vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_core__DOT__u_rf__DOT__regs_q[9U] = 0ULL;
        vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_core__DOT__u_rf__DOT__regs_q[10U] = 0ULL;
        vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_core__DOT__u_rf__DOT__regs_q[11U] = 0ULL;
        vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_core__DOT__u_rf__DOT__regs_q[12U] = 0ULL;
        vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_core__DOT__u_rf__DOT__regs_q[13U] = 0ULL;
        vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_core__DOT__u_rf__DOT__regs_q[14U] = 0ULL;
        vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_core__DOT__u_rf__DOT__regs_q[15U] = 0ULL;
        vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_core__DOT__u_rf__DOT__regs_q[16U] = 0ULL;
        vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_core__DOT__u_rf__DOT__regs_q[17U] = 0ULL;
        vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_core__DOT__u_rf__DOT__regs_q[18U] = 0ULL;
        vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_core__DOT__u_rf__DOT__regs_q[19U] = 0ULL;
        vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_core__DOT__u_rf__DOT__regs_q[20U] = 0ULL;
        vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_core__DOT__u_rf__DOT__regs_q[21U] = 0ULL;
        vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_core__DOT__u_rf__DOT__regs_q[22U] = 0ULL;
        vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_core__DOT__u_rf__DOT__regs_q[23U] = 0ULL;
        vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_core__DOT__u_rf__DOT__regs_q[24U] = 0ULL;
        vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_core__DOT__u_rf__DOT__regs_q[25U] = 0ULL;
        vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_core__DOT__u_rf__DOT__regs_q[26U] = 0ULL;
        vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_core__DOT__u_rf__DOT__regs_q[27U] = 0ULL;
        vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_core__DOT__u_rf__DOT__regs_q[28U] = 0ULL;
        vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_core__DOT__u_rf__DOT__regs_q[29U] = 0ULL;
        vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_core__DOT__u_rf__DOT__regs_q[30U] = 0ULL;
        vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_core__DOT__u_rf__DOT__regs_q[31U] = 0ULL;
    }
    vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_memdom_csr__DOT__mem_domain_select_q 
        = __Vdly__tb_nvisc_core_v02_with_mem_domains__DOT__u_memdom_csr__DOT__mem_domain_select_q;
    vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_memdom_csr__DOT__mem_domain_override_enable_q 
        = __Vdly__tb_nvisc_core_v02_with_mem_domains__DOT__u_memdom_csr__DOT__mem_domain_override_enable_q;
    vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_core__DOT__u_pc__DOT__pc_q 
        = __Vdly__tb_nvisc_core_v02_with_mem_domains__DOT__u_core__DOT__u_pc__DOT__pc_q;
    vlSelfRef.__VdlyCommitQueuetb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_execmem__DOT__mem_q.commit(vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_execmem__DOT__mem_q);
    vlSelfRef.__VdlyCommitQueuetb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_livehot__DOT__mem_q.commit(vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_livehot__DOT__mem_q);
    vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_data_lane__DOT__u_3d_dram__DOT__u_dram__DOT__busy_q 
        = __Vdly__tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_data_lane__DOT__u_3d_dram__DOT__u_dram__DOT__busy_q;
    vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_data_lane__DOT__u_3d_dram__DOT__u_dram__DOT__latency_q 
        = __Vdly__tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_data_lane__DOT__u_3d_dram__DOT__u_dram__DOT__latency_q;
    vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_data_lane__DOT__u_3d_dram__DOT__u_dram__DOT__pending_read_q 
        = __Vdly__tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_data_lane__DOT__u_3d_dram__DOT__u_dram__DOT__pending_read_q;
    vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_data_lane__DOT__u_3d_dram__DOT__u_dram__DOT__pending_write_q 
        = __Vdly__tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_data_lane__DOT__u_3d_dram__DOT__u_dram__DOT__pending_write_q;
    vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_data_lane__DOT__u_3d_dram__DOT__u_dram__DOT__pending_wdata_q 
        = __Vdly__tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_data_lane__DOT__u_3d_dram__DOT__u_dram__DOT__pending_wdata_q;
    vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_data_lane__DOT__u_3d_dram__DOT__u_dram__DOT__pending_index_q 
        = __Vdly__tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_data_lane__DOT__u_3d_dram__DOT__u_dram__DOT__pending_index_q;
    vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_data_lane__DOT__u_3d_dram__DOT__u_dram__DOT__pending_id_q 
        = __Vdly__tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_data_lane__DOT__u_3d_dram__DOT__u_dram__DOT__pending_id_q;
    vlSelfRef.__VdlyCommitQueuetb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_data_lane__DOT__u_3d_dram__DOT__u_dram__DOT__mem_q.commit(vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_data_lane__DOT__u_3d_dram__DOT__u_dram__DOT__mem_q);
    if (vlSelfRef.rst_n) {
        vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_core__DOT__u_csr__DOT__thread_id_q 
            = vlSelfRef.thread_id_i;
        vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_core__DOT__u_csr__DOT__branch_id_q 
            = vlSelfRef.branch_id_i;
        vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_core__DOT__u_csr__DOT__state_id_q 
            = vlSelfRef.state_id_i;
        vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_core__DOT__u_csr__DOT__commit_id_q 
            = vlSelfRef.commit_id_i;
        vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_core__DOT__u_csr__DOT__privilege_q 
            = vlSelfRef.privilege_i;
        vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_core__DOT__u_csr__DOT__aegis_policy_id_q 
            = vlSelfRef.aegis_policy_id_i;
        __Vdly__tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_data_lane__DOT__cache3d_resp_valid_w = 0U;
        __Vdly__tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_data_lane__DOT__cache3d_resp_rdata_w = 0ULL;
        __Vdly__tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_data_lane__DOT__cache3d_resp_write_ack_w = 0U;
        __Vdly__tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_data_lane__DOT__cache3d_fault_w = 0U;
        __Vdly__tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_data_lane__DOT__cache3d_fault_code_w = 0U;
        vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_data_lane__DOT__u_3d_dram__DOT__cache_mem_req_valid_w = 0U;
        vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_data_lane__DOT__u_3d_dram__DOT__cache_mem_req_is_read_w = 0U;
        vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_data_lane__DOT__u_3d_dram__DOT__cache_mem_req_is_write_w = 0U;
        vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_data_lane__DOT__u_3d_dram__DOT__cache_mem_req_paddr_w = 0ULL;
        vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_data_lane__DOT__u_3d_dram__DOT__cache_mem_req_wdata_w = 0ULL;
        vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_data_lane__DOT__u_3d_dram__DOT__cache_mem_req_size_bytes_w = 0U;
        vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_data_lane__DOT__u_3d_dram__DOT__cache_mem_req_id_w = 0U;
        if (((IData)(vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__cache_csr_flush_3d_w) 
             | (IData)(vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__cache_csr_flush_hierarchy_w))) {
            __VdlySet__tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_data_lane__DOT__u_3d_dram__DOT__u_3d_cache__DOT__valid_q__v0 = 1U;
        }
        if ((0U == (IData)(vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_data_lane__DOT__u_3d_dram__DOT__u_3d_cache__DOT__state_q))) {
            if (vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_data_lane__DOT__l1d_mem_req_valid_w) {
                if ((0U == (7U & (IData)(vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_data_lane__DOT__l1d_mem_req_paddr_w)))) {
                    if ((8U == (IData)(vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_data_lane__DOT__l1d_mem_req_size_bytes_w))) {
                        if (((IData)(vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_data_lane__DOT__l1d_mem_req_is_read_w) 
                             ^ (IData)(vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_data_lane__DOT__l1d_mem_req_is_write_w))) {
                            if (vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_data_lane__DOT__l1d_mem_req_is_read_w) {
                                if ((vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_data_lane__DOT__u_3d_dram__DOT__u_3d_cache__DOT__valid_q
                                     [(0x0000000fU 
                                       & (IData)((vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_data_lane__DOT__l1d_mem_req_paddr_w 
                                                  >> 3U)))] 
                                     & (vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_data_lane__DOT__u_3d_dram__DOT__u_3d_cache__DOT__tag_q
                                        [(0x0000000fU 
                                          & (IData)(
                                                    (vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_data_lane__DOT__l1d_mem_req_paddr_w 
                                                     >> 3U)))] 
                                        == (0xffffffffffffff80ULL 
                                            & vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_data_lane__DOT__l1d_mem_req_paddr_w)))) {
                                    __Vdly__tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_data_lane__DOT__cache3d_resp_valid_w = 1U;
                                    __Vdly__tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_data_lane__DOT__cache3d_resp_rdata_w 
                                        = vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_data_lane__DOT__u_3d_dram__DOT__u_3d_cache__DOT__data_q
                                        [(0x0000000fU 
                                          & (IData)(
                                                    (vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_data_lane__DOT__l1d_mem_req_paddr_w 
                                                     >> 3U)))];
                                } else {
                                    __Vdly__tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_data_lane__DOT__u_3d_dram__DOT__u_3d_cache__DOT__pending_index_q 
                                        = (0x0000000fU 
                                           & (IData)(
                                                     (vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_data_lane__DOT__l1d_mem_req_paddr_w 
                                                      >> 3U)));
                                    __Vdly__tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_data_lane__DOT__u_3d_dram__DOT__u_3d_cache__DOT__pending_tag_q 
                                        = (0xffffffffffffff80ULL 
                                           & vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_data_lane__DOT__l1d_mem_req_paddr_w);
                                    vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_data_lane__DOT__u_3d_dram__DOT__cache_mem_req_valid_w = 1U;
                                    vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_data_lane__DOT__u_3d_dram__DOT__cache_mem_req_is_read_w = 1U;
                                    vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_data_lane__DOT__u_3d_dram__DOT__cache_mem_req_paddr_w 
                                        = vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_data_lane__DOT__l1d_mem_req_paddr_w;
                                    vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_data_lane__DOT__u_3d_dram__DOT__cache_mem_req_size_bytes_w 
                                        = vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_data_lane__DOT__l1d_mem_req_size_bytes_w;
                                    vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_data_lane__DOT__u_3d_dram__DOT__cache_mem_req_id_w 
                                        = (0x000000ffU 
                                           & (vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__data_req_id_w[3U] 
                                              >> 0x00000013U));
                                    __Vdly__tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_data_lane__DOT__u_3d_dram__DOT__u_3d_cache__DOT__state_q = 1U;
                                }
                            } else if (vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_data_lane__DOT__l1d_mem_req_is_write_w) {
                                __VdlyDim0__tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_data_lane__DOT__u_3d_dram__DOT__u_3d_cache__DOT__valid_q__v16 
                                    = (0x0000000fU 
                                       & (IData)((vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_data_lane__DOT__l1d_mem_req_paddr_w 
                                                  >> 3U)));
                                __VdlySet__tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_data_lane__DOT__u_3d_dram__DOT__u_3d_cache__DOT__valid_q__v16 = 1U;
                                __VdlyVal__tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_data_lane__DOT__u_3d_dram__DOT__u_3d_cache__DOT__tag_q__v0 
                                    = (0xffffffffffffff80ULL 
                                       & vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_data_lane__DOT__l1d_mem_req_paddr_w);
                                __VdlyDim0__tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_data_lane__DOT__u_3d_dram__DOT__u_3d_cache__DOT__tag_q__v0 
                                    = (0x0000000fU 
                                       & (IData)((vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_data_lane__DOT__l1d_mem_req_paddr_w 
                                                  >> 3U)));
                                __VdlyVal__tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_data_lane__DOT__u_3d_dram__DOT__u_3d_cache__DOT__data_q__v0 
                                    = vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_data_lane__DOT__l1d_mem_req_wdata_w;
                                __VdlyDim0__tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_data_lane__DOT__u_3d_dram__DOT__u_3d_cache__DOT__data_q__v0 
                                    = (0x0000000fU 
                                       & (IData)((vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_data_lane__DOT__l1d_mem_req_paddr_w 
                                                  >> 3U)));
                                __Vdly__tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_data_lane__DOT__u_3d_dram__DOT__u_3d_cache__DOT__pending_index_q 
                                    = (0x0000000fU 
                                       & (IData)((vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_data_lane__DOT__l1d_mem_req_paddr_w 
                                                  >> 3U)));
                                __Vdly__tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_data_lane__DOT__u_3d_dram__DOT__u_3d_cache__DOT__pending_tag_q 
                                    = (0xffffffffffffff80ULL 
                                       & vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_data_lane__DOT__l1d_mem_req_paddr_w);
                                vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_data_lane__DOT__u_3d_dram__DOT__cache_mem_req_valid_w = 1U;
                                vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_data_lane__DOT__u_3d_dram__DOT__cache_mem_req_is_write_w = 1U;
                                vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_data_lane__DOT__u_3d_dram__DOT__cache_mem_req_paddr_w 
                                    = vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_data_lane__DOT__l1d_mem_req_paddr_w;
                                vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_data_lane__DOT__u_3d_dram__DOT__cache_mem_req_wdata_w 
                                    = vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_data_lane__DOT__l1d_mem_req_wdata_w;
                                vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_data_lane__DOT__u_3d_dram__DOT__cache_mem_req_size_bytes_w 
                                    = vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_data_lane__DOT__l1d_mem_req_size_bytes_w;
                                vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_data_lane__DOT__u_3d_dram__DOT__cache_mem_req_id_w 
                                    = (0x000000ffU 
                                       & (vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__data_req_id_w[3U] 
                                          >> 0x00000013U));
                                __Vdly__tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_data_lane__DOT__u_3d_dram__DOT__u_3d_cache__DOT__state_q = 2U;
                            }
                        } else {
                            __Vdly__tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_data_lane__DOT__cache3d_fault_w = 1U;
                            __Vdly__tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_data_lane__DOT__cache3d_fault_code_w = 0x0c03U;
                        }
                    } else {
                        __Vdly__tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_data_lane__DOT__cache3d_fault_w = 1U;
                        __Vdly__tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_data_lane__DOT__cache3d_fault_code_w = 0x0c02U;
                    }
                } else {
                    __Vdly__tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_data_lane__DOT__cache3d_fault_w = 1U;
                    __Vdly__tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_data_lane__DOT__cache3d_fault_code_w = 0x0c01U;
                }
            }
        } else if ((1U == (IData)(vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_data_lane__DOT__u_3d_dram__DOT__u_3d_cache__DOT__state_q))) {
            if (vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_data_lane__DOT__u_3d_dram__DOT__dram_fault_w) {
                __Vdly__tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_data_lane__DOT__cache3d_fault_w = 1U;
                __Vdly__tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_data_lane__DOT__cache3d_fault_code_w 
                    = vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_data_lane__DOT__u_3d_dram__DOT__dram_fault_code_w;
                __Vdly__tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_data_lane__DOT__u_3d_dram__DOT__u_3d_cache__DOT__state_q = 0U;
            } else if (vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_data_lane__DOT__u_3d_dram__DOT__dram_resp_valid_w) {
                __VdlyDim0__tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_data_lane__DOT__u_3d_dram__DOT__u_3d_cache__DOT__valid_q__v17 
                    = vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_data_lane__DOT__u_3d_dram__DOT__u_3d_cache__DOT__pending_index_q;
                __VdlySet__tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_data_lane__DOT__u_3d_dram__DOT__u_3d_cache__DOT__valid_q__v17 = 1U;
                __Vdly__tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_data_lane__DOT__cache3d_resp_valid_w = 1U;
                __Vdly__tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_data_lane__DOT__cache3d_resp_rdata_w 
                    = vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_data_lane__DOT__u_3d_dram__DOT__dram_resp_rdata_w;
                __Vdly__tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_data_lane__DOT__u_3d_dram__DOT__u_3d_cache__DOT__state_q = 0U;
                __VdlyVal__tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_data_lane__DOT__u_3d_dram__DOT__u_3d_cache__DOT__tag_q__v1 
                    = vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_data_lane__DOT__u_3d_dram__DOT__u_3d_cache__DOT__pending_tag_q;
                __VdlyDim0__tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_data_lane__DOT__u_3d_dram__DOT__u_3d_cache__DOT__tag_q__v1 
                    = vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_data_lane__DOT__u_3d_dram__DOT__u_3d_cache__DOT__pending_index_q;
                __VdlySet__tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_data_lane__DOT__u_3d_dram__DOT__u_3d_cache__DOT__tag_q__v1 = 1U;
                __VdlyVal__tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_data_lane__DOT__u_3d_dram__DOT__u_3d_cache__DOT__data_q__v1 
                    = vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_data_lane__DOT__u_3d_dram__DOT__dram_resp_rdata_w;
                __VdlyDim0__tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_data_lane__DOT__u_3d_dram__DOT__u_3d_cache__DOT__data_q__v1 
                    = vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_data_lane__DOT__u_3d_dram__DOT__u_3d_cache__DOT__pending_index_q;
            }
        } else if ((2U == (IData)(vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_data_lane__DOT__u_3d_dram__DOT__u_3d_cache__DOT__state_q))) {
            if (vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_data_lane__DOT__u_3d_dram__DOT__dram_fault_w) {
                __Vdly__tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_data_lane__DOT__cache3d_fault_w = 1U;
                __Vdly__tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_data_lane__DOT__cache3d_fault_code_w 
                    = vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_data_lane__DOT__u_3d_dram__DOT__dram_fault_code_w;
                __Vdly__tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_data_lane__DOT__u_3d_dram__DOT__u_3d_cache__DOT__state_q = 0U;
            } else if (((IData)(vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_data_lane__DOT__u_3d_dram__DOT__dram_resp_valid_w) 
                        & (IData)(vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_data_lane__DOT__u_3d_dram__DOT__dram_resp_write_ack_w))) {
                __Vdly__tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_data_lane__DOT__cache3d_resp_valid_w = 1U;
                __Vdly__tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_data_lane__DOT__cache3d_resp_write_ack_w = 1U;
                __Vdly__tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_data_lane__DOT__u_3d_dram__DOT__u_3d_cache__DOT__state_q = 0U;
            }
        } else {
            __Vdly__tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_data_lane__DOT__u_3d_dram__DOT__u_3d_cache__DOT__state_q = 0U;
        }
        if ((1U & (~ VL_ONEHOT_I((((2U == (IData)(vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_data_lane__DOT__u_3d_dram__DOT__u_3d_cache__DOT__state_q)) 
                                   << 2U) | (((1U == (IData)(vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_data_lane__DOT__u_3d_dram__DOT__u_3d_cache__DOT__state_q)) 
                                              << 1U) 
                                             | (0U 
                                                == (IData)(vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_data_lane__DOT__u_3d_dram__DOT__u_3d_cache__DOT__state_q)))))))) {
            if ((0U != (((2U == (IData)(vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_data_lane__DOT__u_3d_dram__DOT__u_3d_cache__DOT__state_q)) 
                         << 2U) | (((1U == (IData)(vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_data_lane__DOT__u_3d_dram__DOT__u_3d_cache__DOT__state_q)) 
                                    << 1U) | (0U == (IData)(vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_data_lane__DOT__u_3d_dram__DOT__u_3d_cache__DOT__state_q)))))) {
                if (VL_UNLIKELY((vlSymsp->_vm_contextp__->assertOn()))) {
                    VL_WRITEF_NX("[%0t] %%Error: nvisc_3d_cache_stub.sv:161: Assertion failed in %m: unique case, but multiple matches found for '2'h%X'\n",4, 'M',vlSymsp->name(),"tb_nvisc_core_v02_with_mem_domains.u_memsys.u_data_lane.u_3d_dram.u_3d_cache", 'T',-9
                                 , '#',64,VL_TIME_UNITED_Q(1000)
                                 , '#',2,(IData)(vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_data_lane__DOT__u_3d_dram__DOT__u_3d_cache__DOT__state_q));
                    VL_STOP_MT("rtl/core_v02\\nvisc_3d_cache_stub.sv", 161, "");
                }
            }
        }
        vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__data_resp_valid_w = 0U;
        vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__data_resp_rdata_w = 0ULL;
        vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__data_resp_write_ack_w = 0U;
        vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__data_fault_w = 0U;
        vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__data_fault_code_w = 0U;
        vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_data_lane__DOT__l1d_mem_req_valid_w = 0U;
        vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_data_lane__DOT__l1d_mem_req_is_read_w = 0U;
        vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_data_lane__DOT__l1d_mem_req_is_write_w = 0U;
        vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_data_lane__DOT__l1d_mem_req_paddr_w = 0ULL;
        vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_data_lane__DOT__l1d_mem_req_wdata_w = 0ULL;
        vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_data_lane__DOT__l1d_mem_req_size_bytes_w = 0U;
        if (vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__effective_flush_data_l1d_w) {
            __Vdly__tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_data_lane__DOT__u_l1d__DOT__valid_q = 0U;
            __VdlySet__tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_data_lane__DOT__u_l1d__DOT__tag_q__v0 = 1U;
            __Vdly__tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_data_lane__DOT__u_l1d__DOT__state_q = 0U;
            __Vdly__tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_data_lane__DOT__u_l1d__DOT__miss_index_q = 0U;
            __Vdly__tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_data_lane__DOT__u_l1d__DOT__miss_tag_q = 0ULL;
            __VdlySet__tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_data_lane__DOT__u_l1d__DOT__tag_q__v1 = 1U;
        }
        if ((0U == (IData)(vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_data_lane__DOT__u_l1d__DOT__state_q))) {
            if ((((IData)(vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__data_req_valid_w) 
                  & (~ (IData)(vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__effective_flush_data_l1d_w))) 
                 & (~ (IData)(vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_data_lane__DOT__u_l1d__DOT__flush_q)))) {
                if ((8U != (IData)(vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__data_req_size_bytes_w))) {
                    vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__data_fault_w = 1U;
                    vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__data_fault_code_w = 0x0501U;
                } else if (((IData)(vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__data_req_is_read_w) 
                            & (IData)(vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__data_req_is_write_w))) {
                    vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__data_fault_w = 1U;
                    vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__data_fault_code_w = 0x0502U;
                } else if (vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__data_req_is_read_w) {
                    if (((IData)(vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__data_req_valid_w) 
                         & ((IData)(vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__data_req_is_read_w) 
                            & ((~ (IData)(vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__effective_flush_data_l1d_w)) 
                               & ((~ (IData)(vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_data_lane__DOT__u_l1d__DOT__flush_q)) 
                                  & (((IData)(vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_data_lane__DOT__u_l1d__DOT__valid_q) 
                                      >> (0x0000000fU 
                                          & (IData)(
                                                    (vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__data_req_paddr_w 
                                                     >> 3U)))) 
                                     & (VL_SHIFTR_QQI(64,64,32, vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__data_req_paddr_w, 7U) 
                                        == vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_data_lane__DOT__u_l1d__DOT__tag_q
                                        [(0x0000000fU 
                                          & (IData)(
                                                    (vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__data_req_paddr_w 
                                                     >> 3U)))]))))))) {
                        vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__data_resp_valid_w = 1U;
                        vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__data_resp_rdata_w 
                            = vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_data_lane__DOT__u_l1d__DOT__data_q
                            [(0x0000000fU & (IData)(
                                                    (vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__data_req_paddr_w 
                                                     >> 3U)))];
                    } else {
                        vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_data_lane__DOT__l1d_mem_req_valid_w = 1U;
                        vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_data_lane__DOT__l1d_mem_req_is_read_w = 1U;
                        vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_data_lane__DOT__l1d_mem_req_is_write_w = 0U;
                        vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_data_lane__DOT__l1d_mem_req_paddr_w 
                            = vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__data_req_paddr_w;
                        vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_data_lane__DOT__l1d_mem_req_wdata_w = 0ULL;
                        vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_data_lane__DOT__l1d_mem_req_size_bytes_w 
                            = vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__data_req_size_bytes_w;
                        __Vdly__tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_data_lane__DOT__u_l1d__DOT__miss_index_q 
                            = (0x0000000fU & (IData)(
                                                     (vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__data_req_paddr_w 
                                                      >> 3U)));
                        __Vdly__tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_data_lane__DOT__u_l1d__DOT__miss_tag_q 
                            = VL_SHIFTR_QQI(64,64,32, vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__data_req_paddr_w, 7U);
                        __Vdly__tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_data_lane__DOT__u_l1d__DOT__state_q = 1U;
                    }
                } else if (vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__data_req_is_write_w) {
                    if ((((IData)(vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_data_lane__DOT__u_l1d__DOT__valid_q) 
                          >> (0x0000000fU & (IData)(
                                                    (vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__data_req_paddr_w 
                                                     >> 3U)))) 
                         & (vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_data_lane__DOT__u_l1d__DOT__tag_q
                            [(0x0000000fU & (IData)(
                                                    (vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__data_req_paddr_w 
                                                     >> 3U)))] 
                            == VL_SHIFTR_QQI(64,64,32, vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__data_req_paddr_w, 7U)))) {
                        __VdlyVal__tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_data_lane__DOT__u_l1d__DOT__data_q__v16 
                            = vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__data_req_wdata_w;
                        __VdlyDim0__tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_data_lane__DOT__u_l1d__DOT__data_q__v16 
                            = (0x0000000fU & (IData)(
                                                     (vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__data_req_paddr_w 
                                                      >> 3U)));
                        __VdlySet__tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_data_lane__DOT__u_l1d__DOT__data_q__v16 = 1U;
                    }
                    vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_data_lane__DOT__l1d_mem_req_valid_w = 1U;
                    vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_data_lane__DOT__l1d_mem_req_is_read_w = 0U;
                    vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_data_lane__DOT__l1d_mem_req_is_write_w = 1U;
                    vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_data_lane__DOT__l1d_mem_req_paddr_w 
                        = vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__data_req_paddr_w;
                    vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_data_lane__DOT__l1d_mem_req_wdata_w 
                        = vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__data_req_wdata_w;
                    vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_data_lane__DOT__l1d_mem_req_size_bytes_w 
                        = vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__data_req_size_bytes_w;
                } else {
                    vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__data_fault_w = 1U;
                    vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__data_fault_code_w = 0x0503U;
                }
            }
        } else if ((1U == (IData)(vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_data_lane__DOT__u_l1d__DOT__state_q))) {
            if (vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_data_lane__DOT__cache3d_fault_w) {
                vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__data_fault_w = 1U;
                vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__data_fault_code_w 
                    = vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_data_lane__DOT__cache3d_fault_code_w;
                __Vdly__tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_data_lane__DOT__u_l1d__DOT__state_q = 0U;
            } else if (vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_data_lane__DOT__cache3d_resp_valid_w) {
                __Vdly__tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_data_lane__DOT__u_l1d__DOT__valid_q 
                    = ((IData)(__Vdly__tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_data_lane__DOT__u_l1d__DOT__valid_q) 
                       | (0x0000ffffU & ((IData)(1U) 
                                         << (IData)(vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_data_lane__DOT__u_l1d__DOT__miss_index_q))));
                vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__data_resp_valid_w = 1U;
                vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__data_resp_rdata_w 
                    = vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_data_lane__DOT__cache3d_resp_rdata_w;
                __Vdly__tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_data_lane__DOT__u_l1d__DOT__state_q = 0U;
                __VdlyVal__tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_data_lane__DOT__u_l1d__DOT__tag_q__v16 
                    = vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_data_lane__DOT__u_l1d__DOT__miss_tag_q;
                __VdlyDim0__tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_data_lane__DOT__u_l1d__DOT__tag_q__v16 
                    = vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_data_lane__DOT__u_l1d__DOT__miss_index_q;
                __VdlySet__tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_data_lane__DOT__u_l1d__DOT__tag_q__v16 = 1U;
                __VdlyVal__tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_data_lane__DOT__u_l1d__DOT__data_q__v17 
                    = vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_data_lane__DOT__cache3d_resp_rdata_w;
                __VdlyDim0__tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_data_lane__DOT__u_l1d__DOT__data_q__v17 
                    = vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_data_lane__DOT__u_l1d__DOT__miss_index_q;
            }
        } else {
            __Vdly__tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_data_lane__DOT__u_l1d__DOT__state_q = 0U;
        }
        if ((1U & (~ VL_ONEHOT_I((((1U == (IData)(vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_data_lane__DOT__u_l1d__DOT__state_q)) 
                                   << 1U) | (0U == (IData)(vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_data_lane__DOT__u_l1d__DOT__state_q))))))) {
            if ((0U != (((1U == (IData)(vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_data_lane__DOT__u_l1d__DOT__state_q)) 
                         << 1U) | (0U == (IData)(vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_data_lane__DOT__u_l1d__DOT__state_q))))) {
                if (VL_UNLIKELY((vlSymsp->_vm_contextp__->assertOn()))) {
                    VL_WRITEF_NX("[%0t] %%Error: nvisc_l1d_cache_stub.sv:164: Assertion failed in %m: unique case, but multiple matches found for '2'h%X'\n",4, 'M',vlSymsp->name(),"tb_nvisc_core_v02_with_mem_domains.u_memsys.u_data_lane.u_l1d", 'T',-9
                                 , '#',64,VL_TIME_UNITED_Q(1000)
                                 , '#',2,(IData)(vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_data_lane__DOT__u_l1d__DOT__state_q));
                    VL_STOP_MT("rtl/core_v02\\nvisc_l1d_cache_stub.sv", 164, "");
                }
            }
        }
        if (((IData)(vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_data_lane__DOT__cache3d_fault_w) 
             & (0U == (IData)(vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_data_lane__DOT__u_l1d__DOT__state_q)))) {
            vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__data_fault_w = 1U;
            vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__data_fault_code_w 
                = vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_data_lane__DOT__cache3d_fault_code_w;
        }
        vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_data_lane__DOT__u_l1d__DOT__flush_q 
            = vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__effective_flush_data_l1d_w;
        if (vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_data_lane__DOT__cache3d_resp_write_ack_w) {
            vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__data_resp_valid_w = 1U;
            vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__data_resp_write_ack_w = 1U;
        }
        vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__data_req_valid_w = 0U;
        vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__data_req_is_read_w = 0U;
        vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__data_req_is_write_w = 0U;
        vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__data_req_paddr_w = 0ULL;
        vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__data_req_wdata_w = 0ULL;
        vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__data_req_size_bytes_w = 0U;
        vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__data_req_id_w[0U] = 0U;
        vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__data_req_id_w[1U] = 0U;
        vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__data_req_id_w[2U] = 0U;
        vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__data_req_id_w[3U] = 0U;
        vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__data_req_id_w[4U] = 0U;
        vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__exec_req_valid_w = 0U;
        vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__exec_req_is_read_w = 0U;
        vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__exec_req_is_write_w = 0U;
        vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__exec_req_paddr_w = 0ULL;
        vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__exec_req_wdata_w = 0ULL;
        vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__exec_req_size_bytes_w = 0U;
        vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__livehot_req_valid_w = 0U;
        vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__livehot_req_is_read_w = 0U;
        vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__livehot_req_is_write_w = 0U;
        vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__livehot_req_paddr_w = 0ULL;
        vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__livehot_req_wdata_w = 0ULL;
        vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__livehot_req_size_bytes_w = 0U;
        vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__router_fault_w = 0U;
        vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__router_fault_code_w = 0U;
        if (vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_core__DOT__mmu_resp_valid_w) {
            if ((1U & (~ VL_ONEHOT_I((((3U == (IData)(vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_memdom_csr__DOT__effective_domain_c)) 
                                       << 2U) | (((2U 
                                                   == (IData)(vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_memdom_csr__DOT__effective_domain_c)) 
                                                  << 1U) 
                                                 | (1U 
                                                    == (IData)(vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_memdom_csr__DOT__effective_domain_c)))))))) {
                if ((0U != (((3U == (IData)(vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_memdom_csr__DOT__effective_domain_c)) 
                             << 2U) | (((2U == (IData)(vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_memdom_csr__DOT__effective_domain_c)) 
                                        << 1U) | (1U 
                                                  == (IData)(vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_memdom_csr__DOT__effective_domain_c)))))) {
                    if (VL_UNLIKELY((vlSymsp->_vm_contextp__->assertOn()))) {
                        VL_WRITEF_NX("[%0t] %%Error: nvisc_memory_domain_router.sv:118: Assertion failed in %m: unique case, but multiple matches found for '3'h%X'\n",4, 'M',vlSymsp->name(),"tb_nvisc_core_v02_with_mem_domains.u_memsys.u_router", 'T',-9
                                     , '#',64,VL_TIME_UNITED_Q(1000)
                                     , '#',3,(IData)(vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_memdom_csr__DOT__effective_domain_c));
                        VL_STOP_MT("rtl/core_v02\\nvisc_memory_domain_router.sv", 118, "");
                    }
                }
            }
            if ((1U == (IData)(vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_memdom_csr__DOT__effective_domain_c))) {
                vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__data_req_valid_w = 1U;
                vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__data_req_is_read_w 
                    = vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_core__DOT__mmu_resp_is_read_w;
                vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__data_req_is_write_w 
                    = vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_core__DOT__mmu_resp_is_write_w;
                vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__data_req_paddr_w 
                    = vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_core__DOT__mmu_resp_paddr_w;
                vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__data_req_wdata_w 
                    = vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_core__DOT__mmu_resp_wdata_w;
                vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__data_req_size_bytes_w 
                    = vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_core__DOT__mmu_resp_size_bytes_w;
                vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__data_req_id_w[0U] = 0U;
                vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__data_req_id_w[1U] = 0U;
                vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__data_req_id_w[2U] = 0U;
                vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__data_req_id_w[3U] = 0U;
                vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__data_req_id_w[4U] = 0U;
            } else if ((2U == (IData)(vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_memdom_csr__DOT__effective_domain_c))) {
                vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__exec_req_valid_w = 1U;
                vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__exec_req_is_read_w 
                    = vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_core__DOT__mmu_resp_is_read_w;
                vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__exec_req_is_write_w 
                    = vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_core__DOT__mmu_resp_is_write_w;
                vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__exec_req_paddr_w 
                    = vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_core__DOT__mmu_resp_paddr_w;
                vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__exec_req_wdata_w 
                    = vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_core__DOT__mmu_resp_wdata_w;
                vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__exec_req_size_bytes_w 
                    = vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_core__DOT__mmu_resp_size_bytes_w;
            } else if ((3U == (IData)(vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_memdom_csr__DOT__effective_domain_c))) {
                vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__livehot_req_valid_w = 1U;
                vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__livehot_req_is_read_w 
                    = vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_core__DOT__mmu_resp_is_read_w;
                vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__livehot_req_is_write_w 
                    = vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_core__DOT__mmu_resp_is_write_w;
                vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__livehot_req_paddr_w 
                    = vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_core__DOT__mmu_resp_paddr_w;
                vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__livehot_req_wdata_w 
                    = vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_core__DOT__mmu_resp_wdata_w;
                vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__livehot_req_size_bytes_w 
                    = vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_core__DOT__mmu_resp_size_bytes_w;
            } else {
                vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__router_fault_w = 1U;
                vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__router_fault_code_w = 0x0801U;
            }
        }
        vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_core__DOT__mmu_resp_is_read_w = 0U;
        vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_core__DOT__mmu_resp_is_write_w = 0U;
        vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_core__DOT__mmu_resp_paddr_w = 0ULL;
        vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_core__DOT__mmu_resp_wdata_w = 0ULL;
        vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_core__DOT__mmu_resp_size_bytes_w = 0U;
        vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_core__DOT__mmu_resp_valid_w = 0U;
        if ((0x02000000U & vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_core__DOT__u_lsu__DOT__req_q[11U])) {
            if ((1U & (~ (IData)(vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_core__DOT__u_mmu__DOT__page_fault_c)))) {
                if ((1U & (~ (IData)(vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_core__DOT__u_mmu__DOT__align_fault_c)))) {
                    vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_core__DOT__mmu_resp_is_read_w 
                        = (1U & (vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_core__DOT__u_lsu__DOT__req_q[10U] 
                                 >> 0x00000018U));
                    vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_core__DOT__mmu_resp_is_write_w 
                        = (1U & (vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_core__DOT__u_lsu__DOT__req_q[10U] 
                                 >> 0x00000017U));
                    vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_core__DOT__mmu_resp_paddr_w 
                        = (((QData)((IData)(vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_core__DOT__u_lsu__DOT__req_q[10U])) 
                            << 0x0000002aU) | (((QData)((IData)(vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_core__DOT__u_lsu__DOT__req_q[9U])) 
                                                << 0x0000000aU) 
                                               | ((QData)((IData)(vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_core__DOT__u_lsu__DOT__req_q[8U])) 
                                                  >> 0x00000016U)));
                    vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_core__DOT__mmu_resp_wdata_w 
                        = (((QData)((IData)(vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_core__DOT__u_lsu__DOT__req_q[6U])) 
                            << 0x0000002aU) | (((QData)((IData)(vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_core__DOT__u_lsu__DOT__req_q[5U])) 
                                                << 0x0000000aU) 
                                               | ((QData)((IData)(vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_core__DOT__u_lsu__DOT__req_q[4U])) 
                                                  >> 0x00000016U)));
                    vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_core__DOT__mmu_resp_size_bytes_w 
                        = (0x000000ffU & (vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_core__DOT__u_lsu__DOT__req_q[4U] 
                                          >> 0x0000000eU));
                    vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_core__DOT__mmu_resp_valid_w = 1U;
                }
            }
        }
        VL_ASSIGN_W(378, vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_core__DOT__u_lsu__DOT__req_q, Vtb_nvisc_core_v02_with_mem_domains__ConstPool__CONST_h3a0f6b6a_0);
        if (vlSelfRef.lsu_valid_o) {
            if ((1U & (~ (IData)(vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_core__DOT__u_lsu__DOT__bad_size_c)))) {
                if ((1U & (~ (IData)(vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_core__DOT__u_lsu__DOT__both_read_write_c)))) {
                    if ((1U & (~ (IData)(vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_core__DOT__u_lsu__DOT__no_op_c)))) {
                        vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_core__DOT__u_lsu__DOT__req_q[10U] 
                            = ((0x003fffffU & vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_core__DOT__u_lsu__DOT__req_q[10U]) 
                               | ((IData)((0x0000000800000008ULL 
                                           | (QData)((IData)(
                                                             (((IData)(vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_core__DOT__ctrl_mem_read_w) 
                                                               << 2U) 
                                                              | ((IData)(vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_core__DOT__ctrl_mem_write_w) 
                                                                 << 1U)))))) 
                                  << 0x00000016U));
                        vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_core__DOT__u_lsu__DOT__req_q[11U] 
                            = (0x03ffffffU & (((IData)(
                                                       (0x0000000800000008ULL 
                                                        | (QData)((IData)(
                                                                          (((IData)(vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_core__DOT__ctrl_mem_read_w) 
                                                                            << 2U) 
                                                                           | ((IData)(vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_core__DOT__ctrl_mem_write_w) 
                                                                              << 1U)))))) 
                                               >> 0x0000000aU) 
                                              | ((IData)(
                                                         ((0x0000000800000008ULL 
                                                           | (QData)((IData)(
                                                                             (((IData)(vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_core__DOT__ctrl_mem_read_w) 
                                                                               << 2U) 
                                                                              | ((IData)(vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_core__DOT__ctrl_mem_write_w) 
                                                                                << 1U))))) 
                                                          >> 0x00000020U)) 
                                                 << 0x00000016U)));
                        vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_core__DOT__u_lsu__DOT__req_q[4U] 
                            = ((0x00003fffU & vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_core__DOT__u_lsu__DOT__req_q[4U]) 
                               | (((IData)(vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_core__DOT__rs2_data_w) 
                                   << 0x00000016U) 
                                  | ((IData)(vlSelfRef.lsu_size_bytes_i) 
                                     << 0x0000000eU)));
                        vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_core__DOT__u_lsu__DOT__req_q[5U] 
                            = (((0x00003fffU & ((IData)(vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_core__DOT__rs2_data_w) 
                                                >> 0x0000000aU)) 
                                | ((IData)(vlSelfRef.lsu_size_bytes_i) 
                                   >> 0x00000012U)) 
                               | ((0x003fc000U & ((IData)(vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_core__DOT__rs2_data_w) 
                                                  >> 0x0000000aU)) 
                                  | ((IData)((vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_core__DOT__rs2_data_w 
                                              >> 0x00000020U)) 
                                     << 0x00000016U)));
                        vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_core__DOT__u_lsu__DOT__req_q[6U] 
                            = ((0xffc00000U & vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_core__DOT__u_lsu__DOT__req_q[6U]) 
                               | ((0x00003fffU & ((IData)(
                                                          (vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_core__DOT__rs2_data_w 
                                                           >> 0x00000020U)) 
                                                  >> 0x0000000aU)) 
                                  | (0x003fc000U & 
                                     ((IData)((vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_core__DOT__rs2_data_w 
                                               >> 0x00000020U)) 
                                      >> 0x0000000aU))));
                        vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_core__DOT__u_lsu__DOT__req_q[6U] 
                            = ((0x003fffffU & vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_core__DOT__u_lsu__DOT__req_q[6U]) 
                               | ((IData)((vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_core__DOT__rs1_data_w 
                                           + (((QData)((IData)(vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_core__DOT__u_dec__DOT__dec[6U])) 
                                               << 0x00000033U) 
                                              | (((QData)((IData)(vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_core__DOT__u_dec__DOT__dec[5U])) 
                                                  << 0x00000013U) 
                                                 | ((QData)((IData)(vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_core__DOT__u_dec__DOT__dec[4U])) 
                                                    >> 0x0000000dU))))) 
                                  << 0x00000016U));
                        vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_core__DOT__u_lsu__DOT__req_q[7U] 
                            = (((IData)((vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_core__DOT__rs1_data_w 
                                         + (((QData)((IData)(vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_core__DOT__u_dec__DOT__dec[6U])) 
                                             << 0x00000033U) 
                                            | (((QData)((IData)(vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_core__DOT__u_dec__DOT__dec[5U])) 
                                                << 0x00000013U) 
                                               | ((QData)((IData)(vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_core__DOT__u_dec__DOT__dec[4U])) 
                                                  >> 0x0000000dU))))) 
                                >> 0x0000000aU) | ((IData)(
                                                           ((vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_core__DOT__rs1_data_w 
                                                             + 
                                                             (((QData)((IData)(vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_core__DOT__u_dec__DOT__dec[6U])) 
                                                               << 0x00000033U) 
                                                              | (((QData)((IData)(vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_core__DOT__u_dec__DOT__dec[5U])) 
                                                                  << 0x00000013U) 
                                                                 | ((QData)((IData)(vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_core__DOT__u_dec__DOT__dec[4U])) 
                                                                    >> 0x0000000dU)))) 
                                                            >> 0x00000020U)) 
                                                   << 0x00000016U));
                        vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_core__DOT__u_lsu__DOT__req_q[8U] 
                            = (((IData)(((vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_core__DOT__rs1_data_w 
                                          + (((QData)((IData)(vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_core__DOT__u_dec__DOT__dec[6U])) 
                                              << 0x00000033U) 
                                             | (((QData)((IData)(vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_core__DOT__u_dec__DOT__dec[5U])) 
                                                 << 0x00000013U) 
                                                | ((QData)((IData)(vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_core__DOT__u_dec__DOT__dec[4U])) 
                                                   >> 0x0000000dU)))) 
                                         >> 0x00000020U)) 
                                >> 0x0000000aU) | ((IData)(
                                                           (vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_core__DOT__rs1_data_w 
                                                            + 
                                                            (((QData)((IData)(vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_core__DOT__u_dec__DOT__dec[6U])) 
                                                              << 0x00000033U) 
                                                             | (((QData)((IData)(vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_core__DOT__u_dec__DOT__dec[5U])) 
                                                                 << 0x00000013U) 
                                                                | ((QData)((IData)(vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_core__DOT__u_dec__DOT__dec[4U])) 
                                                                   >> 0x0000000dU))))) 
                                                   << 0x00000016U));
                        vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_core__DOT__u_lsu__DOT__req_q[9U] 
                            = (((IData)((vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_core__DOT__rs1_data_w 
                                         + (((QData)((IData)(vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_core__DOT__u_dec__DOT__dec[6U])) 
                                             << 0x00000033U) 
                                            | (((QData)((IData)(vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_core__DOT__u_dec__DOT__dec[5U])) 
                                                << 0x00000013U) 
                                               | ((QData)((IData)(vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_core__DOT__u_dec__DOT__dec[4U])) 
                                                  >> 0x0000000dU))))) 
                                >> 0x0000000aU) | ((IData)(
                                                           ((vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_core__DOT__rs1_data_w 
                                                             + 
                                                             (((QData)((IData)(vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_core__DOT__u_dec__DOT__dec[6U])) 
                                                               << 0x00000033U) 
                                                              | (((QData)((IData)(vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_core__DOT__u_dec__DOT__dec[5U])) 
                                                                  << 0x00000013U) 
                                                                 | ((QData)((IData)(vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_core__DOT__u_dec__DOT__dec[4U])) 
                                                                    >> 0x0000000dU)))) 
                                                            >> 0x00000020U)) 
                                                   << 0x00000016U));
                        vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_core__DOT__u_lsu__DOT__req_q[10U] 
                            = ((0xffc00000U & vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_core__DOT__u_lsu__DOT__req_q[10U]) 
                               | ((IData)(((vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_core__DOT__rs1_data_w 
                                            + (((QData)((IData)(vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_core__DOT__u_dec__DOT__dec[6U])) 
                                                << 0x00000033U) 
                                               | (((QData)((IData)(vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_core__DOT__u_dec__DOT__dec[5U])) 
                                                   << 0x00000013U) 
                                                  | ((QData)((IData)(vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_core__DOT__u_dec__DOT__dec[4U])) 
                                                     >> 0x0000000dU)))) 
                                           >> 0x00000020U)) 
                                  >> 0x0000000aU));
                        vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_core__DOT__u_lsu__DOT__req_q[0U] 
                            = vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_core__DOT__u_dec__DOT__dec[0U];
                        vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_core__DOT__u_lsu__DOT__req_q[1U] 
                            = vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_core__DOT__u_dec__DOT__dec[1U];
                        vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_core__DOT__u_lsu__DOT__req_q[2U] 
                            = vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_core__DOT__u_dec__DOT__dec[2U];
                        vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_core__DOT__u_lsu__DOT__req_q[3U] 
                            = vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_core__DOT__u_dec__DOT__dec[3U];
                        vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_core__DOT__u_lsu__DOT__req_q[4U] 
                            = (0x00000040U | ((0xffffc000U 
                                               & vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_core__DOT__u_lsu__DOT__req_q[4U]) 
                                              | (0x0000003fU 
                                                 & vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_core__DOT__u_dec__DOT__dec[4U])));
                    }
                }
            }
        }
    } else {
        vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_core__DOT__u_csr__DOT__thread_id_q = 0U;
        vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_core__DOT__u_csr__DOT__branch_id_q = 1U;
        vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_core__DOT__u_csr__DOT__state_id_q = 1U;
        vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_core__DOT__u_csr__DOT__commit_id_q = 0U;
        vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_core__DOT__u_csr__DOT__privilege_q = 2U;
        vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_core__DOT__u_csr__DOT__aegis_policy_id_q = 0U;
        __VdlySet__tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_data_lane__DOT__u_3d_dram__DOT__u_3d_cache__DOT__valid_q__v18 = 1U;
        __Vdly__tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_data_lane__DOT__u_3d_dram__DOT__u_3d_cache__DOT__state_q = 0U;
        __Vdly__tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_data_lane__DOT__cache3d_resp_valid_w = 0U;
        __Vdly__tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_data_lane__DOT__cache3d_resp_rdata_w = 0ULL;
        __Vdly__tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_data_lane__DOT__cache3d_resp_write_ack_w = 0U;
        __Vdly__tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_data_lane__DOT__cache3d_fault_w = 0U;
        __Vdly__tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_data_lane__DOT__cache3d_fault_code_w = 0U;
        vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_data_lane__DOT__u_3d_dram__DOT__cache_mem_req_valid_w = 0U;
        vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_data_lane__DOT__u_3d_dram__DOT__cache_mem_req_is_read_w = 0U;
        vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_data_lane__DOT__u_3d_dram__DOT__cache_mem_req_is_write_w = 0U;
        vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_data_lane__DOT__u_3d_dram__DOT__cache_mem_req_paddr_w = 0ULL;
        vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_data_lane__DOT__u_3d_dram__DOT__cache_mem_req_wdata_w = 0ULL;
        vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_data_lane__DOT__u_3d_dram__DOT__cache_mem_req_size_bytes_w = 0U;
        vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_data_lane__DOT__u_3d_dram__DOT__cache_mem_req_id_w = 0U;
        __Vdly__tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_data_lane__DOT__u_3d_dram__DOT__u_3d_cache__DOT__pending_index_q = 0U;
        __Vdly__tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_data_lane__DOT__u_3d_dram__DOT__u_3d_cache__DOT__pending_tag_q = 0ULL;
        __VdlySet__tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_data_lane__DOT__u_3d_dram__DOT__u_3d_cache__DOT__tag_q__v3 = 1U;
        __Vdly__tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_data_lane__DOT__u_l1d__DOT__state_q = 0U;
        __Vdly__tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_data_lane__DOT__u_l1d__DOT__valid_q = 0U;
        __VdlySet__tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_data_lane__DOT__u_l1d__DOT__tag_q__v17 = 1U;
        __Vdly__tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_data_lane__DOT__u_l1d__DOT__miss_index_q = 0U;
        __Vdly__tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_data_lane__DOT__u_l1d__DOT__miss_tag_q = 0ULL;
        vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_data_lane__DOT__u_l1d__DOT__flush_q = 0U;
        __VdlySet__tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_data_lane__DOT__u_l1d__DOT__tag_q__v18 = 1U;
        vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__data_resp_valid_w = 0U;
        vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__data_resp_rdata_w = 0ULL;
        vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__data_resp_write_ack_w = 0U;
        vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__data_fault_w = 0U;
        vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__data_fault_code_w = 0U;
        vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_data_lane__DOT__l1d_mem_req_valid_w = 0U;
        vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_data_lane__DOT__l1d_mem_req_is_read_w = 0U;
        vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_data_lane__DOT__l1d_mem_req_is_write_w = 0U;
        vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_data_lane__DOT__l1d_mem_req_paddr_w = 0ULL;
        vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_data_lane__DOT__l1d_mem_req_wdata_w = 0ULL;
        vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_data_lane__DOT__l1d_mem_req_size_bytes_w = 0U;
        __VdlySet__tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_data_lane__DOT__u_l1d__DOT__tag_q__v19 = 1U;
        vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__data_req_valid_w = 0U;
        vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__data_req_is_read_w = 0U;
        vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__data_req_is_write_w = 0U;
        vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__data_req_paddr_w = 0ULL;
        vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__data_req_wdata_w = 0ULL;
        vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__data_req_size_bytes_w = 0U;
        vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__data_req_id_w[0U] = 0U;
        vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__data_req_id_w[1U] = 0U;
        vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__data_req_id_w[2U] = 0U;
        vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__data_req_id_w[3U] = 0U;
        vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__data_req_id_w[4U] = 0U;
        vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__exec_req_valid_w = 0U;
        vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__exec_req_is_read_w = 0U;
        vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__exec_req_is_write_w = 0U;
        vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__exec_req_paddr_w = 0ULL;
        vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__exec_req_wdata_w = 0ULL;
        vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__exec_req_size_bytes_w = 0U;
        vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__livehot_req_valid_w = 0U;
        vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__livehot_req_is_read_w = 0U;
        vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__livehot_req_is_write_w = 0U;
        vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__livehot_req_paddr_w = 0ULL;
        vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__livehot_req_wdata_w = 0ULL;
        vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__livehot_req_size_bytes_w = 0U;
        vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__router_fault_w = 0U;
        vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__router_fault_code_w = 0U;
        vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_core__DOT__mmu_resp_is_read_w = 0U;
        vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_core__DOT__mmu_resp_is_write_w = 0U;
        vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_core__DOT__mmu_resp_paddr_w = 0ULL;
        vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_core__DOT__mmu_resp_wdata_w = 0ULL;
        vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_core__DOT__mmu_resp_size_bytes_w = 0U;
        vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_core__DOT__mmu_resp_valid_w = 0U;
        VL_ASSIGN_W(378, vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_core__DOT__u_lsu__DOT__req_q, Vtb_nvisc_core_v02_with_mem_domains__ConstPool__CONST_h3a0f6b6a_0);
    }
    vlSelfRef.dbg_rf_r1_o = vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_core__DOT__u_rf__DOT__regs_q[1U];
    vlSelfRef.dbg_rf_r2_o = vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_core__DOT__u_rf__DOT__regs_q[2U];
    vlSelfRef.dbg_rf_r3_o = vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_core__DOT__u_rf__DOT__regs_q[3U];
    vlSelfRef.pc_valid_o = vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_core__DOT__u_pc__DOT__valid_q;
    vlSelfRef.imem_req_valid_o = ((~ ((IData)(vlSelfRef.stall_i) 
                                      | (IData)(vlSelfRef.flush_i))) 
                                  & (IData)(vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_core__DOT__u_pc__DOT__valid_q));
    vlSelfRef.mem_req_vaddr_o = vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_core__DOT__mmu_resp_vaddr_w;
    vlSelfRef.mem_req_domain_o = vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_core__DOT__mmu_resp_mem_domain_w;
    vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__wrapper_override_domain_w 
        = ((IData)(vlSelfRef.mem_domain_override_valid_i)
            ? (IData)(vlSelfRef.mem_domain_override_i)
            : (IData)(vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_core__DOT__mmu_resp_mem_domain_w));
    vlSelfRef.imem_req_addr_o = vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_core__DOT__u_pc__DOT__pc_q;
    vlSelfRef.pc_o = vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_core__DOT__u_pc__DOT__pc_q;
    if ((1U & (~ (IData)(vlSelfRef.rst_n)))) {
        vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_core__DOT__u_csr__DOT__core_id_q = 0U;
    }
    vlSelfRef.fetch_valid_o = (1U & (vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_core__DOT__u_if__DOT__fetch_q[7U] 
                                     >> 3U));
    vlSelfRef.fetch_instr_o = ((vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_core__DOT__u_if__DOT__fetch_q[5U] 
                                << 0x0000001dU) | (vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_core__DOT__u_if__DOT__fetch_q[4U] 
                                                   >> 3U));
    vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_data_lane__DOT__u_3d_dram__DOT__dram_fault_w 
        = __Vdly__tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_data_lane__DOT__u_3d_dram__DOT__dram_fault_w;
    vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_data_lane__DOT__u_3d_dram__DOT__dram_fault_code_w 
        = __Vdly__tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_data_lane__DOT__u_3d_dram__DOT__dram_fault_code_w;
    vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_data_lane__DOT__u_3d_dram__DOT__dram_resp_valid_w 
        = __Vdly__tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_data_lane__DOT__u_3d_dram__DOT__dram_resp_valid_w;
    vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_data_lane__DOT__u_3d_dram__DOT__dram_resp_rdata_w 
        = __Vdly__tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_data_lane__DOT__u_3d_dram__DOT__dram_resp_rdata_w;
    vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_data_lane__DOT__u_3d_dram__DOT__dram_resp_write_ack_w 
        = __Vdly__tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_data_lane__DOT__u_3d_dram__DOT__dram_resp_write_ack_w;
    vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_data_lane__DOT__u_3d_dram__DOT__u_3d_cache__DOT__pending_index_q 
        = __Vdly__tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_data_lane__DOT__u_3d_dram__DOT__u_3d_cache__DOT__pending_index_q;
    vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_data_lane__DOT__u_3d_dram__DOT__u_3d_cache__DOT__pending_tag_q 
        = __Vdly__tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_data_lane__DOT__u_3d_dram__DOT__u_3d_cache__DOT__pending_tag_q;
    vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_data_lane__DOT__u_3d_dram__DOT__u_3d_cache__DOT__state_q 
        = __Vdly__tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_data_lane__DOT__u_3d_dram__DOT__u_3d_cache__DOT__state_q;
    if (__VdlySet__tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_data_lane__DOT__u_3d_dram__DOT__u_3d_cache__DOT__valid_q__v0) {
        vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_data_lane__DOT__u_3d_dram__DOT__u_3d_cache__DOT__valid_q[0U] = 0U;
        vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_data_lane__DOT__u_3d_dram__DOT__u_3d_cache__DOT__valid_q[1U] = 0U;
        vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_data_lane__DOT__u_3d_dram__DOT__u_3d_cache__DOT__valid_q[2U] = 0U;
        vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_data_lane__DOT__u_3d_dram__DOT__u_3d_cache__DOT__valid_q[3U] = 0U;
        vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_data_lane__DOT__u_3d_dram__DOT__u_3d_cache__DOT__valid_q[4U] = 0U;
        vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_data_lane__DOT__u_3d_dram__DOT__u_3d_cache__DOT__valid_q[5U] = 0U;
        vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_data_lane__DOT__u_3d_dram__DOT__u_3d_cache__DOT__valid_q[6U] = 0U;
        vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_data_lane__DOT__u_3d_dram__DOT__u_3d_cache__DOT__valid_q[7U] = 0U;
        vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_data_lane__DOT__u_3d_dram__DOT__u_3d_cache__DOT__valid_q[8U] = 0U;
        vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_data_lane__DOT__u_3d_dram__DOT__u_3d_cache__DOT__valid_q[9U] = 0U;
        vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_data_lane__DOT__u_3d_dram__DOT__u_3d_cache__DOT__valid_q[10U] = 0U;
        vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_data_lane__DOT__u_3d_dram__DOT__u_3d_cache__DOT__valid_q[11U] = 0U;
        vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_data_lane__DOT__u_3d_dram__DOT__u_3d_cache__DOT__valid_q[12U] = 0U;
        vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_data_lane__DOT__u_3d_dram__DOT__u_3d_cache__DOT__valid_q[13U] = 0U;
        vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_data_lane__DOT__u_3d_dram__DOT__u_3d_cache__DOT__valid_q[14U] = 0U;
        vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_data_lane__DOT__u_3d_dram__DOT__u_3d_cache__DOT__valid_q[15U] = 0U;
    }
    if (__VdlySet__tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_data_lane__DOT__u_3d_dram__DOT__u_3d_cache__DOT__valid_q__v16) {
        vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_data_lane__DOT__u_3d_dram__DOT__u_3d_cache__DOT__valid_q[__VdlyDim0__tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_data_lane__DOT__u_3d_dram__DOT__u_3d_cache__DOT__valid_q__v16] = 1U;
        vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_data_lane__DOT__u_3d_dram__DOT__u_3d_cache__DOT__tag_q[__VdlyDim0__tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_data_lane__DOT__u_3d_dram__DOT__u_3d_cache__DOT__tag_q__v0] 
            = __VdlyVal__tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_data_lane__DOT__u_3d_dram__DOT__u_3d_cache__DOT__tag_q__v0;
        vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_data_lane__DOT__u_3d_dram__DOT__u_3d_cache__DOT__data_q[__VdlyDim0__tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_data_lane__DOT__u_3d_dram__DOT__u_3d_cache__DOT__data_q__v0] 
            = __VdlyVal__tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_data_lane__DOT__u_3d_dram__DOT__u_3d_cache__DOT__data_q__v0;
    }
    if (__VdlySet__tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_data_lane__DOT__u_3d_dram__DOT__u_3d_cache__DOT__valid_q__v17) {
        vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_data_lane__DOT__u_3d_dram__DOT__u_3d_cache__DOT__valid_q[__VdlyDim0__tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_data_lane__DOT__u_3d_dram__DOT__u_3d_cache__DOT__valid_q__v17] = 1U;
    }
    if (__VdlySet__tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_data_lane__DOT__u_3d_dram__DOT__u_3d_cache__DOT__valid_q__v18) {
        vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_data_lane__DOT__u_3d_dram__DOT__u_3d_cache__DOT__valid_q[0U] = 0U;
        vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_data_lane__DOT__u_3d_dram__DOT__u_3d_cache__DOT__valid_q[1U] = 0U;
    }
    if (__VdlySet__tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_data_lane__DOT__u_3d_dram__DOT__u_3d_cache__DOT__tag_q__v1) {
        vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_data_lane__DOT__u_3d_dram__DOT__u_3d_cache__DOT__tag_q[__VdlyDim0__tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_data_lane__DOT__u_3d_dram__DOT__u_3d_cache__DOT__tag_q__v1] 
            = __VdlyVal__tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_data_lane__DOT__u_3d_dram__DOT__u_3d_cache__DOT__tag_q__v1;
        vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_data_lane__DOT__u_3d_dram__DOT__u_3d_cache__DOT__data_q[__VdlyDim0__tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_data_lane__DOT__u_3d_dram__DOT__u_3d_cache__DOT__data_q__v1] 
            = __VdlyVal__tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_data_lane__DOT__u_3d_dram__DOT__u_3d_cache__DOT__data_q__v1;
    }
    if (__VdlySet__tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_data_lane__DOT__u_3d_dram__DOT__u_3d_cache__DOT__valid_q__v18) {
        vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_data_lane__DOT__u_3d_dram__DOT__u_3d_cache__DOT__tag_q[0U] = 0ULL;
        vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_data_lane__DOT__u_3d_dram__DOT__u_3d_cache__DOT__data_q[0U] = 0ULL;
    }
    if (__VdlySet__tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_data_lane__DOT__u_3d_dram__DOT__u_3d_cache__DOT__tag_q__v3) {
        vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_data_lane__DOT__u_3d_dram__DOT__u_3d_cache__DOT__valid_q[2U] = 0U;
        vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_data_lane__DOT__u_3d_dram__DOT__u_3d_cache__DOT__valid_q[3U] = 0U;
        vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_data_lane__DOT__u_3d_dram__DOT__u_3d_cache__DOT__valid_q[4U] = 0U;
        vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_data_lane__DOT__u_3d_dram__DOT__u_3d_cache__DOT__valid_q[5U] = 0U;
        vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_data_lane__DOT__u_3d_dram__DOT__u_3d_cache__DOT__valid_q[6U] = 0U;
        vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_data_lane__DOT__u_3d_dram__DOT__u_3d_cache__DOT__valid_q[7U] = 0U;
        vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_data_lane__DOT__u_3d_dram__DOT__u_3d_cache__DOT__valid_q[8U] = 0U;
        vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_data_lane__DOT__u_3d_dram__DOT__u_3d_cache__DOT__valid_q[9U] = 0U;
        vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_data_lane__DOT__u_3d_dram__DOT__u_3d_cache__DOT__valid_q[10U] = 0U;
        vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_data_lane__DOT__u_3d_dram__DOT__u_3d_cache__DOT__valid_q[11U] = 0U;
        vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_data_lane__DOT__u_3d_dram__DOT__u_3d_cache__DOT__valid_q[12U] = 0U;
        vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_data_lane__DOT__u_3d_dram__DOT__u_3d_cache__DOT__valid_q[13U] = 0U;
        vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_data_lane__DOT__u_3d_dram__DOT__u_3d_cache__DOT__valid_q[14U] = 0U;
        vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_data_lane__DOT__u_3d_dram__DOT__u_3d_cache__DOT__valid_q[15U] = 0U;
        vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_data_lane__DOT__u_3d_dram__DOT__u_3d_cache__DOT__tag_q[1U] = 0ULL;
        vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_data_lane__DOT__u_3d_dram__DOT__u_3d_cache__DOT__tag_q[2U] = 0ULL;
        vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_data_lane__DOT__u_3d_dram__DOT__u_3d_cache__DOT__tag_q[3U] = 0ULL;
        vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_data_lane__DOT__u_3d_dram__DOT__u_3d_cache__DOT__tag_q[4U] = 0ULL;
        vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_data_lane__DOT__u_3d_dram__DOT__u_3d_cache__DOT__tag_q[5U] = 0ULL;
        vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_data_lane__DOT__u_3d_dram__DOT__u_3d_cache__DOT__tag_q[6U] = 0ULL;
        vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_data_lane__DOT__u_3d_dram__DOT__u_3d_cache__DOT__tag_q[7U] = 0ULL;
        vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_data_lane__DOT__u_3d_dram__DOT__u_3d_cache__DOT__tag_q[8U] = 0ULL;
        vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_data_lane__DOT__u_3d_dram__DOT__u_3d_cache__DOT__tag_q[9U] = 0ULL;
        vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_data_lane__DOT__u_3d_dram__DOT__u_3d_cache__DOT__tag_q[10U] = 0ULL;
        vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_data_lane__DOT__u_3d_dram__DOT__u_3d_cache__DOT__tag_q[11U] = 0ULL;
        vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_data_lane__DOT__u_3d_dram__DOT__u_3d_cache__DOT__tag_q[12U] = 0ULL;
        vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_data_lane__DOT__u_3d_dram__DOT__u_3d_cache__DOT__tag_q[13U] = 0ULL;
        vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_data_lane__DOT__u_3d_dram__DOT__u_3d_cache__DOT__tag_q[14U] = 0ULL;
        vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_data_lane__DOT__u_3d_dram__DOT__u_3d_cache__DOT__tag_q[15U] = 0ULL;
        vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_data_lane__DOT__u_3d_dram__DOT__u_3d_cache__DOT__data_q[1U] = 0ULL;
        vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_data_lane__DOT__u_3d_dram__DOT__u_3d_cache__DOT__data_q[2U] = 0ULL;
        vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_data_lane__DOT__u_3d_dram__DOT__u_3d_cache__DOT__data_q[3U] = 0ULL;
        vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_data_lane__DOT__u_3d_dram__DOT__u_3d_cache__DOT__data_q[4U] = 0ULL;
        vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_data_lane__DOT__u_3d_dram__DOT__u_3d_cache__DOT__data_q[5U] = 0ULL;
        vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_data_lane__DOT__u_3d_dram__DOT__u_3d_cache__DOT__data_q[6U] = 0ULL;
        vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_data_lane__DOT__u_3d_dram__DOT__u_3d_cache__DOT__data_q[7U] = 0ULL;
        vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_data_lane__DOT__u_3d_dram__DOT__u_3d_cache__DOT__data_q[8U] = 0ULL;
        vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_data_lane__DOT__u_3d_dram__DOT__u_3d_cache__DOT__data_q[9U] = 0ULL;
        vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_data_lane__DOT__u_3d_dram__DOT__u_3d_cache__DOT__data_q[10U] = 0ULL;
        vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_data_lane__DOT__u_3d_dram__DOT__u_3d_cache__DOT__data_q[11U] = 0ULL;
        vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_data_lane__DOT__u_3d_dram__DOT__u_3d_cache__DOT__data_q[12U] = 0ULL;
        vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_data_lane__DOT__u_3d_dram__DOT__u_3d_cache__DOT__data_q[13U] = 0ULL;
        vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_data_lane__DOT__u_3d_dram__DOT__u_3d_cache__DOT__data_q[14U] = 0ULL;
        vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_data_lane__DOT__u_3d_dram__DOT__u_3d_cache__DOT__data_q[15U] = 0ULL;
    }
    __Vtableidx1 = vlSelfRef.rst_n;
    vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__cache_csr_flush_l1d_w 
        = Vtb_nvisc_core_v02_with_mem_domains__ConstPool__TABLE_h8cec2904_0
        [__Vtableidx1];
    vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__cache_csr_flush_3d_w 
        = Vtb_nvisc_core_v02_with_mem_domains__ConstPool__TABLE_h8cec2904_0
        [__Vtableidx1];
    vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__cache_csr_flush_hierarchy_w 
        = Vtb_nvisc_core_v02_with_mem_domains__ConstPool__TABLE_h8cec2904_0
        [__Vtableidx1];
    vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_data_lane__DOT__cache3d_fault_w 
        = __Vdly__tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_data_lane__DOT__cache3d_fault_w;
    vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_data_lane__DOT__cache3d_fault_code_w 
        = __Vdly__tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_data_lane__DOT__cache3d_fault_code_w;
    vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_data_lane__DOT__cache3d_resp_valid_w 
        = __Vdly__tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_data_lane__DOT__cache3d_resp_valid_w;
    vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_data_lane__DOT__cache3d_resp_rdata_w 
        = __Vdly__tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_data_lane__DOT__cache3d_resp_rdata_w;
    vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_data_lane__DOT__cache3d_resp_write_ack_w 
        = __Vdly__tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_data_lane__DOT__cache3d_resp_write_ack_w;
    vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_data_lane__DOT__u_l1d__DOT__valid_q 
        = __Vdly__tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_data_lane__DOT__u_l1d__DOT__valid_q;
    vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_data_lane__DOT__u_l1d__DOT__state_q 
        = __Vdly__tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_data_lane__DOT__u_l1d__DOT__state_q;
    vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_data_lane__DOT__u_l1d__DOT__miss_index_q 
        = __Vdly__tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_data_lane__DOT__u_l1d__DOT__miss_index_q;
    vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_data_lane__DOT__u_l1d__DOT__miss_tag_q 
        = __Vdly__tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_data_lane__DOT__u_l1d__DOT__miss_tag_q;
    if (__VdlySet__tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_data_lane__DOT__u_l1d__DOT__tag_q__v0) {
        vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_data_lane__DOT__u_l1d__DOT__tag_q[0U] = 0ULL;
        vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_data_lane__DOT__u_l1d__DOT__data_q[0U] = 0ULL;
    }
    if (__VdlySet__tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_data_lane__DOT__u_l1d__DOT__tag_q__v1) {
        vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_data_lane__DOT__u_l1d__DOT__tag_q[1U] = 0ULL;
        vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_data_lane__DOT__u_l1d__DOT__tag_q[2U] = 0ULL;
        vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_data_lane__DOT__u_l1d__DOT__tag_q[3U] = 0ULL;
        vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_data_lane__DOT__u_l1d__DOT__tag_q[4U] = 0ULL;
        vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_data_lane__DOT__u_l1d__DOT__tag_q[5U] = 0ULL;
        vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_data_lane__DOT__u_l1d__DOT__tag_q[6U] = 0ULL;
        vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_data_lane__DOT__u_l1d__DOT__tag_q[7U] = 0ULL;
        vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_data_lane__DOT__u_l1d__DOT__tag_q[8U] = 0ULL;
        vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_data_lane__DOT__u_l1d__DOT__tag_q[9U] = 0ULL;
        vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_data_lane__DOT__u_l1d__DOT__tag_q[10U] = 0ULL;
        vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_data_lane__DOT__u_l1d__DOT__tag_q[11U] = 0ULL;
        vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_data_lane__DOT__u_l1d__DOT__tag_q[12U] = 0ULL;
        vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_data_lane__DOT__u_l1d__DOT__tag_q[13U] = 0ULL;
        vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_data_lane__DOT__u_l1d__DOT__tag_q[14U] = 0ULL;
        vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_data_lane__DOT__u_l1d__DOT__tag_q[15U] = 0ULL;
        vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_data_lane__DOT__u_l1d__DOT__data_q[1U] = 0ULL;
        vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_data_lane__DOT__u_l1d__DOT__data_q[2U] = 0ULL;
        vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_data_lane__DOT__u_l1d__DOT__data_q[3U] = 0ULL;
        vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_data_lane__DOT__u_l1d__DOT__data_q[4U] = 0ULL;
        vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_data_lane__DOT__u_l1d__DOT__data_q[5U] = 0ULL;
        vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_data_lane__DOT__u_l1d__DOT__data_q[6U] = 0ULL;
        vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_data_lane__DOT__u_l1d__DOT__data_q[7U] = 0ULL;
        vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_data_lane__DOT__u_l1d__DOT__data_q[8U] = 0ULL;
        vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_data_lane__DOT__u_l1d__DOT__data_q[9U] = 0ULL;
        vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_data_lane__DOT__u_l1d__DOT__data_q[10U] = 0ULL;
        vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_data_lane__DOT__u_l1d__DOT__data_q[11U] = 0ULL;
        vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_data_lane__DOT__u_l1d__DOT__data_q[12U] = 0ULL;
        vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_data_lane__DOT__u_l1d__DOT__data_q[13U] = 0ULL;
        vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_data_lane__DOT__u_l1d__DOT__data_q[14U] = 0ULL;
        vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_data_lane__DOT__u_l1d__DOT__data_q[15U] = 0ULL;
    }
    if (__VdlySet__tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_data_lane__DOT__u_l1d__DOT__tag_q__v16) {
        vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_data_lane__DOT__u_l1d__DOT__tag_q[__VdlyDim0__tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_data_lane__DOT__u_l1d__DOT__tag_q__v16] 
            = __VdlyVal__tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_data_lane__DOT__u_l1d__DOT__tag_q__v16;
    }
    if (__VdlySet__tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_data_lane__DOT__u_l1d__DOT__tag_q__v17) {
        vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_data_lane__DOT__u_l1d__DOT__tag_q[0U] = 0ULL;
    }
    if (__VdlySet__tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_data_lane__DOT__u_l1d__DOT__tag_q__v18) {
        vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_data_lane__DOT__u_l1d__DOT__tag_q[1U] = 0ULL;
    }
    if (__VdlySet__tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_data_lane__DOT__u_l1d__DOT__data_q__v16) {
        vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_data_lane__DOT__u_l1d__DOT__data_q[__VdlyDim0__tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_data_lane__DOT__u_l1d__DOT__data_q__v16] 
            = __VdlyVal__tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_data_lane__DOT__u_l1d__DOT__data_q__v16;
    }
    if (__VdlySet__tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_data_lane__DOT__u_l1d__DOT__tag_q__v16) {
        vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_data_lane__DOT__u_l1d__DOT__data_q[__VdlyDim0__tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_data_lane__DOT__u_l1d__DOT__data_q__v17] 
            = __VdlyVal__tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_data_lane__DOT__u_l1d__DOT__data_q__v17;
    }
    if (__VdlySet__tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_data_lane__DOT__u_l1d__DOT__tag_q__v17) {
        vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_data_lane__DOT__u_l1d__DOT__data_q[0U] = 0ULL;
    }
    if (__VdlySet__tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_data_lane__DOT__u_l1d__DOT__tag_q__v18) {
        vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_data_lane__DOT__u_l1d__DOT__data_q[1U] = 0ULL;
    }
    if (__VdlySet__tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_data_lane__DOT__u_l1d__DOT__tag_q__v19) {
        vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_data_lane__DOT__u_l1d__DOT__tag_q[2U] = 0ULL;
        vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_data_lane__DOT__u_l1d__DOT__tag_q[3U] = 0ULL;
        vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_data_lane__DOT__u_l1d__DOT__tag_q[4U] = 0ULL;
        vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_data_lane__DOT__u_l1d__DOT__tag_q[5U] = 0ULL;
        vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_data_lane__DOT__u_l1d__DOT__tag_q[6U] = 0ULL;
        vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_data_lane__DOT__u_l1d__DOT__tag_q[7U] = 0ULL;
        vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_data_lane__DOT__u_l1d__DOT__tag_q[8U] = 0ULL;
        vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_data_lane__DOT__u_l1d__DOT__tag_q[9U] = 0ULL;
        vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_data_lane__DOT__u_l1d__DOT__tag_q[10U] = 0ULL;
        vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_data_lane__DOT__u_l1d__DOT__tag_q[11U] = 0ULL;
        vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_data_lane__DOT__u_l1d__DOT__tag_q[12U] = 0ULL;
        vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_data_lane__DOT__u_l1d__DOT__tag_q[13U] = 0ULL;
        vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_data_lane__DOT__u_l1d__DOT__tag_q[14U] = 0ULL;
        vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_data_lane__DOT__u_l1d__DOT__tag_q[15U] = 0ULL;
        vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_data_lane__DOT__u_l1d__DOT__data_q[2U] = 0ULL;
        vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_data_lane__DOT__u_l1d__DOT__data_q[3U] = 0ULL;
        vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_data_lane__DOT__u_l1d__DOT__data_q[4U] = 0ULL;
        vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_data_lane__DOT__u_l1d__DOT__data_q[5U] = 0ULL;
        vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_data_lane__DOT__u_l1d__DOT__data_q[6U] = 0ULL;
        vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_data_lane__DOT__u_l1d__DOT__data_q[7U] = 0ULL;
        vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_data_lane__DOT__u_l1d__DOT__data_q[8U] = 0ULL;
        vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_data_lane__DOT__u_l1d__DOT__data_q[9U] = 0ULL;
        vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_data_lane__DOT__u_l1d__DOT__data_q[10U] = 0ULL;
        vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_data_lane__DOT__u_l1d__DOT__data_q[11U] = 0ULL;
        vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_data_lane__DOT__u_l1d__DOT__data_q[12U] = 0ULL;
        vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_data_lane__DOT__u_l1d__DOT__data_q[13U] = 0ULL;
        vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_data_lane__DOT__u_l1d__DOT__data_q[14U] = 0ULL;
        vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_data_lane__DOT__u_l1d__DOT__data_q[15U] = 0ULL;
    }
    vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__effective_flush_data_l1d_w 
        = ((IData)(vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__cache_csr_flush_l1d_w) 
           | (IData)(vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__cache_csr_flush_hierarchy_w));
    vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_memdom_csr__DOT__effective_domain_c 
        = ((IData)(vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_memdom_csr__DOT__mem_domain_override_enable_q)
            ? (IData)(vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_memdom_csr__DOT__mem_domain_select_q)
            : (IData)(vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__wrapper_override_domain_w));
    vlSelfRef.dbg_data_route_valid_o = vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__data_req_valid_w;
    vlSelfRef.dbg_exec_route_valid_o = vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__exec_req_valid_w;
    vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_execmem__DOT__in_range_c 
        = ((0x0000000000002000ULL <= vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__exec_req_paddr_w) 
           & (0x0000000000000100ULL > VL_SHIFTR_QQI(64,64,32, 
                                                    (vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__exec_req_paddr_w 
                                                     - 0x0000000000002000ULL), 3U)));
    vlSelfRef.dbg_livehot_route_valid_o = vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__livehot_req_valid_w;
    vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_livehot__DOT__in_range_c 
        = ((0x0000000000003000ULL <= vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__livehot_req_paddr_w) 
           & (0x0000000000000100ULL > VL_SHIFTR_QQI(64,64,32, 
                                                    (vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__livehot_req_paddr_w 
                                                     - 0x0000000000003000ULL), 3U)));
    vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_execmem__DOT__op_ok_c 
        = ((IData)(vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__exec_req_is_read_w) 
           ^ (IData)(vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__exec_req_is_write_w));
    vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_livehot__DOT__op_ok_c 
        = ((IData)(vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__livehot_req_is_read_w) 
           ^ (IData)(vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__livehot_req_is_write_w));
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
    vlSelfRef.memsys_resp_write_ack_o = tb_nvisc_core_v02_with_mem_domains__DOT__memsys_resp_write_ack_w;
    vlSelfRef.memsys_resp_rdata_o = vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__memsys_resp_rdata_w;
    vlSelfRef.load_wb_data_o = vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__memsys_resp_rdata_w;
    vlSelfRef.memsys_fault_code_o = tb_nvisc_core_v02_with_mem_domains__DOT__memsys_fault_code_w;
    vlSelfRef.memsys_resp_valid_o = vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__memsys_resp_valid_w;
    vlSelfRef.memsys_fault_o = vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__memsys_fault_w;
    vlSelfRef.load_wb_valid_o = ((IData)(vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__memsys_resp_valid_w) 
                                 & ((~ (IData)(vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__memsys_fault_w)) 
                                    & (IData)(vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_core__DOT__load_pending_q)));
    vlSelfRef.mem_req_is_read_o = vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_core__DOT__mmu_resp_is_read_w;
    vlSelfRef.mem_req_is_write_o = vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_core__DOT__mmu_resp_is_write_w;
    vlSelfRef.mem_req_paddr_o = vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_core__DOT__mmu_resp_paddr_w;
    vlSelfRef.mem_req_wdata_o = vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_core__DOT__mmu_resp_wdata_w;
    vlSelfRef.mem_req_size_bytes_o = vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_core__DOT__mmu_resp_size_bytes_w;
    vlSelfRef.mem_req_valid_o = vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_core__DOT__mmu_resp_valid_w;
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
    vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_core__DOT__u_mmu__DOT__page_fault_c 
        = (IData)(((0x003fffc0U == (0x003fffc0U & vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_core__DOT__u_lsu__DOT__req_q[10U])) 
                   & (vlSelfRef.tb_nvisc_core_v02_with_mem_domains__DOT__u_core__DOT__u_lsu__DOT__req_q[11U] 
                      >> 0x00000019U)));
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

void Vtb_nvisc_core_v02_with_mem_domains___024root___eval_nba(Vtb_nvisc_core_v02_with_mem_domains___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_nvisc_core_v02_with_mem_domains___024root___eval_nba\n"); );
    Vtb_nvisc_core_v02_with_mem_domains__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    if ((3ULL & vlSelfRef.__VnbaTriggered[0U])) {
        Vtb_nvisc_core_v02_with_mem_domains___024root___nba_sequent__TOP__0(vlSelf);
    }
}

void Vtb_nvisc_core_v02_with_mem_domains___024root___trigger_orInto__act_vec_vec(VlUnpacked<QData/*63:0*/, 1> &out, const VlUnpacked<QData/*63:0*/, 1> &in) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_nvisc_core_v02_with_mem_domains___024root___trigger_orInto__act_vec_vec\n"); );
    // Locals
    IData/*31:0*/ n;
    // Body
    n = 0U;
    do {
        out[n] = (out[n] | in[n]);
        n = ((IData)(1U) + n);
    } while ((0U >= n));
}

#ifdef VL_DEBUG
VL_ATTR_COLD void Vtb_nvisc_core_v02_with_mem_domains___024root___dump_triggers__act(const VlUnpacked<QData/*63:0*/, 1> &triggers, const std::string &tag);
#endif  // VL_DEBUG

bool Vtb_nvisc_core_v02_with_mem_domains___024root___eval_phase__act(Vtb_nvisc_core_v02_with_mem_domains___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_nvisc_core_v02_with_mem_domains___024root___eval_phase__act\n"); );
    Vtb_nvisc_core_v02_with_mem_domains__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    Vtb_nvisc_core_v02_with_mem_domains___024root___eval_triggers_vec__act(vlSelf);
#ifdef VL_DEBUG
    if (VL_UNLIKELY(vlSymsp->_vm_contextp__->debug())) {
        Vtb_nvisc_core_v02_with_mem_domains___024root___dump_triggers__act(vlSelfRef.__VactTriggered, "act"s);
    }
#endif
    Vtb_nvisc_core_v02_with_mem_domains___024root___trigger_orInto__act_vec_vec(vlSelfRef.__VnbaTriggered, vlSelfRef.__VactTriggered);
    return (0U);
}

void Vtb_nvisc_core_v02_with_mem_domains___024root___trigger_clear__act(VlUnpacked<QData/*63:0*/, 1> &out) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_nvisc_core_v02_with_mem_domains___024root___trigger_clear__act\n"); );
    // Locals
    IData/*31:0*/ n;
    // Body
    n = 0U;
    do {
        out[n] = 0ULL;
        n = ((IData)(1U) + n);
    } while ((1U > n));
}

bool Vtb_nvisc_core_v02_with_mem_domains___024root___eval_phase__nba(Vtb_nvisc_core_v02_with_mem_domains___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_nvisc_core_v02_with_mem_domains___024root___eval_phase__nba\n"); );
    Vtb_nvisc_core_v02_with_mem_domains__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Locals
    CData/*0:0*/ __VnbaExecute;
    // Body
    __VnbaExecute = Vtb_nvisc_core_v02_with_mem_domains___024root___trigger_anySet__act(vlSelfRef.__VnbaTriggered);
    if (__VnbaExecute) {
        Vtb_nvisc_core_v02_with_mem_domains___024root___eval_nba(vlSelf);
        Vtb_nvisc_core_v02_with_mem_domains___024root___trigger_clear__act(vlSelfRef.__VnbaTriggered);
    }
    return (__VnbaExecute);
}

void Vtb_nvisc_core_v02_with_mem_domains___024root___eval(Vtb_nvisc_core_v02_with_mem_domains___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_nvisc_core_v02_with_mem_domains___024root___eval\n"); );
    Vtb_nvisc_core_v02_with_mem_domains__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Locals
    IData/*31:0*/ __VicoIterCount;
    IData/*31:0*/ __VnbaIterCount;
    // Body
    __VicoIterCount = 0U;
    vlSelfRef.__VicoFirstIteration = 1U;
    do {
        if (VL_UNLIKELY(((0x00002710U < __VicoIterCount)))) {
#ifdef VL_DEBUG
            Vtb_nvisc_core_v02_with_mem_domains___024root___dump_triggers__ico(vlSelfRef.__VicoTriggered, "ico"s);
#endif
            VL_FATAL_MT("rtl/core_v02\\tb_nvisc_core_v02_with_mem_domains.sv", 5, "", "DIDNOTCONVERGE: Input combinational region did not converge after '--converge-limit' of 10000 tries");
        }
        __VicoIterCount = ((IData)(1U) + __VicoIterCount);
        vlSelfRef.__VicoPhaseResult = Vtb_nvisc_core_v02_with_mem_domains___024root___eval_phase__ico(vlSelf);
        vlSelfRef.__VicoFirstIteration = 0U;
    } while (vlSelfRef.__VicoPhaseResult);
    __VnbaIterCount = 0U;
    do {
        if (VL_UNLIKELY(((0x00002710U < __VnbaIterCount)))) {
#ifdef VL_DEBUG
            Vtb_nvisc_core_v02_with_mem_domains___024root___dump_triggers__act(vlSelfRef.__VnbaTriggered, "nba"s);
#endif
            VL_FATAL_MT("rtl/core_v02\\tb_nvisc_core_v02_with_mem_domains.sv", 5, "", "DIDNOTCONVERGE: NBA region did not converge after '--converge-limit' of 10000 tries");
        }
        __VnbaIterCount = ((IData)(1U) + __VnbaIterCount);
        vlSelfRef.__VactIterCount = 0U;
        do {
            if (VL_UNLIKELY(((0x00002710U < vlSelfRef.__VactIterCount)))) {
#ifdef VL_DEBUG
                Vtb_nvisc_core_v02_with_mem_domains___024root___dump_triggers__act(vlSelfRef.__VactTriggered, "act"s);
#endif
                VL_FATAL_MT("rtl/core_v02\\tb_nvisc_core_v02_with_mem_domains.sv", 5, "", "DIDNOTCONVERGE: Active region did not converge after '--converge-limit' of 10000 tries");
            }
            vlSelfRef.__VactIterCount = ((IData)(1U) 
                                         + vlSelfRef.__VactIterCount);
            vlSelfRef.__VactPhaseResult = Vtb_nvisc_core_v02_with_mem_domains___024root___eval_phase__act(vlSelf);
        } while (vlSelfRef.__VactPhaseResult);
        vlSelfRef.__VnbaPhaseResult = Vtb_nvisc_core_v02_with_mem_domains___024root___eval_phase__nba(vlSelf);
    } while (vlSelfRef.__VnbaPhaseResult);
}

#ifdef VL_DEBUG
void Vtb_nvisc_core_v02_with_mem_domains___024root___eval_debug_assertions(Vtb_nvisc_core_v02_with_mem_domains___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_nvisc_core_v02_with_mem_domains___024root___eval_debug_assertions\n"); );
    Vtb_nvisc_core_v02_with_mem_domains__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    if (VL_UNLIKELY(((vlSelfRef.clk & 0xfeU)))) {
        Verilated::overWidthError("clk");
    }
    if (VL_UNLIKELY(((vlSelfRef.rst_n & 0xfeU)))) {
        Verilated::overWidthError("rst_n");
    }
    if (VL_UNLIKELY(((vlSelfRef.imem_resp_valid_i & 0xfeU)))) {
        Verilated::overWidthError("imem_resp_valid_i");
    }
    if (VL_UNLIKELY(((vlSelfRef.imem_resp_fault_i & 0xfeU)))) {
        Verilated::overWidthError("imem_resp_fault_i");
    }
    if (VL_UNLIKELY(((vlSelfRef.privilege_i & 0xf8U)))) {
        Verilated::overWidthError("privilege_i");
    }
    if (VL_UNLIKELY(((vlSelfRef.dbg_rf_we_i & 0xfeU)))) {
        Verilated::overWidthError("dbg_rf_we_i");
    }
    if (VL_UNLIKELY(((vlSelfRef.dbg_rf_waddr_i & 0xe0U)))) {
        Verilated::overWidthError("dbg_rf_waddr_i");
    }
    if (VL_UNLIKELY(((vlSelfRef.stall_i & 0xfeU)))) {
        Verilated::overWidthError("stall_i");
    }
    if (VL_UNLIKELY(((vlSelfRef.flush_i & 0xfeU)))) {
        Verilated::overWidthError("flush_i");
    }
    if (VL_UNLIKELY(((vlSelfRef.redirect_valid_i & 0xfeU)))) {
        Verilated::overWidthError("redirect_valid_i");
    }
    if (VL_UNLIKELY(((vlSelfRef.branch_taken_i & 0xfeU)))) {
        Verilated::overWidthError("branch_taken_i");
    }
    if (VL_UNLIKELY(((vlSelfRef.trap_valid_i & 0xfeU)))) {
        Verilated::overWidthError("trap_valid_i");
    }
    if (VL_UNLIKELY(((vlSelfRef.rollback_redirect_i 
                      & 0xfeU)))) {
        Verilated::overWidthError("rollback_redirect_i");
    }
    if (VL_UNLIKELY(((vlSelfRef.mem_domain_override_valid_i 
                      & 0xfeU)))) {
        Verilated::overWidthError("mem_domain_override_valid_i");
    }
    if (VL_UNLIKELY(((vlSelfRef.mem_domain_override_i 
                      & 0xf8U)))) {
        Verilated::overWidthError("mem_domain_override_i");
    }
    if (VL_UNLIKELY(((vlSelfRef.memdom_csr_valid_i 
                      & 0xfeU)))) {
        Verilated::overWidthError("memdom_csr_valid_i");
    }
    if (VL_UNLIKELY(((vlSelfRef.memdom_csr_write_i 
                      & 0xfeU)))) {
        Verilated::overWidthError("memdom_csr_write_i");
    }
    if (VL_UNLIKELY(((vlSelfRef.memdom_csr_read_i & 0xfeU)))) {
        Verilated::overWidthError("memdom_csr_read_i");
    }
    if (VL_UNLIKELY(((vlSelfRef.memdom_csr_addr_i & 0xf000U)))) {
        Verilated::overWidthError("memdom_csr_addr_i");
    }
}
#endif  // VL_DEBUG
