// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Model implementation (design independent parts)

#include "Vtb_nvisc_core_v02_with_mem_domains__pch.h"

//============================================================
// Constructors

Vtb_nvisc_core_v02_with_mem_domains::Vtb_nvisc_core_v02_with_mem_domains(VerilatedContext* _vcontextp__, const char* _vcname__)
    : VerilatedModel{*_vcontextp__}
    , vlSymsp{new Vtb_nvisc_core_v02_with_mem_domains__Syms(contextp(), _vcname__, this)}
    , clk{vlSymsp->TOP.clk}
    , rst_n{vlSymsp->TOP.rst_n}
    , imem_resp_valid_i{vlSymsp->TOP.imem_resp_valid_i}
    , imem_resp_fault_i{vlSymsp->TOP.imem_resp_fault_i}
    , thread_id_i{vlSymsp->TOP.thread_id_i}
    , privilege_i{vlSymsp->TOP.privilege_i}
    , lsu_size_bytes_i{vlSymsp->TOP.lsu_size_bytes_i}
    , dbg_rf_we_i{vlSymsp->TOP.dbg_rf_we_i}
    , dbg_rf_waddr_i{vlSymsp->TOP.dbg_rf_waddr_i}
    , stall_i{vlSymsp->TOP.stall_i}
    , flush_i{vlSymsp->TOP.flush_i}
    , redirect_valid_i{vlSymsp->TOP.redirect_valid_i}
    , branch_taken_i{vlSymsp->TOP.branch_taken_i}
    , trap_valid_i{vlSymsp->TOP.trap_valid_i}
    , rollback_redirect_i{vlSymsp->TOP.rollback_redirect_i}
    , mem_domain_override_valid_i{vlSymsp->TOP.mem_domain_override_valid_i}
    , mem_domain_override_i{vlSymsp->TOP.mem_domain_override_i}
    , memdom_csr_valid_i{vlSymsp->TOP.memdom_csr_valid_i}
    , memdom_csr_write_i{vlSymsp->TOP.memdom_csr_write_i}
    , memdom_csr_read_i{vlSymsp->TOP.memdom_csr_read_i}
    , memdom_csr_resp_valid_o{vlSymsp->TOP.memdom_csr_resp_valid_o}
    , memdom_csr_fault_o{vlSymsp->TOP.memdom_csr_fault_o}
    , imem_req_valid_o{vlSymsp->TOP.imem_req_valid_o}
    , pc_valid_o{vlSymsp->TOP.pc_valid_o}
    , fetch_valid_o{vlSymsp->TOP.fetch_valid_o}
    , decode_class_o{vlSymsp->TOP.decode_class_o}
    , alu_result_valid_o{vlSymsp->TOP.alu_result_valid_o}
    , alu_zero_o{vlSymsp->TOP.alu_zero_o}
    , alu_negative_o{vlSymsp->TOP.alu_negative_o}
    , alu_overflow_o{vlSymsp->TOP.alu_overflow_o}
    , branch_taken_internal_o{vlSymsp->TOP.branch_taken_internal_o}
    , alu_valid_o{vlSymsp->TOP.alu_valid_o}
    , lsu_valid_o{vlSymsp->TOP.lsu_valid_o}
    , csr_valid_o{vlSymsp->TOP.csr_valid_o}
    , branch_valid_o{vlSymsp->TOP.branch_valid_o}
    , mem_req_valid_o{vlSymsp->TOP.mem_req_valid_o}
    , mem_req_is_read_o{vlSymsp->TOP.mem_req_is_read_o}
    , mem_req_is_write_o{vlSymsp->TOP.mem_req_is_write_o}
    , mem_req_size_bytes_o{vlSymsp->TOP.mem_req_size_bytes_o}
    , mem_req_domain_o{vlSymsp->TOP.mem_req_domain_o}
    , memsys_resp_valid_o{vlSymsp->TOP.memsys_resp_valid_o}
    , memsys_resp_write_ack_o{vlSymsp->TOP.memsys_resp_write_ack_o}
    , memsys_fault_o{vlSymsp->TOP.memsys_fault_o}
    , dbg_data_route_valid_o{vlSymsp->TOP.dbg_data_route_valid_o}
    , dbg_exec_route_valid_o{vlSymsp->TOP.dbg_exec_route_valid_o}
    , dbg_livehot_route_valid_o{vlSymsp->TOP.dbg_livehot_route_valid_o}
    , load_wb_valid_o{vlSymsp->TOP.load_wb_valid_o}
    , core_fault_o{vlSymsp->TOP.core_fault_o}
    , imem_resp_fault_code_i{vlSymsp->TOP.imem_resp_fault_code_i}
    , aegis_policy_id_i{vlSymsp->TOP.aegis_policy_id_i}
    , memdom_csr_addr_i{vlSymsp->TOP.memdom_csr_addr_i}
    , memdom_csr_fault_code_o{vlSymsp->TOP.memdom_csr_fault_code_o}
    , memsys_fault_code_o{vlSymsp->TOP.memsys_fault_code_o}
    , core_fault_code_o{vlSymsp->TOP.core_fault_code_o}
    , imem_resp_instr_i{vlSymsp->TOP.imem_resp_instr_i}
    , branch_id_i{vlSymsp->TOP.branch_id_i}
    , state_id_i{vlSymsp->TOP.state_id_i}
    , commit_id_i{vlSymsp->TOP.commit_id_i}
    , fetch_instr_o{vlSymsp->TOP.fetch_instr_o}
    , lsu_base_value_i{vlSymsp->TOP.lsu_base_value_i}
    , lsu_store_data_i{vlSymsp->TOP.lsu_store_data_i}
    , dbg_rf_wdata_i{vlSymsp->TOP.dbg_rf_wdata_i}
    , redirect_pc_i{vlSymsp->TOP.redirect_pc_i}
    , branch_target_i{vlSymsp->TOP.branch_target_i}
    , trap_vector_i{vlSymsp->TOP.trap_vector_i}
    , rollback_pc_i{vlSymsp->TOP.rollback_pc_i}
    , memdom_csr_wdata_i{vlSymsp->TOP.memdom_csr_wdata_i}
    , memdom_csr_rdata_o{vlSymsp->TOP.memdom_csr_rdata_o}
    , imem_req_addr_o{vlSymsp->TOP.imem_req_addr_o}
    , pc_o{vlSymsp->TOP.pc_o}
    , dbg_rf_r1_o{vlSymsp->TOP.dbg_rf_r1_o}
    , dbg_rf_r2_o{vlSymsp->TOP.dbg_rf_r2_o}
    , dbg_rf_r3_o{vlSymsp->TOP.dbg_rf_r3_o}
    , alu_result_o{vlSymsp->TOP.alu_result_o}
    , branch_target_internal_o{vlSymsp->TOP.branch_target_internal_o}
    , mem_req_vaddr_o{vlSymsp->TOP.mem_req_vaddr_o}
    , mem_req_paddr_o{vlSymsp->TOP.mem_req_paddr_o}
    , mem_req_wdata_o{vlSymsp->TOP.mem_req_wdata_o}
    , memsys_resp_rdata_o{vlSymsp->TOP.memsys_resp_rdata_o}
    , load_wb_data_o{vlSymsp->TOP.load_wb_data_o}
    , rootp{&(vlSymsp->TOP)}
{
    // Register model with the context
    contextp()->addModel(this);
}

