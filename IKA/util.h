#ifndef _UTIL_H_
#define _UTIL_H_
#define _CRT_SECURE_NO_WARNINGS
#define FIELD_SIZE 60

#include<Windows.h>
#include"glm\glm.hpp"
#include"glut.h"
//#include"vec3.h"

using namespace glm;

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
	SCENE_GAME_INIT,//�Q�[��������
	SCENE_GAME,//�Q�[��
	SCENE_RESULT_INIT,//�Q�[���I��������
	SCENE_RESULT,//�Q�[���I����
	SCENE_MAX,
};


struct RGB {
	unsigned char b, g, r;
};

struct  A {
	unsigned char a;
};


//typedef struct{
//	BITMAPFILEHEADER bf;
//	BITMAPINFOHEADER bi;
//	RGB *pixels;
//	A *alpha;
//}BMP;


GLuint bmp_load_Data(const char *file_name);

float distance(glm::vec3 &_vec0, glm::vec3 &_vec1);

void drawString(const char* _str);
void drawStroke(const char* _str);
void drawBits(unsigned int _bits);
void setColor(const int _colorType);

#endif