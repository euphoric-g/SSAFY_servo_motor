#pragma once

#include <vector>

#include "PosInfo.h"

class RouteNode {
private:
public:
	float distance;
	float offset;
	PosInfo pos;
	float weight;
	bool offroad;
	float blocked_by_obstacle;
	RouteNode *last;
	float distance_from_last;
	float last_ccw;
	float ccw_sum;
	RouteNode() {}
	RouteNode(float distance, float offset) {}
	void operator*(RouteNode &rhs);
	void multiply(RouteNode &rhs, float to_middle);
};