#ifndef _UTIL_H_
#define _UTIL_H_
#define _CRT_SECURE_NO_WARNINGS
#define FIELD_SIZE 50

#include<Windows.h>
#include "../glm/glm.hpp"

enum 
{
	PLAYER_1,//�P��
	PLAYER_2,//�Q��
	OTHER,//�v���C���[�Ȃ�
};

enum{
	TEAM_OTHER,//�t�B�[���h
	TEAM_PLAYER,//�v���C���[�J���[
	TEAM_ENEMY,//�G�J���[
	TEAM_PLAYER_SHIP,//�v���C���[���@�̃J���[
	TEAM_ENEMY_SHIP//�G���@�̃J���[
};
enum{
	SCENE_TITLE_INIT,//�^�C�g��������
	SCENE_TITLE,//�^�C�g��
	SCENE_GAMERULE,//�Q�[������
	SCENE_GAME_INIT,//�Q�[��������
	SCENE_GAME,//�Q�[��
	SCENE_RESULT_INIT,//�Q�[���I��������
	SCENE_RESULT,//�Q�[���I����
	SCENE_MAX,
};

//RGB
struct RGB {
	unsigned char r, g, b;
};

//���l
struct  RGBA {
	unsigned char r, g, b, a;
};

float distance(glm::vec3 &_vec0, glm::vec3 &_vec1);
void scrDraw(const char* name);
void drawString(const char* _str);
void drawStroke(const char* _str);
void drawBits(unsigned int _bits);
void setColor(const int _colorType);
char parcalc(int panel_counter);
#endif