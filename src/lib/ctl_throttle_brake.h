#pragma once

#include "PosInfo.h"
#include "WaypointInfo.h"
#include "../DrivingInterface/DrivingInfo.h"

std::pair<float, float> ctl_throttle_brake(Car::CarStateValues &sensing_info, WaypointInfo waypoint);