#include "PosInfo.h"
#include "../DrivingInterface/DrivingInfo.h"

PosInfo cog_opponent_to_PosInfo(Car::CarStateValues &sensing_info) {
	auto &opponent = sensing_info.opponent_cars_info[0];
	// ...
	return PosInfo(0, 0);
}