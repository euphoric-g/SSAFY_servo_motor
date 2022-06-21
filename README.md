# SSAFY_servo_motor

싸피레이스 자율주행 코드입니다.   
자세한 내용은 [요구사항명세서.hwp](요구사항명세서.hwp)를 참조하세요.


---


## 개발 가이드

respository를 clone 한 후 src/MyCar.vcxproj 파일을 열어서 작업해주세요.   
작업 후 SSAFY_servo_motor 폴더에서 커밋해주세요.   
개발 로그는 README.md 하단에 남겨주세요.   

### 필요 프로그램

Git GUI, Git BASH 등 버전 관리 프로그램   
Microsoft Visual Studio 2017 Community (Windows8.1 SDK 필수)   
싸피레이스 시뮬레이터(ssafy_sim_2022_0608_1800_license)   


### 새로운 함수를 추가하고 싶을 때

요구사항명세서에 새 함수에 대한 명세와 설명을 추가한 뒤 반드시 visual studio 내에서 새 cpp 파일을 추가해주세요.   
파일 생성시 하단의 경로가 [SSAFY_servo_motor\src\lib](/src/lib/)이 맞는지 확인해주세요.   
함수를 구현하였다면 [src.h](src/src.h) 헤더에서 새로 구현한 함수를 추가한 뒤 [MyCar.cpp](src/MyCar.cpp)에서 호출하여 사용합니다.


---


## 개발 로그


#### 20220617

* 개발 준비 완료 (다른 컴퓨터에서 작동 확인됨)

#### 20220620

* 직선, 원 연산용 LineEq, CircEq 클래스 추가
* 중앙선을 좌표평면으로 대응시키는 cog_waypoints_to_PosInfo 함수 구현

#### 20220621

* 직선의 내분점 계산을 위한 internal_division 함수 구현
* PosInfo 클래스에 normalize 함수 구현(방향을 유지하며 원점과의 거리를 1로 만듦)
* LineEq 클래스에 기울기를 반환하는 grad 함수 구현
* distance, to_middle 값 쌍을 좌표평면으로 대응시키기 위한 cog_locate_conversion 함수 구현
* 장애물 정보를 좌표평면으로 대응시키기 위한 cog_obstacles_to_PosInfo 함수 구현