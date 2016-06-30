#define _CRT_SECURE_NO_WARNINGS
#include "scene_resurt.h"
#include <stdio.h>
#include "../library/util.h"
#include "../glut.h"
#include "../manager/sounds_manager.h"
#include "../manager/texture_manager.h"
#include <Xinput.h>

extern int leftTime;
extern int panel_count_player;
extern int panel_count_enemy;
extern int frame;
extern int width;
extern int height;
void scene_resurt(int &sceneType, unsigned char *keyboadKeys, unsigned char *lastKeyboardKeys, unsigned int downKeys)
{
	/*b�{�^���������ꂽ��^�C�g���V�[���ւ̈ڍs�i�������Ɂj*/
	if ((downKeys &XINPUT_GAMEPAD_B)||(keyboadKeys[13] == 1 && lastKeyboardKeys[13] == 0))
	{

		/*��������~*/
		SoundsManager::GetInstance()->StopBGM();

		//se�̍Đ�
		SoundsManager::GetInstance()->PlaySE(CRI_GAME_SOUNDS_SE_BUTTON);

		leftTime = 0;
		sceneType = SCENE_TITLE_INIT;
	}

}

void scene_resurt_draw() {
	//��ʕ����̏�����
	glViewport(0, 0, width, height);

	glMatrixMode(GL_PROJECTION);//GLenum mode
	glLoadIdentity();//�ˉe�s��̏�����

	glMatrixMode(GL_MODELVIEW);//GLenum mode	�J�����̐ݒ�
	glLoadIdentity();//������

	//���U���g��ʂ̉摜�̕`��
	scrDraw("resurt");

	/*�h��ꂽ�p�l���̖��������ŕێ�*/
	float p = (float)panel_count_player / (float)(FIELD_SIZE*FIELD_SIZE) * 100.0f;
	int pp = p;

	char str[256];
	sprintf(str, "%d %%", pp);
	glMatrixMode(GL_PROJECTION);//GLenum mode
	glLoadIdentity();//�ˉe�s��̏�����
	glMatrixMode(GL_MODELVIEW);//GLenum mode	�J�����̐ݒ�
	glLoadIdentity();//������
	glLineWidth(3);
	setColor(TEAM_PLAYER);
	glTranslatef(-.7, .2, 0);//x,y,z
	glScalef(0.00075, 0.00075, 0.00075);
	drawStroke("PLAYER1 TEAM:");
	glLoadIdentity();//������
	glTranslatef(.15, .2, 0);//x,y,z
	glScalef(0.00075, 0.00075, 0.00075);
	drawStroke(str);


	p = (float)panel_count_enemy / (float)(FIELD_SIZE*FIELD_SIZE) * 100.0f;
	pp = p;
	sprintf(str, "%d %%", pp);
	glLoadIdentity();//������
	setColor(TEAM_ENEMY);
	glTranslatef(-.7, 0, 0);//x,y,z
	glScalef(0.00075, 0.00075, 0.00075);
	drawStroke("PLAYER2 TEAM:");
	glLoadIdentity();
	glTranslatef(.15, 0, 0);//x,y,z
	glScalef(0.00075, 0.00075, 0.00075);
	drawStroke(str);

	//�v���C���[�Q���v���C���[1���h������������������
	if (panel_count_enemy>panel_count_player)
	{
		glLoadIdentity();//������
		setColor(TEAM_ENEMY);
		glTranslatef(0, -0.7, 0);//x,y,z
		glScalef(0.00075, 0.00075, 0.00075);
		drawStroke("PLAYER2 WIN!!!!");

	}//�v���C���[�P���v���C���[2���h������������������
	else if (panel_count_player>panel_count_enemy)
	{
		glLoadIdentity();//������
		setColor(TEAM_PLAYER);
		glTranslatef(0, -0.7, 0);//x,y,z
		glScalef(0.00075, 0.00075, 0.00075);
		drawStroke("PLAYER1 WIN!!!!");
	}
	if (frame % 60 < 30) {
		glLoadIdentity();//������
		glColor3f(0, 0, 0);
		glTranslatef(0, -0.8, 0);//x,y,z
		glScalef(0.0005, 0.00055, 0.0005);
		drawStroke("push ENTER / BUTTON B");
	}

}
