
//------------
//�ǂݍ��ރw�b�_�[
#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<conio.h>
#define _USE_MATH_DEFINES
#include<math.h>
#include<list>
#include<stdlib.h>
#include<time.h>

#include"scene.h"
#include"panel.h"
#include"util.h"
#include"flyingobject.h"
#include"ship.h"
#include"bullet.h"
#include"camera.h"
#include"model.h"
#include "./myn_library/sounds_manager.h"
#include "./texture/texture.h"

#include"glm\glm.hpp"
#include"glm\gtx\transform.hpp" 
#include"glut.h"


/*��ʂ̃T�C�Y*/
int width = 640;
int height = 480;

int frame = 0;//	�t���[���J�E���g
int sceneType = SCENE_TITLE_INIT;
int panel_count_player = 0;
int panel_count_enemy = 0;
int timeCount = 30;
int leftTime = 0;
bool is_game_set = false;


//2�����z��
extern Panel panels[FIELD_SIZE][FIELD_SIZE];

Camera camera;//�J��������
Model model;//���f���ǂݍ��ݎ���
std::list<Ship> ships;
std::list<Bullet> bulletList;

unsigned int pressedKeys;//��������Ă�L�[
unsigned int releasedKeys;//��������ĂȂ��L�[
unsigned int lastKeys;//�P�t���[���O�̃L�[
unsigned int changedKeys;//�ω��̂������L�[
unsigned int upKeys;//�������ꂽ�L�[
unsigned int downKeys;//�������ꂽ�L�[

//joystick�̏�Ԏ擾
void joystick(unsigned int buttonMask, int x, int y, int z){
	float x1 = x / 1000.0f;
	float y1 = -y / 1000.0f;
	
	pressedKeys = buttonMask;//��������Ă���L�[
	releasedKeys = ~pressedKeys;//��������Ă���L�[�̕␔
	changedKeys = lastKeys ^ pressedKeys;//�ω��̂������L�[
	downKeys = changedKeys & pressedKeys;//�������ꂽ�L�[
	upKeys = changedKeys & releasedKeys;//���͂Ȃ��ꂽ�L�[

	//�W���C�X�e�B�b�N�̃R���g���[��
	for (Ship& sp : ships){
		if (sp.playerID ==PLAYER_1)
		sp.Control(x1, y1, downKeys, pressedKeys);
	}
	lastKeys = pressedKeys;//�P�t���[���O�̃L�[

}

/*�L�[�{�[�h�̏�Ԃ̎擾*/
unsigned char keyboadKeys[256]={};
unsigned char lastKeyboardKeys[256] = {};
void keyboard(unsigned char key, int x, int y){//������Ă���Ƃ�

	keyboadKeys[key] = 1;
	
}

void keyboardUp(unsigned char key, int x, int y){//	�L�[�{�[�h�������ꂽ�Ƃ�
	keyboadKeys[key] = 0;

}


void timer(int value){

	glutForceJoystickFunc();//joystick�̃f�[�^���擾���ăW���C�X�e�B�b�N�R�[���o�b�N�֐����Ă�
	glutTimerFunc(
		1000 / 60,		//unsigned int millis,�^�C�}�[�����~���b��N������
		timer,	//void (GLUTCALLBACK *func)(int value),
		0);		//int value

	/*�t���[���J�E���g*/
	frame++;

	//�V�[���̌Ăяo��
	scene(sceneType,
		keyboadKeys,lastKeyboardKeys,
		downKeys);

	/*�P�t���[���܂��̂�����Ă����L�[�{�[�h��ۑ�*/
	memcpy(lastKeyboardKeys, keyboadKeys, 256);
	
	glutPostRedisplay();

}


void display(void){
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);//GLbitFIELD_SIZE mask

	 /* ADX2�T�[�o�����̎��s */
	criAtomEx_ExecuteMain();

	//�`��̃V�[���Ăяo��
	sceneDraw(sceneType);
	
	glFlush();

}



int main(int argc, char *argv[]){

	glutInit(
		&argc,//int *argcp,
		argv);//char **argv

	//�E�C���h�E�T�C�Y
	glutInitWindowSize(
		width,  // int width
		height);// int height

	glutCreateWindow("title");//const char *title

	glutDisplayFunc(display);//void (GLUTCALLBACK *func)(void)

	glutTimerFunc(
		0,		//unsigned int millis,�^�C�}�[�����~���b��N������
		timer,	//void (GLUTCALLBACK *func)(int value),
		0);		//int value

	glutJoystickFunc(
		joystick,	//void(GLUTCALLBACK *func)(unsigned int buttonMask, int x, int y, int z),
		0);			//int pollInterval

	glutKeyboardFunc(keyboard);//void (GLUTCALLBACK *func)(unsigned char key, int x, int y)

	glutKeyboardUpFunc(keyboardUp);

	srand(time(NULL));
	

	Panel::setPanel();//panel�̏�����

	/*�v���C���[�`�[���̍쐬*/
	//player1
	Ship player = Ship(glm::vec3(0, 0.5, 0),TEAM_PLAYER,TEAM_PLAYER_SHIP, PLAYER_1, "ikachan4.blend.x");
	ships.push_back(player);
	Ship player2 = Ship(glm::vec3(FIELD_SIZE, 0.5, 0), TEAM_PLAYER,TEAM_PLAYER_SHIP, OTHER, "ikachan4.blend.x");//glm::vec3& _pos, int _team, int _shipColor, int _playerID
	ships.push_back(player2);


	/*�G�`�[���̐���*/
	//player2
	Ship enemy = Ship(glm::vec3(0, 0.5, FIELD_SIZE), TEAM_ENEMY,TEAM_ENEMY_SHIP, PLAYER_2, "ikachan4.blend.x");
	ships.push_back(enemy);
	Ship enemy2 = Ship(glm::vec3(FIELD_SIZE, 0.5, FIELD_SIZE), TEAM_ENEMY, TEAM_ENEMY_SHIP, OTHER, "ikachan4.blend.x");
	ships.push_back(enemy2);

	/*�J�����̏�����*/
	for (Ship& sp : ships)
	Camera::Camera(&sp);

	//�J���[�̏�����
	for (int z = 0; z < FIELD_SIZE; z++)
	{
		for (int x = 0; x < FIELD_SIZE; x++){
			panels[z][x].team = TEAM_OTHER;
		}
	}

	/*�����x�̏�����*/
	player.deceleration = 0.95;
	

	/*���C�����[�v*/
	glutMainLoop();


}
