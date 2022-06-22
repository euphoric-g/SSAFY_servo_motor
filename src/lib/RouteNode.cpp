#include "RouteNode.h"

#include "LineEq.h"
#include "ccw.h"

void RouteNode::operator*(RouteNode &rhs) {
	float obs_eval = blocked_by_obstacle;
	float dist_eval = (pos - rhs.pos) * (pos - rhs.pos);
	float ccw_eval = abs(ccw(last->pos, pos, rhs.pos));
	float dist_grad = abs(dist_eval - last->distance_from_last);
	float ccw_grad = ccw_sum + 100 * ccw_eval * ccw_eval;
	float weight_eval = weight + dist_eval + ccw_grad * ccw_grad * ccw_grad + obs_eval;
	if (weight_eval < rhs.weight) {
		rhs.ccw_sum = ccw_sum + ccw_eval;
		rhs.weight = weight_eval;
		rhs.distance_from_last = dist_eval;
		rhs.last_ccw = ccw_eval;
		rhs.last = this;
	}
}

void RouteNode::multiply(RouteNode &rhs, float to_middle) {
	float obs_eval = blocked_by_obstacle;
	float dist_eval = (pos - rhs.pos) * (pos - rhs.pos);
	float ccw_eval = ccw(PosInfo(to_middle, 0), pos, rhs.pos);
	float weight_eval = weight + dist_eval + ccw_eval * ccw_eval * ccw_eval + obs_eval;
	if (weight_eval < rhs.weight) {
		rhs.weight = weight_eval;
		rhs.distance_from_last = dist_eval;
		rhs.last_ccw = ccw_eval;
		rhs.last = this;
	}
}