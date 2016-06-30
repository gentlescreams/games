#define _CRT_SECURE_NO_WARNINGS
#include "scene_resurt.h"
#include <stdio.h>
#include "../library/util.h"
#include "../glut.h"
#include "../manager/sounds_manager.h"
#include "../manager/texture_manager.h"
#include <Xinput.h>

extern int leftTime;
extern int panel_count_player;
extern int panel_count_enemy;
extern int frame;
extern int width;
extern int height;
void scene_resurt(int &sceneType, unsigned char *keyboadKeys, unsigned char *lastKeyboardKeys, unsigned int downKeys)
{
	/*bボタンが押されたらタイトルシーンへの移行（初期化に）*/
	if ((downKeys &XINPUT_GAMEPAD_B)||(keyboadKeys[13] == 1 && lastKeyboardKeys[13] == 0))
	{

		/*ｂｇｍ停止*/
		SoundsManager::GetInstance()->StopBGM();

		//seの再生
		SoundsManager::GetInstance()->PlaySE(CRI_GAME_SOUNDS_SE_BUTTON);

		leftTime = 0;
		sceneType = SCENE_TITLE_INIT;
	}

}

void scene_resurt_draw() {
	//画面分割の初期化
	glViewport(0, 0, width, height);

	glMatrixMode(GL_PROJECTION);//GLenum mode
	glLoadIdentity();//射影行列の初期化

	glMatrixMode(GL_MODELVIEW);//GLenum mode	カメラの設定
	glLoadIdentity();//初期化

	//リザルト画面の画像の描画
	scrDraw("resurt");

	/*塗られたパネルの枚数を％で保持*/
	float p = (float)panel_count_player / (float)(FIELD_SIZE*FIELD_SIZE) * 100.0f;
	int pp = p;

	char str[256];
	sprintf(str, "%d %%", pp);
	glMatrixMode(GL_PROJECTION);//GLenum mode
	glLoadIdentity();//射影行列の初期化
	glMatrixMode(GL_MODELVIEW);//GLenum mode	カメラの設定
	glLoadIdentity();//初期化
	glLineWidth(3);
	setColor(TEAM_PLAYER);
	glTranslatef(-.7, .2, 0);//x,y,z
	glScalef(0.00075, 0.00075, 0.00075);
	drawStroke("PLAYER1 TEAM:");
	glLoadIdentity();//初期化
	glTranslatef(.15, .2, 0);//x,y,z
	glScalef(0.00075, 0.00075, 0.00075);
	drawStroke(str);


	p = (float)panel_count_enemy / (float)(FIELD_SIZE*FIELD_SIZE) * 100.0f;
	pp = p;
	sprintf(str, "%d %%", pp);
	glLoadIdentity();//初期化
	setColor(TEAM_ENEMY);
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
		setColor(TEAM_ENEMY);
		glTranslatef(0, -0.7, 0);//x,y,z
		glScalef(0.00075, 0.00075, 0.00075);
		drawStroke("PLAYER2 WIN!!!!");

	}//プレイヤー１がプレイヤー2より塗った数が多かったら
	else if (panel_count_player>panel_count_enemy)
	{
		glLoadIdentity();//初期化
		setColor(TEAM_PLAYER);
		glTranslatef(0, -0.7, 0);//x,y,z
		glScalef(0.00075, 0.00075, 0.00075);
		drawStroke("PLAYER1 WIN!!!!");
	}
	if (frame % 60 < 30) {
		glLoadIdentity();//初期化
		glColor3f(0, 0, 0);
		glTranslatef(0, -0.8, 0);//x,y,z
		glScalef(0.0005, 0.00055, 0.0005);
		drawStroke("push ENTER / BUTTON B");
	}

}
