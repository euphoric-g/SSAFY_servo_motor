#include "RouteNode.h"

#include <cstdio>

#include "LineEq.h"
#include "ccw.h"

void RouteNode::operator*(RouteNode &rhs) {
	float obs_eval = blocked_by_obstacle;
	float dist_eval = sqrtf((pos - rhs.pos) * (pos - rhs.pos));
	float ccw_eval = abs(ccw(last->pos, pos, rhs.pos) - last->last_ccw);
	float dist_grad = abs(dist_eval - last->distance_from_last);
	float ccw_grad = ccw_sum + 0.1 * ccw_eval * ccw_eval;
	float weight_eval = weight + dist_eval + ccw_grad + obs_eval;
	if (weight_eval < rhs.weight) {
		rhs.ccw_sum = ccw_sum + ccw_eval;
		rhs.weight = weight_eval;
		rhs.distance_from_last = dist_eval;
		rhs.last_ccw = ccw_eval;
		rhs.last = this;
		
	}	
	/*if (obs_eval > 100) {
		printf("obs_eval = %.2f, dist = %.2f, last_ccw = %.2f, ccw_eval = %.2f, last_weight = %.2f\n", obs_eval, dist_eval, last->last_ccw, ccw_eval, weight);
		printf("new weight = weight[%.2f] + dist_eval[%.2f] + ccw_grad[%.2f] + obs_eval[%.2f] = %.2f\n", weight, dist_eval, ccw_grad, obs_eval, weight_eval);
	}*/
}

void RouteNode::multiply(RouteNode &rhs, float to_middle) {
	float obs_eval = blocked_by_obstacle;
	float dist_eval = sqrtf((pos - rhs.pos) * (pos - rhs.pos));
	float ccw_eval = abs(ccw(PosInfo(to_middle, 0), pos, rhs.pos) - last_ccw);
	float weight_eval = weight + dist_eval + 0.1 * ccw_eval * ccw_eval + obs_eval;
	if (weight_eval < rhs.weight) {
		rhs.weight = weight_eval;
		rhs.distance_from_last = dist_eval;
		rhs.last_ccw = ccw_eval;
		rhs.last = this;
	}
}
