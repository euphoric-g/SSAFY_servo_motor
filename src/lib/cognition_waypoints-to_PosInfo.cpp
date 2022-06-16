#include <algorithm>

#include "PosInfo.h"
#include "../DrivingInterface/DrivingInfo.h"

std::vector<PosInfo> cognition_waypoints_to_PosInfo(Car::CarStateValues &sensing_info) {
	using namespace std;

	vector<PosInfo> ret;
	
	auto &dists = sensing_info.distance_to_way_points;
	auto &angles = sensing_info.track_forward_angles;
	
	vector<pair<float, float>> waypoints(dists.size());
	transform(dists.begin(), dists.end(), angles.begin(), back_inserter(waypoints), [](float a, float b) { return std::make_pair(a, b); });
	
	for(const auto &waypoint : waypoints) {

	}

	return ret;
}