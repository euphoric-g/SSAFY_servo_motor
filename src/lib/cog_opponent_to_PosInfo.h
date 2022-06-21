#pragma once

#include "../DrivingInterface/DrivingInfo.h"
#include "PosInfo.h"
#include "cog_locate_conversion.h"

PosInfo cog_opponent_to_PosInfo(Car::CarStateValues &sensing_info);