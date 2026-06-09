// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Primary model header
//
// This header should be included by all source files instantiating the design.
// The class here is then constructed to instantiate the design.
// See the Verilator manual for examples.

#ifndef VERILATED_VTB_NVISC_CORE_V02_WITH_MEM_DOMAINS_H_
#define VERILATED_VTB_NVISC_CORE_V02_WITH_MEM_DOMAINS_H_  // guard

#include "verilated.h"

class Vtb_nvisc_core_v02_with_mem_domains__Syms;
class Vtb_nvisc_core_v02_with_mem_domains___024root;

// This class is the main interface to the Verilated model
class alignas(VL_CACHE_LINE_BYTES) Vtb_nvisc_core_v02_with_mem_domains VL_NOT_FINAL : public VerilatedModel {
  private:
    // Symbol table holding complete model state (owned by this class)
    Vtb_nvisc_core_v02_with_mem_domains__Syms* const vlSymsp;

  public:

    // CONSTEXPR CAPABILITIES
    // Verilated with --trace?
    static constexpr bool traceCapable = false;

    // PORTS
    // The application code writes and reads these signals to
    // propagate new values into/out from the Verilated model.
    VL_IN8(&clk,0,0);
    VL_IN8(&rst_n,0,0);
    VL_IN8(&imem_resp_valid_i,0,0);
    VL_IN8(&imem_resp_fault_i,0,0);
    VL_IN8(&thread_id_i,7,0);
    VL_IN8(&privilege_i,2,0);
    VL_IN8(&lsu_size_bytes_i,7,0);
    VL_IN8(&dbg_rf_we_i,0,0);
    VL_IN8(&dbg_rf_waddr_i,4,0);
    VL_IN8(&stall_i,0,0);
    VL_IN8(&flush_i,0,0);
    VL_IN8(&redirect_valid_i,0,0);
    VL_IN8(&branch_taken_i,0,0);
    VL_IN8(&trap_valid_i,0,0);
    VL_IN8(&rollback_redirect_i,0,0);
    VL_IN8(&mem_domain_override_valid_i,0,0);
    VL_IN8(&mem_domain_override_i,2,0);
    VL_IN8(&memdom_csr_valid_i,0,0);
    VL_IN8(&memdom_csr_write_i,0,0);
    VL_IN8(&memdom_csr_read_i,0,0);
    VL_OUT8(&memdom_csr_resp_valid_o,0,0);
    VL_OUT8(&memdom_csr_fault_o,0,0);
    VL_OUT8(&imem_req_valid_o,0,0);
    VL_OUT8(&pc_valid_o,0,0);
    VL_OUT8(&fetch_valid_o,0,0);
    VL_OUT8(&decode_class_o,7,0);
    VL_OUT8(&alu_result_valid_o,0,0);
    VL_OUT8(&alu_zero_o,0,0);
    VL_OUT8(&alu_negative_o,0,0);
    VL_OUT8(&alu_overflow_o,0,0);
    VL_OUT8(&branch_taken_internal_o,0,0);
    VL_OUT8(&alu_valid_o,0,0);
    VL_OUT8(&lsu_valid_o,0,0);
    VL_OUT8(&csr_valid_o,0,0);
    VL_OUT8(&branch_valid_o,0,0);
    VL_OUT8(&mem_req_valid_o,0,0);
    VL_OUT8(&mem_req_is_read_o,0,0);
    VL_OUT8(&mem_req_is_write_o,0,0);
    VL_OUT8(&mem_req_size_bytes_o,7,0);
    VL_OUT8(&mem_req_domain_o,2,0);
    VL_OUT8(&memsys_resp_valid_o,0,0);
    VL_OUT8(&memsys_resp_write_ack_o,0,0);
    VL_OUT8(&memsys_fault_o,0,0);
    VL_OUT8(&dbg_data_route_valid_o,0,0);
    VL_OUT8(&dbg_exec_route_valid_o,0,0);
    VL_OUT8(&dbg_livehot_route_valid_o,0,0);
    VL_OUT8(&load_wb_valid_o,0,0);
    VL_OUT8(&core_fault_o,0,0);
    VL_IN16(&imem_resp_fault_code_i,15,0);
    VL_IN16(&aegis_policy_id_i,15,0);
    VL_IN16(&memdom_csr_addr_i,11,0);
    VL_OUT16(&memdom_csr_fault_code_o,15,0);
    VL_OUT16(&memsys_fault_code_o,15,0);
    VL_OUT16(&core_fault_code_o,15,0);
    VL_IN(&imem_resp_instr_i,31,0);
    VL_IN(&branch_id_i,31,0);
    VL_IN(&state_id_i,31,0);
    VL_IN(&commit_id_i,31,0);
    VL_OUT(&fetch_instr_o,31,0);
    VL_IN64(&lsu_base_value_i,63,0);
    VL_IN64(&lsu_store_data_i,63,0);
    VL_IN64(&dbg_rf_wdata_i,63,0);
    VL_IN64(&redirect_pc_i,63,0);
    VL_IN64(&branch_target_i,63,0);
    VL_IN64(&trap_vector_i,63,0);
    VL_IN64(&rollback_pc_i,63,0);
    VL_IN64(&memdom_csr_wdata_i,63,0);
    VL_OUT64(&memdom_csr_rdata_o,63,0);
    VL_OUT64(&imem_req_addr_o,63,0);
    VL_OUT64(&pc_o,63,0);
    VL_OUT64(&dbg_rf_r1_o,63,0);
    VL_OUT64(&dbg_rf_r2_o,63,0);
    VL_OUT64(&dbg_rf_r3_o,63,0);
    VL_OUT64(&alu_result_o,63,0);
    VL_OUT64(&branch_target_internal_o,63,0);
    VL_OUT64(&mem_req_vaddr_o,63,0);
    VL_OUT64(&mem_req_paddr_o,63,0);
    VL_OUT64(&mem_req_wdata_o,63,0);
    VL_OUT64(&memsys_resp_rdata_o,63,0);
    VL_OUT64(&load_wb_data_o,63,0);

