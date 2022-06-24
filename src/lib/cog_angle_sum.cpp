#include "cog_angle_sum.h"

float cog_angle_sum(Car::CarStateValues &sensing_info) {
	auto &angles = sensing_info.track_forward_angles;

	float sum = 0.0f;
	for (int i = 0; i < angles.size(); i++) {
		sum += abs(angles[i] - angles[i - 1]);
	}
	return sum;
}

float cog_angle_sum(Car::CarStateValues &sensing_info, int from, int to) {
	auto &angles = sensing_info.track_forward_angles;

	float sum = 0.0f;
	for (int i = from; i < to; i++) {
		sum += abs(angles[i] - angles[i - 1]);
	}
	return sum;
}