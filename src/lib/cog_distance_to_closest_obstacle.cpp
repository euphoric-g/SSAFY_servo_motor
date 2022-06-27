#include "cog_distance_to_closest_obstacle.h"

float cog_distance_to_closest_obstacle(Car::CarStateValues &sensing_info, std::vector<PosInfo> obstacles) {
	PosInfo car(sensing_info.to_middle, 0);
	float closest = 1e8;
	for (auto &obstacle : obstacles) {
		if (car.dist(obstacle) < closest) closest = car.dist(obstacle);
	}
	return closest;
}