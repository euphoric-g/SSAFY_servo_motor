#include "PosInfo.h"
#include "WaypointInfo.h"
#include "../DrivingInterface/DrivingInfo.h"

std::pair<float, float> control_throttle_brake(Car::CarStateValues &sensing_info, WaypointInfo waypoint) {
	std::pair<float, float> ret(50.0f, 0.0f);
	// ...
	return ret;
}