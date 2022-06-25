#pragma once

#include "PosInfo.h"
#include "LineEq.h"
#include <utility>

class LineEq;

class CircEq {
private:
	bool initialized = true;
public:
	float a;
	float b;
	float r;
	CircEq() : initialized(false) {}
	CircEq(float a, float b, float r) : a(a), b(b), r(r) {}
	CircEq(PosInfo p1, float r) : a(p1.x), b(p1.y), r(r) {}
	std::pair<PosInfo, PosInfo> operator*(LineEq rhs);
	int intersections(LineEq rhs);
};