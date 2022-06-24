#include "LineEq.h"

#include <cmath>

LineEq::LineEq(PosInfo p1, PosInfo p2) {
	if (abs(p1.x - p2.x) <= 1e-4) {
		a = 1;
		b = 0;
		c = -p1.x;
	}
	else {
		a = (p2.y - p1.y);
		b = -(p2.x - p1.x);
		c = p1.y * (p2.x - p1.x) - p1.x * (p2.y - p1.y);
	}
}

LineEq::LineEq(float grad, PosInfo p) {
	*this = LineEq(p, p + PosInfo(1, grad));
}

LineEq LineEq::operator+(LineEq rhs) { return LineEq(a + rhs.a, b + rhs.b, c + rhs.c); }
LineEq LineEq::operator-(LineEq rhs) { return LineEq(a - rhs.a, b - rhs.b, c - rhs.c); }

PosInfo LineEq::operator*(LineEq rhs) {
	float &a1 = a, &b1 = b, &c1 = c, &a2 = rhs.a, &b2 = rhs.b, &c2 = rhs.c;
	float x, y;
	if (abs(b1) <= 1e-4 || abs(b2) <= 1e-4) {
		if (abs(b1) <= 1e-4 && abs(b2) > 1e-4) {
			x = -c1;
			y = (a2 * c1 - c2) / b2;
		}
		else if (abs(b2) <= 1e-4 && abs(b1) > 1e-4) {
			x = -c2;
			y = (a1 * c2 - c1) / b1;
		}
		else {
			return PosInfo(0, 100);
		}
	}
	else {
		x = (b1 * c2 - b2 * c1) / (a1 * b2 - a2 * b1);
		y = (-a1 * x / b1) - (c1 / b1);
	}
	return PosInfo(x, y);
}

std::pair<PosInfo, PosInfo> LineEq::operator*(CircEq rhs) {
	if (b == 0) {
		float d = (rhs.r * rhs.r) - (c / a + a)*(c / a + a);
		if (d > 0) {
			float x = -c / a;
			float y0 = b + sqrtf(d);
			float y1 = b - sqrtf(d);
			return std::make_pair(PosInfo(x, y0), PosInfo(x, y1));
		}
		return std::make_pair(PosInfo(), PosInfo());

	}
	float m = -a / b, n = -c / b;
	float d = (m * m * n * n) - (m * m + 1) * (n * n - rhs.r * rhs.r);
	if (d > 0) {
		float x0 = (-m * n - sqrtf(d)) / (m * m + 1);
		float x1 = (-m * n + sqrtf(d)) / (m * m + 1);
		float y0 = m * x0 + n;
		float y1 = m * x1 + n;
		return std::make_pair(PosInfo(x0, y0), PosInfo(x1, y1));
	}
	// b^2-4ac <= 0 (undefined)
	return std::make_pair(PosInfo(), PosInfo());
}

float LineEq::grad() {
	return -a / b;
}

float LineEq::dist(PosInfo p) {
	return abs(a * p.x + b * p.y + c) / sqrtf(a*a + b * b + c);
}