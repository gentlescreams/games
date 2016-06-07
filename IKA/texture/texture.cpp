#define _CRT_SECURE_NO_WARNINGS

#include"texture.h"
#include"../util.h"
#include"../glut.h"


Texture::Texture()
{}


Texture::Texture(const char *file_name)
{


	FILE *pFile = fopen(file_name, "rb");
	assert(pFile != NULL);


	fread(&bf, sizeof(bf), 1, pFile);
	fread(&bi, sizeof(bi), 1, pFile);

	pixels = (RGB*)malloc(bi.biWidth*bi.biHeight * 3);//RGB　メモリの確保

	fread(pixels, bi.biWidth*bi.biHeight * 3, 1, pFile);

	fclose(pFile);

	for (int i = 0; i < bi.biWidth * bi.biHeight; i++)//rgbの入れ替え
	{
		unsigned char keep = 0;
		keep = pixels[i].r;
		pixels[i].r = pixels[i].b;
		pixels[i].b = keep;

	}
	//画像の入れ替え
	for (int y = 0; y < bi.biHeight / 2; y++)
	{
		for (int x = 0; x < bi.biWidth; x++)
		{
			RGB keep = pixels[bi.biWidth * y + x];
			pixels[bi.biWidth * y + x] = pixels[bi.biWidth * (bi.biHeight - 1 - y) + x];
			pixels[bi.biWidth * (bi.biHeight - 1 - y) + x] = keep;

		}
	}
	//αのメモリ確保
	alpha = (A*)malloc(sizeof(A)*bi.biWidth*bi.biHeight);
	for (int i = 0; i < bi.biWidth * bi.biHeight; i++)//rgbの入れ替え
	{
		alpha[i].a = pixels[i].r;
	}

	/*テクスチャのハンドル作成*/
	glGenTextures(1, &tex_id);
	glBindTexture(GL_TEXTURE_2D, tex_id);

	/*	テクスチャパラメータ*/
	glTexImage2D(
		GL_TEXTURE_2D,      // GLenum target
		0,                  // GLint level　ミップマップ　テクスチャの簡略化　遠くから見たときに切り替えをする　
		GL_RGB,             // GLint internalformat　テクスチャのフォーマット
		bi.biWidth, bi.biHeight,               // GLsizei width, height
		0,                  // GLint border
		GL_RGB,             // GLenum format　ピクセルのフォーマット
		GL_UNSIGNED_BYTE,   // GLenum type
		pixels);            // const GLvoid *pixels

							   //縮小時のフィルター
	glTexParameteri(
		GL_TEXTURE_2D,          // GLenum target
		GL_TEXTURE_MIN_FILTER,  // GLenum pname
		GL_NEAREST);            // GLint param

								//拡大時のフィルター
	glTexParameteri(
		GL_TEXTURE_2D,        // GLenum target
		GL_TEXTURE_MAG_FILTER,// GLenum pname
		GL_NEAREST);          // GLint param

}


Texture::~Texture()
{
	/*テクスチャ解放*/
	glDeleteTextures(1, &tex_id);
}






