#include "Simulator.h"

#define PI 3.14159262

PerformanceResult Simulator::run_simulation(
    Aircraft aircraft,
    Environment environment,
    Flight_Condition flight_condition)
{
    if (aircraft.wing.wing_area <= 0 || flight_condition.velocity <= 0) {
        return PerformanceResult{};
    }

    bool level_flight = false;

    // 1. Compute weight
    float W = aircraft.get_weight(environment);

    // 2. Compute wing aspect ratio
    float AR = aircraft.wing.get_aspect_ratio();

    // 3. Required lift coefficient
    float CL_required =
        (2 * W) /
        (environment.air_density *
        (flight_condition.velocity * flight_condition.velocity) *
        aircraft.wing.wing_area);

    // 4. Induced drag coefficient
    float CD_induced =
        (CL_required * CL_required) /
        (PI * aircraft.oswald_efficiency * AR);

    // 5. Total drag coefficient
    float CD_total = aircraft.CD0 + CD_induced;

    // 6. Drag force
    float D =
        0.5 *
        environment.air_density *
        (flight_condition.velocity * flight_condition.velocity) *
        aircraft.wing.wing_area *
        CD_total;

    // 7. Lift
    float L =
        0.5 *
        environment.air_density *
        (flight_condition.velocity * flight_condition.velocity) *
        aircraft.wing.wing_area *
        CL_required;

    // 8. Thrust-to-weight ratio
    float TWR = aircraft.available_thrust / W;

    // 9. Lift-to-drag ratio
    float L_over_D = CL_required / CD_total;

    // 10. Level flight check
    level_flight = (aircraft.available_thrust >= D);

    // 11. Fill result
    PerformanceResult result;
    result.lift = L;
    result.drag = D;
    result.required_CL = CL_required;
    result.aspect_ratio = AR;
    result.lift_to_drag_ratio = L_over_D;
    result.TWR = TWR;
    result.level_flight_possible = level_flight;

    return result;
}