Vtb_nvisc_core_v02_with_mem_domains::Vtb_nvisc_core_v02_with_mem_domains(const char* _vcname__)
    : Vtb_nvisc_core_v02_with_mem_domains(Verilated::threadContextp(), _vcname__)
{
}

//============================================================
// Destructor

Vtb_nvisc_core_v02_with_mem_domains::~Vtb_nvisc_core_v02_with_mem_domains() {
    delete vlSymsp;
}

//============================================================
// Evaluation function

#ifdef VL_DEBUG
void Vtb_nvisc_core_v02_with_mem_domains___024root___eval_debug_assertions(Vtb_nvisc_core_v02_with_mem_domains___024root* vlSelf);
#endif  // VL_DEBUG
void Vtb_nvisc_core_v02_with_mem_domains___024root___eval_static(Vtb_nvisc_core_v02_with_mem_domains___024root* vlSelf);
void Vtb_nvisc_core_v02_with_mem_domains___024root___eval_initial(Vtb_nvisc_core_v02_with_mem_domains___024root* vlSelf);
void Vtb_nvisc_core_v02_with_mem_domains___024root___eval_settle(Vtb_nvisc_core_v02_with_mem_domains___024root* vlSelf);
void Vtb_nvisc_core_v02_with_mem_domains___024root___eval(Vtb_nvisc_core_v02_with_mem_domains___024root* vlSelf);

