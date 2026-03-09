#ifndef Aircraft_H
#define Aircraft_H

#include "Wing.h"
#include "Environment.h"

class Aircraft {
public:
    Aircraft(float mass, float available_thrust, Wing wing, float CD0, float oswald_efficiency);

    float mass;
    float available_thrust;
    Wing wing;
    float CD0;
    float oswald_efficiency;

    float get_weight(Environment environment);
};

#endif