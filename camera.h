#ifndef CAMERA_H_
#define CAMERA_H_
#include "ship.h"
#include "glut.h"
#include "glm\glm.hpp"

//
//カメラクラス
//

class Camera{
public:
	Camera(){};
	Camera(Ship *p);
	glm::vec3 pos;
	float yaw;//回転
	float yawSpeed;//回転時のスピード
	void Draw(Ship *p);//描画
	void Control(Ship *p);//挙動
	glm::mat4 project;//射影行列の取得変数
	glm::mat4 modelview;//モデルビューの取得変数

};

#endif 