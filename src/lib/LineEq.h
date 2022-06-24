#pragma once

#include "PosInfo.h"
#include "CircEq.h"
#include <utility>

class CircEq;

class LineEq {
private:
	bool initialized = true;
public:
	float a;
	float b;
	float c;
	LineEq() : initialized(false) {}
	LineEq(float a, float b, float c) : a(a), b(b), c(c) {}
	LineEq(float grad, PosInfo p);
	LineEq(PosInfo p1, PosInfo p2);
	LineEq operator+(LineEq rhs);
	LineEq operator-(LineEq rhs);
	PosInfo operator*(LineEq rhs);
	std::pair<PosInfo, PosInfo> operator*(CircEq rhs);
	float grad();
	float dist(PosInfo p);
};