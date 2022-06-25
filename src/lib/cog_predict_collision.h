#pragma once

#include <vector>

#include "PosInfo.h"
#include "LineEq.h"
#include "CircEq.h"

int cog_predict_collision(std::vector<PosInfo> obstacles, LineEq line);