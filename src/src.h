#pragma once

#include <vector>

#include "DrivingInterface/DrivingInfo.h"

#include "lib/PosInfo.h"
#include "lib/WaypointInfo.h"
#include "lib/LineEq.h"
#include "lib/CircEq.h"

Car::ControlValues example(Car::CarStateValues &sensing_info);

// cognition

extern std::vector<PosInfo> cog_obstacles_to_PosInfo(Car::CarStateValues &sensing_info);
extern PosInfo cog_opponent_to_PosInfo(Car::CarStateValues &sensing_info);
extern std::vector<PosInfo> cog_waypoints_to_PosInfo(Car::CarStateValues &sensing_info);
extern bool cog_predict_road_departure(Car::CarStateValues &sensing_info);
extern bool cog_road_departure(Car::CarStateValues &sensing_info);
extern PosInfo cog_locate_conversion(Car::CarStateValues &sensing_info, float distance, float offset);
extern float cog_predict_collision_between_two_points(Car::CarStateValues &sensing_info, PosInfo p1, PosInfo p2);

// judge

extern float ccw(PosInfo p1, PosInfo p2, PosInfo p3);
extern std::vector<WaypointInfo> jud_make_WaypointInfo_candidates(Car::CarStateValues &sensing_info);
extern WaypointInfo jud_path_smoothing(Car::CarStateValues &sensing_info, WaypointInfo waypoint);

// control

extern std::pair<float, float> ctl_throttle_brake(Car::CarStateValues &sensing_info, WaypointInfo waypoint);
extern float ctl_steering(Car::CarStateValues &sensing_info, WaypointInfo waypoint);
extern float ctl_steering_coefficient(Car::CarStateValues &sensing_info, WaypointInfo waypoint);
