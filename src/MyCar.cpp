#include <iostream>
#include <algorithm>
#include <vector>
#include <numeric>
#include "RuleBasedDriving.h"
#include "src.h"

using namespace std;
using namespace Car;

bool is_debug = false;
bool enable_api_control = true;	// true(Controlled by code) /false(Controlled by keyboard)

PosInfo last_target = PosInfo();

ControlValues control_driving(CarStateValues sensing_info)
{

	// cout << "========================= waypoints ==========================\n";
	auto waypoints = cog_waypoints_to_PosInfo(sensing_info);
	auto obstacles = cog_obstacles_to_PosInfo(sensing_info);
	
	for (auto &waypoint : waypoints) {
		cout << "(" << waypoint.x << ", " << waypoint.y << ")\n";
	}
	PosInfo car = PosInfo(sensing_info.to_middle, 0);
	LineEq CarLine = LineEq(1 / tanf(sensing_info.moving_angle * acosf(-1) / 180), car);

	cout << "CarLine\n";
	cout << CarLine.a << "x" << (CarLine.b >= 0 ? "+" : "") << CarLine.b << "y" << (CarLine.c >= 0 ? "+" : "") << CarLine.c << "=0\n";
	
	auto line = cog_road_departure(sensing_info) ? LineEq(PosInfo(sensing_info.to_middle, 0), waypoints[2]) : LineEq(waypoints[0], waypoints[4]);
	auto line2 = LineEq(waypoints[waypoints.size()-1], waypoints[waypoints.size()-10]);
	cout << line.a << "x" << (line.b >= 0 ? "+" : "") << line.b << "y" << (line.c >= 0 ? "+" : "") << line.c << "=0\n";

	PosInfo target = line * line2;
	if (waypoints[waypoints.size()-5].dist(target) < 15.0f) {
		cout << "Target is close to endpoint, target point\n(" << target.x << ", " << target.y << ")\n";
		target = waypoints[waypoints.size() - 1];
	}

	cout << "Last Target Point\n(" << last_target.x << ", " << last_target.y << ")\n";
	last_target = target = internal_division(target, last_target, 1, 1 + sensing_info.speed / 50);
	cout << "Target Point\n(" << target.x << ", " << target.y << ")\n";

	if (cog_predict_collision(obstacles, car, CarLine, LineEq(car, target))) {
		target = cog_obstacle_avoidance(sensing_info, obstacles, LineEq(car, target));
		cout << "[avoidance system] target point modified\n(" << target.x << ", " << target.y << ")\n";
	}

	cout << "========================= obstacles ==========================\n";
	for (auto &obstacle : obstacles) {
		cout << "(" << obstacle.x << ", " << obstacle.y << ")\n";
	}
	/*
	cout << "========================= RouteTable =========================\n";

	RouteTable rt(sensing_info, cog_waypoints_to_PosInfo(sensing_info));
	
	WaypointInfo routes = rt.getWaypoint2();
	
	for (const auto &waypoint : routes.waypoints) {
		cout << "(" << waypoint.x << ", " << waypoint.y << ")\n";
	}

	cout << "==============================================================\n";
	*/

	if (is_debug)
	{
		cout << "=========================================================" << endl;
		cout << "[MyCar] to middle: " << sensing_info.to_middle << endl;

		cout << "[MyCar] collided: " << sensing_info.collided << endl;
		cout << "[MyCar] car speed: " << sensing_info.speed << "km/h" << endl;

		cout << "[MyCar] is moving forward: " << sensing_info.moving_forward << endl;
		cout << "[MyCar] moving angle: " << sensing_info.moving_angle << endl;
		cout << "[MyCar] lap_progress: " << sensing_info.lap_progress << endl;

		cout << "[MyCar] track_forward_angles: ";
		for (int i = 0; i < sensing_info.track_forward_angles.size(); i++)
		{
			cout << sensing_info.track_forward_angles[i] << ", ";
		}
		cout << endl;

		cout << "[MyCar] track_forward_obstacles: ";
		for (int i = 0; i < sensing_info.track_forward_obstacles.size(); i++)
		{
			cout << "{dist: " << sensing_info.track_forward_obstacles[i].dist 
				 << ", to_middle: " << sensing_info.track_forward_obstacles[i].to_middle << "}, ";
		}
		cout << endl;

		cout << "[MyCar] opponent_cars_info: ";
		for (int i = 0; i < sensing_info.opponent_cars_info.size(); i++)
		{
			cout << "{dist: " << sensing_info.opponent_cars_info[i].dist 
				 << ", to_middle: " << sensing_info.opponent_cars_info[i].to_middle 
				 << ", speed: " << sensing_info.opponent_cars_info[i].speed << "km/h}, ";
		}
		cout << endl;

		cout << "[MyCar] distance_to_way_points: ";
		for (int i = 0; i < sensing_info.distance_to_way_points.size(); i++)
		{
			cout << sensing_info.distance_to_way_points[i] << ", ";
		}
		cout << endl;

		cout << "=========================================================" << endl;
	}

	ControlValues car_controls;
	// ===========================================================
	// Area for writing code about driving rule ==================
	// ===========================================================
	// Editing area starts from here
	//	

	// 시나리오 1. Moving straight forward
	car_controls.steering = 0;
	car_controls.throttle = 1;
	car_controls.brake = 0;

	// 시나리오 2. basic 예제
	// car_controls = example(sensing_info);

	float theta_car = sensing_info.moving_angle;
	float theta_target = target.y != 0 ? atanf(target.x / target.y) * 180 / acosf(-1) : 0;
	float steering_angle = theta_target - theta_car;
	float speed_limit = 140 - 1 * (abs(grad_to_moving_angle(LineEq(car, waypoints[8]).grad())) - 15) - 1 * (abs(steering_angle) - 15);
	if (speed_limit < 90) speed_limit = 90;

	// car_controls.brake = abs(steering_angle / 1000);
	if (sensing_info.speed < speed_limit/2) car_controls.brake = 0;
	if (sensing_info.speed > speed_limit) {
		car_controls.brake = abs(steering_angle / 1000) + (sensing_info.speed - speed_limit) / 25;
		if (car_controls.brake >= 1.0) car_controls.brake = 1;
	}
	car_controls.throttle = 1 - car_controls.brake;
	car_controls.steering = steering_angle / 90;

	cout << "[MyCar] Target : (" << target.x << ", " << target.y << "), steering_angle = " << steering_angle << "\n";
	cout << "theta_car = moving_angle[" << sensing_info.moving_angle << "]\n";
	cout << "theta_target = atan(target.x / target.y)[" << atanf(target.x / target.y) << "] * 180 / pi = " << theta_target << "\n";
	cout << "SPEED LIMIT = " << speed_limit << "\n";
	if (cog_road_departure(sensing_info)) cout << "[ROAD DEPARTURE DETECTED]\n";
	cout << "brake = " << car_controls.brake << ", throttle = " << car_controls.throttle << ", steering = " << car_controls.steering << "\n";

	if (is_debug)
	{
		cout << "[MyCar] steering:" << car_controls.steering << ", throttle:" << car_controls.throttle
			 << ", brake:" << car_controls.brake << endl;
	}
	//
	// Editing area ends
	// ===========================================================
	if (cog_distance_to_closest_obstacle(sensing_info, obstacles) < 3 && sensing_info.speed < 5) {
		car_controls.throttle = -1;
		car_controls.brake = 0;
		car_controls.steering = 0;
	}

	return car_controls;
}

int main()
{
	// ===========================================================
	// Don't modify below area. ==================================
	// ===========================================================
	cout << "[MyCar] Start Bot! (CPP)" << endl;

	int return_code = StartDriving(control_driving, enable_api_control);

	cout << "[MyCar] End Bot! (CPP)" << endl;

	// ==========================================================

	return return_code;
}