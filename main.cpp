
//------------
//読み込むヘッダー
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <conio.h>
#define _USE_MATH_DEFINES
#include <math.h>
#include <list>
#include <stdlib.h>
#include <time.h>
#include "scene.h"
#include "./field/panel.h"
#include "./library/util.h"
#include "flyingobject.h"
#include "ship.h"
#include "bullet.h"
#include "camera.h"
#include "model.h"
#include "./controllers/pad_controller.h"

#include "./manager/pc/cri_adx2le.h"
#include "glm\glm.hpp"
#include "glm\gtx\transform.hpp" 
#include "glut.h"

extern PadController gamePad[MAX_CONTROLLERS];

/*画面のサイズ*/
int width = 800;
int height = 680;

int frame = 0;//	フレームカウント
int sceneType = SCENE_TITLE_INIT;
bool is_game_set = false;


//2次元配列
extern Panel panels[FIELD_SIZE][FIELD_SIZE];

Camera camera;//カメラ実体
Model model;//モデル読み込み実体
std::list<Ship> ships;
std::list<Bullet> bulletList;

/*キーボードの状態の取得*/
unsigned char keyboadKeys[256] = {};
unsigned char lastKeyboardKeys[256] = {};
int specialKeys[256] = {};
int lastSpesialKeys[256] = {};

//押されているとき
void keyboard(unsigned char key, int x, int y) {

	keyboadKeys[key] = 1;

}

//	キーボードが離されたとき
void keyboardUp(unsigned char key, int x, int y) {
	keyboadKeys[key] = 0;

}


void timer(int value) {

	glutForceJoystickFunc();//joystickのデータを取得してジョイスティックコールバック関数を呼ぶ
	glutTimerFunc(
		1000 / 60,		//unsigned int millis,タイマーを何ミリ秒後起動する
		timer,	//void (GLUTCALLBACK *func)(int value),
		0);		//int value

				/*フレームカウント*/
	frame++;

	//ジョイスティックのコントロール


	for (DWORD i = 0; i < MAX_CONTROLLERS; i++) {
		gamePad[i].Update();


	}


	for (Ship& sp : ships) {
		if (sp.playerID == PLAYER_1)
			sp.Control(gamePad[0].x, gamePad[0].y, gamePad[0].downKeys, gamePad[0].pressedKeys);

		if (sp.playerID == PLAYER_2) {
			//キーボードの処理
			sp.KeysControl(keyboadKeys, lastKeyboardKeys);

		}
		else if (sp.playerID == OTHER) {
			sp.Control();
		}

	}

	//シーンの呼び出し
	scene(sceneType, keyboadKeys, lastKeyboardKeys,
		gamePad[0].downKeys);


	/*１フレームまえのおされていたキーボードを保存*/
	memcpy(lastKeyboardKeys, keyboadKeys, 256);

	glutPostRedisplay();

}


void display(void) {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);//GLbitFIELD_SIZE mask
													   /* ADX2サーバ処理の実行 */
	criAtomEx_ExecuteMain();

	//描画のシーン呼び出し
	sceneDraw(sceneType);

	glFlush();

}



int main(int argc, char *argv[]) {

	glutInit(
		&argc,//int *argcp,
		argv);//char **argv

			  //ウインドウサイズ
	glutInitWindowSize(
		width,  // int width
		height);// int height

	glutCreateWindow("ika");//const char *title

	glutDisplayFunc(display);//void (GLUTCALLBACK *func)(void)

	glutTimerFunc(
		0,		//unsigned int millis,タイマーを何ミリ秒後起動する
		timer,	//void (GLUTCALLBACK *func)(int value),
		0);		//int value

	srand(time(NULL));

	/*キーボード入力取得関数の登録-----------------------------*/
	glutKeyboardFunc(keyboard);//void (GLUTCALLBACK *func)(unsigned char key, int x, int y)
	glutKeyboardUpFunc(keyboardUp);// void (GLUTCALLBACK *func)(unsigned char key, int x, int y)
	/*---------------------------------------------------------*/

	Panel::setPanel();//panelの初期化

	/*プレイヤーの作成*/
	Ship player = Ship(glm::vec3(0, 0.5, 0), TEAM_PLAYER, TEAM_PLAYER_SHIP, PLAYER_1, "materials/ikachan4.blend.x");
	ships.push_back(player);
	Ship player2 = Ship(glm::vec3(0, 0.5, FIELD_SIZE), TEAM_ENEMY, TEAM_ENEMY_SHIP, PLAYER_2, "materials/ikachan4.blend.x");//glm::vec3& _pos, int _team, int _shipColor, int _playerID
	ships.push_back(player2);


	/*npcの生成*/
	Ship enemy = Ship(glm::vec3(FIELD_SIZE, 0.5, 0), TEAM_PLAYER, TEAM_PLAYER_SHIP, OTHER, "materials/ikachan4.blend.x");
	ships.push_back(enemy);
	Ship enemy2 = Ship(glm::vec3(FIELD_SIZE, 0.5, FIELD_SIZE), TEAM_ENEMY, TEAM_ENEMY_SHIP, OTHER, "materials/ikachan4.blend.x");
	ships.push_back(enemy2);

	/*カメラの初期化*/
	for (Ship& sp : ships)
		Camera::Camera(&sp);

	//カラーの初期化
	for (int z = 0; z < FIELD_SIZE; z++)
	{
		for (int x = 0; x < FIELD_SIZE; x++) {
			panels[z][x].team = TEAM_OTHER;
		}
	}

	/*加速度の初期化*/
	player.deceleration = 0.95;


	/*メインループ*/
	glutMainLoop();


}
