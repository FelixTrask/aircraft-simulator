#include "Wing.h"

Wing::Wing(float wingspan, float wing_area)
    : wingspan(wingspan), wing_area(wing_area)
{}

float Wing::get_aspect_ratio()
{
    return (wingspan*wingspan) / wing_area;
}
