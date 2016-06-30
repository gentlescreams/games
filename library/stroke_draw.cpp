#include "stroke_draw.h"
#include "../library/util.h"
#include "../glut.h"


StrokeDraw* StrokeDraw::instance = nullptr;

StrokeDraw* StrokeDraw::GetInstance() {
	//インスタンスがなければメモリを確保
	if (instance == nullptr)
	{
		instance = new StrokeDraw();
	}

	return instance;

}


void StrokeDraw::gameSet(const int player) {

	glMatrixMode(GL_PROJECTION);//GLenum mode
	glLoadIdentity();//射影行列の初期化
	glMatrixMode(GL_MODELVIEW);//GLenum mode	カメラの設定

	if (player == PLAYER_1)
	{
		//上画面プレイヤー１
		glLoadIdentity();//初期化
		glColor3f(0, 0, 0);
		glTranslatef(-.3, 0, 0);//x,y,z
		glScalef(0.00075, 0.00075, 0.00075);
		drawStroke("GAME SET!");
		glLoadIdentity();
		glColor3f(0, 0, 0);
		glTranslatef(-.8, -.2, 0);
		glScalef(0.00065, 0.00065, 0.00065);
		drawStroke("  push   BUTTON B");


	}

	if (player == PLAYER_2)
	{
		//下画面　プレイヤー２
		glLoadIdentity();//初期化
		glColor3f(0, 0, 0);
		glTranslatef(-.29, 0.01, 0);//x,y,z
		glScalef(0.00075, 0.00075, 0.00075);
		drawStroke("GAME SET!");
		glLoadIdentity();
		glColor3f(0, 0, 0);
		glTranslatef(-.79, -.21, 0);
		glScalef(0.00065, 0.00065, 0.00065);
		drawStroke("  push ENTERKEY ");
	}

}

void StrokeDraw::gameControl() {
	//////操作説明
	glLoadIdentity();//初期化
					 //	glColor3f(1.0f / 255 * 127, 1.0f / 255 * 127, 1.0f / 255 * 127);
	glColor3f(0, 0, 0);//黒
	glTranslatef(-0.95, -0.95, 0);//x,y,z
	glLineWidth(2);
	glScalef(0.0007, 0.0007, 0.0007);
	drawStroke("[LStick]Control [A]Fire");

}

void StrokeDraw::gameKeyControl() {
	////操作説明////
	glLoadIdentity();//初期化
					 //	glColor3f(1.0f / 255 * 127, 1.0f / 255 * 127, 1.0f / 255 * 127);
	glColor3f(0, 0, 0);//黒
	glTranslatef(-0.95, -0.95, 0);//x,y,z
	glLineWidth(2);
	glScalef(0.0007, 0.0007, 0.0007);
	drawStroke("[W/S/A/D]Control [Space]Fire");
	///////////////

}

void StrokeDraw::Score(int team, const char* score, const char* name) {
	glLoadIdentity();//初期化
	setColor(team);
	if (team ==TEAM_PLAYER )
	{
		glTranslatef(-.85, .75, 0);//x,y,z
	}
	else
	{
		glTranslatef(.75, .75, 0);//x,y,z

	}

	glLineWidth(2);
	glScalef(0.0005, 0.0005, 0.0005);
	drawStroke(score);
	glLoadIdentity();
	setColor(team);
	if (team == TEAM_PLAYER)
	{
		glTranslatef(-.9, .9, 0);//x,y,z
	}
	else{
		glTranslatef(.6, .9, 0);//x,y,z
	}
	glLineWidth(2);
	glScalef(0.0006, 0.0006, 0.0006);
	drawStroke(name);

}


StrokeDraw::StrokeDraw()
{
}

StrokeDraw::~StrokeDraw()
{
}
