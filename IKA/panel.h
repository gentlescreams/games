#ifndef _PANEL_H_
#define _PANEL_H_
#include"util.h"
#include"vec3.h"


class Panel{//°‚Ìƒpƒlƒ‹
public:
	int team;
	glm::vec3 pos;
	void draw();

	static void setPanel();
};



#endif