#pragma once

#include <vector>

#include "PosInfo.h"
#include "LineEq.h"
#include "CircEq.h"

int cog_predict_collision(std::vector<PosInfo> obstacles, PosInfo car, LineEq carLine, LineEq line);
float cog_rate_line(std::vector<PosInfo> obstacles, LineEq line, float distance);