#!/usr/bin/env bash
set -euo pipefail

CFLAGS="-std=gnu++17 -I../sim"
LDFLAGS="-lstdc++"

run_core_test() {
  local test_cpp="$1"
  local label="$2"

  echo
  echo "========== ${label} =========="
  rm -rf obj_dir

  CXX=/ucrt64/bin/g++ verilator \
    -sv -f filelist_core_v02.f \
    --top-module nvisc_core_v02 \
    --cc --exe "${test_cpp}" --build \
    -Wno-fatal \
    -CFLAGS "${CFLAGS}" \
    -LDFLAGS "${LDFLAGS}"

  ./obj_dir/Vnvisc_core_v02
}

run_wrapper_test() {
  local top="$1"
  local binary="$2"
  local test_cpp="$3"
  local label="$4"

  echo
  echo "========== ${label} =========="
  rm -rf obj_dir

  CXX=/ucrt64/bin/g++ verilator \
    -sv -f filelist_core_v02.f \
    --top-module "${top}" \
    --cc --exe "${test_cpp}" --build \
    -Wno-fatal \
    -CFLAGS "${CFLAGS}" \
    -LDFLAGS "${LDFLAGS}"

  ./obj_dir/"${binary}"
}

run_core_test sim/sim_core_v02_smoke.cpp     "CORE SMOKE"
run_core_test sim/sim_core_v02_alu_ops.cpp   "ALU OPS"
run_core_test sim/sim_core_v02_branch.cpp    "BRANCH"
run_core_test sim/sim_core_v02_load_wb.cpp   "LOAD WRITEBACK"
run_core_test sim/sim_core_v02_store.cpp     "STORE DATAPATH"
run_core_test sim/sim_core_v02_mmu_fault.cpp "MMU FAULT"

run_wrapper_test \
  tb_nvisc_core_v02_with_dmem \
  Vtb_nvisc_core_v02_with_dmem \
  sim/sim_core_v02_with_dmem.cpp \
  "CORE + DMEM"

run_wrapper_test \
  tb_nvisc_core_v02_with_l1i_l1d_dmem \
  Vtb_nvisc_core_v02_with_l1i_l1d_dmem \
  sim/sim_core_v02_with_l1i_l1d_dmem.cpp \
  "CORE + L1I + L1D + DMEM"

run_wrapper_test \
  tb_nvisc_core_v02_with_irq \
  Vtb_nvisc_core_v02_with_irq \
  sim/sim_core_v02_irq_redirect.cpp \
  "CORE + IRQ REDIRECT"

run_wrapper_test \
  tb_nvisc_core_v02_with_irq_csr \
  Vtb_nvisc_core_v02_with_irq_csr \
  sim/sim_core_v02_irq_csr_redirect.cpp \
  "CORE + IRQ CSR REDIRECT"

run_wrapper_test \
  tb_nvisc_memory_domain_subsystem \
  Vtb_nvisc_memory_domain_subsystem \
  sim/sim_memory_domain_subsystem.cpp \
  "MEMORY DOMAIN SUBSYSTEM"

run_wrapper_test \
  nvisc_cache_maintenance_csr \
  Vnvisc_cache_maintenance_csr \
  sim/sim_cache_maintenance_csr.cpp \
  "CACHE MAINTENANCE CSR"

run_wrapper_test \
  tb_nvisc_memory_domain_subsystem \
  Vtb_nvisc_memory_domain_subsystem \
  sim/sim_memory_domain_cache_csr_flush.cpp \
  "MEMORY DOMAIN CACHE CSR FLUSH"

run_wrapper_test \
  nvisc_dram_controller_stub \
  Vnvisc_dram_controller_stub \
  sim/sim_dram_controller_stub.cpp \
  "DRAM CONTROLLER"

run_wrapper_test \
  nvisc_3d_cache_stub \
  Vnvisc_3d_cache_stub \
  sim/sim_3d_cache_stub.cpp \
  "3D CACHE"

run_wrapper_test \
  tb_nvisc_3d_cache_with_dram \
  Vtb_nvisc_3d_cache_with_dram \
  sim/sim_3d_cache_with_dram.cpp \
  "3D CACHE + DRAM"

run_wrapper_test \
  tb_nvisc_data_lane_3d_dram \
  Vtb_nvisc_data_lane_3d_dram \
  sim/sim_data_lane_3d_dram.cpp \
  "DATA LANE + 3D + DRAM"

run_wrapper_test \
  tb_nvisc_data_lane_3d_dram \
  Vtb_nvisc_data_lane_3d_dram \
  sim/sim_data_lane_flush_hierarchy.cpp \
  "DATA LANE FLUSH HIERARCHY"

run_wrapper_test \
  tb_nvisc_core_v02_with_mem_domains \
  Vtb_nvisc_core_v02_with_mem_domains \
  sim/sim_core_v02_with_mem_domains.cpp \
  "CORE + MEMORY DOMAINS"

run_wrapper_test \
  tb_nvisc_core_v02_with_mem_domains \
  Vtb_nvisc_core_v02_with_mem_domains \
  sim/sim_core_v02_nondata_domains.cpp \
  "CORE + NON-DATA MEMORY DOMAINS"

echo
echo "========== CORE v0.2 REGRESSION PASS =========="
