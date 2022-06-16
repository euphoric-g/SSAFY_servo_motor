#pragma once

class PosInfo {
private:
public:
	float x, y;
	PosInfo() : x(0), y(0) { }
	PosInfo(float _x, float _y) : x(_x), y(_y) { }
	PosInfo operator+(PosInfo rhs) { return PosInfo(x + rhs.x, y + rhs.y); }
	PosInfo operator-(PosInfo rhs) { return PosInfo(x - rhs.x, y - rhs.y); }
	float operator*(PosInfo rhs) { return x * rhs.x + y * rhs.y; }
	float operator/(PosInfo rhs) { return x * rhs.y - y * rhs.x; }
};