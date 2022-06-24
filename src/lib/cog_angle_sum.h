#pragma once

#include "../DrivingInterface/DrivingInfo.h"

float cog_angle_sum(Car::CarStateValues &sensing_info);
float cog_angle_sum(Car::CarStateValues &sensing_info, int from, int to);