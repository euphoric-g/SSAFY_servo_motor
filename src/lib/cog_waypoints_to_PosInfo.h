#pragma once

#include <algorithm>

#include "PosInfo.h"
#include "LineEq.h"
#include "ccw.h"
#include "../DrivingInterface/DrivingInfo.h"

std::vector<PosInfo> cog_waypoints_to_PosInfo(Car::CarStateValues &sensing_info);