#include <iostream>
#include <algorithm>
#include <vector>
#include "RuleBasedDriving.h"
#include "src.h"

using namespace std;
using namespace Car;

bool is_debug = true;
bool enable_api_control = false;	// true(Controlled by code) /false(Controlled by keyboard)

void test_two_line() {
	while (1) {
		cout << "Enter a, b, c for line equation 1 (ax + by + c = 0) : ";
		float a, b, c;
		cin >> a >> b >> c;
		LineEq line1(a, b, c);
		cout << "Enter a, b, c for line equation 2 (ax + by + c = 0) : ";
		cin >> a >> b >> c;
		LineEq line2(a, b, c);
		PosInfo crossing = line1 * line2;
		cout << "crossing at (" << crossing.x << ", " << crossing.y << ")\n";
	}
}

void test_line_eq() {
	while (1) {
		cout << "Enter slope and a point for line equation : ";
		float slope, x, y;
		cin >> slope >> x >> y;
		LineEq line(slope, PosInfo(x, y));
		cout << line.a << "x + (" << line.b << ")y + (" << line.c << ") = 0\n";
	}
}

void test_line_circle() {
	while (1) {
		cout << "Enter a, b, r for circle equation ((x-a)^2 + (y-b)^2 = r^2) : ";
		float a, b, c;
		cin >> a >> b >> c;
		CircEq circ(a, b, c);
		cout << "Enter a, b, c for line equation (ax + by + c = 0) : ";
		cin >> a >> b >> c;
		LineEq line(a, b, c);
		auto crossing = line * circ;
		cout << "crossing at (" << crossing.first.x << ", " << crossing.first.y << "), (" << crossing.second.x << ", " << crossing.second.y << ")\n";
	}
}

ControlValues control_driving(CarStateValues sensing_info)
{
	// test_two_line();
	// test_line_eq();
	// test_line_circle();

	/*
	cout << "===========================================================\n";
	for (auto &waypoint : cog_waypoints_to_PosInfo(sensing_info)) {
		cout << "(" << waypoint.x << ", " << waypoint.y << ")\n";
	}
	cout << "===========================================================\n";
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
	car_controls = example(sensing_info);


	if (is_debug)
	{
		cout << "[MyCar] steering:" << car_controls.steering << ", throttle:" << car_controls.throttle
			 << ", brake:" << car_controls.brake << endl;
	}
	//
	// Editing area ends
	// ===========================================================

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
