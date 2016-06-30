#ifndef _PANEL_H_
#define _PANEL_H_
#include "../library/util.h"
#include "../glut.h"


class Panel{//°‚Ìƒpƒlƒ‹
public:
	int team;
	glm::vec3 pos;
	void Draw();
	void CreatePanel();
	static void setPanel();
};



#endif