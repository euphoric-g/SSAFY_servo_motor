#pragma once

#include <vector>

#include "DrivingInterface/DrivingInfo.h"

#include "lib/PosInfo.h"
#include "lib/WaypointInfo.h"
#include "lib/LineEq.h"
#include "lib/CircEq.h"
#include "lib/ccw.h"
#include "lib/cog_waypoints_to_PosInfo.h"
#include "lib/cog_obstacles_to_PosInfo.h"
#include "lib/cog_locate_conversion.h"

Car::ControlValues example(Car::CarStateValues &sensing_info);

// cognition

extern PosInfo cog_opponent_to_PosInfo(Car::CarStateValues &sensing_info);
extern bool cog_predict_road_departure(Car::CarStateValues &sensing_info);
extern bool cog_road_departure(Car::CarStateValues &sensing_info);
extern float cog_predict_collision_between_two_points(Car::CarStateValues &sensing_info, PosInfo p1, PosInfo p2);

// judge

extern std::vector<WaypointInfo> jud_make_WaypointInfo_candidates(Car::CarStateValues &sensing_info);
extern WaypointInfo jud_path_smoothing(Car::CarStateValues &sensing_info, WaypointInfo waypoint);

// control

extern std::pair<float, float> ctl_throttle_brake(Car::CarStateValues &sensing_info, WaypointInfo waypoint);
extern float ctl_steering(Car::CarStateValues &sensing_info, WaypointInfo waypoint);
extern float ctl_steering_coefficient(Car::CarStateValues &sensing_info, WaypointInfo waypoint);
