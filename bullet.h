#ifndef _BULLET_H_
#define _BULLET_H_
#include"flyingobject.h"


//
//íeÇÃê∂ê¨ÉNÉâÉX
//


class  Bullet :public FlyingObject//ÇΩÇ‹
{
public:
	Bullet();
	Bullet(const glm::vec3& _pos, const glm::vec3& _speed, int _isDead,int _team ,int _bodyColor,float _Yaw);
	void Draw();
};

#endif