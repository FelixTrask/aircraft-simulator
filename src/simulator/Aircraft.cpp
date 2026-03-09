#include "Aircraft.h"

Aircraft::Aircraft(float mass,
                   float available_thrust,
                   Wing wing,
                   float CD0,
                   float oswald_efficiency)

    : mass(mass), available_thrust(available_thrust), wing(wing), CD0(CD0), oswald_efficiency(oswald_efficiency)
{}

float Aircraft::get_weight(Environment environment)
{
    return mass * environment.gravity;
}