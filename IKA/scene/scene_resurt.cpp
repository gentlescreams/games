#define _CRT_SECURE_NO_WARNINGS
#include "scene_resurt.h"
#include <stdio.h>
#include "../util.h"


extern int leftTime;
extern int panel_count_player;
extern int panel_count_enemy;

extern int width;
extern int height;


void scene_resurt(int &sceneType, unsigned char *keyboadKeys, unsigned char *lastKeyboardKeys, unsigned int downKeys)
{
	if ((keyboadKeys[13] == 1 && lastKeyboardKeys[13] == 0) || (downKeys & GLUT_JOYSTICK_BUTTON_B))
	{
		leftTime = 0;
		sceneType = SCENE_TITLE;
	}

}

void scene_resurt_draw() {
	//��ʕ����̏�����
	glViewport(0, 0, width, height);


	/*�h��ꂽ�p�l���̖��������ŕێ�*/
	float p = (float)panel_count_player / (float)(FIELD_SIZE*FIELD_SIZE) * 100.0f;
	int pp = p;

	char str[256];
	sprintf(str, "%d %%", pp);
	glMatrixMode(GL_PROJECTION);//GLenum mode
	glLoadIdentity();//�ˉe�s��̏�����
	glMatrixMode(GL_MODELVIEW);//GLenum mode	�J�����̐ݒ�
	glLoadIdentity();//������
	setColor(TEAM_PLAYER_SHIP);
	glTranslatef(-.7, .5, 0);//x,y,z
	glScalef(0.00075, 0.00075, 0.00075);
	drawStroke("PLAYER1 TEAM:");
	glLoadIdentity();//������
	glTranslatef(.15, .5, 0);//x,y,z
	glScalef(0.00075, 0.00075, 0.00075);
	drawStroke(str);


	p = (float)panel_count_enemy / (float)(FIELD_SIZE*FIELD_SIZE) * 100.0f;
	pp = p;
	sprintf(str, "%d %%", pp);
	glLoadIdentity();//������
	setColor(TEAM_ENEMY_SHIP);
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
		setColor(TEAM_ENEMY_SHIP);
		glTranslatef(0, -0.7, 0);//x,y,z
		glScalef(0.00075, 0.00075, 0.00075);
		drawStroke("PLAYER2 WIN!!!!");

	}//�v���C���[�P���v���C���[2���h������������������
	else if (panel_count_player>panel_count_enemy)
	{
		glLoadIdentity();//������
		setColor(TEAM_PLAYER_SHIP);
		glTranslatef(0, -0.7, 0);//x,y,z
		glScalef(0.00075, 0.00075, 0.00075);
		drawStroke("PLAYER1 WIN!!!!");
	}

	glLoadIdentity();//������
	glColor3f(0, 1, 1);
	glTranslatef(0, -0.8, 0);//x,y,z
	glScalef(0.0005, 0.00055, 0.0005);
	drawStroke("push ENTER / BUTTON B");


}
