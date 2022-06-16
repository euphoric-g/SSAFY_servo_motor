#pragma once

#include <vector>
#include "PosInfo.h"

class WaypointInfo {
private:
public:
	std::vector<PosInfo> waypoints;
	WaypointInfo() {}
	float rate_difficulty(void);
};