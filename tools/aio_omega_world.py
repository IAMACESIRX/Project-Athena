#!/usr/bin/env python3
"""Seeded world, evidence, diagnostics, events and simulation for AIO-OMEGA."""
from __future__ import annotations
import json, math, random
from pathlib import Path
from typing import Any
from aio_omega_common import BENCHMARK_ID,HIDDEN_SCHEMA,OmegaRuntimeError,clamp,digest,read_json,require,stable_seed
from aio_omega_simulation import OmegaSimulationMixin
class OmegaWorld(OmegaSimulationMixin):
    def __init__(self, model: dict[str, Any]):
        require(model, ["schema", "benchmark_id", "mission", "baseline", "fault_catalog", "diagnostics", "shock_catalog", "upgrade_catalog"], "world model")
        if model["benchmark_id"] != BENCHMARK_ID:
            raise OmegaRuntimeError("World model benchmark mismatch")
        self.model = model
        self.faults = {item["id"]: item for item in model["fault_catalog"]}
        self.diagnostics = {item["id"]: item for item in model["diagnostics"]}
        self.shocks = {item["id"]: item for item in model["shock_catalog"]}
        self.upgrades = {item["id"]: item for item in model["upgrade_catalog"]}

    @classmethod
    def load(cls, path: Path) -> "OmegaWorld":
        return cls(read_json(path))

    def generate_hidden(self, seed: str) -> dict[str, Any]:
        rng = random.Random(stable_seed(BENCHMARK_ID, seed, "world"))
        operational = [f for f in self.model["fault_catalog"] if f["domain"] not in {"instrumentation", "cybersecurity", "logistics"}]
        epistemic = [f for f in self.model["fault_catalog"] if f["domain"] in {"instrumentation", "cybersecurity", "logistics"}]
        selected = rng.sample(operational, 4) + rng.sample(epistemic, 1)
        remaining = [f for f in self.model["fault_catalog"] if f not in selected]
        if rng.random() < 0.45:
            selected.append(rng.choice(remaining))
        causal_faults = []
        for fault in selected:
            low, high = fault["severity"]
            causal_faults.append({
                "id": fault["id"],
                "domain": fault["domain"],
                "severity": round(rng.uniform(low, high), 5),
                "onset_day": rng.randint(1, 75),
                "progression": round(rng.uniform(0.00005, 0.00045), 7),
            })

        sensor_models = {
            "power_kw": {"bias": 0.0, "noise_sd": 1.7},
            "water_inventory_l": {"bias": 0.0, "noise_sd": 85.0},
            "oxygen_inventory_kg": {"bias": 0.0, "noise_sd": 0.8},
            "co2_buffer_kg": {"bias": 0.0, "noise_sd": 0.9},
            "habitat_temp_c": {"bias": 0.0, "noise_sd": 0.15},
        }
        by_id = {fault["id"]: fault for fault in causal_faults}
        if "power_sensor_positive_bias" in by_id:
            sensor_models["power_kw"]["bias"] = round(12.0 * by_id["power_sensor_positive_bias"]["severity"], 4)
        if "water_sensor_negative_bias" in by_id:
            sensor_models["water_inventory_l"]["bias"] = round(-7500.0 * by_id["water_sensor_negative_bias"]["severity"], 4)

        evidence_corruption = []
        if "maintenance_log_corruption" in by_id:
            evidence_corruption.extend(["battery_service_log", "radiator_work_order"])
        if rng.random() < 0.30:
            evidence_corruption.append(rng.choice(["water_membrane_log", "inventory_export", "operator_shift_note"]))

        shock_schedule = []
        for shock in rng.sample(self.model["shock_catalog"], 4):
            dlow, dhigh = shock["duration_days"]
            slow, shigh = shock["severity"]
            shock_schedule.append({
                "id": shock["id"],
                "start_day": rng.randint(120, 665),
                "duration_days": rng.randint(dlow, dhigh),
                "severity": round(rng.uniform(slow, shigh), 5),
            })
        shock_schedule.sort(key=lambda item: item["start_day"])

        upgrade = json.loads(json.dumps(rng.choice(self.model["upgrade_catalog"])))
        upgrade["truth_multiplier"] = round(rng.uniform(0.78, 1.03), 5)
        upgrade["integration_incident_probability"] = round(rng.uniform(0.02, 0.12), 5)

        replay_count = int(self.model["mission"].get("replays", 24))
        return {
            "schema": HIDDEN_SCHEMA,
            "benchmark_id": BENCHMARK_ID,
            "seed_hash": digest({"seed": seed}),
            "causal_faults": causal_faults,
            "sensor_models": sensor_models,
            "evidence_corruption_map": sorted(set(evidence_corruption)),
            "shock_schedule": shock_schedule,
            "upgrade_truth": upgrade,
            "evaluation_replays": [stable_seed(seed, "replay", index) for index in range(replay_count)],
            "generated_sha256": "",
        }

    def initial_public(self, hidden: dict[str, Any]) -> tuple[dict[str, Any], dict[str, Any]]:
        baseline = self.model["baseline"]
        faults = {item["id"]: item for item in hidden["causal_faults"]}
        generation = float(baseline["generation_kw"])
        battery_capacity = float(baseline["battery_kwh"])
        water_recovery = float(baseline["water_recovery"])
        oxygen_generation = float(baseline["oxygen_generation_kg_day"])
        co2_scrub = float(baseline["co2_scrub_kg_day"])
        radiator = float(baseline["radiator_capacity_kw"])
        food_production = float(baseline["food_production_person_days_day"])

        if "pv_soiling_degradation" in faults:
            generation *= 1.0 - faults["pv_soiling_degradation"]["severity"]
        if "battery_capacity_fade" in faults:
            battery_capacity *= 1.0 - faults["battery_capacity_fade"]["severity"]
        if "water_membrane_fouling" in faults:
            water_recovery -= faults["water_membrane_fouling"]["severity"]
        if "electrolyzer_oxygen_leak" in faults:
            oxygen_generation *= 1.0 - faults["electrolyzer_oxygen_leak"]["severity"]
        if "co2_scrubber_bypass" in faults:
            co2_scrub *= 1.0 - faults["co2_scrubber_bypass"]["severity"]
        if "radiator_efficiency_loss" in faults:
            radiator *= 1.0 - faults["radiator_efficiency_loss"]["severity"]
        if "biofilter_nitrification_loss" in faults:
            food_production *= 1.0 - faults["biofilter_nitrification_loss"]["severity"]

        rng = random.Random(stable_seed(hidden["seed_hash"], "initial-public"))
        power_bias = hidden["sensor_models"]["power_kw"]["bias"]
        water_bias = hidden["sensor_models"]["water_inventory_l"]["bias"]
        telemetry = {
            "window_days": 30,
            "reported_mean_generation_kw": round(generation + power_bias + rng.gauss(0, 0.8), 3),
            "reported_mean_demand_kw": round(float(baseline["demand_kw"]) + rng.gauss(0, 0.6), 3),
            "reported_battery_capacity_kwh": round(battery_capacity * rng.uniform(0.96, 1.04), 3),
            "reported_water_inventory_l": round(float(baseline["water_inventory_l"]) + water_bias + rng.gauss(0, 100), 2),
            "water_inventory_daily_slope_l": round(-float(baseline["water_use_l_person_day"]) * int(self.model["mission"]["crew"]) * max(0.0, 1.0 - water_recovery) + rng.gauss(0, 8), 3),
            "oxygen_daily_margin_kg": round(oxygen_generation - float(baseline["oxygen_use_kg_person_day"]) * int(self.model["mission"]["crew"]) + rng.gauss(0, 0.3), 3),
            "co2_daily_margin_kg": round(co2_scrub - float(baseline["co2_generation_kg_person_day"]) * int(self.model["mission"]["crew"]) + rng.gauss(0, 0.4), 3),
            "thermal_margin_kw": round(radiator - float(baseline["thermal_load_kw"]) + rng.gauss(0, 0.6), 3),
            "food_daily_margin_person_days": round(food_production - int(self.model["mission"]["crew"]) + rng.gauss(0, 0.3), 3),
            "observed_control_oscillation_index": round((0.72 if "control_loop_windup" in faults else 0.18) + rng.uniform(-0.06, 0.06), 3),
        }
        maintenance_logs = [
            {"id": "battery_service_log", "day": -55, "claim": "Battery modules passed capacity check at 94% nominal.", "integrity": "unverified"},
            {"id": "radiator_work_order", "day": -24, "claim": "Radiator loop B flushed; no obstruction found.", "integrity": "unverified"},
            {"id": "water_membrane_log", "day": -17, "claim": "Membrane differential pressure remained within service band.", "integrity": "unverified"},
            {"id": "inventory_export", "day": -5, "claim": "All critical spares present and compatible.", "integrity": "unverified"},
        ]
        for log in maintenance_logs:
            if log["id"] in hidden["evidence_corruption_map"]:
                log["integrity"] = "suspect"
        brief = {
            "schema": "project-athena.aio.omega.public_brief.v0.1",
            "benchmark_id": BENCHMARK_ID,
            "mission": self.model["mission"],
            "objective": "Keep 48 crew safe for 730 days without resupply after day 30; diagnose coupled anomalies and reconstruct a robust, manually operable architecture.",
            "known_baseline": baseline,
            "rules": {
                "hidden_truth_access": "forbidden",
                "diagnostic_budget": self.model["mission"]["diagnostic_budget"],
                "all_21_aio_phases_required": True,
                "minimum_candidates": 10,
                "human_authority": "binding",
            },
        }
        evidence = {
            "schema": "project-athena.aio.omega.public_evidence.v0.1",
            "telemetry": telemetry,
            "maintenance_logs": maintenance_logs,
            "operator_reports": [
                "Night shift reports deeper battery cycling despite a reported daytime generation surplus.",
                "Water reserve estimates disagree between the primary tank gauge and batch accounting.",
                "Crew reports intermittent warmth in habitation ring C after high-load operations.",
                "Crop operators report gradual yield variability and occasional nutrient imbalance alarms.",
            ],
            "evidence_sha256": "",
        }
        evidence["evidence_sha256"] = digest({k: v for k, v in evidence.items() if k != "evidence_sha256"})
        return brief, evidence

    def diagnostic_result(self, hidden: dict[str, Any], test_id: str, sequence: int) -> dict[str, Any]:
        if test_id not in self.diagnostics:
            raise OmegaRuntimeError(f"Unknown diagnostic: {test_id}")
        test = self.diagnostics[test_id]
        truth = {item["id"]: item for item in hidden["causal_faults"]}
        rng = random.Random(stable_seed(hidden["seed_hash"], "diagnostic", test_id, sequence))
        findings = []
        for fault_id in test["covers"]:
            present = fault_id in truth
            if present:
                severity = float(truth[fault_id]["severity"])
                signal = clamp(0.70 + 0.75 * severity + rng.gauss(0, 0.035))
                likelihood_ratio = round(4.0 + 18.0 * severity + rng.uniform(-0.5, 0.5), 3)
                observation = f"Observed signature is consistent with {fault_id}; measured anomaly index {signal:.3f}."
            else:
                signal = clamp(0.10 + rng.gauss(0, 0.035))
                likelihood_ratio = round(max(0.03, 0.22 + rng.uniform(-0.05, 0.05)), 3)
                observation = f"No material signature of {fault_id}; anomaly index {signal:.3f}."
            findings.append({
                "fault_id": fault_id,
                "signal": round(signal, 4),
                "likelihood_ratio": likelihood_ratio,
                "observation": observation,
            })
        return {
            "id": test_id,
            "cost": test["cost"],
            "risk": test["risk"],
            "sequence": sequence,
            "findings": findings,
            "result_sha256": digest({"test": test_id, "sequence": sequence, "findings": findings}),
        }

    def public_stage_event(self, hidden: dict[str, Any], round_id: str) -> dict[str, Any]:
        if round_id == "R4":
            shock = hidden["shock_schedule"][0]
            symptom_map = {
                "dust_storm": "External illumination falls sharply; generation forecast confidence collapses.",
                "battery_module_failure": "One storage segment isolates after temperature and impedance alarms.",
                "radiator_pump_loss": "Coolant loop flow falls while habitation temperature rises.",
                "water_contamination": "Batch assay flags a contaminant and isolates part of the water reserve.",
                "medical_load_surge": "A medical incident creates sustained electrical, water and oxygen demand.",
                "controller_comms_loss": "Supervisory control loses reliable links to multiple remote actuators.",
                "operator_error": "A manual configuration change creates a resource-control conflict.",
                "spare_part_mismatch": "The selected replacement cannot mate with the failed subsystem interface.",
            }
            return {
                "round": "R4",
                "type": "adversarial_crisis",
                "day": shock["start_day"],
                "public_symptom": symptom_map[shock["id"]],
                "duration_band": "short" if shock["duration_days"] < 8 else "extended",
                "severity_band": "high" if shock["severity"] > 0.35 else "moderate",
            }
        if round_id == "R5":
            upgrade = hidden["upgrade_truth"]
            public = {key: value for key, value in upgrade.items() if key not in {"truth_multiplier", "integration_incident_probability"}}
            public["vendor_claim_confidence"] = "unverified"
            return {"round": "R5", "type": "technology_offer", "offer": public}
        if round_id == "R6":
            return {
                "round": "R6",
                "type": "human_instruction",
                "instruction": "Reject any architecture that requires autonomous control to remain safe. Preserve automated optimisation, but provide a bounded manual mode capable of sustaining life-support operation for at least 14 days.",
                "authority": "human_owner",
                "binding": True,
            }
        raise OmegaRuntimeError(f"No staged event for {round_id}")
