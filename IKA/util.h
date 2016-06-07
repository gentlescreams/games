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
	PLAYER_1,//１ｐ
	PLAYER_2,//２ｐ
	OTHER,//プレイヤーなし
};

enum{
	TEAM_OTHER,//フィールド
	TEAM_PLAYER,//プレイヤーカラー
	TEAM_ENEMY,//敵カラー
	TEAM_PLAYER_SHIP,//プレイヤー自機のカラー
	TEAM_ENEMY_SHIP//敵自機のカラー
};
enum{
	SCENE_TITLE_INIT,//タイトル初期化
	SCENE_TITLE,//タイトル
	SCENE_GAME_INIT,//ゲーム初期化
	SCENE_GAME,//ゲーム
	SCENE_RESULT_INIT,//ゲーム終了初期化
	SCENE_RESULT,//ゲーム終了時
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