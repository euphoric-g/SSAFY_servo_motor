#include "RouteTable.h"
#include "LineEq.h"
#include "ccw.h"
#include "internal_division.h"
#include "cog_obstacles_to_PosInfo.h"
#include "cog_opponent_to_PosInfo.h"

std::pair<PosInfo, PosInfo> crossing_and_unit_vector(std::vector<PosInfo> &waypoints, float dist) {
	if (dist < sqrtf(waypoints[0] * waypoints[0])) {
		PosInfo crossing = internal_division(PosInfo(0, 0), waypoints[0], dist, sqrtf(waypoints[0] * waypoints[0]) - dist);
		LineEq crossing_line(LineEq(PosInfo(0, 0), waypoints[0]).grad(), crossing);
		PosInfo unit_vector = PosInfo(1, -1 / crossing_line.grad()).normalize();
		return std::make_pair(crossing, unit_vector);
	}

	float accumulate = sqrtf(waypoints[0] * waypoints[0]);
	int cursor = 1;

	PosInfo from = waypoints[cursor];
	PosInfo to;

	while (accumulate + 10.0 < dist) {
		cursor++;
		accumulate += 10.0;
	}
	if (cursor >= waypoints.size()) to = waypoints[19];
	else to = waypoints[cursor];
	from = waypoints[cursor - 1];

	PosInfo crossing = internal_division(from, to, dist - accumulate, 10 - (dist - accumulate));
	LineEq crossing_line(LineEq(from, to).grad(), crossing);
	PosInfo unit_vector = PosInfo(1, -1 / crossing_line.grad()).normalize();

	return std::make_pair(crossing, unit_vector);
}

RouteTable::RouteTable(Car::CarStateValues &sensing_info, std::vector<PosInfo> waypoints)
	: sensing_info(sensing_info), waypoints(waypoints) {
	car_moving_angle = sensing_info.moving_angle;
	car_to_middle = sensing_info.to_middle;

	grid_size = 0.5;
	rows = (int)(150.0 / grid_size);
	cols = (int)(15.0 / grid_size);
	center_col = cols / 2;

	table = std::vector<std::vector<RouteNode>>(rows, std::vector<RouteNode>(cols, RouteNode()));

	// std::cout << "RouteTable init...\ngrid_size = 0.5\nrows = " << rows << "\ncols = " << cols << "\n";
	for (int r = 0; r < rows; r++) {

		float dist = grid_size * r;
		auto cu = crossing_and_unit_vector(waypoints, dist);
		// std::cout << "initializing row = " << r << "\ndistance = " << dist << "\ncrossing = " << cu.first.x << ", " << cu.first.y << "\nunit_vector = " << cu.second.x << ", " << cu.second.y << '\n';
		for (int c = 0; c < cols; c++) {
			auto &tb = table[r][c];
			float os = (c - center_col) * grid_size;

			tb.distance = dist;
			tb.offset = os;
			tb.pos = cu.first + cu.second * os;
			tb.offroad = abs(os) <= half_road_limit;
			tb.weight = 1e8;
			tb.blocked_by_obstacle = 0.001f;
			tb.ccw_sum = 0.001f;

			for (auto &obstacle : obstacles) {
				float dif = (obstacle - tb.pos) * (obstacle - tb.pos);
				if (dif > tb.blocked_by_obstacle) tb.blocked_by_obstacle = 1000 / (dif * dif);
			}

			if (!r) {
				LineEq moving(1 / tanf(car_moving_angle * acos(-1) / 180), PosInfo(car_to_middle, 0));
				auto backpts = CircEq(PosInfo(car_to_middle, 0), 1) * moving;
				PosInfo backpoint = backpts.first.y > backpts.second.y ? backpts.second : backpts.first;
				float _ccw = ccw(backpoint, PosInfo(car_to_middle, 0), tb.pos);
				float d = (tb.pos - PosInfo(car_to_middle, 0))*(tb.pos - PosInfo(car_to_middle, 0));
				tb.weight = d + _ccw * _ccw * _ccw * _ccw;
				tb.distance_from_last = d;
				tb.last = nullptr;
				tb.last_ccw = _ccw;
			}
			else if (r == 1) {
				if (c - 1 >= 0) table[r - 1][c - 1].multiply(tb, car_to_middle);
				table[r - 1][c].multiply(tb, car_to_middle);
				if (c + 1 < cols) table[r - 1][c + 1].multiply(tb, car_to_middle);
			} else {
				for (int back = 0; back < 2; back++) {
					for (int lr = -back; lr < back; lr++) {
						if (c + lr >= 0 && c + lr < cols && r-back >= 1) {
							table[r - back][c + lr] * tb;
						}
					}
				}
			}
			// std::cout << "[" << r << "][" << c << "]=" << tb.weight << " ";
		}
		// std::cout << "\n";
	}
}

WaypointInfo RouteTable::getWaypoint() {
	WaypointInfo winfo;
	auto &waypoints = winfo.waypoints;
	RouteNode *route_trace = nullptr;
	float min_weight = 1e8;
	for (int i = 0; i < cols; i++) {
		if (table[rows - 1][i].weight < min_weight) {
			min_weight = table[rows - 1][i].weight;
			route_trace = &table[rows - 1][i];
		}
	}
	while (route_trace->last != nullptr) {
		waypoints.push_back(route_trace->pos);
		route_trace = route_trace->last;
	}
	return winfo;
}