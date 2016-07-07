#define _CRT_SECURE_NO_WARNINGS

#include "texture.h"
#include "../library/util.h"
#include "../glut.h"

#include <string>
#include <iostream>
//
//テクスチャ読み込み、開放、指定
//



Texture::Texture()
{}

//テクスチャデータ読み込み
RGB* Texture::LeadTexture(const char *file_name )
{
	FILE *pFile = fopen(file_name, "rb");
	assert(pFile != NULL);


	fread(&bf, sizeof(bf), 1, pFile);
	fread(&bi, sizeof(bi), 1, pFile);

	RGB* rgb = nullptr;
	rgb = (RGB*)malloc(bi.biWidth*bi.biHeight * 3);//RGB　メモリの確保

	fread(rgb, bi.biWidth*bi.biHeight * 3, 1, pFile);

	fclose(pFile);

	for (int i = 0; i < bi.biWidth * bi.biHeight; i++)//rgbの入れ替え
	{
		unsigned char keep = 0;
		keep = rgb[i].r;
		rgb[i].r = rgb[i].b;
		rgb[i].b = keep;

	}


	//for (i = 0; i<bi.biWidth*bi.biHeight; i++) {
	//	 r = pixels[i * 4 + 0]; /* R要素 */
	//	int g = imageData[i * 4 + 1]; /* G要素 */
	//	int b = imageData[i * 4 + 2]; /* B要素 */
	//	if (r == ? ? && g == ? ? && b == ? ? ) { /* ??に値を入れて任意の色を特定 */
	//		imageData[i * 4 + 3] = 0; /* 透過する */
	//	}
	//	else {
	//		imageData[i * 4 + 3] = 255; /* 透過しない */
	//	}
	//}

	//画像の入れ替え
	for (int y = 0; y < bi.biHeight / 2; y++)
	{
		for (int x = 0; x < bi.biWidth; x++)
		{
			RGB keep = rgb[bi.biWidth * y + x];
			rgb[bi.biWidth * y + x] = rgb[bi.biWidth * (bi.biHeight - 1 - y) + x];
			rgb[bi.biWidth * (bi.biHeight - 1 - y) + x] = keep;

		}
	}

	/*テクスチャのハンドル作成*/
	glGenTextures(1, &tex_id);
	glBindTexture(GL_TEXTURE_2D, tex_id);


	return rgb;
}


Texture::~Texture()
{
	/*テクスチャ解放*/
	glDeleteTextures(1, &tex_id);
}


//テクスチャ指定
void Texture::BindTexture() {

	glBindTexture(GL_TEXTURE_2D, tex_id);

}


void Texture::TexParam() {
	/*	テクスチャパラメータ*/
	glTexImage2D(
		GL_TEXTURE_2D,      // GLenum target
		0,                  // GLint level　ミップマップ　テクスチャの簡略化　遠くから見たときに切り替えをする　
		GL_RGB,             // GLint internalformat　テクスチャのフォーマット
		bi.biWidth, bi.biHeight,               // GLsizei width, height
		0,                  // GLint border
		GL_RGB,             // GLenum format　ピクセルのフォーマット
		GL_UNSIGNED_BYTE,   // GLenum type
		pixels);            // const GLvoid *rgb

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

void Texture::TexAlphaParam() {

	glBlendFunc(
		GL_SRC_ALPHA,           // GLenum sfactor
		GL_ONE_MINUS_SRC_ALPHA);// GLenum dfactor

	glEnable(GL_BLEND);//ブレンド有効にする

	glTexImage2D(
		GL_TEXTURE_2D,//GLenum target,
		0,//GLint level, 
		GL_RGBA,//GLint internalformat,
		bi.biWidth,//GLsizei width, 
		bi.biHeight,//GLsizei height, 
		0,//GLint border, 
		GL_RGBA,//GLenum format, 
		GL_UNSIGNED_BYTE,//GLenum type, 
		rgba);//const GLvoid *pixels

	glTexParameteri(
		GL_TEXTURE_2D,          // GLenum target
		GL_TEXTURE_MIN_FILTER,  // GLenum pname
		GL_NEAREST);            // GLint param

	glTexParameteri(
		GL_TEXTURE_2D,        // GLenum target
		GL_TEXTURE_MAG_FILTER,// GLenum pname
		GL_NEAREST);          // GLint param
}

//テクスチャデータを合成
void Texture::SynthesisTexture(RGB *mask) {
	rgba = (RGBA*)malloc(bi.biWidth*bi.biHeight * 4);//RGBA　メモリの確保
	//RGBAにRGBの画像いれる
	for (int i = 0; i < bi.biWidth * bi.biHeight; i++)//rgbのデータを入れ込む
	{
		rgba[i].r = pixels[i].r;
		rgba[i].b = pixels[i].b;
		rgba[i].g = pixels[i].g;

		rgba[i].a = mask[i].r;//α値
	}
}

void Texture::Run(const char* file_name,const char* mask_name) {

	//bmpデータ読み込み
	pixels = LeadTexture(file_name);

	std::string str(mask_name);
	std::string str2("nomask");
	std::cout << "str : " << str << std::endl;
	//マスクがなければ透過処理しない
	if	(str != str2)
	{
		RGB *mask = NULL;//マスク用

		//マスクデータ読み込み
		mask = LeadTexture(mask_name);
		//マスクデータをRGBAに代入
		SynthesisTexture(mask);
		//パラメータ
		TexAlphaParam();
	}
	else{
		//パラメータ
		TexParam();
	}
}