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
	glm::mat4 project;//射影行列の取得変数
	glm::mat4 modelview;//モデルビューの取得変数

};

#endif 