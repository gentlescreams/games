#define _USE_MATH_DEFINES
#define _CRT_SECURE_NO_WARNINGS

#include "scene_game.h"
#include <list>
#include "../scene.h"
#include "../ship.h"
#include "../bullet.h"
#include "../field/panel.h"
#include "../camera.h"
#include "../glm\gtx\transform.hpp"
#include "../manager/sounds_manager.h"
#include "../manager/texture_manager.h"
#include "../field/skybox.h"
#include "../controllers/pad_controller.h"
#include "../library/stroke_draw.h"
#include "../library/item.h"

#include <Xinput.h>


extern PadController gamePad[MAX_CONTROLLERS];
extern int leftTime;
extern std::list<Ship> ships;
extern std::list<Bullet> bulletList;
extern Panel panels[FIELD_SIZE][FIELD_SIZE];
extern int width;
extern int height;
extern Camera camera;

int panel_count_player = 0;//パネルカウンタ　１P
int panel_count_enemy = 0;//パネルカウンタ　2P
int timeCount;
int leftTime = 0;
extern bool is_game_set;
SkyBox sk;
Item item;
//ゲームシーン呼び出し関数
void scene_game(int &sceneType, unsigned char *keyboadKeys, unsigned char *lastKeyboardKeys, unsigned int downKeys) {
	//タイムがマイナスにならないように
	if (leftTime > 0)
		leftTime--;



	//ゲーム終了以外は
	if (is_game_set != true)
	{
		item.Move();
		for (Ship& sp : ships) {

			//プレイヤー以外のコントロール
			if (sp.playerID == OTHER) {
				sp.Control();
			}

			sp.Update();
			//プレイヤーがフィールドから出ないようにする
			sp.playerArea();
		}

		//弾とフィールドのあたり判定
		for (Bullet& bul : bulletList) {
			bul.Update();
			bul.speed.y -= .009f;

			if (bul.pos.y < 0)
			{
				int x = (int)bul.pos.x;
				int z = (int)bul.pos.z;


				panels[z][x].team = bul.team;
				bul.isDead = 1;
				if (panels[z][x].team)
				{
					panels[z + 1][x + 1].team = bul.team;
					panels[z + 1][x].team = bul.team;
					panels[z][x + 1].team = bul.team;


				}
			}
			else if (bul.pos.x<0 || bul.pos.x>FIELD_SIZE || bul.pos.z<0 || bul.pos.z > FIELD_SIZE)
			{
				bul.isDead = 1;
			}
		}

		/*パネルのカウント*/
		panel_count_player = 0;
		panel_count_enemy = 0;
		for (int z = 0; z < FIELD_SIZE; z++)
		{
			for (int x = 0; x < FIELD_SIZE; x++)
			{
				//パネルのチームのカラーによって＋＋
				if (panels[z][x].team == TEAM_PLAYER) panel_count_player++;
				if (panels[z][x].team == TEAM_ENEMY) panel_count_enemy++;
			}
		}

		//弾の移動処理
		for (Bullet& Bt : bulletList) {
			for (Ship& sp : ships) {
				if (Bt.team == sp.team) {
					continue;
				}
				if (Bt.isDead == 0 && distance(Bt.pos, sp.pos) < 2) {
					Bt.isDead = 1;
					sp.pos = sp.startPoint;
					glm::vec3 v = glm::vec3(FIELD_SIZE / 2, 0, FIELD_SIZE / 2) - sp.pos;
					sp.yaw = atan2f(v.x, v.z) * 180 / M_PI;
				}
			}
		}
	}


	//ラムダ式　死んだら解放
	bulletList.remove_if([](Bullet& chr)->bool { return(chr.isDead == 1); });

	if (leftTime / 120 <= 0) {
		is_game_set = true;


			//ｂボタンが押されたらシーンを移行
		if ((downKeys & XINPUT_GAMEPAD_B) || (keyboadKeys[13] == 1 && lastKeyboardKeys[13] == 0))
		{
			SoundsManager::GetInstance()->StopBGM();
			SoundsManager::GetInstance()->PlaySE(CRI_GAME_SOUNDS_SE_BUTTON);
			panel_count_player = 0;
			panel_count_enemy = 0;
			is_game_set = false;
			sceneType = SCENE_RESULT_INIT;
			for (int z = 0; z < FIELD_SIZE; z++)
			{
				for (int x = 0; x < FIELD_SIZE; x++)
				{
					if (panels[z][x].team == TEAM_PLAYER) panel_count_player++;
					if (panels[z][x].team == TEAM_ENEMY) panel_count_enemy++;
				}
			}
		}
	}

}


