#include "PosInfo.h"

float ccw(PosInfo p1, PosInfo p2, PosInfo p3) {
	return (p2 - p1) / (p3 - p2);
}