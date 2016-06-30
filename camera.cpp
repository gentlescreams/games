#define _USE_MATH_DEFINES
#include<math.h>
#include<list>
#include"camera.h"
#include"ship.h"
#include"glut.h"

Camera::Camera(Ship *p){
	//回転値の初期値
	yaw =p->yaw;

	//カメラの初期値
	pos = glm::vec3(p->pos.x - sin(yaw*M_PI / 180) * 5, p->pos.y + 4, p->pos.z - cos(yaw*M_PI / 180) * 5);
	//スピードの初期速度
	yawSpeed = 0;

}

void Camera::Control(Ship *p){
	pos = glm::vec3(p->pos.x - sin(yaw*M_PI / 180) * 5, p->pos.y + 4, p->pos.z - cos(yaw*M_PI / 180) * 5);

}


void Camera::Draw(Ship *p){
	gluLookAt(
		pos.x, pos.y, pos.z,
		p->pos.x, p->pos.y + 1.5, p->pos.z,
		0, 1, 0);
}

