#include "flyingobject.h"
#include "./library/util.h"


void FlyingObject::Update(){


	pos += speed;//����
	speed *= deceleration;//����

	//����
	yaw += yawSpeed;
	yawSpeed *= deceleration;
}



