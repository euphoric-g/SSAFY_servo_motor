#include "cog_waypoints_to_PosInfo.h"

#include <algorithm>
#include "LineEq.h"
#include "ccw.h"

std::vector<PosInfo> cog_waypoints_to_PosInfo(Car::CarStateValues &sensing_info) {
	using namespace std;

	vector<PosInfo> ret;

	auto &dists = sensing_info.distance_to_way_points;
	auto &angles = sensing_info.track_forward_angles;

	vector<pair<float, float>> waypoints;
	transform(dists.begin(), dists.end(), angles.begin(), back_inserter(waypoints), [](float a, float b) { return std::make_pair(a, b); });

	float to_middle = sensing_info.to_middle;
	float x = 0, y = sqrtf(waypoints[0].first * waypoints[0].first - to_middle * to_middle);
	ret.push_back(PosInfo(x, y));

	float last_decision = 0.0f;

	for (int i = 1; i < waypoints.size(); i++) {
		float &dist = waypoints[i].first, &angle = waypoints[i].second;
		float decision = angle;
		decision = (decision + waypoints[i - 1].second) / 2;
		float rad;
		LineEq approx;
		if (abs(decision) < 1e-4) {
			approx = LineEq(PosInfo(x, y), PosInfo(x, y + 1));
		}
		else {
			rad = 1 / tanf(decision * acosf(-1) / 180);
			approx = LineEq(rad, PosInfo(x, y));
		}
		CircEq circ(to_middle, 0, dist);
		auto candidates = approx * circ;

		auto calc_ccw = ccw((ret.size() > 1 ? ret[ret.size()-2] : PosInfo(0, 0)), PosInfo(x, y), candidates.first);
		PosInfo choose;
		if (calc_ccw * (decision - last_decision) <= 0) {
			choose = candidates.first;
			if ((ret.back() - choose)*(ret.back() - choose) > (ret.back()-candidates.second)*(ret.back()-candidates.second) * 2) choose = candidates.second;		}
		else {
			choose = candidates.second;
			if ((ret.back() - choose)*(ret.back() - choose) > (ret.back() - candidates.first)*(ret.back() - candidates.first) * 2) choose = candidates.first;		}

		/*
		std::cout << "i = " << i << "\n";
		std::cout << "current waypoint position : " << x << ", " << y << "\n";
		std::cout << "dist : " << dist << ", angle = " << angle << ", decision = " << decision << "\n";
		std::cout << "Line Equation : " << approx.a << ", " << approx.b << ", " << approx.c << "\n";
		std::cout << "Circle Equation : " << circ.a << ", " << circ.b << ", " << circ.r << "\n";
		std::cout << "candidates (" << candidates.first.x << ", " << candidates.first.y << "), (" << candidates.second.x << ", " << candidates.second.y << ")\n";
		std::cout << "calc_ccw : " << calc_ccw << ", decision_diff : " << (decision - last_decision) << "\n";
		std::cout << "ccw path : " << (ret.size() > 1 ? ret[ret.size()-2].x : 0) << ", " << (ret.size() > 1 ? ret[ret.size()-2].y : 0) << ") -> (" << x << ", " << y << ") -> (" << candidates.first.x << ", " << candidates.first.y << ")\n";
		std::cout << "(" << choose.x << ", " << choose.y << ") chosen\n";
		*/

		last_decision = decision;

		x = choose.x;
		y = choose.y;

		ret.push_back(choose);
	}

	return ret;
}