#pragma once
#include <vector>

#include "../DrivingInterface/DrivingInfo.h"
#include "PosInfo.h"
#include "internal_division.h"

PosInfo cog_locate_conversion(Car::CarStateValues &sensing_info, std::vector<PosInfo> waypoints, float distance, float offset);
PosInfo cog_locate_conversion(Car::CarStateValues &sensing_info, float distance, float offset);