void scene_game_draw() {

	/*上画面　プレイヤー１の描画処理*/
	glViewport(0, height / 2, width, height / 2);
	/*ビューポートの取得*/
	glm::ivec4 viewport;
	glGetIntegerv(
		GL_VIEWPORT,// GLenum pname
		(GLint*)&viewport);  // GLint *params

	 /*フィールド描画--------------------------------*/

	//スカイボックス描画
	sk.Draw();
	//2次元配列
	for (int z = 0; z < FIELD_SIZE; z++)
	{
		for (int x = 0; x < FIELD_SIZE; x++)
		{
			panels[z][x].CreatePanel();
		}
	}

	/*------------------------------------------------------*/

	//自
	for (Ship& sp : ships) {
		//スクリーン座標の取得

		sp.scr_pos = glm::project(sp.pos, camera.modelview, camera.project, viewport);

		sp.Draw();
	}

	//弾
	for (Bullet& b : bulletList) {
		b.Draw();
	}


	glMatrixMode(GL_PROJECTION);//GLenum mode
	glLoadIdentity();//射影行列の初期化
	glMatrixMode(GL_MODELVIEW);//GLenum mode	カメラの設定

	glDisable(GL_DEPTH_TEST);


	//操作説明
	StrokeDraw::GetInstance()->gameControl();

	//ゲーム中のプレイヤーがパネルを塗った％---------------------------------------
	float p = (float)panel_count_player / (float)(FIELD_SIZE*FIELD_SIZE) * 100.0f;
	int pp = p;
	char str[256];
	sprintf(str, "%d %%", pp);

	//プレイヤーのスコア
	StrokeDraw::GetInstance()->Score(TEAM_PLAYER, str, "PLAYER1");

	//敵がパネルを塗った％
	p = (float)panel_count_enemy / (float)(FIELD_SIZE*FIELD_SIZE) * 100.0f;
	pp = p;
	sprintf(str, "%d %%", pp);

	//プレイヤーのスコア
	StrokeDraw::GetInstance()->Score(TEAM_ENEMY, str, "PLAYER2");
	//----------------------------------------------------------------------------

	//フレーム数値をいれる　描画
	sprintf(str, "%d", leftTime / 120);
	if (leftTime / 120 <= 3)//３秒前は色をかえて表示
	{
		glLoadIdentity();//初期化
		glTranslatef(-0.02, 0.7, 0);
		glLineWidth(3);
		glScalef(0.0015, 0.0015, 0.0015);
		glColor3f(1, 0, 0);
	}
	else {
		glLoadIdentity();//初期化
		glTranslatef(-0.02, 0.8, 0);
		glLineWidth(2);
		glScalef(0.0008, 0.0008, 0.0008);
		glColor3f(0, 0, 0);
	}
	drawStroke(str);

	//タイムアップになった時の処理
	if (leftTime / 120 == 0) {

		StrokeDraw::GetInstance()->gameSet(PLAYER_1);
	}

		///////-------------------------------
		/*視点*/

		glMatrixMode(GL_PROJECTION);//GLenum mode
		glLoadIdentity();//初期化
		gluPerspective(
			45,		//GLdouble fovy,角度
			(float)width / (height / 2),		//GLdouble aspect,画面の幅
			0.1,	//Ldouble zNear,カメラからの距離　この数値より近いものは描画されない
			1000);	// GLdouble zFarカメラからの距離　この数値より遠いものは描画されない

		/*射影行列の取得*/
		glGetFloatv(
			GL_PROJECTION_MATRIX,   // GLenum pname
			(GLfloat*)&camera.project);               // GLfloat *paramsアドレスを渡す

		glMatrixMode(GL_MODELVIEW);//GLenum mode	カメラの設定
		glLoadIdentity();

		/*下画面　プレイヤー２の処理*/
		glViewport(0, 0, width, height / 2);
		/*ビューポートの取得*/
		glm::ivec4 viewport_2p;
		glGetIntegerv(
			GL_VIEWPORT,// GLenum pname
			(GLint*)&viewport_2p);  // GLint *params

		for (Ship& sp : ships) {
			if (sp.playerID == PLAYER_2) {
				gluLookAt(
					sp.pos.x - sin(sp.yaw*M_PI / 180) * 8, 4, sp.pos.z - cos(sp.yaw*M_PI / 180) * 8,//GLdouble eyex, eyey, eyez,
					sp.pos.x, sp.pos.y + 1.3, sp.pos.z,//GLdouble centerx, centery, centerz,
					0, 1, 0);//GLdouble upx, upy, upz
			}
		}

		//モデルビュー行列取得
		glGetFloatv(
			GL_MODELVIEW_MATRIX,			// GLenum pname
			(GLfloat*)&camera.modelview);   // GLfloat *params

		/*フィールド描画--------------------------------*/

		//スカイボックス描画
		sk.Draw();
		//2次元配列
		for (int z = 0; z < FIELD_SIZE; z++)
		{
			for (int x = 0; x < FIELD_SIZE; x++)
			{
				panels[z][x].CreatePanel();
			}
		}

		/*------------------------------------------------------*/

		//自
		for (Ship& sp : ships) {
			//	スクリーン座標の取得
			sp.scr_pos = glm::project(sp.pos, camera.modelview, camera.project, viewport_2p);
			//プレイヤーの上に座標もってきている
			sp.scr_pos.y += (float)height / 2;
			//描画

			sp.Draw();
		}

		item.Draw();
		//弾
		for (Bullet& b : bulletList)
			b.Draw();

		glMatrixMode(GL_PROJECTION);//GLenum mode
		glLoadIdentity();//射影行列の初期化
		glMatrixMode(GL_MODELVIEW);//GLenum mode	カメラの設定

		glDisable(GL_DEPTH_TEST);

		//操作説明
		StrokeDraw::GetInstance()->gameKeyControl();

		//現在のパネルの塗った数を％表示--------------------------------

		//ゲーム中のプレイヤーがパネルを塗った％
		p = (float)panel_count_player / (float)(FIELD_SIZE*FIELD_SIZE) * 100.0f;
		pp = p;

		sprintf(str, "%d %%", pp);

		StrokeDraw::GetInstance()->Score(TEAM_PLAYER, str, "PLAYER1");


		//敵がパネルを塗った％
		p = (float)panel_count_enemy / (float)(FIELD_SIZE*FIELD_SIZE) * 100.0f;
		pp = p;
		sprintf(str, "%d %%", pp);

		StrokeDraw::GetInstance()->Score(TEAM_ENEMY, str, "PLAYER2");

		//--------------------------------------------------------------

		//タイムアップになった時の処理
		if (leftTime / 120 == 0) {

			StrokeDraw::GetInstance()->gameSet(PLAYER_2);
		}
	}

