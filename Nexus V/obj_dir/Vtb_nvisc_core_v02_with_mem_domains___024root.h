// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design internal header
// See Vtb_nvisc_core_v02_with_mem_domains.h for the primary calling header

#ifndef VERILATED_VTB_NVISC_CORE_V02_WITH_MEM_DOMAINS___024ROOT_H_
#define VERILATED_VTB_NVISC_CORE_V02_WITH_MEM_DOMAINS___024ROOT_H_  // guard

#include "verilated.h"


class Vtb_nvisc_core_v02_with_mem_domains__Syms;

class alignas(VL_CACHE_LINE_BYTES) Vtb_nvisc_core_v02_with_mem_domains___024root final {
  public:

    // DESIGN SPECIFIC STATE
    // Anonymous structures to workaround compiler member-count bugs
    struct {
        VL_IN8(clk,0,0);
        VL_IN8(rst_n,0,0);
        VL_IN8(imem_resp_valid_i,0,0);
        VL_IN8(imem_resp_fault_i,0,0);
        VL_IN8(thread_id_i,7,0);
        VL_IN8(privilege_i,2,0);
        VL_IN8(lsu_size_bytes_i,7,0);
        VL_IN8(dbg_rf_we_i,0,0);
        VL_IN8(dbg_rf_waddr_i,4,0);
        VL_IN8(stall_i,0,0);
        VL_IN8(flush_i,0,0);
        VL_IN8(redirect_valid_i,0,0);
        VL_IN8(branch_taken_i,0,0);
        VL_IN8(trap_valid_i,0,0);
        VL_IN8(rollback_redirect_i,0,0);
        VL_IN8(mem_domain_override_valid_i,0,0);
        VL_IN8(mem_domain_override_i,2,0);
        VL_IN8(memdom_csr_valid_i,0,0);
        VL_IN8(memdom_csr_write_i,0,0);
        VL_IN8(memdom_csr_read_i,0,0);
        VL_OUT8(memdom_csr_resp_valid_o,0,0);
        VL_OUT8(memdom_csr_fault_o,0,0);
        VL_OUT8(imem_req_valid_o,0,0);
        VL_OUT8(pc_valid_o,0,0);
        VL_OUT8(fetch_valid_o,0,0);
        VL_OUT8(decode_class_o,7,0);
        VL_OUT8(alu_result_valid_o,0,0);
        VL_OUT8(alu_zero_o,0,0);
        VL_OUT8(alu_negative_o,0,0);
        VL_OUT8(alu_overflow_o,0,0);
        VL_OUT8(branch_taken_internal_o,0,0);
        VL_OUT8(alu_valid_o,0,0);
        VL_OUT8(lsu_valid_o,0,0);
        VL_OUT8(csr_valid_o,0,0);
        VL_OUT8(branch_valid_o,0,0);
        VL_OUT8(mem_req_valid_o,0,0);
        VL_OUT8(mem_req_is_read_o,0,0);
        VL_OUT8(mem_req_is_write_o,0,0);
        VL_OUT8(mem_req_size_bytes_o,7,0);
        VL_OUT8(mem_req_domain_o,2,0);
        VL_OUT8(memsys_resp_valid_o,0,0);
        VL_OUT8(memsys_resp_write_ack_o,0,0);
        VL_OUT8(memsys_fault_o,0,0);
        VL_OUT8(dbg_data_route_valid_o,0,0);
        VL_OUT8(dbg_exec_route_valid_o,0,0);
        VL_OUT8(dbg_livehot_route_valid_o,0,0);
        VL_OUT8(load_wb_valid_o,0,0);
        VL_OUT8(core_fault_o,0,0);
        CData/*2:0*/ tb_nvisc_core_v02_with_mem_domains__DOT__wrapper_override_domain_w;
        CData/*0:0*/ tb_nvisc_core_v02_with_mem_domains__DOT__memsys_resp_valid_w;
        CData/*0:0*/ tb_nvisc_core_v02_with_mem_domains__DOT__memsys_fault_w;
        CData/*2:0*/ tb_nvisc_core_v02_with_mem_domains__DOT__u_memdom_csr__DOT__mem_domain_select_q;
        CData/*0:0*/ tb_nvisc_core_v02_with_mem_domains__DOT__u_memdom_csr__DOT__mem_domain_override_enable_q;
        CData/*2:0*/ tb_nvisc_core_v02_with_mem_domains__DOT__u_memdom_csr__DOT__effective_domain_c;
        CData/*0:0*/ tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__data_req_valid_w;
        CData/*0:0*/ tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__data_req_is_read_w;
        CData/*0:0*/ tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__data_req_is_write_w;
        CData/*7:0*/ tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__data_req_size_bytes_w;
        CData/*0:0*/ tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__exec_req_valid_w;
        CData/*0:0*/ tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__exec_req_is_read_w;
        CData/*0:0*/ tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__exec_req_is_write_w;
        CData/*7:0*/ tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__exec_req_size_bytes_w;
        CData/*0:0*/ tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__livehot_req_valid_w;
        CData/*0:0*/ tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__livehot_req_is_read_w;
    };
    struct {
        CData/*0:0*/ tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__livehot_req_is_write_w;
        CData/*7:0*/ tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__livehot_req_size_bytes_w;
        CData/*0:0*/ tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__router_fault_w;
        CData/*0:0*/ tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__data_resp_valid_w;
        CData/*0:0*/ tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__data_resp_write_ack_w;
        CData/*0:0*/ tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__data_fault_w;
        CData/*0:0*/ tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__cache_csr_flush_l1d_w;
        CData/*0:0*/ tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__cache_csr_flush_3d_w;
        CData/*0:0*/ tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__cache_csr_flush_hierarchy_w;
        CData/*0:0*/ tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__effective_flush_data_l1d_w;
        CData/*0:0*/ tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__exec_resp_valid_w;
        CData/*0:0*/ tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__exec_resp_write_ack_w;
        CData/*0:0*/ tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__exec_fault_w;
        CData/*0:0*/ tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__livehot_resp_valid_w;
        CData/*0:0*/ tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__livehot_resp_write_ack_w;
        CData/*0:0*/ tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__livehot_fault_w;
        CData/*2:0*/ tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__pending_domain_q;
        CData/*0:0*/ tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_data_lane__DOT__l1d_mem_req_valid_w;
        CData/*0:0*/ tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_data_lane__DOT__l1d_mem_req_is_read_w;
        CData/*0:0*/ tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_data_lane__DOT__l1d_mem_req_is_write_w;
        CData/*7:0*/ tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_data_lane__DOT__l1d_mem_req_size_bytes_w;
        CData/*0:0*/ tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_data_lane__DOT__cache3d_resp_valid_w;
        CData/*0:0*/ tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_data_lane__DOT__cache3d_resp_write_ack_w;
        CData/*0:0*/ tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_data_lane__DOT__cache3d_fault_w;
        CData/*1:0*/ tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_data_lane__DOT__u_l1d__DOT__state_q;
        CData/*3:0*/ tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_data_lane__DOT__u_l1d__DOT__miss_index_q;
        CData/*0:0*/ tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_data_lane__DOT__u_l1d__DOT__flush_q;
        CData/*0:0*/ tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_data_lane__DOT__u_3d_dram__DOT__cache_mem_req_valid_w;
        CData/*0:0*/ tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_data_lane__DOT__u_3d_dram__DOT__cache_mem_req_is_read_w;
        CData/*0:0*/ tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_data_lane__DOT__u_3d_dram__DOT__cache_mem_req_is_write_w;
        CData/*7:0*/ tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_data_lane__DOT__u_3d_dram__DOT__cache_mem_req_size_bytes_w;
        CData/*7:0*/ tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_data_lane__DOT__u_3d_dram__DOT__cache_mem_req_id_w;
        CData/*0:0*/ tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_data_lane__DOT__u_3d_dram__DOT__dram_resp_valid_w;
        CData/*0:0*/ tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_data_lane__DOT__u_3d_dram__DOT__dram_resp_write_ack_w;
        CData/*0:0*/ tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_data_lane__DOT__u_3d_dram__DOT__dram_fault_w;
        CData/*1:0*/ tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_data_lane__DOT__u_3d_dram__DOT__u_3d_cache__DOT__state_q;
        CData/*3:0*/ tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_data_lane__DOT__u_3d_dram__DOT__u_3d_cache__DOT__pending_index_q;
        CData/*0:0*/ tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_data_lane__DOT__u_3d_dram__DOT__u_dram__DOT__busy_q;
        CData/*2:0*/ tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_data_lane__DOT__u_3d_dram__DOT__u_dram__DOT__latency_q;
        CData/*0:0*/ tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_data_lane__DOT__u_3d_dram__DOT__u_dram__DOT__pending_read_q;
        CData/*0:0*/ tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_data_lane__DOT__u_3d_dram__DOT__u_dram__DOT__pending_write_q;
        CData/*7:0*/ tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_data_lane__DOT__u_3d_dram__DOT__u_dram__DOT__pending_id_q;
        CData/*0:0*/ tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_execmem__DOT__in_range_c;
        CData/*0:0*/ tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_execmem__DOT__op_ok_c;
        CData/*0:0*/ tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_livehot__DOT__in_range_c;
        CData/*0:0*/ tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_livehot__DOT__op_ok_c;
        CData/*0:0*/ tb_nvisc_core_v02_with_mem_domains__DOT__u_core__DOT__mmu_resp_valid_w;
        CData/*0:0*/ tb_nvisc_core_v02_with_mem_domains__DOT__u_core__DOT__mmu_resp_is_read_w;
        CData/*0:0*/ tb_nvisc_core_v02_with_mem_domains__DOT__u_core__DOT__mmu_resp_is_write_w;
        CData/*7:0*/ tb_nvisc_core_v02_with_mem_domains__DOT__u_core__DOT__mmu_resp_size_bytes_w;
        CData/*2:0*/ tb_nvisc_core_v02_with_mem_domains__DOT__u_core__DOT__mmu_resp_mem_domain_w;
        CData/*0:0*/ tb_nvisc_core_v02_with_mem_domains__DOT__u_core__DOT__mmu_fault_w;
        CData/*0:0*/ tb_nvisc_core_v02_with_mem_domains__DOT__u_core__DOT__branch_taken_w;
        CData/*0:0*/ tb_nvisc_core_v02_with_mem_domains__DOT__u_core__DOT__rf_we_w;
        CData/*4:0*/ tb_nvisc_core_v02_with_mem_domains__DOT__u_core__DOT__rf_waddr_w;
        CData/*0:0*/ tb_nvisc_core_v02_with_mem_domains__DOT__u_core__DOT__load_pending_q;
        CData/*4:0*/ tb_nvisc_core_v02_with_mem_domains__DOT__u_core__DOT__load_rd_q;
        CData/*0:0*/ tb_nvisc_core_v02_with_mem_domains__DOT__u_core__DOT__ctrl_reg_write_w;
        CData/*0:0*/ tb_nvisc_core_v02_with_mem_domains__DOT__u_core__DOT__ctrl_mem_read_w;
        CData/*0:0*/ tb_nvisc_core_v02_with_mem_domains__DOT__u_core__DOT__ctrl_mem_write_w;
        CData/*0:0*/ tb_nvisc_core_v02_with_mem_domains__DOT__u_core__DOT__lsu_fault_w;
        CData/*0:0*/ tb_nvisc_core_v02_with_mem_domains__DOT__u_core__DOT__csr_fault_w;
        CData/*7:0*/ tb_nvisc_core_v02_with_mem_domains__DOT__u_core__DOT__u_csr__DOT__core_id_q;
        CData/*7:0*/ tb_nvisc_core_v02_with_mem_domains__DOT__u_core__DOT__u_csr__DOT__thread_id_q;
    };
    struct {
        CData/*2:0*/ tb_nvisc_core_v02_with_mem_domains__DOT__u_core__DOT__u_csr__DOT__privilege_q;
        CData/*0:0*/ tb_nvisc_core_v02_with_mem_domains__DOT__u_core__DOT__u_pc__DOT__valid_q;
        CData/*0:0*/ tb_nvisc_core_v02_with_mem_domains__DOT__u_core__DOT__u_if__DOT__fault_q;
        CData/*0:0*/ tb_nvisc_core_v02_with_mem_domains__DOT__u_core__DOT__u_lsu__DOT__bad_size_c;
        CData/*0:0*/ tb_nvisc_core_v02_with_mem_domains__DOT__u_core__DOT__u_lsu__DOT__both_read_write_c;
        CData/*0:0*/ tb_nvisc_core_v02_with_mem_domains__DOT__u_core__DOT__u_lsu__DOT__no_op_c;
        CData/*0:0*/ tb_nvisc_core_v02_with_mem_domains__DOT__u_core__DOT__u_mmu__DOT__page_fault_c;
        CData/*0:0*/ tb_nvisc_core_v02_with_mem_domains__DOT__u_core__DOT__u_mmu__DOT__align_fault_c;
        CData/*0:0*/ __VstlFirstIteration;
        CData/*0:0*/ __VstlPhaseResult;
        CData/*0:0*/ __VicoFirstIteration;
        CData/*0:0*/ __VicoPhaseResult;
        CData/*0:0*/ __Vtrigprevexpr___TOP__clk__0;
        CData/*0:0*/ __Vtrigprevexpr___TOP__rst_n__0;
        CData/*0:0*/ __VactPhaseResult;
        CData/*0:0*/ __VnbaPhaseResult;
        VL_IN16(imem_resp_fault_code_i,15,0);
        VL_IN16(aegis_policy_id_i,15,0);
        VL_IN16(memdom_csr_addr_i,11,0);
        VL_OUT16(memdom_csr_fault_code_o,15,0);
        VL_OUT16(memsys_fault_code_o,15,0);
        VL_OUT16(core_fault_code_o,15,0);
        SData/*15:0*/ tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__router_fault_code_w;
        SData/*15:0*/ tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__data_fault_code_w;
        SData/*15:0*/ tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__exec_fault_code_w;
        SData/*15:0*/ tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__livehot_fault_code_w;
        SData/*15:0*/ tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_data_lane__DOT__cache3d_fault_code_w;
        SData/*15:0*/ tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_data_lane__DOT__u_l1d__DOT__valid_q;
        SData/*15:0*/ tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_data_lane__DOT__u_3d_dram__DOT__dram_fault_code_w;
        SData/*9:0*/ tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_data_lane__DOT__u_3d_dram__DOT__u_dram__DOT__pending_index_q;
        SData/*15:0*/ tb_nvisc_core_v02_with_mem_domains__DOT__u_core__DOT__mmu_fault_code_w;
        SData/*15:0*/ tb_nvisc_core_v02_with_mem_domains__DOT__u_core__DOT__lsu_fault_code_w;
        SData/*15:0*/ tb_nvisc_core_v02_with_mem_domains__DOT__u_core__DOT__csr_fault_code_w;
        SData/*15:0*/ tb_nvisc_core_v02_with_mem_domains__DOT__u_core__DOT__u_csr__DOT__aegis_policy_id_q;
        SData/*15:0*/ tb_nvisc_core_v02_with_mem_domains__DOT__u_core__DOT__u_if__DOT__fault_code_q;
        VL_IN(imem_resp_instr_i,31,0);
        VL_IN(branch_id_i,31,0);
        VL_IN(state_id_i,31,0);
        VL_IN(commit_id_i,31,0);
        VL_OUT(fetch_instr_o,31,0);
        IData/*31:0*/ tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_data_lane__DOT__u_3d_dram__DOT__u_dram__DOT__i;
        IData/*31:0*/ tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_execmem__DOT__i;
        IData/*31:0*/ tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_livehot__DOT__i;
        IData/*31:0*/ tb_nvisc_core_v02_with_mem_domains__DOT__u_core__DOT__u_csr__DOT__branch_id_q;
        IData/*31:0*/ tb_nvisc_core_v02_with_mem_domains__DOT__u_core__DOT__u_csr__DOT__state_id_q;
        IData/*31:0*/ tb_nvisc_core_v02_with_mem_domains__DOT__u_core__DOT__u_csr__DOT__commit_id_q;
        IData/*31:0*/ __VactIterCount;
        VL_IN64(lsu_base_value_i,63,0);
        VL_IN64(lsu_store_data_i,63,0);
        VL_IN64(dbg_rf_wdata_i,63,0);
        VL_IN64(redirect_pc_i,63,0);
        VL_IN64(branch_target_i,63,0);
        VL_IN64(trap_vector_i,63,0);
        VL_IN64(rollback_pc_i,63,0);
        VL_IN64(memdom_csr_wdata_i,63,0);
        VL_OUT64(memdom_csr_rdata_o,63,0);
        VL_OUT64(imem_req_addr_o,63,0);
        VL_OUT64(pc_o,63,0);
        VL_OUT64(dbg_rf_r1_o,63,0);
        VL_OUT64(dbg_rf_r2_o,63,0);
        VL_OUT64(dbg_rf_r3_o,63,0);
        VL_OUT64(alu_result_o,63,0);
        VL_OUT64(branch_target_internal_o,63,0);
        VL_OUT64(mem_req_vaddr_o,63,0);
    };
    struct {
        VL_OUT64(mem_req_paddr_o,63,0);
        VL_OUT64(mem_req_wdata_o,63,0);
        VL_OUT64(memsys_resp_rdata_o,63,0);
        VL_OUT64(load_wb_data_o,63,0);
        QData/*63:0*/ tb_nvisc_core_v02_with_mem_domains__DOT__memsys_resp_rdata_w;
        QData/*63:0*/ tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__data_req_paddr_w;
        QData/*63:0*/ tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__data_req_wdata_w;
        VlWide<5>/*130:0*/ tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__data_req_id_w;
        QData/*63:0*/ tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__exec_req_paddr_w;
        QData/*63:0*/ tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__exec_req_wdata_w;
        QData/*63:0*/ tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__livehot_req_paddr_w;
        QData/*63:0*/ tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__livehot_req_wdata_w;
        QData/*63:0*/ tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__data_resp_rdata_w;
        QData/*63:0*/ tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__exec_resp_rdata_w;
        QData/*63:0*/ tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__livehot_resp_rdata_w;
        QData/*63:0*/ tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_data_lane__DOT__l1d_mem_req_paddr_w;
        QData/*63:0*/ tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_data_lane__DOT__l1d_mem_req_wdata_w;
        QData/*63:0*/ tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_data_lane__DOT__cache3d_resp_rdata_w;
        QData/*63:0*/ tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_data_lane__DOT__u_l1d__DOT__miss_tag_q;
        QData/*63:0*/ tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_data_lane__DOT__u_3d_dram__DOT__cache_mem_req_paddr_w;
        QData/*63:0*/ tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_data_lane__DOT__u_3d_dram__DOT__cache_mem_req_wdata_w;
        QData/*63:0*/ tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_data_lane__DOT__u_3d_dram__DOT__dram_resp_rdata_w;
        QData/*63:0*/ tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_data_lane__DOT__u_3d_dram__DOT__u_3d_cache__DOT__pending_tag_q;
        QData/*63:0*/ tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_data_lane__DOT__u_3d_dram__DOT__u_dram__DOT__pending_wdata_q;
        QData/*63:0*/ tb_nvisc_core_v02_with_mem_domains__DOT__u_core__DOT__mmu_resp_vaddr_w;
        QData/*63:0*/ tb_nvisc_core_v02_with_mem_domains__DOT__u_core__DOT__mmu_resp_paddr_w;
        QData/*63:0*/ tb_nvisc_core_v02_with_mem_domains__DOT__u_core__DOT__mmu_resp_wdata_w;
        QData/*63:0*/ tb_nvisc_core_v02_with_mem_domains__DOT__u_core__DOT__rs1_data_w;
        QData/*63:0*/ tb_nvisc_core_v02_with_mem_domains__DOT__u_core__DOT__rs2_data_w;
        QData/*63:0*/ tb_nvisc_core_v02_with_mem_domains__DOT__u_core__DOT__rf_wdata_w;
        QData/*63:0*/ tb_nvisc_core_v02_with_mem_domains__DOT__u_core__DOT__u_pc__DOT__pc_q;
        VlWide<8>/*227:0*/ tb_nvisc_core_v02_with_mem_domains__DOT__u_core__DOT__u_if__DOT__fetch_q;
        VlWide<11>/*334:0*/ tb_nvisc_core_v02_with_mem_domains__DOT__u_core__DOT__u_dec__DOT__dec;
        QData/*63:0*/ tb_nvisc_core_v02_with_mem_domains__DOT__u_core__DOT__u_alu__DOT__result_c;
        VlWide<12>/*377:0*/ tb_nvisc_core_v02_with_mem_domains__DOT__u_core__DOT__u_lsu__DOT__req_q;
        VlUnpacked<QData/*63:0*/, 16> tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_data_lane__DOT__u_l1d__DOT__tag_q;
        VlUnpacked<QData/*63:0*/, 16> tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_data_lane__DOT__u_l1d__DOT__data_q;
        VlUnpacked<CData/*0:0*/, 16> tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_data_lane__DOT__u_3d_dram__DOT__u_3d_cache__DOT__valid_q;
        VlUnpacked<QData/*63:0*/, 16> tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_data_lane__DOT__u_3d_dram__DOT__u_3d_cache__DOT__tag_q;
        VlUnpacked<QData/*63:0*/, 16> tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_data_lane__DOT__u_3d_dram__DOT__u_3d_cache__DOT__data_q;
        VlUnpacked<QData/*63:0*/, 1024> tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_data_lane__DOT__u_3d_dram__DOT__u_dram__DOT__mem_q;
        VlUnpacked<QData/*63:0*/, 256> tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_execmem__DOT__mem_q;
        VlUnpacked<QData/*63:0*/, 256> tb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_livehot__DOT__mem_q;
        VlUnpacked<QData/*63:0*/, 32> tb_nvisc_core_v02_with_mem_domains__DOT__u_core__DOT__u_rf__DOT__regs_q;
        VlUnpacked<QData/*63:0*/, 1> __VstlTriggered;
        VlUnpacked<QData/*63:0*/, 1> __VicoTriggered;
        VlUnpacked<QData/*63:0*/, 1> __VactTriggered;
        VlUnpacked<QData/*63:0*/, 1> __VnbaTriggered;
    };
    VlNBACommitQueue<VlUnpacked<QData/*63:0*/, 1024>, false, QData/*63:0*/, 1> __VdlyCommitQueuetb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_data_lane__DOT__u_3d_dram__DOT__u_dram__DOT__mem_q;
    VlNBACommitQueue<VlUnpacked<QData/*63:0*/, 256>, false, QData/*63:0*/, 1> __VdlyCommitQueuetb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_execmem__DOT__mem_q;
    VlNBACommitQueue<VlUnpacked<QData/*63:0*/, 256>, false, QData/*63:0*/, 1> __VdlyCommitQueuetb_nvisc_core_v02_with_mem_domains__DOT__u_memsys__DOT__u_livehot__DOT__mem_q;

    // INTERNAL VARIABLES
    Vtb_nvisc_core_v02_with_mem_domains__Syms* vlSymsp;
    const char* vlNamep;

    // CONSTRUCTORS
    Vtb_nvisc_core_v02_with_mem_domains___024root(Vtb_nvisc_core_v02_with_mem_domains__Syms* symsp, const char* namep);
    ~Vtb_nvisc_core_v02_with_mem_domains___024root();
    VL_UNCOPYABLE(Vtb_nvisc_core_v02_with_mem_domains___024root);

    // INTERNAL METHODS
    void __Vconfigure(bool first);
};


#endif  // guard
