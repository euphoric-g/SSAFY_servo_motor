#pragma once

#include "PosInfo.h"
#include "WaypointInfo.h"
#include "../DrivingInterface/DrivingInfo.h"

float ctl_steering(Car::CarStateValues &sensing_info, WaypointInfo waypoint);