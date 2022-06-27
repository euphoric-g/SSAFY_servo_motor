#include "cog_obstacle_avoidance.h"

#include <cmath>
#include <algorithm>

#include "cog_locate_conversion.h"
#include "cog_predict_collision.h"
#include "cog_waypoints_to_PosInfo.h"
#include "grad_to_moving_angle.h"
#include "ccw.h"

PosInfo cog_obstacle_avoidance(Car::CarStateValues &sensing_info, std::vector<PosInfo> obstacles , LineEq line) {
	using std::vector;
	using std::sort;

	auto &obstacles_raw = sensing_info.track_forward_obstacles;
	PosInfo car(sensing_info.to_middle, 0);
	LineEq carLine = LineEq(1 / tanf(sensing_info.moving_angle * acosf(-1) / 180), car);

	float moving_angle = sensing_info.moving_angle;
	float grad_og = line.grad() < 0 ? (-90 - atanf(line.grad()) * 180 / acosf(-1)) : (90 - atanf(line.grad()) * 180 / acosf(-1));

	sort(obstacles.begin(), obstacles.end(), [](PosInfo p1, PosInfo p2) { return p1.y < p2.y; });
	float closest_y = obstacles.begin()->y;

	vector<PosInfo> obs_group;
	vector<PosInfo> candidates;

	for (auto &obstacle : obstacles) {
		if (abs(obstacle.y - closest_y) <= 1.0f) obs_group.push_back(obstacle);
	}

	PosInfo second = car + PosInfo(1, carLine.grad() * 100) * (carLine.grad() > 0 ? 1 : -1);
	for (float x = -sensing_info.half_road_limit; x <= sensing_info.half_road_limit; x += 0.1f) {
		bool pass = false;
		for (auto &obs : obs_group) {
			if (abs(x - obs.x) < 3.1f) pass = true;
			// if (ccw(car, second, PosInfo(x, closest_y)) * ccw(car, second, obs) > 0) pass = true;
			// if ((x - obs.x) * (car.x - obs.x) <= 0) pass = true;
		}
		if (pass) continue;
		candidates.push_back(PosInfo(x, closest_y));
	}

	if (candidates.empty()) return PosInfo(0, 100);

	sort(candidates.begin(), candidates.end(), [&grad_og, &moving_angle, &car](PosInfo p1, PosInfo p2) {
		float angle1 = grad_to_moving_angle(LineEq(car, p1).grad());
		float angle2 = grad_to_moving_angle(LineEq(car, p2).grad());
		float eval1 = abs(grad_og - angle1) + abs(moving_angle - angle1);
		float eval2 = abs(grad_og - angle2) + abs(moving_angle - angle2);
		return eval1 < eval2;
		// return abs(moving_angle - angle1) < abs(moving_angle - angle2);
		// return abs(grad_og - angle1) < abs(grad_og - angle2);
	});

	/*std::cout << "selected avoidance point\n";
	std::cout << "(" << candidates.begin()->x << ", " << candidates.begin()->y << ")\n";
	std::cout << "point angle = " << grad_to_moving_angle(LineEq(car, *candidates.begin()).grad()) << ", grad_og = " << grad_og << ", moving_angle = " << moving_angle << "\n";*/

	return *candidates.begin();

	//std::vector<PosInfo> candidates;
	//float avoid_offset = 4;

	///*for (auto &waypoint : cog_waypoints_to_PosInfo(sensing_info)) {
	//	LineEq new_line(car, waypoint);
	//	if (cog_predict_collision(obstacles, new_line)) candidates.push_back(waypoint);
	//	new_line = LineEq(car, waypoint + PosInfo(avoid_offset, 0));
	//	if (cog_predict_collision(obstacles, new_line)) candidates.push_back(waypoint + PosInfo(avoid_offset, 0));
	//	new_line = LineEq(car, waypoint - PosInfo(avoid_offset, 0));
	//	if (cog_predict_collision(obstacles, new_line)) candidates.push_back(waypoint - PosInfo(avoid_offset, 0));
	//}*/

	//for (const auto &obstacle : obstacles_raw) {
	//	LineEq new_line(car, cog_locate_conversion(sensing_info, obstacle.dist, obstacle.to_middle) + PosInfo(avoid_offset, 0));
	//	if (cog_predict_collision(obstacles, new_line)) candidates.push_back(cog_locate_conversion(sensing_info, obstacle.dist, obstacle.to_middle) + PosInfo(avoid_offset, 0));
	//}
	//for (const auto &obstacle : obstacles_raw) {
	//	LineEq new_line(car, cog_locate_conversion(sensing_info, obstacle.dist, obstacle.to_middle) - PosInfo(avoid_offset, 0));
	//	if (cog_predict_collision(obstacles, new_line)) candidates.push_back(cog_locate_conversion(sensing_info, obstacle.dist, obstacle.to_middle) - PosInfo(avoid_offset, 0));
	//}

	//std::sort(candidates.begin(), candidates.end(), [&obstacles, &car, &moving_angle, &grad_og](PosInfo p1, PosInfo p2) -> bool {
	//	LineEq line1(car, p1), line2(car, p2);
	//	float grad1 = line1.grad() < 0 ? -90 - atanf(line1.grad()) : 90 - atanf(line1.grad());
	//	float grad2 = line2.grad() < 0 ? -90 - atanf(line2.grad()) : 90 - atanf(line2.grad());
	//	float dist1 = car.dist(p1), dist2 = car.dist(p2);
	//	// return abs(grad1 - moving_angle) < abs(grad2 - moving_angle);
	//	return abs(grad1 - grad_og) < abs(grad2 - grad_og);
	//	float eval1 = 10 / cog_rate_line(obstacles, line1, 0) + abs(grad1 - grad_og);
	//	float eval2 = 10 / cog_rate_line(obstacles, line2, 0) + abs(grad2 - grad_og);
	//	return eval1 < eval2;
	//});
	//std::cout << "==== candidates ====\n";
	//for (const auto &candidate : candidates) {
	//	std::cout << "(" << candidate.x << ", " << candidate.y << ")\n";
	//}
	//if(!candidates.empty()) return *candidates.begin();
	//std::cout << "EMERGENCY\n";
	//return car + PosInfo(100, line.grad() * 100);
}