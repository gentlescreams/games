#ifndef _FLYINGOBJECT_H_
#define _FLYINGOBJECT_H_
#include"util.h"
#include"glm\glm.hpp"


class  FlyingObject//Šî’êƒNƒ‰ƒX
{
public:

	glm::vec3 pos;
	glm::vec3 speed;
	int isDead;
	int team;
	int bodyColor;
	float yaw;
	float yawSpeed;
	float deceleration;
	void Update();
	virtual void Draw() = 0;//	ƒˆ‰¼‘zŠÖ”
};

#endif