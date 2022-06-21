#include "cog_obstacles_to_PosInfo.h"

std::vector<PosInfo> cog_obstacles_to_PosInfo(Car::CarStateValues &sensing_info) {
	return cog_obstacles_to_PosInfo(sensing_info, cog_waypoints_to_PosInfo(sensing_info));
}

std::vector<PosInfo> cog_obstacles_to_PosInfo(Car::CarStateValues &sensing_info, std::vector<PosInfo> waypoints) {
	std::vector<PosInfo> ret;

	auto &obstacles = sensing_info.track_forward_obstacles;

	std::transform(obstacles.begin(), obstacles.end(), std::back_inserter(ret), [&sensing_info, &waypoints](Car::ObstaclesInfo obs) -> PosInfo {
		return cog_locate_conversion(sensing_info, waypoints, obs.dist, obs.to_middle);
	});

	return ret;
}