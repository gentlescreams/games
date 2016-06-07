#define _USE_MATH_DEFINES
#define _CRT_SECURE_NO_WARNINGS
#include<list>
#include<math.h>

#include"scene.h"

#include "./scene/scene_title.h"
#include "./scene/scene_game.h"
#include "./scene/scene_resurt.h"
#include "bullet.h"
#include "camera.h"
#include "ship.h"
#include "util.h"
#include "panel.h"
#include "glut.h"
#include "glm\glm.hpp"
#include "glm\gtx\transform.hpp" 
#include "./myn_library/sounds_manager.h"
#include "./texture/texture.h"
#include "./myn_library/texture_manager.h"

extern std::list<Ship> ships;
extern Panel panels[FIELD_SIZE][FIELD_SIZE];
extern std::list<Bullet> bulletList;

extern int width;
extern int height;
SoundsManager sm;

extern Camera camera;
Texture *tex01;
Texture *tex02;
Texture *tex03;

//extern Texture tex;
TextureManager tm;
void scene(int &sceneType,unsigned char *keyboadKeys,unsigned char *lastKeyboardKeys,unsigned int downKeys){

	switch (sceneType)
	{
	case SCENE_TITLE_INIT://タイトル初期化
		//sm.Load("a");
		sm.PlayBGM();

		/*テクスチャ読み込み*/
		tex01 = new Texture("gesotaso.bmp");
		tex02 = new Texture("gesotaso2.bmp");
		tex03 = new Texture("gesotaso3.bmp");
		tm.id.insert(std::make_pair("player", tex01));
		tm.id.insert(std::make_pair("enemy", tex02));
		tm.id.insert(std::make_pair("samp", tex03));

		sceneType = SCENE_TITLE;
		break;

	case SCENE_TITLE://タイトル

		/*タイトルシーン関数呼び出し*/
		scene_title(sceneType, keyboadKeys, lastKeyboardKeys, downKeys);

		break;

	case SCENE_GAME://ゲーム

		/*ゲームシーンの呼び出し*/
		scene_game(sceneType, keyboadKeys, lastKeyboardKeys, downKeys);

		break;
	case SCENE_RESULT:

		/*リザルトシーンの呼び出し*/
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
		100);	// GLdouble zFarカメラからの距離　この数値より遠いものは描画されない


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
	{
		//glEnable(GL_TEXTURE_2D);
		//glBindTexture(GL_TEXTURE_2D, tm.id["player"]->tex_id);

		//float v[] = {
		//	-1, 1,
		//	-1, -1,
		//	1, 1,
		//	1, -1
		//};

		//glEnableClientState(GL_VERTEX_ARRAY);
		//glVertexPointer(
		//	2, GL_FLOAT, 0, v);
		//float f = 1;
		//float t[] = {
		//	0, 0,
		//	0, f,
		//	f, 0,
		//	f, f
		//};
		//glEnableClientState(GL_TEXTURE_COORD_ARRAY);
		//glTexCoordPointer(
		//	2,			//GLint size, ,
		//	GL_FLOAT,	// GLenum type
		//	0,			//GLsizei stride,
		//	t);			//const GLvoid *pointer)
		//
		//glDrawArrays(
		//	GL_TRIANGLE_STRIP,   // GLenum mode
		//	0,              // GLint first
		//	4);             // GLsizei count

		/*タイトルシーン描画関数*/
		scene_title_draw();
	}
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