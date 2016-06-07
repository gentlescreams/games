#ifndef CAMERA_H_
#define CAMERA_H_
#include"vec3.h"
#include"ship.h"
#include "glut.h"

//
//
//

class Camera{
public:
	Camera(){};
	Camera(Ship *p);
	glm::vec3 pos;
	float yaw;
	float yawSpeed;
	void Draw(Ship *p);
	void Control(Ship *p);
	glm::mat4 project;//�ˉe�s��̎擾�ϐ�
	glm::mat4 modelview;//���f���r���[�̎擾�ϐ�

};

#endif 