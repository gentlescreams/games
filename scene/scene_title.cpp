#define _USE_MATH_DEFINES
#define _CRT_SECURE_NO_WARNINGS

#include "../scene/scene_title.h"

#include<math.h>
#include<list>

#include "../ship.h"
#include"../library/util.h"
#include"../field/panel.h"

#include "../glut.h"
#include "../glm\glm.hpp"
#include "../glm\gtx\transform.hpp" 
#include "../manager/sounds_manager.h"
#include "../manager/texture_manager.h"
#include <Xinput.h>

extern int leftTime;
extern int frame;//	�t���[���J�E���g
extern std::list<Ship> ships;
extern Panel panels[FIELD_SIZE][FIELD_SIZE];


//�^�C�g���V�[���Ăяo���֐�
void scene_title(int &sceneType, unsigned char *keyboadKeys, unsigned char *lastKeyboardKeys, unsigned int downKeys) {

	//�G���^�[�L�[�@�a�{�^���������ꂽ��
	if ((downKeys & XINPUT_GAMEPAD_B) || (keyboadKeys[13] == 1 && lastKeyboardKeys[13] == 0)) {
		//	bgm�̒�~
		SoundsManager::GetInstance()->StopBGM();

		//se�Đ�
		SoundsManager::GetInstance()->PlaySE(CRI_GAME_SOUNDS_SE_BUTTON);


		leftTime = 60 * 31;

		//�v���C���[�̌���
		for (Ship& sp : ships) {
			sp.pos = sp.startPoint;
			glm::vec3 v = glm::vec3(FIELD_SIZE / 2, 0, FIELD_SIZE / 2) - sp.pos;
			sp.yaw = atan2f(v.x, v.z) * 180 / M_PI;

			printf("a");
		}

		//�t�B�[���h�p�l���̏����J���[�ݒ�
		for (int z = 0; z < FIELD_SIZE; z++)
		{
			for (int x = 0; x < FIELD_SIZE; x++) {
				panels[z][x].team = TEAM_OTHER;
			}
		}
		//���[���V�[����
		sceneType = SCENE_GAMERULE;

	}
}


void scene_title_draw() {
	glMatrixMode(GL_PROJECTION);//GLenum mode
	glLoadIdentity();//�ˉe�s��̏�����

	glMatrixMode(GL_MODELVIEW);//GLenum mode	�J�����̐ݒ�
	glLoadIdentity();//������

	//�^�C�g����ʂ̉摜�`��
	scrDraw("title");

	//�{�^���̕�����_�ł��Ȃ���\��
	if (frame % 60 <30) {
		glColor3f(0, 0, 0);
		glLoadIdentity();//������
		glTranslatef(-.75, -.4, 0);//x,y,z
		glScalef(0.001, 0.001, 0.001);
		glLineWidth(3);
		drawStroke("2player games!");
		glLoadIdentity();//������
		glTranslatef(-.75, -.65, 0);//x,y,z
		glScalef(0.0007, 0.0007, 0.0007);
		drawStroke(" push BUTTON B or ENTERKEY");

	}
}
