#ifndef SIMULATOR_H
#define SIMULATOR_H

#include "Aircraft.h"
#include "Environment.h"
#include "Flight_Condition.h"
#include "PerformanceResult.h"

class Simulator {
public:
    PerformanceResult run_simulation(
        Aircraft aircraft,
        Environment environment,
        Flight_Condition flight_condition
    );
};

#endif