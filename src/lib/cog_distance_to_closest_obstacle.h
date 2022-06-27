#pragma once

#include <vector>
#include "../DrivingInterface/DrivingInfo.h"
#include "PosInfo.h"

float cog_distance_to_closest_obstacle(Car::CarStateValues &sensing_info, std::vector<PosInfo> obstacles);