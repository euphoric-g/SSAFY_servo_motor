#pragma once
#include "PosInfo.h"
#include "WaypointInfo.h"
#include "../DrivingInterface/DrivingInfo.h"

float ctl_steering_coefficient(Car::CarStateValues &sensing_info, WaypointInfo waypoint);