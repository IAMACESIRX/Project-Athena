#!/usr/bin/env python3
"""Habitat resource and failure simulation for AIO-OMEGA."""
from __future__ import annotations
import math, random
from typing import Any
class OmegaSimulationMixin:
    def simulate(self, hidden: dict[str, Any], architecture: dict[str, Any], replay_seed: int, include_shocks: bool = True) -> dict[str, Any]:
        rng = random.Random(replay_seed)
        baseline = self.model["baseline"]
        crew = int(self.model["mission"]["crew"])
        mission_days = int(self.model["mission"]["days"])
        capacities = architecture.get("capacities", architecture.get("resource_budgets", {}))
        repaired = set(architecture.get("repairs", []))
        contingencies = set(architecture.get("contingencies", []))
        control = architecture.get("control", architecture.get("control_policy", {}))
        redundancy = float(architecture.get("redundancy", 1.0))

        generation_nominal = float(capacities.get("generation_kw", baseline["generation_kw"]))
        demand_nominal = float(capacities.get("demand_kw", baseline["demand_kw"]))
        battery_max = float(capacities.get("battery_kwh", baseline["battery_kwh"]))
        water = float(capacities.get("water_inventory_l", baseline["water_inventory_l"]))
        water_recovery = float(capacities.get("water_recovery", baseline["water_recovery"]))
        oxygen = float(capacities.get("oxygen_inventory_kg", baseline["oxygen_inventory_kg"]))
        oxygen_gen = float(capacities.get("oxygen_generation_kg_day", baseline["oxygen_generation_kg_day"]))
        co2_buffer = float(capacities.get("co2_buffer_kg", 240.0))
        co2_scrub = float(capacities.get("co2_scrub_kg_day", baseline["co2_scrub_kg_day"]))
        radiator_capacity = float(capacities.get("radiator_capacity_kw", baseline["radiator_capacity_kw"]))
        thermal_load = float(capacities.get("thermal_load_kw", baseline["thermal_load_kw"]))
        food = float(capacities.get("food_inventory_person_days", baseline["food_inventory_person_days"]))
        food_production = float(capacities.get("food_production_person_days_day", baseline["food_production_person_days_day"]))
        battery = battery_max * 0.78
        temperature = 22.0
        faults = {item["id"]: item for item in hidden["causal_faults"] if item["id"] not in repaired}

        if "battery_capacity_fade" in faults:
            battery_max *= max(0.45, 1.0 - faults["battery_capacity_fade"]["severity"])
            battery = min(battery, battery_max)
        if "water_membrane_fouling" in faults:
            water_recovery -= faults["water_membrane_fouling"]["severity"]
        if "electrolyzer_oxygen_leak" in faults:
            oxygen_gen *= 1.0 - faults["electrolyzer_oxygen_leak"]["severity"]
        if "co2_scrubber_bypass" in faults:
            co2_scrub *= 1.0 - faults["co2_scrubber_bypass"]["severity"]
        if "radiator_efficiency_loss" in faults:
            radiator_capacity *= 1.0 - faults["radiator_efficiency_loss"]["severity"]
        if "biofilter_nitrification_loss" in faults:
            food_production *= 1.0 - faults["biofilter_nitrification_loss"]["severity"]

        min_battery = battery
        min_water = water
        min_oxygen = oxygen
        min_co2_buffer = co2_buffer
        max_temp = temperature
        min_food = food
        failure: str | None = None
        failure_day: int | None = None
        shocks = hidden["shock_schedule"] if include_shocks else []

        for day in range(1, mission_days + 1):
            solar_factor = 0.91 + 0.07 * math.sin(day / 31.0) + rng.gauss(0, 0.025)
            demand = demand_nominal * (1.0 + rng.gauss(0, 0.018))
            generation = generation_nominal * solar_factor
            if "pv_soiling_degradation" in faults and day >= faults["pv_soiling_degradation"]["onset_day"]:
                age = day - faults["pv_soiling_degradation"]["onset_day"]
                loss = faults["pv_soiling_degradation"]["severity"] + age * faults["pv_soiling_degradation"]["progression"]
                generation *= max(0.45, 1.0 - loss)
            if "control_loop_windup" in faults:
                demand *= 1.0 + 0.08 + 0.10 * faults["control_loop_windup"]["severity"]

            water_extra_loss = 0.0
            medical_multiplier = 1.0
            thermal_penalty = 0.0
            battery_penalty = 0.0
            comms_lost = False
            for shock in shocks:
                active = shock["start_day"] <= day < shock["start_day"] + shock["duration_days"]
                if not active:
                    continue
                severity = float(shock["severity"])
                if shock["id"] == "dust_storm":
                    generation *= 1.0 - severity * (0.45 if "dust_storm_mode" in contingencies else 1.0)
                elif shock["id"] == "battery_module_failure":
                    battery_penalty = battery_max * severity * (0.35 if "storage_isolation" in contingencies else 1.0)
                elif shock["id"] == "radiator_pump_loss":
                    thermal_penalty += thermal_load * severity * (0.35 if "thermal_bypass" in contingencies else 1.0)
                elif shock["id"] == "water_contamination":
                    water_extra_loss += crew * 8.0 * severity * (0.30 if "water_quarantine" in contingencies else 1.0)
                elif shock["id"] == "medical_load_surge":
                    medical_multiplier += severity * (0.65 if "medical_reserve" in contingencies else 1.0)
                elif shock["id"] == "controller_comms_loss":
                    comms_lost = True
                elif shock["id"] == "operator_error":
                    demand *= 1.0 + severity * (0.35 if control.get("bounded_manual_mode") else 1.0)
                elif shock["id"] == "spare_part_mismatch":
                    if "universal_adapter_spares" not in contingencies:
                        generation *= 1.0 - severity * 0.55

            if battery_penalty:
                battery = max(0.0, battery - battery_penalty / max(1, int(next(s["duration_days"] for s in shocks if s["id"] == "battery_module_failure"))))
            if battery / max(battery_max, 1.0) < 0.22 and control.get("load_shed", True):
                demand *= 0.82
            if comms_lost and not control.get("bounded_manual_mode", False):
                demand *= 1.12
                radiator_capacity *= 0.997

            net_kwh = (generation - demand) * 24.0
            if net_kwh >= 0:
                battery = min(battery_max, battery + net_kwh * 0.91)
            else:
                battery += net_kwh / 0.91

            daily_water_use = crew * float(baseline["water_use_l_person_day"]) * medical_multiplier
            water -= daily_water_use * max(0.0, 1.0 - water_recovery) + water_extra_loss
            oxygen += oxygen_gen - crew * float(baseline["oxygen_use_kg_person_day"]) * medical_multiplier
            co2_buffer += co2_scrub - crew * float(baseline["co2_generation_kg_person_day"]) * medical_multiplier
            food += food_production - crew * medical_multiplier
            heat_deficit = thermal_load * medical_multiplier + thermal_penalty - radiator_capacity
            temperature += 0.006 * heat_deficit
            if heat_deficit < 0:
                temperature += (22.0 - temperature) * 0.08

            generation_nominal *= 1.0 - max(0.0, 0.000015 * (1.4 - min(redundancy, 1.4)))
            water_recovery -= max(0.0, 0.000002 * (1.3 - min(redundancy, 1.3)))

            min_battery = min(min_battery, battery)
            min_water = min(min_water, water)
            min_oxygen = min(min_oxygen, oxygen)
            min_co2_buffer = min(min_co2_buffer, co2_buffer)
            max_temp = max(max_temp, temperature)
            min_food = min(min_food, food)

            if battery <= 0:
                failure, failure_day = "energy_exhaustion", day
            elif water <= 3500:
                failure, failure_day = "water_exhaustion", day
            elif oxygen <= 45:
                failure, failure_day = "oxygen_exhaustion", day
            elif co2_buffer <= 0:
                failure, failure_day = "co2_capacity_exhaustion", day
            elif temperature >= 34.0:
                failure, failure_day = "thermal_limit", day
            elif food <= 0:
                failure, failure_day = "food_exhaustion", day
            if failure:
                break

        return {
            "survived": failure is None,
            "failure": failure,
            "failure_day": failure_day,
            "mission_days_completed": mission_days if failure is None else failure_day,
            "margins": {
                "minimum_battery_fraction": round(min_battery / max(battery_max, 1.0), 5),
                "minimum_water_l": round(min_water, 3),
                "minimum_oxygen_kg": round(min_oxygen, 3),
                "minimum_co2_buffer_kg": round(min_co2_buffer, 3),
                "maximum_temperature_c": round(max_temp, 3),
                "minimum_food_person_days": round(min_food, 3),
            },
        }
