#define _USE_MATH_DEFINES
#define _CRT_SECURE_NO_WARNINGS

#include "../scene/scene_title.h"

#include<math.h>
#include<list>

#include "../ship.h"
#include"../util.h"
#include"../panel.h"

#include "../glut.h"
#include "../glm\glm.hpp"
#include "../glm\gtx\transform.hpp" 

extern int leftTime;
extern int frame;//	フレームカウント
extern std::list<Ship> ships;
extern Panel panels[FIELD_SIZE][FIELD_SIZE];

//タイトルシーン呼び出し関数
void scene_title(int &sceneType, unsigned char *keyboadKeys, unsigned char *lastKeyboardKeys, unsigned int downKeys) {
	if ((keyboadKeys[13] == 1 && lastKeyboardKeys[13] == 0) || (downKeys & GLUT_JOYSTICK_BUTTON_B)) {
		sceneType = SCENE_GAME;
		leftTime = 60 * 31;
		//プレイヤーの向き
		for (Ship& sp : ships) {
			sp.pos = sp.startPoint;
			glm::vec3 v = glm::vec3(FIELD_SIZE / 2, 0, FIELD_SIZE / 2) - sp.pos;
			sp.yaw = atan2f(v.x, v.z) * 180 / M_PI;
		}
		for (int z = 0; z < FIELD_SIZE; z++)
		{
			for (int x = 0; x < FIELD_SIZE; x++) {
				panels[z][x].team = TEAM_OTHER;
			}
		}
	}




}


void scene_title_draw() {
	glMatrixMode(GL_PROJECTION);//GLenum mode
	glLoadIdentity();//射影行列の初期化

	glMatrixMode(GL_MODELVIEW);//GLenum mode	カメラの設定
	glLoadIdentity();//初期化
	glColor3f(1, 1, 1);
	glTranslatef(-.3, .2, 0);//x,y,z
	glScalef(0.003, 0.003, 0.003);
	glLineWidth(3);// GLfloat width


	drawStroke("IKA");

	if (frame % 60 <30) {
		glLoadIdentity();//初期化
		glTranslatef(-.75, -.4, 0);//x,y,z
		glScalef(0.001, 0.001, 0.001);
		glLineWidth(1);
		drawStroke("player1 : BUTTON B");
		glLoadIdentity();//初期化
		glTranslatef(-.75, -.65, 0);//x,y,z
		glScalef(0.001, 0.001, 0.001);
		glLineWidth(1);
		drawStroke("player2 : ENTER");

	}

}
