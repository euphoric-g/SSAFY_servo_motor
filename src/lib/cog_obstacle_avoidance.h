#pragma once

#include <vector>
#include "../DrivingInterface/DrivingInfo.h"
#include "PosInfo.h"
#include "LineEq.h"

PosInfo cog_obstacle_avoidance(Car::CarStateValues &sensing_info, std::vector<PosInfo> obstacles, LineEq line);