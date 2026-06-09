`timescale 1ns / 1ps

package nvisc_core_v02_pkg;

    // -------------------------------------------------------------------------
    // Nexus-V Core v0.2 baseline constants
    // -------------------------------------------------------------------------
    parameter int NV_CORE_ID_W      = 8;
    parameter int NV_THREAD_ID_W    = 8;
    parameter int NV_BRANCH_ID_W    = 32;
    parameter int NV_STATE_ID_W     = 32;
    parameter int NV_COMMIT_ID_W    = 32;
    parameter int NV_PRIV_W         = 3;
    parameter int NV_POLICY_ID_W    = 16;

    parameter int NV_XLEN           = 64;
    parameter int NV_INSTR_W        = 32;
    parameter int NV_REG_ADDR_W     = 5;
    parameter logic [63:0] NV_RESET_VECTOR = 64'h0000_0000_0000_0000;

    // -------------------------------------------------------------------------
    // Privilege levels
    // -------------------------------------------------------------------------
    typedef enum logic [NV_PRIV_W-1:0] {
        NV_PRIV_USER      = 3'd0,
        NV_PRIV_SUPERVISOR= 3'd1,
        NV_PRIV_MACHINE   = 3'd2,
        NV_PRIV_AEGIS     = 3'd3,
        NV_PRIV_DEBUG     = 3'd4
    } nvisc_priv_e;

    // -------------------------------------------------------------------------
    // Instruction classes
    // -------------------------------------------------------------------------
    typedef enum logic [7:0] {
        NV_ICLASS_NOP      = 8'd0,
        NV_ICLASS_ALU      = 8'd1,
        NV_ICLASS_LOAD     = 8'd2,
        NV_ICLASS_STORE    = 8'd3,
        NV_ICLASS_BRANCH   = 8'd4,
        NV_ICLASS_CSR      = 8'd5,
        NV_ICLASS_VECTOR   = 8'd6,
        NV_ICLASS_TENSOR   = 8'd7,
        NV_ICLASS_ROUTE    = 8'd8,
        NV_ICLASS_RSM      = 8'd9,
        NV_ICLASS_AEGIS    = 8'd10,
        NV_ICLASS_QUANTUM  = 8'd11,
        NV_ICLASS_SYSTEM   = 8'd12,
        NV_ICLASS_ILLEGAL  = 8'hFF
    } nvisc_instr_class_e;


    // -------------------------------------------------------------------------
    // ALU operation encoding
    // -------------------------------------------------------------------------
    typedef enum logic [2:0] {
        NV_ALU_ADD = 3'd0,
        NV_ALU_SUB = 3'd1,
        NV_ALU_AND = 3'd2,
        NV_ALU_OR  = 3'd3,
        NV_ALU_XOR = 3'd4,
        NV_ALU_SLT = 3'd5
    } nvisc_alu_op_e;

    // -------------------------------------------------------------------------
    // Four-domain memory model
    // -------------------------------------------------------------------------
    typedef enum logic [2:0] {
        NV_MEM_INSTRUCTION = 3'd0,
        NV_MEM_DATA        = 3'd1,
        NV_MEM_EXECUTION   = 3'd2,
        NV_MEM_LIVE_HOT    = 3'd3,
        NV_MEM_RSM_PAGE    = 3'd4,
        NV_MEM_AEGIS_SEC   = 3'd5,
        NV_MEM_TENSOR_SCR  = 3'd6,
        NV_MEM_QUANTUM     = 3'd7
    } nvisc_mem_domain_e;

    // -------------------------------------------------------------------------
    // Core identity metadata
    // -------------------------------------------------------------------------
    typedef struct packed {
        logic [NV_CORE_ID_W-1:0]   core_id;
        logic [NV_THREAD_ID_W-1:0] thread_id;
        logic [NV_BRANCH_ID_W-1:0] branch_id;
        logic [NV_STATE_ID_W-1:0]  state_id;
        logic [NV_COMMIT_ID_W-1:0] commit_id;
        nvisc_priv_e              privilege;
        logic [NV_POLICY_ID_W-1:0] aegis_policy_id;
    } nvisc_exec_identity_t;

    // -------------------------------------------------------------------------
    // Fetch packet
    // -------------------------------------------------------------------------
    typedef struct packed {
        logic                      valid;
        logic [63:0]               pc;
        logic [NV_INSTR_W-1:0]     instr;
        nvisc_exec_identity_t      id;
    } nvisc_fetch_packet_t;

    // -------------------------------------------------------------------------
    // Decoded instruction packet
    // -------------------------------------------------------------------------
    typedef struct packed {
        logic                      valid;
        logic [63:0]               pc;
        logic [NV_INSTR_W-1:0]     instr;

        nvisc_instr_class_e        instr_class;
        nvisc_alu_op_e             alu_op;

        logic [6:0]                opcode;
        logic [NV_REG_ADDR_W-1:0]  rd;
        logic [NV_REG_ADDR_W-1:0]  rs1;
        logic [NV_REG_ADDR_W-1:0]  rs2;
        logic [63:0]               imm;

        logic                      reg_write;
        logic                      mem_read;
        logic                      mem_write;
        logic                      csr_read;
        logic                      csr_write;
        logic                      branch;
        logic                      illegal;

        nvisc_mem_domain_e         mem_domain;
        nvisc_exec_identity_t      id;
    } nvisc_decode_packet_t;

    // -------------------------------------------------------------------------
    // Memory request / response
    // -------------------------------------------------------------------------
    typedef struct packed {
        logic                      valid;
        logic [31:0]               tx_id;
        logic                      is_read;
        logic                      is_write;
        logic                      is_atomic;
        logic [63:0]               vaddr;
        logic [63:0]               paddr;
        logic [63:0]               wdata;
        logic [7:0]                size_bytes;
        logic [7:0]                burst_len;
        nvisc_mem_domain_e         mem_domain;
        nvisc_exec_identity_t      id;
    } nvisc_mem_req_t;

    typedef struct packed {
        logic                      valid;
        logic [31:0]               tx_id;
        logic [63:0]               rdata;
        logic                      fault;
        logic [15:0]               fault_code;
        nvisc_exec_identity_t      id;
    } nvisc_mem_resp_t;

    // -------------------------------------------------------------------------
    // CSR addresses
    // -------------------------------------------------------------------------
    localparam logic [11:0] CSR_CORE_ID       = 12'h000;
    localparam logic [11:0] CSR_THREAD_ID     = 12'h001;
    localparam logic [11:0] CSR_BRANCH_ID_LO  = 12'h002;
    localparam logic [11:0] CSR_STATE_ID_LO   = 12'h003;
    localparam logic [11:0] CSR_COMMIT_ID_LO  = 12'h004;
    localparam logic [11:0] CSR_PRIVILEGE     = 12'h005;
    localparam logic [11:0] CSR_AEGIS_POLICY  = 12'h006;
    localparam logic [11:0] CSR_STATUS        = 12'h007;

endpackage
