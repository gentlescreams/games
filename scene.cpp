#define _USE_MATH_DEFINES
#define _CRT_SECURE_NO_WARNINGS
#include <list>
#include <math.h>
#include <array>
#include <string>

#include"scene.h"

#include "./scene/scene_title.h"
#include "./scene/scene_gamerule.h"
#include "./scene/scene_game.h"
#include "./scene/scene_resurt.h"
#include "bullet.h"
#include "camera.h"
#include "ship.h"
#include "./library/util.h"
#include "./field/panel.h"
#include "glut.h"
#include "glm\glm.hpp"
#include "glm\gtx\transform.hpp" 
#include "./manager/sounds_manager.h"
#include "./manager/texture_manager.h"

extern std::list<Ship> ships;
extern Panel panels[FIELD_SIZE][FIELD_SIZE];
extern std::list<Bullet> bulletList;

extern int width;
extern int height;

extern Camera camera;

void scene(int &sceneType, unsigned char *keyboadKeys, unsigned char *lastKeyboardKeys,unsigned int downKeys){

	switch (sceneType)
	{
	case SCENE_TITLE_INIT://タイトル初期化
	{
		//bgm再生
		SoundsManager::GetInstance()->PlayBGM(CRI_GAME_SOUNDS_BGM_TITLE);
		//テクスチャ登録
		TextureManager::GetInstance()->ResourceCreate();

		sceneType = SCENE_TITLE;
	}
		break;

	case SCENE_TITLE://タイトル

		/*タイトルシーン関数呼び出し*/
		scene_title(sceneType, keyboadKeys, lastKeyboardKeys, downKeys);

		break;
	case SCENE_GAMERULE:
		//ルールシーン関数呼び出し
		scene_rule(sceneType, keyboadKeys, lastKeyboardKeys, downKeys);

		break;
	case SCENE_GAME_INIT://ゲーム初期化

		//bgm再生
		SoundsManager::GetInstance()->PlayBGM(CRI_GAME_SOUNDS_BGM_GAME);
		sceneType = SCENE_GAME;
		break;
	case SCENE_GAME://ゲーム

		//ゲームシーンの呼び出し
		scene_game(sceneType, keyboadKeys, lastKeyboardKeys, downKeys);

		break;
	case SCENE_RESULT_INIT://リザルト初期化
		//bgm再生
		SoundsManager::GetInstance()->PlayBGM(CRI_GAME_SOUNDS_BGM_RESURT);

		sceneType = SCENE_RESULT;
		break;
	case SCENE_RESULT:

		//リザルトシーンの呼び出し
		scene_resurt(sceneType, keyboadKeys, lastKeyboardKeys, downKeys);

		break;
	default:
		break;
	}

}



void sceneDraw(int &sceneType){

	/*カメラの初期設定*/
	glMatrixMode(GL_PROJECTION);//GLenum mode
	glLoadIdentity();//初期化
	gluPerspective(
		45,		//GLdouble fovy,角度
		(float)width / (height / 2),		//GLdouble aspect,画面の幅
		0.1,	//Ldouble zNear,カメラからの距離　この数値より近いものは描画されない
		1000);	// GLdouble zFarカメラからの距離　この数値より遠いものは描画されない

	glGetFloatv(
		GL_PROJECTION_MATRIX,   // GLenum pname
		(GLfloat*)&camera.project);               // GLfloat *paramsアドレスを渡す

	glMatrixMode(GL_MODELVIEW);//GLenum mode	カメラの設定
	glLoadIdentity();
	Ship& player = *ships.begin();
	gluLookAt(
		player.pos.x - sin(player.yaw*M_PI / 180) * 8, 4, player.pos.z - cos(player.yaw*M_PI / 180) * 8,//GLdouble eyex, eyey, eyez,
		player.pos.x, player.pos.y + 1.3, player.pos.z,//GLdouble centerx, centery, centerz,
		0, 1, 0);//GLdouble upx, upy, upz

	//モデルビュー行列取得

	glGetFloatv(
		GL_MODELVIEW_MATRIX,// GLenum pname
		(GLfloat*)&camera.modelview);         // GLfloat *param
	


	switch (sceneType)
	{

	case SCENE_TITLE:
		/*タイトルシーン描画関数*/
		scene_title_draw();
		break;
	case SCENE_GAMERULE:
		/*ルールシーン描画関数*/
		scene_rule_draw();
		break;
	case SCENE_GAME:
		/*ゲームシーン描画関数*/
		scene_game_draw();
		break;

	case SCENE_RESULT:
		/*リザルトシーン描画関数*/
		scene_resurt_draw();		
		break;
	default:
		break;
	}

}