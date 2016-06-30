#define _USE_MATH_DEFINES
#define _CRT_SECURE_NO_WARNINGS
#include <list>
#include <math.h>
#include <array>
#include <string>

#include"scene.h"

#include "./scene/scene_title.h"
#include "./scene/scene_gamerule.h"
#include "./scene/scene_game.h"
#include "./scene/scene_resurt.h"
#include "bullet.h"
#include "camera.h"
#include "ship.h"
#include "./library/util.h"
#include "./field/panel.h"
#include "glut.h"
#include "glm\glm.hpp"
#include "glm\gtx\transform.hpp" 
#include "./manager/sounds_manager.h"
#include "./manager/texture_manager.h"

extern std::list<Ship> ships;
extern Panel panels[FIELD_SIZE][FIELD_SIZE];
extern std::list<Bullet> bulletList;

extern int width;
extern int height;

extern Camera camera;

void scene(int &sceneType, unsigned char *keyboadKeys, unsigned char *lastKeyboardKeys,unsigned int downKeys){

	switch (sceneType)
	{
	case SCENE_TITLE_INIT://�^�C�g��������
	{
		//bgm�Đ�
		SoundsManager::GetInstance()->PlayBGM(CRI_GAME_SOUNDS_BGM_TITLE);
		//�e�N�X�`���o�^
		TextureManager::GetInstance()->ResourceCreate();

		sceneType = SCENE_TITLE;
	}
		break;

	case SCENE_TITLE://�^�C�g��

		/*�^�C�g���V�[���֐��Ăяo��*/
		scene_title(sceneType, keyboadKeys, lastKeyboardKeys, downKeys);

		break;
	case SCENE_GAMERULE:
		//���[���V�[���֐��Ăяo��
		scene_rule(sceneType, keyboadKeys, lastKeyboardKeys, downKeys);

		break;
	case SCENE_GAME_INIT://�Q�[��������

		//bgm�Đ�
		SoundsManager::GetInstance()->PlayBGM(CRI_GAME_SOUNDS_BGM_GAME);
		sceneType = SCENE_GAME;
		break;
	case SCENE_GAME://�Q�[��

		//�Q�[���V�[���̌Ăяo��
		scene_game(sceneType, keyboadKeys, lastKeyboardKeys, downKeys);

		break;
	case SCENE_RESULT_INIT://���U���g������
		//bgm�Đ�
		SoundsManager::GetInstance()->PlayBGM(CRI_GAME_SOUNDS_BGM_RESURT);

		sceneType = SCENE_RESULT;
		break;
	case SCENE_RESULT:

		//���U���g�V�[���̌Ăяo��
		scene_resurt(sceneType, keyboadKeys, lastKeyboardKeys, downKeys);

		break;
	default:
		break;
	}

}



void sceneDraw(int &sceneType){

	/*�J�����̏����ݒ�*/
	glMatrixMode(GL_PROJECTION);//GLenum mode
	glLoadIdentity();//������
	gluPerspective(
		45,		//GLdouble fovy,�p�x
		(float)width / (height / 2),		//GLdouble aspect,��ʂ̕�
		0.1,	//Ldouble zNear,�J��������̋����@���̐��l���߂����͕̂`�悳��Ȃ�
		1000);	// GLdouble zFar�J��������̋����@���̐��l��艓�����͕̂`�悳��Ȃ�

	glGetFloatv(
		GL_PROJECTION_MATRIX,   // GLenum pname
		(GLfloat*)&camera.project);               // GLfloat *params�A�h���X��n��

	glMatrixMode(GL_MODELVIEW);//GLenum mode	�J�����̐ݒ�
	glLoadIdentity();
	Ship& player = *ships.begin();
	gluLookAt(
		player.pos.x - sin(player.yaw*M_PI / 180) * 8, 4, player.pos.z - cos(player.yaw*M_PI / 180) * 8,//GLdouble eyex, eyey, eyez,
		player.pos.x, player.pos.y + 1.3, player.pos.z,//GLdouble centerx, centery, centerz,
		0, 1, 0);//GLdouble upx, upy, upz

	//���f���r���[�s��擾

	glGetFloatv(
		GL_MODELVIEW_MATRIX,// GLenum pname
		(GLfloat*)&camera.modelview);         // GLfloat *param
	


	switch (sceneType)
	{

	case SCENE_TITLE:
		/*�^�C�g���V�[���`��֐�*/
		scene_title_draw();
		break;
	case SCENE_GAMERULE:
		/*���[���V�[���`��֐�*/
		scene_rule_draw();
		break;
	case SCENE_GAME:
		/*�Q�[���V�[���`��֐�*/
		scene_game_draw();
		break;

	case SCENE_RESULT:
		/*���U���g�V�[���`��֐�*/
		scene_resurt_draw();		
		break;
	default:
		break;
	}

}