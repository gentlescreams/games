
//------------
//読み込むヘッダー
#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<conio.h>
#define _USE_MATH_DEFINES
#include<math.h>
#include<list>
#include<stdlib.h>
#include<time.h>

#include"scene.h"
#include"panel.h"
#include"util.h"
#include"flyingobject.h"
#include"ship.h"
#include"bullet.h"
#include"camera.h"
#include"model.h"
#include "./myn_library/sounds_manager.h"
#include "./texture/texture.h"

#include"glm\glm.hpp"
#include"glm\gtx\transform.hpp" 
#include"glut.h"


/*画面のサイズ*/
int width = 640;
int height = 480;

int frame = 0;//	フレームカウント
int sceneType = SCENE_TITLE_INIT;
int panel_count_player = 0;
int panel_count_enemy = 0;
int timeCount = 30;
int leftTime = 0;
bool is_game_set = false;


//2次元配列
extern Panel panels[FIELD_SIZE][FIELD_SIZE];

Camera camera;//カメラ実体
Model model;//モデル読み込み実体
std::list<Ship> ships;
std::list<Bullet> bulletList;

unsigned int pressedKeys;//今押されてるキー
unsigned int releasedKeys;//今押されてないキー
unsigned int lastKeys;//１フレーム前のキー
unsigned int changedKeys;//変化のあったキー
unsigned int upKeys;//今離されたキー
unsigned int downKeys;//今押されたキー

//joystickの状態取得
void joystick(unsigned int buttonMask, int x, int y, int z){
	float x1 = x / 1000.0f;
	float y1 = -y / 1000.0f;
	
	pressedKeys = buttonMask;//今押されているキー
	releasedKeys = ~pressedKeys;//今押されているキーの補数
	changedKeys = lastKeys ^ pressedKeys;//変化のあったキー
	downKeys = changedKeys & pressedKeys;//今押されたキー
	upKeys = changedKeys & releasedKeys;//今はなされたキー

	//ジョイスティックのコントロール
	for (Ship& sp : ships){
		if (sp.playerID ==PLAYER_1)
		sp.Control(x1, y1, downKeys, pressedKeys);
	}
	lastKeys = pressedKeys;//１フレーム前のキー

}

/*キーボードの状態の取得*/
unsigned char keyboadKeys[256]={};
unsigned char lastKeyboardKeys[256] = {};
void keyboard(unsigned char key, int x, int y){//押されているとき

	keyboadKeys[key] = 1;
	
}

void keyboardUp(unsigned char key, int x, int y){//	キーボードが離されたとき
	keyboadKeys[key] = 0;

}


void timer(int value){

	glutForceJoystickFunc();//joystickのデータを取得してジョイスティックコールバック関数を呼ぶ
	glutTimerFunc(
		1000 / 60,		//unsigned int millis,タイマーを何ミリ秒後起動する
		timer,	//void (GLUTCALLBACK *func)(int value),
		0);		//int value

	/*フレームカウント*/
	frame++;

	//シーンの呼び出し
	scene(sceneType,
		keyboadKeys,lastKeyboardKeys,
		downKeys);

	/*１フレームまえのおされていたキーボードを保存*/
	memcpy(lastKeyboardKeys, keyboadKeys, 256);
	
	glutPostRedisplay();

}


void display(void){
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);//GLbitFIELD_SIZE mask

	 /* ADX2サーバ処理の実行 */
	criAtomEx_ExecuteMain();

	//描画のシーン呼び出し
	sceneDraw(sceneType);
	
	glFlush();

}



int main(int argc, char *argv[]){

	glutInit(
		&argc,//int *argcp,
		argv);//char **argv

	//ウインドウサイズ
	glutInitWindowSize(
		width,  // int width
		height);// int height

	glutCreateWindow("title");//const char *title

	glutDisplayFunc(display);//void (GLUTCALLBACK *func)(void)

	glutTimerFunc(
		0,		//unsigned int millis,タイマーを何ミリ秒後起動する
		timer,	//void (GLUTCALLBACK *func)(int value),
		0);		//int value

	glutJoystickFunc(
		joystick,	//void(GLUTCALLBACK *func)(unsigned int buttonMask, int x, int y, int z),
		0);			//int pollInterval

	glutKeyboardFunc(keyboard);//void (GLUTCALLBACK *func)(unsigned char key, int x, int y)

	glutKeyboardUpFunc(keyboardUp);

	srand(time(NULL));
	

	Panel::setPanel();//panelの初期化

	/*プレイヤーチームの作成*/
	//player1
	Ship player = Ship(glm::vec3(0, 0.5, 0),TEAM_PLAYER,TEAM_PLAYER_SHIP, PLAYER_1, "ikachan4.blend.x");
	ships.push_back(player);
	Ship player2 = Ship(glm::vec3(FIELD_SIZE, 0.5, 0), TEAM_PLAYER,TEAM_PLAYER_SHIP, OTHER, "ikachan4.blend.x");//glm::vec3& _pos, int _team, int _shipColor, int _playerID
	ships.push_back(player2);


	/*敵チームの生成*/
	//player2
	Ship enemy = Ship(glm::vec3(0, 0.5, FIELD_SIZE), TEAM_ENEMY,TEAM_ENEMY_SHIP, PLAYER_2, "ikachan4.blend.x");
	ships.push_back(enemy);
	Ship enemy2 = Ship(glm::vec3(FIELD_SIZE, 0.5, FIELD_SIZE), TEAM_ENEMY, TEAM_ENEMY_SHIP, OTHER, "ikachan4.blend.x");
	ships.push_back(enemy2);

	/*カメラの初期化*/
	for (Ship& sp : ships)
	Camera::Camera(&sp);

	//カラーの初期化
	for (int z = 0; z < FIELD_SIZE; z++)
	{
		for (int x = 0; x < FIELD_SIZE; x++){
			panels[z][x].team = TEAM_OTHER;
		}
	}

	/*加速度の初期化*/
	player.deceleration = 0.95;
	

	/*メインループ*/
	glutMainLoop();


}
