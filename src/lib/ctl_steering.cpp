#include "ctl_steering.h"

#include "PosInfo.h"

float ctl_steering(Car::CarStateValues &sensing_info, WaypointInfo waypoint) {
	float ret = sensing_info.to_middle / -10.0f;
	
	vector <PosInfo> v = cog_waypoints_to_PosInfo(sensing_info);

	float rad, degree1, degree2, degree;

	// 전방 waypoint 2개가지고 사이각도로 주행
	// 전방 1개로 하니까 오차가 좀 크게 나오는거같음
	// 현재 제어 파트 구현사항 : 주행 방향에 따라 steering값 조절
	// 추가 구현 사항 : 도로의 외곽으로 갈수록 다시 중앙선 찾아 복귀하는 조정 값 구현 필요
	degree1 = atan(v[1].x / v[1].y) * 180 / acos(-1);
	degree2 = atan(v[2].x / v[2].y) * 180 / acos(-1);

	// 차량의 차선 중앙 정렬을 위한 미세 조정 값 계산
	float middle_add = (sensing_info.to_middle / 80) * -1;

	// 150과 90은 임의 보정값 -90에서 90으로 degree가 나오므로 90으로 나눠졌는데
	// 생각보다 steering값의 변화가 없음 그래서 전방 2개 waypoint로 구해서 더하게 했음
	ret = degree2 / 150;
	ret += degree1 / 90;
	ret += middle_add;

	//cout << "steering : " << ret << "\n\n\n";

	return ret;
}
