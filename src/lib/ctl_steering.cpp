#include "PosInfo.h"
#include "WaypointInfo.h"
#include "../DrivingInterface/DrivingInfo.h"

float ctl_steering(Car::CarStateValues &sensing_info, WaypointInfo waypoint) {
	float ret = sensing_info.to_middle / -10.0f;
	// ...
	return ret;
}