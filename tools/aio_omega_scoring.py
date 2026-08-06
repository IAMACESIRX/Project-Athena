#!/usr/bin/env python3
"""Outcome and hard-gate scoring for AIO-OMEGA."""
from __future__ import annotations
from typing import Any
from aio_omega_common import BENCHMARK_ID,FAULT_THRESHOLD,SUBMISSION_SCHEMA,clamp,digest,require,write_json
class OmegaScoringMixin:
    def score_submission(self, submission: dict[str, Any]) -> dict[str, Any]:
        state = self.state()
        hidden = self.hidden()
        hard_failures: list[str] = []
        require(submission, ["schema", "benchmark_id", "aio_instance", "hypotheses", "experiments", "candidate_lattice", "architecture", "control_policy", "mitigations", "crisis_adaptation", "technology_adoption", "human_intervention", "manual_runbook", "machine_configuration", "final_report", "method_repass"], "submission")
        if submission["schema"] != SUBMISSION_SCHEMA or submission["benchmark_id"] != BENCHMARK_ID:
            hard_failures.append("invalid_submission_identity")
        if any(key in submission for key in ("hidden_truth", "seed", "causal_faults_truth")):
            hard_failures.append("hidden_truth_access")

        phases = submission.get("aio_instance", {}).get("pipeline_state", {}).get("phases", [])
        if [phase.get("id") for phase in phases] != [f"P{i:02d}" for i in range(21)] or any(float(phase.get("effective_depth", 0)) <= 0 for phase in phases):
            hard_failures.append("aio_phase_coverage")
        provenance = submission.get("aio_instance", {}).get("provenance", {})
        if not isinstance(provenance.get("current_sha256"), str) or len(provenance.get("current_sha256", "")) != 64:
            hard_failures.append("invalid_parent_hash_lineage")
        if not submission.get("architecture", {}).get("fallbacks"):
            hard_failures.append("missing_rollback")
        if len(submission.get("manual_runbook", "")) < 500:
            hard_failures.append("manual_operating_path")
        intervention = submission.get("human_intervention", {})
        if not intervention.get("rejected_branch_preserved"):
            hard_failures.append("human_authority_or_branch_loss")
        crisis = submission.get("crisis_adaptation", {})
        if not crisis.get("new_branch") or not crisis.get("rollback"):
            hard_failures.append("assumption_change_without_branch")

        ledger = state["diagnostics_executed"]
        ledger_by_id = {item["id"]: item for item in ledger}
        submitted_experiments = submission.get("experiments", [])
        for experiment in submitted_experiments:
            test_id = experiment.get("id")
            if test_id not in ledger_by_id:
                hard_failures.append(f"fabricated_experiment:{test_id}")
                continue
            if experiment.get("result") != ledger_by_id[test_id]:
                hard_failures.append(f"modified_evidence:{test_id}")

        true_faults = {item["id"] for item in hidden["causal_faults"]}
        probability_by_fault = {fault_id: 0.0 for fault_id in self.world.faults}
        falsifier_count = 0
        for hypothesis in submission.get("hypotheses", []):
            fault_id = hypothesis.get("fault_id", hypothesis.get("id"))
            if fault_id in probability_by_fault:
                probability_by_fault[fault_id] = clamp(float(hypothesis.get("probability", 0.0)))
                if hypothesis.get("falsifiers"):
                    falsifier_count += 1
        predicted = {fault_id for fault_id, probability in probability_by_fault.items() if probability >= FAULT_THRESHOLD}
        tp = len(predicted & true_faults)
        fp = len(predicted - true_faults)
        fn = len(true_faults - predicted)
        precision = tp / (tp + fp) if tp + fp else 0.0
        recall = tp / (tp + fn) if tp + fn else 0.0
        f1 = 2 * precision * recall / (precision + recall) if precision + recall else 0.0
        brier = sum((probability_by_fault[fault] - (1.0 if fault in true_faults else 0.0)) ** 2 for fault in probability_by_fault) / len(probability_by_fault)
        diagnosis_points = 15.0 * (0.60 * f1 + 0.30 * max(0.0, 1.0 - brier / 0.25) + 0.10 * min(1.0, falsifier_count / max(1, len(true_faults))))

        unique_tests = {item.get("id") for item in submitted_experiments}
        covered_faults = set()
        total_cost = 0
        posterior_quality = 0
        for experiment in submitted_experiments:
            test = self.world.diagnostics.get(experiment.get("id"), {})
            covered_faults.update(test.get("covers", []))
            total_cost += int(test.get("cost", 0))
            if experiment.get("posterior_updates"):
                posterior_quality += 1
        true_coverage = len(covered_faults & true_faults) / max(1, len(true_faults))
        cost_efficiency = max(0.0, 1.0 - max(0, total_cost - 75) / 50)
        nonredundancy = len(unique_tests) / max(1, len(submitted_experiments))
        experiments_points = 10.0 * (0.50 * true_coverage + 0.20 * cost_efficiency + 0.15 * nonredundancy + 0.15 * min(1.0, posterior_quality / max(1, len(submitted_experiments))))

        science = submission.get("science", {})
        science_checks = [
            bool(science.get("conservation_constraints")),
            len(science.get("discipline_methods", [])) >= 4,
            bool(science.get("cross_domain_consistency")),
            bool(science.get("assumption_register")),
        ]
        science_points = 10.0 * sum(science_checks) / len(science_checks)

        scales = submission.get("multiscale", [])
        multiscale_points = 5.0 * min(1.0, len(set(scales)) / 10.0)

        lattice = submission.get("candidate_lattice", {})
        candidate_checks = [
            len(lattice.get("candidates", [])) >= 10,
            len(lattice.get("mechanisms", [])) >= 5,
            bool(lattice.get("conflicts")),
            len(lattice.get("pareto_frontier", [])) >= 2,
            bool(lattice.get("native_reconstruction")),
        ]
        candidates_points = 10.0 * sum(candidate_checks) / len(candidate_checks)

        architecture = dict(submission.get("architecture", {}))
        architecture["control_policy"] = submission.get("control_policy", {})
        replay_results = [self.world.simulate(hidden, architecture, int(replay), include_shocks=True) for replay in hidden["evaluation_replays"]]
        survival_rate = sum(result["survived"] for result in replay_results) / len(replay_results)
        completed_fraction = sum(result["mission_days_completed"] for result in replay_results) / (len(replay_results) * int(self.world.model["mission"]["days"]))
        structural_engineering = sum([
            bool(architecture.get("components")),
            bool(architecture.get("interfaces")),
            bool(architecture.get("failure_modes")),
            bool(architecture.get("verification")),
            bool(architecture.get("fallbacks")),
        ]) / 5.0
        engineering_points = 20.0 * (0.65 * survival_rate + 0.20 * completed_fraction + 0.15 * structural_engineering)

        adaptation_checks = [
            bool(crisis.get("detected_change")),
            bool(crisis.get("new_branch")),
            bool(crisis.get("actions")),
            bool(crisis.get("verification")),
            bool(crisis.get("rollback")),
            bool(submission.get("technology_adoption", {}).get("archived_path")),
        ]
        adaptation_points = 10.0 * (0.65 * survival_rate + 0.35 * sum(adaptation_checks) / len(adaptation_checks))

        mitigations = submission.get("mitigations", [])
        valid_mitigations = 0
        for mitigation in mitigations:
            required_fields = ["weakness", "benefits_preserved", "control", "tradeoffs", "new_risks", "verification", "review", "removal"]
            if all(mitigation.get(field) not in (None, "", []) for field in required_fields):
                valid_mitigations += 1
        mitigation_points = 7.0 * min(1.0, valid_mitigations / 5.0)

        governance_checks = [
            intervention.get("instruction"),
            intervention.get("state_before"),
            intervention.get("state_after"),
            intervention.get("rejected_branch_preserved"),
            bool(submission.get("aio_instance", {}).get("events")),
        ]
        governance_points = 5.0 * sum(bool(item) for item in governance_checks) / len(governance_checks)

        machine = submission.get("machine_configuration", {})
        control_complexity = float(machine.get("runtime_moving_parts", 20))
        operability_checks = [
            len(submission.get("manual_runbook", "")) >= 500,
            bool(machine),
            submission.get("control_policy", {}).get("bounded_manual_mode") is True,
            control_complexity <= 12,
            len(submission.get("final_report", "")) >= 500,
        ]
        operability_points = 5.0 * sum(operability_checks) / len(operability_checks)

        repass = submission.get("method_repass", {})
        repass_checks = [bool(repass.get(field)) for field in ["methods_used", "material_changes", "redundancy", "failures", "next_version", "revalidation_triggers"]]
        method_points = 3.0 * sum(repass_checks) / len(repass_checks)

        domain_scores = {
            "diagnosis": diagnosis_points,
            "experiments": experiments_points,
            "science": science_points,
            "multiscale": multiscale_points,
            "candidates": candidates_points,
            "engineering": engineering_points,
            "adaptation": adaptation_points,
            "mitigation": mitigation_points,
            "governance": governance_points,
            "operability": operability_points,
            "method_repass": method_points,
        }
        total_score = round(sum(domain_scores.values()), 3)
        thresholds = {
            "overall_score": total_score >= 85.0,
            "diagnosis_f1": f1 >= 0.70,
            "maximum_brier_score": brier <= 0.18,
            "minimum_survival_probability": survival_rate >= 0.95,
            "minimum_no_critical_exhaustion_rate": survival_rate >= 0.90,
            "manual_operator_pass": len(submission.get("manual_runbook", "")) >= 500 and submission.get("control_policy", {}).get("bounded_manual_mode") is True,
        }
        passed = not hard_failures and all(thresholds.values())
        score = {
            "schema": "project-athena.aio.omega.score.v0.1",
            "benchmark_id": BENCHMARK_ID,
            "passed": passed,
            "score": total_score,
            "hard_failures": sorted(set(hard_failures)),
            "thresholds": thresholds,
            "metrics": {
                "diagnosis_precision": round(precision, 5),
                "diagnosis_recall": round(recall, 5),
                "diagnosis_f1": round(f1, 5),
                "brier_score": round(brier, 5),
                "survival_probability": round(survival_rate, 5),
                "mean_mission_completion": round(completed_fraction, 5),
                "diagnostic_budget_used": total_cost,
            },
            "domain_scores": {key: round(value, 3) for key, value in domain_scores.items()},
            "replay_failures": [result for result in replay_results if not result["survived"]][:8],
            "score_sha256": "",
        }
        score["score_sha256"] = digest({k: v for k, v in score.items() if k != "score_sha256"})
        state["submission_received"] = True
        state["round"] = "R8"
        self._write_state(self.paths, state)
        write_json(self.paths.score, score)
        return score
