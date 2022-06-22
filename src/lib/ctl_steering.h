#pragma once

#include "PosInfo.h"
#include "WaypointInfo.h"
#include "../DrivingInterface/DrivingInfo.h"
#include <vector>
#include <cmath>
#include "cog_waypoints_to_PosInfo.h"

using namespace std;

float ctl_steering(Car::CarStateValues &sensing_info, WaypointInfo waypoint);
