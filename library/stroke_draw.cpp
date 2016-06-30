#include "stroke_draw.h"
#include "../library/util.h"
#include "../glut.h"


StrokeDraw* StrokeDraw::instance = nullptr;

StrokeDraw* StrokeDraw::GetInstance() {
	//�C���X�^���X���Ȃ���΃��������m��
	if (instance == nullptr)
	{
		instance = new StrokeDraw();
	}

	return instance;

}


void StrokeDraw::gameSet(const int player) {

	glMatrixMode(GL_PROJECTION);//GLenum mode
	glLoadIdentity();//�ˉe�s��̏�����
	glMatrixMode(GL_MODELVIEW);//GLenum mode	�J�����̐ݒ�

	if (player == PLAYER_1)
	{
		//���ʃv���C���[�P
		glLoadIdentity();//������
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
		//����ʁ@�v���C���[�Q
		glLoadIdentity();//������
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
	//////�������
	glLoadIdentity();//������
					 //	glColor3f(1.0f / 255 * 127, 1.0f / 255 * 127, 1.0f / 255 * 127);
	glColor3f(0, 0, 0);//��
	glTranslatef(-0.95, -0.95, 0);//x,y,z
	glLineWidth(2);
	glScalef(0.0007, 0.0007, 0.0007);
	drawStroke("[LStick]Control [A]Fire");

}

void StrokeDraw::gameKeyControl() {
	////�������////
	glLoadIdentity();//������
					 //	glColor3f(1.0f / 255 * 127, 1.0f / 255 * 127, 1.0f / 255 * 127);
	glColor3f(0, 0, 0);//��
	glTranslatef(-0.95, -0.95, 0);//x,y,z
	glLineWidth(2);
	glScalef(0.0007, 0.0007, 0.0007);
	drawStroke("[W/S/A/D]Control [Space]Fire");
	///////////////

}

void StrokeDraw::Score(int team, const char* score, const char* name) {
	glLoadIdentity();//������
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
