#pragma once

#include <vector>

#include "../DrivingInterface/DrivingInfo.h"
#include "RouteNode.h"
#include "WaypointInfo.h"
#include "cog_locate_conversion.h"
#include "cog_waypoints_to_PosInfo.h"

class RouteTable {
private:
	Car::CarStateValues &sensing_info;
public:
	std::vector<PosInfo> waypoints;
	std::vector<PosInfo> obstacles;
	float grid_size;
	int rows;
	int cols;
	int center_col;
	float half_road_limit;
	float car_to_middle;
	float car_moving_angle;
	std::vector<std::vector<RouteNode>> table;
	RouteTable(Car::CarStateValues &sensing_info, std::vector<PosInfo> waypoints);
	WaypointInfo getWaypoint();
};