#define _USE_MATH_DEFINES
#define _CRT_SECURE_NO_WARNINGS

#include "scene_game.h"
#include <list>
#include "../scene.h"
#include "../ship.h"
#include "../bullet.h"
#include "../panel.h"
#include "../camera.h"
#include "../glm\gtx\transform.hpp"


extern int leftTime;

extern std::list<Ship> ships;
extern std::list<Bullet> bulletList;

extern int panel_count_player;//プレイヤーのパネルカウンター
extern int panel_count_enemy;//敵のパネルカウンター

extern Panel panels[FIELD_SIZE][FIELD_SIZE];
extern bool is_game_set;

extern int width;
extern int height;

extern Camera camera;


//ゲームシーン呼び出し関数
void scene_game(int &sceneType, unsigned char *keyboadKeys, unsigned char *lastKeyboardKeys, unsigned int downKeys) {
	//タイムがマイナスにならないように
	if (leftTime > 0)
		leftTime--;


	//ゲーム終了以外は
	if (is_game_set != true)
	{
		for (Ship& sp : ships) {

			if (sp.playerID == PLAYER_2) {
				//キーボードの処理
				sp.Control(keyboadKeys, lastKeyboardKeys);

			}
			else if (sp.playerID == OTHER) {
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
				if (panels[z][x].team == TEAM_PLAYER) panel_count_player++;
				if (panels[z][x].team == TEAM_ENEMY) panel_count_enemy++;
			}
			//						printf("player:%d enemy:%d\n", panel_count_player, panel_count_enemy);
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

	if (leftTime / 60 <= 0) {
		is_game_set = true;

		if ((keyboadKeys[13] == 1 && lastKeyboardKeys[13] == 0) || (downKeys & GLUT_JOYSTICK_BUTTON_B))
		{
			panel_count_player = 0;
			panel_count_enemy = 0;
			is_game_set = false;
			sceneType = SCENE_RESULT;
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

	glEnable(GL_DEPTH_TEST);	// GLenum cap　深度テスト　


//--------------------------
	glEnableClientState(GL_VERTEX_ARRAY);// GLenum array
	glEnableClientState(GL_NORMAL_ARRAY);
//---------------------------

	/*上画面　プレイヤー１の描画処理*/
	glViewport(0, height / 2, width, height / 2);

	/*ビューポートの取得*/
	glm::ivec4 viewport;
	glGetIntegerv(
		GL_VIEWPORT,// GLenum pname
		(GLint*)&viewport);  // GLint *params

 ///////////////フィールド
		//2次元配列
	for (int z = 0; z < FIELD_SIZE; z++)
	{
		for (int x = 0; x < FIELD_SIZE; x++)
		{
			panels[z][x].draw();
		}
	}



	//自
	for (Ship& sp : ships) {
		//スクリーン座標の取得
		
		sp.scr_pos = glm::project(sp.pos, camera.modelview, camera.project, viewport);

		sp.Draw();
	}

	//弾
	for (Bullet& b : bulletList)
		b.Draw();

	glMatrixMode(GL_PROJECTION);//GLenum mode
	glLoadIdentity();//射影行列の初期化
	glMatrixMode(GL_MODELVIEW);//GLenum mode	カメラの設定

	glDisable(GL_DEPTH_TEST);

	//////操作説明
	glLoadIdentity();//初期化
	glColor3f(1.0f / 255 * 127, 1.0f / 255 * 127, 1.0f / 255 * 127);
	glTranslatef(-0.95, -0.95, 0);//x,y,z
	glLineWidth(2);
	glScalef(0.0007, 0.0007, 0.0007);
	drawStroke("[LStick]Control [A]Fire");

	////////ゲーム中のプレイヤーがパネルを塗った％
	float p = (float)panel_count_player / (float)(FIELD_SIZE*FIELD_SIZE) * 100.0f;
	int pp = p;
	char str[256];
	sprintf(str, "%d %%", pp);

	glLoadIdentity();//初期化
	setColor(TEAM_PLAYER);
	glTranslatef(-.85, .75, 0);//x,y,z
	glLineWidth(2);
	glScalef(0.0005, 0.0005, 0.0005);
	drawStroke(str);
	glLoadIdentity();
	setColor(TEAM_PLAYER);
	glTranslatef(-.9, .9, 0);//x,y,z
	glLineWidth(2);
	glScalef(0.0006, 0.0006, 0.0006);
	drawStroke("PLAYER1");

	//敵がパネルを塗った％
	p = (float)panel_count_enemy / (float)(FIELD_SIZE*FIELD_SIZE) * 100.0f;
	pp = p;
	sprintf(str, "%d %%", pp);

	glLoadIdentity();//初期化
	setColor(TEAM_ENEMY);
	glTranslatef(.75, .75, 0);//x,y,z
	glLineWidth(2);
	glScalef(0.0005, 0.0005, 0.0005);
	drawStroke(str);
	glLoadIdentity();
	setColor(TEAM_ENEMY);
	glTranslatef(.6, .9, 0);//x,y,z
	glLineWidth(2);
	glScalef(0.0006, 0.0006, 0.0006);
	drawStroke("PLAYER2");


	//フレーム数値をいれる　描画
	glLoadIdentity();//初期化
	glTranslatef(0, 0.8, 0);
	sprintf(str, "%d", leftTime / 60);
	if (leftTime / 60 <= 5)
	{
		glScalef(0.001, 0.001, 0.001);
		glColor3f(1, 0, 0);
	}
	else {
		glScalef(0.0008, 0.0008, 0.0008);
		glColor3f(1, 1, 0);
	}
	drawStroke(str);

	//タイムアップになった時の処理
	if (leftTime / 60 == 0) {

		glMatrixMode(GL_PROJECTION);//GLenum mode
		glLoadIdentity();//射影行列の初期化
		glMatrixMode(GL_MODELVIEW);//GLenum mode	カメラの設定

								   //白
		glLoadIdentity();//初期化
		glColor3f(1, 1, 1);
		glTranslatef(-.3, 0, 0);//x,y,z
		glScalef(0.00075, 0.00075, 0.00075);
		drawStroke("GAME SET!");
		glLoadIdentity();
		glColor3f(1, 1, 1);
		glTranslatef(-.8, -.2, 0);
		glScalef(0.00065, 0.00065, 0.00065);
		drawStroke("push ENTER / BUTTON B");

		//黒
		glLoadIdentity();//初期化
		glColor3f(0, 0, 0);
		glTranslatef(-.29, 0.01, 0);//x,y,z
		glScalef(0.00075, 0.00075, 0.00075);
		drawStroke("GAME SET!");
		glLoadIdentity();
		glColor3f(0, 0, 0);
		glTranslatef(-.79, -.21, 0);
		glScalef(0.00065, 0.00065, 0.00065);
		drawStroke("push ENTER / BUTTON B");
	}


	///////-------------------------------
	/*視点*/
	glMatrixMode(GL_PROJECTION);//GLenum mode
	glLoadIdentity();//初期化
	gluPerspective(
		45,		//GLdouble fovy,角度
		(float)width / (height / 2),		//GLdouble aspect,画面の幅
		0.1,	//Ldouble zNear,カメラからの距離　この数値より近いものは描画されない
		100);	// GLdouble zFarカメラからの距離　この数値より遠いものは描画されない


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
//	glm::mat4 modelview_2p;
	glGetFloatv(
		GL_MODELVIEW_MATRIX,// GLenum pname
		(GLfloat*)&camera.modelview);         // GLfloat *params


										  //---------------------------------------------------------


										  ///////////////フィールド
										  //2次元配列
	for (int z = 0; z < FIELD_SIZE; z++)
	{
		for (int x = 0; x < FIELD_SIZE; x++)
		{
			panels[z][x].draw();
		}
	}
	//自
	for (Ship& sp : ships) {
		//	スクリーン座標の取得
		sp.scr_pos = glm::project(sp.pos, camera.modelview, camera.project, viewport_2p);
		//プレイヤーの上に座標もってきている
		sp.scr_pos.y += (float)height / 2;
		//描画

		sp.Draw();
	}

	//弾
	for (Bullet& b : bulletList)
		b.Draw();

	glMatrixMode(GL_PROJECTION);//GLenum mode
	glLoadIdentity();//射影行列の初期化
	glMatrixMode(GL_MODELVIEW);//GLenum mode	カメラの設定

	glDisable(GL_DEPTH_TEST);

	////操作説明////
	glLoadIdentity();//初期化
	glColor3f(1.0f / 255 * 127, 1.0f / 255 * 127, 1.0f / 255 * 127);
	glTranslatef(-0.95, -0.95, 0);//x,y,z
	glLineWidth(2);
	glScalef(0.0007, 0.0007, 0.0007);
	drawStroke("[W/S/A/D]Control [Space]Fire");
	///////////////

	/*現在のパネルの塗った数を％表示*/

	////////ゲーム中のプレイヤーがパネルを塗った％
	p = (float)panel_count_player / (float)(FIELD_SIZE*FIELD_SIZE) * 100.0f;
	pp = p;

	sprintf(str, "%d %%", pp);

	glLoadIdentity();//初期化
	setColor(TEAM_PLAYER);
	glTranslatef(-.85, .75, 0);//x,y,z
	glLineWidth(2);
	glScalef(0.0005, 0.0005, 0.0005);
	drawStroke(str);
	glLoadIdentity();
	setColor(TEAM_PLAYER);
	glTranslatef(-.9, .9, 0);//x,y,z
	glLineWidth(2);
	glScalef(0.0006, 0.0006, 0.0006);
	drawStroke("PLAYER1");

	//敵がパネルを塗った％
	p = (float)panel_count_enemy / (float)(FIELD_SIZE*FIELD_SIZE) * 100.0f;
	pp = p;
	sprintf(str, "%d %%", pp);

	glLoadIdentity();//初期化
	setColor(TEAM_ENEMY);
	glTranslatef(.7, 0.75, 0);//x,y,z
	glLineWidth(2);
	glScalef(0.0005, 0.0005, 0.0005);
	drawStroke(str);
	glLoadIdentity();
	setColor(TEAM_ENEMY);
	glTranslatef(.6, .9, 0);//x,y,z
	glLineWidth(2);
	glScalef(0.0006, 0.0006, 0.0006);
	drawStroke("PLAYER2");

	////////////////////////////////
	//タイムアップになった時の処理
	if (leftTime / 60 == 0) {

		glMatrixMode(GL_PROJECTION);//GLenum mode
		glLoadIdentity();//射影行列の初期化
		glMatrixMode(GL_MODELVIEW);//GLenum mode	カメラの設定

								   //白
		glLoadIdentity();//初期化
		glColor3f(1, 1, 1);
		glTranslatef(-.3, 0, 0);//x,y,z
		glScalef(0.00075, 0.00075, 0.00075);
		drawStroke("GAME SET!");
		glLoadIdentity();
		glColor3f(1, 1, 1);
		glTranslatef(-.8, -.2, 0);
		glScalef(0.00065, 0.00065, 0.00065);
		drawStroke("push ENTER / BUTTON B");

		//黒
		glLoadIdentity();//初期化
		glColor3f(0, 0, 0);
		glTranslatef(-.29, 0.01, 0);//x,y,z
		glScalef(0.00075, 0.00075, 0.00075);
		drawStroke("GAME SET!");
		glLoadIdentity();
		glColor3f(0, 0, 0);
		glTranslatef(-.79, -.21, 0);
		glScalef(0.00065, 0.00065, 0.00065);
		drawStroke("push ENTER / BUTTON B");
	}
}