    // CELLS
    // Public to allow access to /* verilator public */ items.
    // Otherwise the application code can consider these internals.

    // Root instance pointer to allow access to model internals,
    // including inlined /* verilator public_flat_* */ items.
    Vtb_nvisc_core_v02_with_mem_domains___024root* const rootp;

    // CONSTRUCTORS
    /// Construct the model; called by application code
    /// If contextp is null, then the model will use the default global context
    /// If name is "", then makes a wrapper with a
    /// single model invisible with respect to DPI scope names.
    explicit Vtb_nvisc_core_v02_with_mem_domains(VerilatedContext* contextp, const char* name = "TOP");
    explicit Vtb_nvisc_core_v02_with_mem_domains(const char* name = "TOP");
    /// Destroy the model; called (often implicitly) by application code
    virtual ~Vtb_nvisc_core_v02_with_mem_domains();
  private:
    VL_UNCOPYABLE(Vtb_nvisc_core_v02_with_mem_domains);  ///< Copying not allowed

  public:
    // API METHODS
    /// Evaluate the model.  Application must call when inputs change.
    void eval() { eval_step(); }
    /// Evaluate when calling multiple units/models per time step.
    void eval_step();
    /// Evaluate at end of a timestep for tracing, when using eval_step().
    /// Application must call after all eval() and before time changes.
    void eval_end_step() {}
    /// Simulation complete, run final blocks.  Application must call on completion.
    void final();
    /// Are there scheduled events to handle?
    bool eventsPending();
    /// Returns time at next time slot. Aborts if !eventsPending()
    uint64_t nextTimeSlot();
    /// Trace signals in the model; called by application code
    void trace(VerilatedTraceBaseC* tfp, int levels, int options = 0) { contextp()->trace(tfp, levels, options); }
    /// Retrieve name of this model instance (as passed to constructor).
    const char* name() const;

    // Abstract methods from VerilatedModel
    const char* hierName() const override final;
    const char* modelName() const override final;
    unsigned threads() const override final;
    /// Prepare for cloning the model at the process level (e.g. fork in Linux)
    /// Release necessary resources. Called before cloning.
    void prepareClone() const;
    /// Re-init after cloning the model at the process level (e.g. fork in Linux)
    /// Re-allocate necessary resources. Called after cloning.
    void atClone() const;
  private:
    // Internal functions - trace registration
    void traceBaseModel(VerilatedTraceBaseC* tfp, int levels, int options);
};

#endif  // guard
