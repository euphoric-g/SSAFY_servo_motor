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
