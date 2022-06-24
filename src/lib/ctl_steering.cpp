#include "ctl_steering.h"

#include "PosInfo.h"

float ctl_steering(Car::CarStateValues &sensing_info, WaypointInfo waypoint) {
	float ret = sensing_info.to_middle / -10.0f;
	
	vector <PosInfo> v = cog_waypoints_to_PosInfo(sensing_info);
	vector <PosInfo> obs = cog_obstacles_to_PosInfo(sensing_info);

	float degree1, degree2, obstacles_degree;

	// 전방 waypoint 2개가지고 사이각도로 주행
	// 전방 1개로 하니까 오차가 좀 크게 나오는거같음
	// 현재 제어 파트 구현사항 : 주행 방향에 따라 steering값 조절
	degree1 = atan(v[1].x / v[1].y) * 180 / acos(-1);
	degree2 = atan(v[2].x / v[2].y) * 180 / acos(-1);

	
	// 아래 구현사항은 현재 example throttle 값을 토대로 보정값 조절한거임
	// example throttle은 생각보다 속도가 많이 느려서 throttle을 높이면 보정값 변경 필요 예상
	// 차량의 Speed 에 따라서 핸들을 돌리는 값을 조정함
	float steer_factor = sensing_info.speed * 1.5f;
	if (sensing_info.speed > 70) steer_factor = sensing_info.speed * 0.85f;
	if (sensing_info.speed > 100) steer_factor = sensing_info.speed * 0.7f;


	// (참고할 전방의 커브 - 내 차량의 주행 각도) / (계산된 steer factor) 값으로 steering 값을 계산
	ret = ((degree1 + degree2) / 2 - sensing_info.moving_angle) / (steer_factor + 0.001f);

	// 차량의 차선 중앙 정렬을 위한 미세 조정 값 계산
	float middle_add = (sensing_info.to_middle / 80) * -1;

	ret += middle_add;

	cout << "steering : " << ret << "\n\n\n";

	return ret;
}
