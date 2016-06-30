
//------------
//�ǂݍ��ރw�b�_�[
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <conio.h>
#define _USE_MATH_DEFINES
#include <math.h>
#include <list>
#include <stdlib.h>
#include <time.h>
#include "scene.h"
#include "./field/panel.h"
#include "./library/util.h"
#include "flyingobject.h"
#include "ship.h"
#include "bullet.h"
#include "camera.h"
#include "model.h"
#include "./controllers/pad_controller.h"

#include "./manager/pc/cri_adx2le.h"
#include "glm\glm.hpp"
#include "glm\gtx\transform.hpp" 
#include "glut.h"

extern PadController gamePad[MAX_CONTROLLERS];

/*��ʂ̃T�C�Y*/
int width = 800;
int height = 680;

int frame = 0;//	�t���[���J�E���g
int sceneType = SCENE_TITLE_INIT;
bool is_game_set = false;


//2�����z��
extern Panel panels[FIELD_SIZE][FIELD_SIZE];

Camera camera;//�J��������
Model model;//���f���ǂݍ��ݎ���
std::list<Ship> ships;
std::list<Bullet> bulletList;

/*�L�[�{�[�h�̏�Ԃ̎擾*/
unsigned char keyboadKeys[256] = {};
unsigned char lastKeyboardKeys[256] = {};
int specialKeys[256] = {};
int lastSpesialKeys[256] = {};

//������Ă���Ƃ�
void keyboard(unsigned char key, int x, int y) {

	keyboadKeys[key] = 1;

}

//	�L�[�{�[�h�������ꂽ�Ƃ�
void keyboardUp(unsigned char key, int x, int y) {
	keyboadKeys[key] = 0;

}


void timer(int value) {

	glutForceJoystickFunc();//joystick�̃f�[�^���擾���ăW���C�X�e�B�b�N�R�[���o�b�N�֐����Ă�
	glutTimerFunc(
		1000 / 60,		//unsigned int millis,�^�C�}�[�����~���b��N������
		timer,	//void (GLUTCALLBACK *func)(int value),
		0);		//int value

				/*�t���[���J�E���g*/
	frame++;

	//�W���C�X�e�B�b�N�̃R���g���[��


	for (DWORD i = 0; i < MAX_CONTROLLERS; i++) {
		gamePad[i].Update();


	}


	for (Ship& sp : ships) {
		if (sp.playerID == PLAYER_1)
			sp.Control(gamePad[0].x, gamePad[0].y, gamePad[0].downKeys, gamePad[0].pressedKeys);

		if (sp.playerID == PLAYER_2) {
			//�L�[�{�[�h�̏���
			sp.KeysControl(keyboadKeys, lastKeyboardKeys);

		}
		else if (sp.playerID == OTHER) {
			sp.Control();
		}

	}

	//�V�[���̌Ăяo��
	scene(sceneType, keyboadKeys, lastKeyboardKeys,
		gamePad[0].downKeys);


	/*�P�t���[���܂��̂�����Ă����L�[�{�[�h��ۑ�*/
	memcpy(lastKeyboardKeys, keyboadKeys, 256);

	glutPostRedisplay();

}


void display(void) {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);//GLbitFIELD_SIZE mask
													   /* ADX2�T�[�o�����̎��s */
	criAtomEx_ExecuteMain();

	//�`��̃V�[���Ăяo��
	sceneDraw(sceneType);

	glFlush();

}



int main(int argc, char *argv[]) {

	glutInit(
		&argc,//int *argcp,
		argv);//char **argv

			  //�E�C���h�E�T�C�Y
	glutInitWindowSize(
		width,  // int width
		height);// int height

	glutCreateWindow("ika");//const char *title

	glutDisplayFunc(display);//void (GLUTCALLBACK *func)(void)

	glutTimerFunc(
		0,		//unsigned int millis,�^�C�}�[�����~���b��N������
		timer,	//void (GLUTCALLBACK *func)(int value),
		0);		//int value

	srand(time(NULL));

	/*�L�[�{�[�h���͎擾�֐��̓o�^-----------------------------*/
	glutKeyboardFunc(keyboard);//void (GLUTCALLBACK *func)(unsigned char key, int x, int y)
	glutKeyboardUpFunc(keyboardUp);// void (GLUTCALLBACK *func)(unsigned char key, int x, int y)
	/*---------------------------------------------------------*/

	Panel::setPanel();//panel�̏�����

	/*�v���C���[�̍쐬*/
	Ship player = Ship(glm::vec3(0, 0.5, 0), TEAM_PLAYER, TEAM_PLAYER_SHIP, PLAYER_1, "materials/ikachan4.blend.x");
	ships.push_back(player);
	Ship player2 = Ship(glm::vec3(0, 0.5, FIELD_SIZE), TEAM_ENEMY, TEAM_ENEMY_SHIP, PLAYER_2, "materials/ikachan4.blend.x");//glm::vec3& _pos, int _team, int _shipColor, int _playerID
	ships.push_back(player2);


	/*npc�̐���*/
	Ship enemy = Ship(glm::vec3(FIELD_SIZE, 0.5, 0), TEAM_PLAYER, TEAM_PLAYER_SHIP, OTHER, "materials/ikachan4.blend.x");
	ships.push_back(enemy);
	Ship enemy2 = Ship(glm::vec3(FIELD_SIZE, 0.5, FIELD_SIZE), TEAM_ENEMY, TEAM_ENEMY_SHIP, OTHER, "materials/ikachan4.blend.x");
	ships.push_back(enemy2);

	/*�J�����̏�����*/
	for (Ship& sp : ships)
		Camera::Camera(&sp);

	//�J���[�̏�����
	for (int z = 0; z < FIELD_SIZE; z++)
	{
		for (int x = 0; x < FIELD_SIZE; x++) {
			panels[z][x].team = TEAM_OTHER;
		}
	}

	/*�����x�̏�����*/
	player.deceleration = 0.95;


	/*���C�����[�v*/
	glutMainLoop();


}
