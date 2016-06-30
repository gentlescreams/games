#define _USE_MATH_DEFINES
#include<math.h>
#include<list>
#include"camera.h"
#include"ship.h"
#include"glut.h"

Camera::Camera(Ship *p){
	//��]�l�̏����l
	yaw =p->yaw;

	//�J�����̏����l
	pos = glm::vec3(p->pos.x - sin(yaw*M_PI / 180) * 5, p->pos.y + 4, p->pos.z - cos(yaw*M_PI / 180) * 5);
	//�X�s�[�h�̏������x
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

