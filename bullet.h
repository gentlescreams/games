#ifndef _BULLET_H_
#define _BULLET_H_
#include"flyingobject.h"


//
//弾の生成クラス
//


class  Bullet :public FlyingObject//たま
{
public:
	Bullet();
	Bullet(const glm::vec3& _pos, const glm::vec3& _speed, int _isDead,int _team ,int _bodyColor,float _Yaw);
	void Draw();
};

#endif