#include "PosInfo.h"

#include <cmath>

PosInfo PosInfo::operator+(PosInfo rhs) {
	return PosInfo(x + rhs.x, y + rhs.y);
}

PosInfo PosInfo::operator-(PosInfo rhs) {
	return PosInfo(x - rhs.x, y - rhs.y);
}

float PosInfo::operator*(PosInfo rhs) {
	return x * rhs.x + y * rhs.y;
}

float PosInfo::operator/(PosInfo rhs) {
	return x * rhs.y - y * rhs.x;
}

PosInfo PosInfo::operator*(float coef) {
	return PosInfo(coef * x, coef * y);
}

PosInfo PosInfo::normalize() {
	float f = sqrtf((*this) * (*this));
	return PosInfo(this->x / f, this->y / f);
}