#pragma once
#include <algorithm>

#include "../DrivingInterface/DrivingInfo.h"

#include "PosInfo.h"
#include "cog_waypoints_to_PosInfo.h"
#include "cog_locate_conversion.h"

std::vector<PosInfo> cog_obstacles_to_PosInfo(Car::CarStateValues &sensing_info);
std::vector<PosInfo> cog_obstacles_to_PosInfo(Car::CarStateValues &sensing_info, std::vector<PosInfo> waypoints);