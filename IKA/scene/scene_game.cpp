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

extern int panel_count_player;//�v���C���[�̃p�l���J�E���^�[
extern int panel_count_enemy;//�G�̃p�l���J�E���^�[

extern Panel panels[FIELD_SIZE][FIELD_SIZE];
extern bool is_game_set;

extern int width;
extern int height;

extern Camera camera;


//�Q�[���V�[���Ăяo���֐�
void scene_game(int &sceneType, unsigned char *keyboadKeys, unsigned char *lastKeyboardKeys, unsigned int downKeys) {
	//�^�C�����}�C�i�X�ɂȂ�Ȃ��悤��
	if (leftTime > 0)
		leftTime--;


	//�Q�[���I���ȊO��
	if (is_game_set != true)
	{
		for (Ship& sp : ships) {

			if (sp.playerID == PLAYER_2) {
				//�L�[�{�[�h�̏���
				sp.Control(keyboadKeys, lastKeyboardKeys);

			}
			else if (sp.playerID == OTHER) {
				sp.Control();
			}

			sp.Update();
			//�v���C���[���t�B�[���h����o�Ȃ��悤�ɂ���
			sp.playerArea();

		}

		//�e�ƃt�B�[���h�̂����蔻��
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

		/*�p�l���̃J�E���g*/
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

		//�e�̈ړ�����
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



	//�����_���@���񂾂���
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

	glEnable(GL_DEPTH_TEST);	// GLenum cap�@�[�x�e�X�g�@


//--------------------------
	glEnableClientState(GL_VERTEX_ARRAY);// GLenum array
	glEnableClientState(GL_NORMAL_ARRAY);
//---------------------------

	/*���ʁ@�v���C���[�P�̕`�揈��*/
	glViewport(0, height / 2, width, height / 2);

	/*�r���[�|�[�g�̎擾*/
	glm::ivec4 viewport;
	glGetIntegerv(
		GL_VIEWPORT,// GLenum pname
		(GLint*)&viewport);  // GLint *params

 ///////////////�t�B�[���h
		//2�����z��
	for (int z = 0; z < FIELD_SIZE; z++)
	{
		for (int x = 0; x < FIELD_SIZE; x++)
		{
			panels[z][x].draw();
		}
	}



	//��
	for (Ship& sp : ships) {
		//�X�N���[�����W�̎擾
		
		sp.scr_pos = glm::project(sp.pos, camera.modelview, camera.project, viewport);

		sp.Draw();
	}

	//�e
	for (Bullet& b : bulletList)
		b.Draw();

	glMatrixMode(GL_PROJECTION);//GLenum mode
	glLoadIdentity();//�ˉe�s��̏�����
	glMatrixMode(GL_MODELVIEW);//GLenum mode	�J�����̐ݒ�

	glDisable(GL_DEPTH_TEST);

	//////�������
	glLoadIdentity();//������
	glColor3f(1.0f / 255 * 127, 1.0f / 255 * 127, 1.0f / 255 * 127);
	glTranslatef(-0.95, -0.95, 0);//x,y,z
	glLineWidth(2);
	glScalef(0.0007, 0.0007, 0.0007);
	drawStroke("[LStick]Control [A]Fire");

	////////�Q�[�����̃v���C���[���p�l����h������
	float p = (float)panel_count_player / (float)(FIELD_SIZE*FIELD_SIZE) * 100.0f;
	int pp = p;
	char str[256];
	sprintf(str, "%d %%", pp);

	glLoadIdentity();//������
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

	//�G���p�l����h������
	p = (float)panel_count_enemy / (float)(FIELD_SIZE*FIELD_SIZE) * 100.0f;
	pp = p;
	sprintf(str, "%d %%", pp);

	glLoadIdentity();//������
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


	//�t���[�����l�������@�`��
	glLoadIdentity();//������
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

	//�^�C���A�b�v�ɂȂ������̏���
	if (leftTime / 60 == 0) {

		glMatrixMode(GL_PROJECTION);//GLenum mode
		glLoadIdentity();//�ˉe�s��̏�����
		glMatrixMode(GL_MODELVIEW);//GLenum mode	�J�����̐ݒ�

								   //��
		glLoadIdentity();//������
		glColor3f(1, 1, 1);
		glTranslatef(-.3, 0, 0);//x,y,z
		glScalef(0.00075, 0.00075, 0.00075);
		drawStroke("GAME SET!");
		glLoadIdentity();
		glColor3f(1, 1, 1);
		glTranslatef(-.8, -.2, 0);
		glScalef(0.00065, 0.00065, 0.00065);
		drawStroke("push ENTER / BUTTON B");

		//��
		glLoadIdentity();//������
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
	/*���_*/
	glMatrixMode(GL_PROJECTION);//GLenum mode
	glLoadIdentity();//������
	gluPerspective(
		45,		//GLdouble fovy,�p�x
		(float)width / (height / 2),		//GLdouble aspect,��ʂ̕�
		0.1,	//Ldouble zNear,�J��������̋����@���̐��l���߂����͕̂`�悳��Ȃ�
		100);	// GLdouble zFar�J��������̋����@���̐��l��艓�����͕̂`�悳��Ȃ�


	/*�ˉe�s��̎擾*/
	glGetFloatv(
		GL_PROJECTION_MATRIX,   // GLenum pname
		(GLfloat*)&camera.project);               // GLfloat *params�A�h���X��n��

	glMatrixMode(GL_MODELVIEW);//GLenum mode	�J�����̐ݒ�
	glLoadIdentity();

	/*����ʁ@�v���C���[�Q�̏���*/
	glViewport(0, 0, width, height / 2);

	/*�r���[�|�[�g�̎擾*/
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


	//���f���r���[�s��擾
//	glm::mat4 modelview_2p;
	glGetFloatv(
		GL_MODELVIEW_MATRIX,// GLenum pname
		(GLfloat*)&camera.modelview);         // GLfloat *params


										  //---------------------------------------------------------


										  ///////////////�t�B�[���h
										  //2�����z��
	for (int z = 0; z < FIELD_SIZE; z++)
	{
		for (int x = 0; x < FIELD_SIZE; x++)
		{
			panels[z][x].draw();
		}
	}
	//��
	for (Ship& sp : ships) {
		//	�X�N���[�����W�̎擾
		sp.scr_pos = glm::project(sp.pos, camera.modelview, camera.project, viewport_2p);
		//�v���C���[�̏�ɍ��W�����Ă��Ă���
		sp.scr_pos.y += (float)height / 2;
		//�`��

		sp.Draw();
	}

	//�e
	for (Bullet& b : bulletList)
		b.Draw();

	glMatrixMode(GL_PROJECTION);//GLenum mode
	glLoadIdentity();//�ˉe�s��̏�����
	glMatrixMode(GL_MODELVIEW);//GLenum mode	�J�����̐ݒ�

	glDisable(GL_DEPTH_TEST);

	////�������////
	glLoadIdentity();//������
	glColor3f(1.0f / 255 * 127, 1.0f / 255 * 127, 1.0f / 255 * 127);
	glTranslatef(-0.95, -0.95, 0);//x,y,z
	glLineWidth(2);
	glScalef(0.0007, 0.0007, 0.0007);
	drawStroke("[W/S/A/D]Control [Space]Fire");
	///////////////

	/*���݂̃p�l���̓h�����������\��*/

	////////�Q�[�����̃v���C���[���p�l����h������
	p = (float)panel_count_player / (float)(FIELD_SIZE*FIELD_SIZE) * 100.0f;
	pp = p;

	sprintf(str, "%d %%", pp);

	glLoadIdentity();//������
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

	//�G���p�l����h������
	p = (float)panel_count_enemy / (float)(FIELD_SIZE*FIELD_SIZE) * 100.0f;
	pp = p;
	sprintf(str, "%d %%", pp);

	glLoadIdentity();//������
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
	//�^�C���A�b�v�ɂȂ������̏���
	if (leftTime / 60 == 0) {

		glMatrixMode(GL_PROJECTION);//GLenum mode
		glLoadIdentity();//�ˉe�s��̏�����
		glMatrixMode(GL_MODELVIEW);//GLenum mode	�J�����̐ݒ�

								   //��
		glLoadIdentity();//������
		glColor3f(1, 1, 1);
		glTranslatef(-.3, 0, 0);//x,y,z
		glScalef(0.00075, 0.00075, 0.00075);
		drawStroke("GAME SET!");
		glLoadIdentity();
		glColor3f(1, 1, 1);
		glTranslatef(-.8, -.2, 0);
		glScalef(0.00065, 0.00065, 0.00065);
		drawStroke("push ENTER / BUTTON B");

		//��
		glLoadIdentity();//������
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





