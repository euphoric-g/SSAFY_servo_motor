#include "internal_division.h"

PosInfo internal_division(PosInfo p1, PosInfo p2, float r1, float r2) {
	float x = (r1 * p2.x + r2 * p1.x) / (r1 + r2);
	float y = (r1 * p2.y + r2 * p1.y) / (r1 + r2);
	return PosInfo(x, y);
}