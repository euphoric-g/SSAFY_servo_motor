#include "CircEq.h"

std::pair<PosInfo, PosInfo> CircEq::operator*(LineEq rhs) {
	return rhs * CircEq(a, b, r);
}

int CircEq::intersections(LineEq rhs) {
	if (abs(rhs.b) <= 1e-4) {
		float d = a + rhs.c / rhs.a - r;
		if (abs(d) <= 1e-4) return 1;
		if (d > 0) return 2;
		return 0;
	}
	float dist = rhs.dist(PosInfo(a, b));
	if (abs(dist - r) <= 1e-4) return 1;
	if (dist > r) return 0;
	return 2;
}