#include "cog_road_departure.h"

bool cog_road_departure(Car::CarStateValues &sensing_info) {
	return abs(sensing_info.to_middle) > (sensing_info.half_road_limit < 3 ? sensing_info.half_road_limit : 3);
}