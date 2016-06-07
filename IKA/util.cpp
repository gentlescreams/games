#define _CRT_SECURE_NO_WARNINGS


#include<assert.h>
#include<Windows.h>
#include<stdio.h>
#include"util.h"
#include<math.h>
#include"glm\glm.hpp"
#include "glut.h"

//GLuint bmp_load_Data(const char *file_name) {//ｂｍｐ画像のロード
//
//
//
//	FILE *pFile = fopen(file_name, "rb");
//	assert(pFile != NULL);
//
//
//	fread(&bd.bf, sizeof(bd.bf), 1, pFile);
//	fread(&bd.bi, sizeof(bd.bi), 1, pFile);
//
//	bd.pixels = (RGB*)malloc(bd.bi.biWidth*bd.bi.biHeight * 3);//RGB　メモリの確保
//
//	fread(bd.pixels, bd.bi.biWidth*bd.bi.biHeight * 3, 1, pFile);
//
//	fclose(pFile);
//
//	for (int i = 0; i < bd.bi.biWidth * bd.bi.biHeight; i++)//rgbの入れ替え
//	{
//		unsigned char keep = 0;
//		keep = bd.pixels[i].r;
//		bd.pixels[i].r = bd.pixels[i].b;
//		bd.pixels[i].b = keep;
//
//	}
//	//画像の入れ替え
//	for (int y = 0; y < bd.bi.biHeight / 2; y++)
//	{
//		for (int x = 0; x < bd.bi.biWidth; x++)
//		{
//			RGB keep = bd.pixels[bd.bi.biWidth * y + x];
//			bd.pixels[bd.bi.biWidth * y + x] = bd.pixels[bd.bi.biWidth * (bd.bi.biHeight - 1 - y) + x];
//			bd.pixels[bd.bi.biWidth * (bd.bi.biHeight - 1 - y) + x] = keep;
//
//		}
//	}
//	//αのメモリ確保
//	bd.alpha = (A*)malloc(sizeof(A)*bd.bi.biWidth*bd.bi.biHeight);
//	for (int i = 0; i < bd.bi.biWidth * bd.bi.biHeight; i++)//rgbの入れ替え
//	{
//		bd.alpha[i].a = bd.pixels[i].r;
//	}
//	
//	/*テクスチャのハンドル作成*/
//	GLuint tex_hn;
//
//	glGenTextures(1, &tex_hn);
//
//
//	glTexImage2D(
//		GL_TEXTURE_2D,      // GLenum target
//		0,                  // GLint level　ミップマップ　テクスチャの簡略化　遠くから見たときに切り替えをする　
//		GL_RGB,             // GLint internalformat　テクスチャのフォーマット
//		bd.bi.biWidth, bd.bi.biHeight,               // GLsizei width, height
//		0,                  // GLint border
//		GL_RGB,             // GLenum format　ピクセルのフォーマット
//		GL_UNSIGNED_BYTE,   // GLenum type
//		bd.pixels);            // const GLvoid *pixels
//
//						 //縮小時のフィルター
//	glTexParameteri(
//		GL_TEXTURE_2D,          // GLenum target
//		GL_TEXTURE_MIN_FILTER,  // GLenum pname
//		GL_NEAREST);            // GLint param
//
//								//拡大時のフィルター
//	glTexParameteri(
//		GL_TEXTURE_2D,        // GLenum target
//		GL_TEXTURE_MAG_FILTER,// GLenum pname
//		GL_NEAREST);          // GLint param
//
//
//	return tex_hn;
//
//
//}




//あたり判定
float distance(glm::vec3 &_vec0, glm::vec3 &_vec1){
	//弾と敵の差のベクトル（向きと距離を調べた）
	glm::vec3 v = _vec0 - _vec1;

	return sqrt(v.x * v.x + v.y * v.y + v.z * v.z);

}

//色の変化
void setColor(const int _colorType){
	switch (_colorType)
	{
	case TEAM_PLAYER://味方
		glColor3f(1.f, 1.f / 255 * 173, 1.f / 255 * 119);
		break;
	case TEAM_PLAYER_SHIP:
		glColor3f(1.f, 1.f / 255 * 127, 1.f / 255 * 39);
		break;
	case TEAM_ENEMY://敵
		glColor3f(1.f/255* 114, 1.f / 255 * 121, 1.f / 255 * 218);
		break;
	case TEAM_ENEMY_SHIP:
		glColor3f(1.f/255* 63, 1.f / 255 * 72, 1.f / 255 * 204);
		break;
	case TEAM_OTHER://初期
		glColor3f(1.f, 1.f, 1.f);
		break;
	}
}


void drawString(const char* _str){//文字列をビットマップ文字で表示


	for (int i = 0; _str[i] != 0; i++)
	{
		glutBitmapCharacter(
			GLUT_BITMAP_9_BY_15,// void *font
			_str[i]);               // int character
	}
}

void drawStroke(const char* _str){//文字列をストローク文字で表示

	for (int i = 0; _str[i] != 0; i++)
	{
		glutStrokeCharacter(
			GLUT_STROKE_ROMAN,	//void *font, フォント指定
			_str[i]);				//int character　文字の指定
	}
}

void drawBits(unsigned int _bits){//渡された値を二進数で表示する
	unsigned int flag = 1 << 31;

	for (int i = 0; i < 32; i++)
	{
		if ((flag >> i)& _bits){
			glutBitmapCharacter(
				GLUT_BITMAP_9_BY_15,// void *font
				'1');               // int character	
		}
		else
		{
			glutBitmapCharacter(
				GLUT_BITMAP_9_BY_15,// void *font
				'0');               // int character	 
		}
		if ((i % 4 == 3) & (31 != i))
		{
			glutBitmapCharacter(
				GLUT_BITMAP_9_BY_15,// void *font
				',');               // int character	 }
		}
	}
}
