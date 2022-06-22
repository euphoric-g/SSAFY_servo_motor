#pragma once

#include "../DrivingInterface/DrivingInfo.h"

#include "PosInfo.h"

std::vector<PosInfo> cog_obstacles_to_PosInfo(Car::CarStateValues &sensing_info);
std::vector<PosInfo> cog_obstacles_to_PosInfo(Car::CarStateValues &sensing_info, std::vector<PosInfo> waypoints);