#include"flyingobject.h"
#include"util.h"


void FlyingObject::Update(){


	pos += speed;//‰Á‘¬
	speed *= deceleration;//Œ¸‘¬

	//ù‰ñ
	yaw += yawSpeed;
	yawSpeed *= deceleration;
}



