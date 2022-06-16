#include "PosInfo.h"
#include "WaypointInfo.h"
#include "../DrivingInterface/DrivingInfo.h"

Car::ControlValues example(Car::CarStateValues &sensing_info) {
	Car::ControlValues car_controls;

	// ������ ���� ���� 1/2 �� ����
	float half_load_width = sensing_info.half_road_limit - 1.25f;

	// ���� �ڵ� ������ ���� ������ ������ Ŀ�� �� ��������
	int angle_num = (int)(sensing_info.speed / 45);
	float ref_angle = angle_num > 0 ? sensing_info.track_forward_angles[angle_num] : 0;

	// ������ ���� �߾� ������ ���� �̼� ���� �� ���
	float middle_add = (sensing_info.to_middle / 80) * -1;

	// ������ Ŀ�� ������ ���� throttle ���� �����Ͽ� �ӵ��� ������
	float throttle_factor = 0.6f / (abs(ref_angle) + 0.1f);
	if (throttle_factor > 0.11f) throttle_factor = 0.11f;   // throttle ���� �ִ� 0.81 �� ����
	float set_throttle = 0.7f + throttle_factor;
	if (sensing_info.speed < 60) set_throttle = 0.9f;  // �ӵ��� 60Km/h ������ ��� 0.9 �� ����
	if (sensing_info.speed > 80) set_throttle = 0.6f;  // �ִ�ӵ��� 80km/h�� ����

	// ������ Speed �� ���� �ڵ��� ������ ���� ������
	float steer_factor = sensing_info.speed * 1.5f;
	if (sensing_info.speed > 70) steer_factor = sensing_info.speed * 0.85f;
	if (sensing_info.speed > 100) steer_factor = sensing_info.speed * 0.7f;

	// (������ ������ Ŀ�� - �� ������ ���� ����) / (���� steer factor) ������ steering ���� ���
	float set_steering = (ref_angle - sensing_info.moving_angle) / (steer_factor + 0.001f);

	// ���� �߾����� ���� �߰��� �����
	set_steering += middle_add;

	//// ��� �� ���� ��Ȳ ó�� ////////////////////////////////////////////////////////////////////////////////////////
	bool full_throttle = true;
	bool emergency_brake = false;

	// ���� Ŀ���� ������ ū ��� �ӵ��� ������
	// ���� �ڵ� ������ ���� �����ϴ� Ŀ�� ���� ���� �� �ָ� �����Ͽ� �̸� �ӵ��� ����
	int road_range = (int)(sensing_info.speed / 30);
	for (int i = 0; i < road_range; i++) {
		float fwd_angle = abs(sensing_info.track_forward_angles[i]);
		if (fwd_angle > 45) {   // Ŀ�갡 45�� �̻��� ��� brake, throttle �� ����
			full_throttle = false;
		}
		if (fwd_angle > 80) {   // Ŀ�갡 80�� �̻��� ��� steering ���� �߰��� ����
			emergency_brake = true;
			break;
		}
	}

	// brake, throttle ����
	float set_brake = 0.0f;
	if (!full_throttle) {
		if (sensing_info.speed > 100) {
			set_brake = 0.3f;
		}
		if (sensing_info.speed > 120) {
			set_throttle = 0.7f;
			set_brake = 0.7f;
		}
		if (sensing_info.speed > 130) {
			set_throttle = 0.5f;
			set_brake = 1.0f;
		}
	}

	// steering ���� �߰��� ����
	if (emergency_brake) {
		if (set_steering > 0) {
			set_steering += 0.3f;
		}
		else {
			set_steering -= 0.3f;
		}
	}

	car_controls.throttle = set_throttle;
	car_controls.steering = set_steering;
	car_controls.brake = set_brake;
	return car_controls;
}