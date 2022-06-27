#include "cog_predict_collision.h"

#include <algorithm>
#include "grad_to_moving_angle.h"

int cog_predict_collision(std::vector<PosInfo> obstacles, PosInfo car, LineEq carLine, LineEq line) {
	if (obstacles.empty()) return 0;
	float closest_y = obstacles.begin()->y;

	std::vector<PosInfo> obs_group;

	for (auto &obstacle : obstacles) {
		if (abs(obstacle.y - closest_y) <= 1.0f) obs_group.push_back(obstacle);
	}

	for (auto &obstacle : obs_group) {
		if (!CircEq(obstacle, 4).intersections(line)) continue;
		if (obstacle.y < 60 && car.dist(obstacle) > 5.0f) {
			float dif = abs(grad_to_moving_angle(line.grad()) - grad_to_moving_angle(LineEq(car, obstacle).grad()));
			float dif2 = abs(grad_to_moving_angle(carLine.grad()) - grad_to_moving_angle(LineEq(car, obstacle).grad()));
			if (CircEq(obstacle, 3.1f).intersections(line) || dif < 5.0f || dif2 < 5.0f) return 1;
		}
	}
	return 0;
}

float cog_rate_line(std::vector<PosInfo> obstacles, LineEq line, float distance) {
	float score = 1e8;
	for (auto &obstacle : obstacles) {
		float s = line.dist(obstacle);
		if (s < score) score = s;
	}
	return score;
}