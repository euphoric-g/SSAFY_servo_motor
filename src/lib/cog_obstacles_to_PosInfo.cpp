#include "PosInfo.h"
#include "../DrivingInterface/DrivingInfo.h"

std::vector<PosInfo> cog_obstacles_to_PosInfo(Car::CarStateValues &sensing_info) {
	std::vector<PosInfo> ret;
	auto &obstacles = sensing_info.track_forward_obstacles;
	// ...
	return ret;
}