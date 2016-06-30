#define _USE_MATH_DEFINES
#define _CRT_SECURE_NO_WARNINGS

#include "../scene/scene_title.h"

#include<math.h>
#include<list>

#include "../ship.h"
#include"../library/util.h"
#include"../field/panel.h"

#include "../glut.h"
#include "../glm\glm.hpp"
#include "../glm\gtx\transform.hpp" 
#include "../manager/sounds_manager.h"
#include "../manager/texture_manager.h"
#include <Xinput.h>

extern int leftTime;
extern int frame;//	フレームカウント
extern std::list<Ship> ships;
extern Panel panels[FIELD_SIZE][FIELD_SIZE];


//タイトルシーン呼び出し関数
void scene_title(int &sceneType, unsigned char *keyboadKeys, unsigned char *lastKeyboardKeys, unsigned int downKeys) {

	//エンターキー　Ｂボタンが押されたら
	if ((downKeys & XINPUT_GAMEPAD_B) || (keyboadKeys[13] == 1 && lastKeyboardKeys[13] == 0)) {
		//	bgmの停止
		SoundsManager::GetInstance()->StopBGM();

		//se再生
		SoundsManager::GetInstance()->PlaySE(CRI_GAME_SOUNDS_SE_BUTTON);


		leftTime = 60 * 31;

		//プレイヤーの向き
		for (Ship& sp : ships) {
			sp.pos = sp.startPoint;
			glm::vec3 v = glm::vec3(FIELD_SIZE / 2, 0, FIELD_SIZE / 2) - sp.pos;
			sp.yaw = atan2f(v.x, v.z) * 180 / M_PI;

			printf("a");
		}

		//フィールドパネルの初期カラー設定
		for (int z = 0; z < FIELD_SIZE; z++)
		{
			for (int x = 0; x < FIELD_SIZE; x++) {
				panels[z][x].team = TEAM_OTHER;
			}
		}
		//ルールシーンへ
		sceneType = SCENE_GAMERULE;

	}
}


void scene_title_draw() {
	glMatrixMode(GL_PROJECTION);//GLenum mode
	glLoadIdentity();//射影行列の初期化

	glMatrixMode(GL_MODELVIEW);//GLenum mode	カメラの設定
	glLoadIdentity();//初期化

	//タイトル画面の画像描画
	scrDraw("title");

	//ボタンの文字を点滅しながら表示
	if (frame % 60 <30) {
		glColor3f(0, 0, 0);
		glLoadIdentity();//初期化
		glTranslatef(-.75, -.4, 0);//x,y,z
		glScalef(0.001, 0.001, 0.001);
		glLineWidth(3);
		drawStroke("2player games!");
		glLoadIdentity();//初期化
		glTranslatef(-.75, -.65, 0);//x,y,z
		glScalef(0.0007, 0.0007, 0.0007);
		drawStroke(" push BUTTON B or ENTERKEY");

	}
}
