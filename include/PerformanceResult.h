#ifndef PERFORMANCE_RESULT_H
#define PERFORMANCE_RESULT_H

typedef struct PR {
    float lift;
    float drag;
    float required_CL;
    float aspect_ratio;
    float lift_to_drag_ratio;
    float TWR;
    bool level_flight_possible;
} PerformanceResult;

#endif