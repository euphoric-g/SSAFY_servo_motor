#include <utility>
#include "PosInfo.h"
#include "LineEq.h"
#include "CircEq.h"

std::pair<PosInfo, PosInfo> CircEq::operator*(LineEq rhs) {
	return rhs * CircEq(a, b, r);
}