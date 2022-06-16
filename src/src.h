#pragma once

#include <vector>

#include "DrivingInterface/DrivingInfo.h"

#include "lib/PosInfo.h"
#include "lib/WaypointInfo.h"

Car::ControlValues example(Car::CarStateValues &sensing_info);

// cognition

extern std::vector<PosInfo> cognition_obstacles_to_PosInfo(Car::CarStateValues &sensing_info);
extern PosInfo cognition_opponent_to_PosInfo(Car::CarStateValues &sensing_info);
extern std::vector<PosInfo> cognition_waypoints_to_PosInfo(Car::CarStateValues &sensing_info);
extern bool cognition_predict_road_departure(Car::CarStateValues &sensing_info);
extern bool cognition_road_departure(Car::CarStateValues &sensing_info);
extern PosInfo cognition_locate_conversion(Car::CarStateValues &sensing_info, float distance, float offset);
extern float cognition_predict_collision_between_two_points(Car::CarStateValues &sensing_info, PosInfo p1, PosInfo p2);

// judge

extern float ccw(PosInfo p1, PosInfo p2, PosInfo p3);
extern std::vector<WaypointInfo> judge_make_WaypointInfo_candidates(Car::CarStateValues &sensing_info);
extern WaypointInfo judge_path_smoothing(Car::CarStateValues &sensing_info, WaypointInfo waypoint);

// control

extern std::pair<float, float> control_throttle_brake(Car::CarStateValues &sensing_info, WaypointInfo waypoint);
extern float control_steering(Car::CarStateValues &sensing_info, WaypointInfo waypoint);
extern float control_steering_coefficient(Car::CarStateValues &sensing_info, WaypointInfo waypoint);