void Vtb_nvisc_core_v02_with_mem_domains::eval_step() {
    VL_DEBUG_IF(VL_DBG_MSGF("+++++TOP Evaluate Vtb_nvisc_core_v02_with_mem_domains::eval_step\n"); );
#ifdef VL_DEBUG
    // Debug assertions
    Vtb_nvisc_core_v02_with_mem_domains___024root___eval_debug_assertions(&(vlSymsp->TOP));
#endif  // VL_DEBUG
    vlSymsp->__Vm_deleter.deleteAll();
    if (VL_UNLIKELY(!vlSymsp->__Vm_didInit)) {
        VL_DEBUG_IF(VL_DBG_MSGF("+ Initial\n"););
        Vtb_nvisc_core_v02_with_mem_domains___024root___eval_static(&(vlSymsp->TOP));
        Vtb_nvisc_core_v02_with_mem_domains___024root___eval_initial(&(vlSymsp->TOP));
        Vtb_nvisc_core_v02_with_mem_domains___024root___eval_settle(&(vlSymsp->TOP));
        vlSymsp->__Vm_didInit = true;
    }
    VL_DEBUG_IF(VL_DBG_MSGF("+ Eval\n"););
    Vtb_nvisc_core_v02_with_mem_domains___024root___eval(&(vlSymsp->TOP));
    // Evaluate cleanup
    Verilated::endOfEval(vlSymsp->__Vm_evalMsgQp);
}

//============================================================
// Events and timing
bool Vtb_nvisc_core_v02_with_mem_domains::eventsPending() { return false; }

uint64_t Vtb_nvisc_core_v02_with_mem_domains::nextTimeSlot() {
    VL_FATAL_MT(__FILE__, __LINE__, "", "No delays in the design");
    return 0;
}

//============================================================
// Utilities

const char* Vtb_nvisc_core_v02_with_mem_domains::name() const {
    return vlSymsp->name();
}

//============================================================
// Invoke final blocks

void Vtb_nvisc_core_v02_with_mem_domains___024root___eval_final(Vtb_nvisc_core_v02_with_mem_domains___024root* vlSelf);

VL_ATTR_COLD void Vtb_nvisc_core_v02_with_mem_domains::final() {
    contextp()->executingFinal(true);
    Vtb_nvisc_core_v02_with_mem_domains___024root___eval_final(&(vlSymsp->TOP));
    contextp()->executingFinal(false);
}

//============================================================
// Implementations of abstract methods from VerilatedModel

const char* Vtb_nvisc_core_v02_with_mem_domains::hierName() const { return vlSymsp->name(); }
const char* Vtb_nvisc_core_v02_with_mem_domains::modelName() const { return "Vtb_nvisc_core_v02_with_mem_domains"; }
unsigned Vtb_nvisc_core_v02_with_mem_domains::threads() const { return 1; }
void Vtb_nvisc_core_v02_with_mem_domains::prepareClone() const { contextp()->prepareClone(); }
void Vtb_nvisc_core_v02_with_mem_domains::atClone() const {
    contextp()->threadPoolpOnClone();
}
