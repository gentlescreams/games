#include "scene_gamerule.h"
#include "../library/util.h"
#include "../glut.h"
#include"../field/panel.h"
#include <Xinput.h>


extern int frame;

void scene_rule(int &sceneType, unsigned char *keyboadKeys, unsigned char *lastKeyboardKeys, unsigned int downKeys) {

	//Ｂボタンが押されたら
	if ((downKeys & XINPUT_GAMEPAD_B ) || (keyboadKeys[13] == 1 && lastKeyboardKeys[13] == 0)) {

		sceneType = SCENE_GAME_INIT;
	}

}


void scene_rule_draw() {
	glMatrixMode(GL_PROJECTION);//GLenum mode
	glLoadIdentity();//射影行列の初期化

	glMatrixMode(GL_MODELVIEW);//GLenum mode	カメラの設定
	glLoadIdentity();//初期化

					 //タイトル画面の画像描画
	scrDraw("rule");
	//ボタンの文字を点滅しながら表示
	if (frame % 60 < 30) {
		glColor3f(0, 0, 0);
		glLineWidth(4);
		glLoadIdentity();//初期化
		glTranslatef(-.73, -.65, 0);//x,y,z
		glScalef(0.001, 0.001, 0.001);
		drawStroke("→");
	}

		glLoadIdentity();//初期化
		glTranslatef(-.75, -.65, 0);//x,y,z
		glScalef(0.0007, 0.0007, 0.0007);
		drawStroke(" push BUTTON B or ENTERKEY");

	
}