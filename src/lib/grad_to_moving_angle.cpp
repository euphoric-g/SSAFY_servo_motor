#include "grad_to_moving_angle.h"

#include <cmath>

float grad_to_moving_angle(float grad) {
	float angle = atanf(grad) * 180 / acosf(-1);
	return angle < 0 ? -90 - angle : 90 - angle;
}