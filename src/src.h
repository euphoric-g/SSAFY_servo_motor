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
#include "lib/cog_predict_road_departure.h"
#include "lib/cog_opponent_to_PosInfo.h"
#include "lib/ctl_steering_coefficient.h"
#include "lib/ctl_steering.h"

Car::ControlValues example(Car::CarStateValues &sensing_info);

// cognition


extern float cog_predict_collision_between_two_points(Car::CarStateValues &sensing_info, PosInfo p1, PosInfo p2);

// judge

extern std::vector<WaypointInfo> jud_make_WaypointInfo_candidates(Car::CarStateValues &sensing_info);
extern WaypointInfo jud_path_smoothing(Car::CarStateValues &sensing_info, WaypointInfo waypoint);

// control

extern std::pair<float, float> ctl_throttle_brake(Car::CarStateValues &sensing_info, WaypointInfo waypoint);