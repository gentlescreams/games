#ifndef _SHIP_H_
#define _SHIP_H_
#include"util.h"
#include"flyingobject.h"
#include"glm\glm.hpp"
#include "model.h"

class Ship :public FlyingObject{//Ž©‹@
public:
	glm::vec3 targetPoint;
	glm::vec3 startPoint;
	glm::vec3 scr_pos;
	int playerID;
	Ship(){ pos = glm::vec3(0, 0.5, 0); targetPoint = glm::vec3(0, 0.5, 0); }
	Ship(glm::vec3& _pos, int _team, int _bodyColor, int _playerID, const char* file_name);
	void Draw();

	void Control(float _x, float _y, unsigned int _downKeys, unsigned int _pressedKeys);
	void Control(unsigned char *keys, unsigned char *lastkeys);
	void Control();
	void Control(float x, float y);
	void playerArea();

	Model model;
private:
	float scale;

};

#endif