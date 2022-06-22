#pragma once

#include "PosInfo.h"
#include "../DrivingInterface/DrivingInfo.h"

std::vector<PosInfo> cog_waypoints_to_PosInfo(Car::CarStateValues &sensing_info);