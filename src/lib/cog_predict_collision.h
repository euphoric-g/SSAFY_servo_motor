#pragma once

#include <vector>

#include "PosInfo.h"
#include "LineEq.h"

float cog_predict_collision(std::vector<PosInfo> obstacles, LineEq line);