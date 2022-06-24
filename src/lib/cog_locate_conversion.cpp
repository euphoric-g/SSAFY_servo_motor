#include "cog_locate_conversion.h"

#include "LineEq.h"
#include "internal_division.h"
#include "cog_waypoints_to_PosInfo.h"

PosInfo cog_locate_conversion(Car::CarStateValues &sensing_info, std::vector<PosInfo> waypoints, float distance, float offset) {

	if (distance < sqrtf(waypoints[0] * waypoints[0])) {
		PosInfo crossing = internal_division(PosInfo(0, 0), waypoints[0], distance, sqrtf(waypoints[0] * waypoints[0]) - distance);
		LineEq crossing_line(LineEq(PosInfo(0, 0), waypoints[0]).grad(), crossing);
		PosInfo unit_vector = PosInfo(1, -1/crossing_line.grad()).normalize();
		return crossing + unit_vector * offset;
	}

	float accumulate = sqrtf(waypoints[0] * waypoints[0]);
	int cursor = 1;

	PosInfo from = waypoints[cursor];
	PosInfo to;

	while (accumulate + 10.0 < distance) {
		cursor++;
		accumulate += 10.0;
	}
	/*
	if (cursor + 1 < waypoints.size()) to = waypoints[cursor + 1];
	else {
		float rad = 1 / tan(sensing_info.track_forward_angles[19] * acos(-1) / 180);
		to = from + PosInfo(1, LineEq(rad, from).grad()).normalize() * 10;
	}
	*/
	if (cursor >= waypoints.size()) to = waypoints[19];
	else to = waypoints[cursor];
	from = waypoints[cursor - 1];

	PosInfo crossing = internal_division(from, to, distance - accumulate, 10 - (distance - accumulate));
	LineEq crossing_line(LineEq(from, to).grad(), crossing);
	PosInfo unit_vector = PosInfo(1, -1/crossing_line.grad()).normalize();

	//std::cout << "locate_conversion distance : " << distance << ", offset : " << offset << "\n";
	//std::cout << "accumulate : " << accumulate << ", cursor : " << cursor << "\n";
	//std::cout << "from : " << from.x << ", " << from.y << ")\n";
	//std::cout << "to : " << to.x << ", " << to.y << "\n";
	//std::cout << "crossing : " << crossing.x << ", " << crossing.y << " = internal_division(from, to) with ratio " << (distance - accumulate) << " : " << (10 - (distance - accumulate)) << "\n";
	//std::cout << "crossing_line : (" << crossing_line.a << ")x+(" << crossing_line.b << ")y+" << crossing_line.c << "=0\n";
	//std::cout << "unit_vector : " << unit_vector.x << ", " << unit_vector.y << "\n";
	//std::cout << "return : " << (crossing + unit_vector * offset).x << ", " << (crossing + unit_vector * offset).y << "\n";

	return crossing + unit_vector * offset;
}

PosInfo cog_locate_conversion(Car::CarStateValues &sensing_info, float distance, float offset) {
	return cog_locate_conversion(sensing_info, cog_waypoints_to_PosInfo(sensing_info), distance, offset);
}