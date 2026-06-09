package nexus_v_soc_verification_pkg;
    typedef enum logic [3:0] {
        EVT_STATE_SNAPSHOT,
        EVT_BRANCH_CREATE,
        EVT_COW_REMAP,
        EVT_ROLLBACK,
        EVT_ROUTE_DONE,
        EVT_TENSOR_JOB_DONE,
        EVT_QSYNC,
        EVT_AEGIS_AUDIT_ALLOW,
        EVT_COMMIT,
        EVT_MINREP
    } nvisc_soc_event_e;
endpackage
