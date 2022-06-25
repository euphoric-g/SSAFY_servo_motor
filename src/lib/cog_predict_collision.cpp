#include "cog_predict_collision.h"

int cog_predict_collision(std::vector<PosInfo> obstacles, LineEq line) {
	for (auto &obstacle : obstacles) {
		if (CircEq(obstacle, 2).intersections(line)) return 1;
	}
	return 0;
}