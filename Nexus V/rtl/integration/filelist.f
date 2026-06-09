// Nexus-V SoC integration filelist.
// Compile packages before modules. If your simulator dislikes duplicate package names from older phase drops,
// compile the latest package versions only or merge package definitions manually.
+incdir+./phase0
+incdir+./rsm_phase1
+incdir+./rsm_rollback
+incdir+./aegis_phase1
+incdir+./topology_phase3
+incdir+./tensor_phase4
+incdir+./quantum_phase5
+incdir+./integration

./phase0/nvisc_pkg.sv
./rsm_rollback/nvisc_rsm_pkg.sv
./aegis_phase1/nvisc_aegis_pkg.sv
./topology_phase3/nvisc_topology_pkg.sv
./tensor_phase4/nvisc_tensor_pkg.sv
./quantum_phase5/nvisc_quantum_pkg.sv
./integration/nexus_v_soc_pkg.sv

./phase0/nvisc_regfile.sv
./phase0/nvisc_alu_slice.sv
./phase0/nvisc_state_token_if.sv
./phase0/nvisc_route_req_arbiter.sv
./phase0/nvisc_routing_unit.sv
./phase0/nvisc_rhombic_dodeca_router_v0.sv
./phase0/nexus_v_phase0_core.sv

./rsm_rollback/nvisc_rsm_delta_log.sv
./rsm_rollback/nvisc_rsm_rollback_fsm.sv
./rsm_rollback/nvisc_rsm_controller_phase1_rollback.sv

./aegis_phase1/nvisc_aegis_trust_telemetry_aggregator.sv
./aegis_phase1/nvisc_aegis_commit_gate.sv
./aegis_phase1/nvisc_aegis_attest_token_unit.sv
./aegis_phase1/nvisc_aegis_minrep_generator.sv
./aegis_phase1/nvisc_aegis_enclave.sv

./topology_phase3/nvisc_poly_crossbar.sv
./topology_phase3/nvisc_route_compute_unit.sv
./topology_phase3/nvisc_router_node.sv
./topology_phase3/nvisc_topology_token_table.sv
./topology_phase3/nvisc_rhombic_dodeca_fabric_v0.sv

./tensor_phase4/nvisc_tensor_descriptor_table.sv
./tensor_phase4/nvisc_tensor_scratchpad.sv
./tensor_phase4/nvisc_tensor_tile_scheduler.sv
./tensor_phase4/nvisc_tensor_compute_unit.sv
./tensor_phase4/nvisc_tensor_node_array_16.sv
./tensor_phase4/nvisc_tensor_route_adapter.sv
./tensor_phase4/nvisc_tensor_reduce_fold_unit.sv
./tensor_phase4/nvisc_tensor_numeric_integrity_unit.sv
./tensor_phase4/nvisc_tensor_dispatch_unit.sv
./tensor_phase4/nvisc_tensor_npu_engine.sv

./quantum_phase5/nvisc_qreg_file.sv
./quantum_phase5/nvisc_qsim_state_bank.sv
./quantum_phase5/nvisc_quantum_gate_unit.sv
./quantum_phase5/nvisc_quantum_measure_unit.sv
./quantum_phase5/nvisc_quantum_token_table.sv
./quantum_phase5/nvisc_quantum_collapse_register.sv
./quantum_phase5/nvisc_qhw_bridge_stub.sv
./quantum_phase5/nvisc_quantum_control_fsm.sv
./quantum_phase5/nvisc_quantum_domain_engine.sv

./integration/nexus_v_soc.sv
./integration/tb_nexus_v_soc_smoke.sv
