#include"flyingobject.h"
#include"util.h"


void FlyingObject::Update(){


	pos += speed;//����
	speed *= deceleration;//����

	//����
	yaw += yawSpeed;
	yawSpeed *= deceleration;
}



