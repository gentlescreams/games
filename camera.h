#ifndef CAMERA_H_
#define CAMERA_H_
#include "ship.h"
#include "glut.h"
#include "glm\glm.hpp"

//
//�J�����N���X
//

class Camera{
public:
	Camera(){};
	Camera(Ship *p);
	glm::vec3 pos;
	float yaw;//��]
	float yawSpeed;//��]���̃X�s�[�h
	void Draw(Ship *p);//�`��
	void Control(Ship *p);//����
	glm::mat4 project;//�ˉe�s��̎擾�ϐ�
	glm::mat4 modelview;//���f���r���[�̎擾�ϐ�

};

#endif 