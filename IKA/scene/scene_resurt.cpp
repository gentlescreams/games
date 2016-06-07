#define _CRT_SECURE_NO_WARNINGS
#include "scene_resurt.h"
#include <stdio.h>
#include "../util.h"


extern int leftTime;
extern int panel_count_player;
extern int panel_count_enemy;

extern int width;
extern int height;


void scene_resurt(int &sceneType, unsigned char *keyboadKeys, unsigned char *lastKeyboardKeys, unsigned int downKeys)
{
	if ((keyboadKeys[13] == 1 && lastKeyboardKeys[13] == 0) || (downKeys & GLUT_JOYSTICK_BUTTON_B))
	{
		leftTime = 0;
		sceneType = SCENE_TITLE;
	}

}

void scene_resurt_draw() {
	//画面分割の初期化
	glViewport(0, 0, width, height);


	/*塗られたパネルの枚数を％で保持*/
	float p = (float)panel_count_player / (float)(FIELD_SIZE*FIELD_SIZE) * 100.0f;
	int pp = p;

	char str[256];
	sprintf(str, "%d %%", pp);
	glMatrixMode(GL_PROJECTION);//GLenum mode
	glLoadIdentity();//射影行列の初期化
	glMatrixMode(GL_MODELVIEW);//GLenum mode	カメラの設定
	glLoadIdentity();//初期化
	setColor(TEAM_PLAYER_SHIP);
	glTranslatef(-.7, .5, 0);//x,y,z
	glScalef(0.00075, 0.00075, 0.00075);
	drawStroke("PLAYER1 TEAM:");
	glLoadIdentity();//初期化
	glTranslatef(.15, .5, 0);//x,y,z
	glScalef(0.00075, 0.00075, 0.00075);
	drawStroke(str);


	p = (float)panel_count_enemy / (float)(FIELD_SIZE*FIELD_SIZE) * 100.0f;
	pp = p;
	sprintf(str, "%d %%", pp);
	glLoadIdentity();//初期化
	setColor(TEAM_ENEMY_SHIP);
	glTranslatef(-.7, 0, 0);//x,y,z
	glScalef(0.00075, 0.00075, 0.00075);
	drawStroke("PLAYER2 TEAM:");
	glLoadIdentity();
	glTranslatef(.15, 0, 0);//x,y,z
	glScalef(0.00075, 0.00075, 0.00075);
	drawStroke(str);

	//プレイヤー２がプレイヤー1より塗った数が多かったら
	if (panel_count_enemy>panel_count_player)
	{
		glLoadIdentity();//初期化
		setColor(TEAM_ENEMY_SHIP);
		glTranslatef(0, -0.7, 0);//x,y,z
		glScalef(0.00075, 0.00075, 0.00075);
		drawStroke("PLAYER2 WIN!!!!");

	}//プレイヤー１がプレイヤー2より塗った数が多かったら
	else if (panel_count_player>panel_count_enemy)
	{
		glLoadIdentity();//初期化
		setColor(TEAM_PLAYER_SHIP);
		glTranslatef(0, -0.7, 0);//x,y,z
		glScalef(0.00075, 0.00075, 0.00075);
		drawStroke("PLAYER1 WIN!!!!");
	}

	glLoadIdentity();//初期化
	glColor3f(0, 1, 1);
	glTranslatef(0, -0.8, 0);//x,y,z
	glScalef(0.0005, 0.00055, 0.0005);
	drawStroke("push ENTER / BUTTON B");


}
