#include "cog_opponent_to_PosInfo.h"

#include "cog_locate_conversion.h"

PosInfo cog_opponent_to_PosInfo(Car::CarStateValues &sensing_info) {
	auto &opponent = sensing_info.opponent_cars_info[0];
	return cog_locate_conversion(sensing_info, opponent.dist, opponent.to_middle);
}