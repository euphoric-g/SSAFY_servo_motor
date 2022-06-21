#pragma once

#include <cmath>

class PosInfo {
private:
public:
	float x, y;
	PosInfo() : x(0), y(0) { }
	PosInfo(float _x, float _y) : x(_x), y(_y) { }
	PosInfo operator+(PosInfo rhs);
	PosInfo operator-(PosInfo rhs);
	float operator*(PosInfo rhs);
	float operator/(PosInfo rhs);
	PosInfo operator*(float coef);
	PosInfo normalize();
};