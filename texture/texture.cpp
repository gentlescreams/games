#define _CRT_SECURE_NO_WARNINGS

#include "texture.h"
#include "../library/util.h"
#include "../glut.h"

#include <string>
#include <iostream>
//
//�e�N�X�`���ǂݍ��݁A�J���A�w��
//



Texture::Texture()
{}

//�e�N�X�`���f�[�^�ǂݍ���
RGB* Texture::LeadTexture(const char *file_name )
{
	FILE *pFile = fopen(file_name, "rb");
	assert(pFile != NULL);


	fread(&bf, sizeof(bf), 1, pFile);
	fread(&bi, sizeof(bi), 1, pFile);

	RGB* rgb = nullptr;
	rgb = (RGB*)malloc(bi.biWidth*bi.biHeight * 3);//RGB�@�������̊m��

	fread(rgb, bi.biWidth*bi.biHeight * 3, 1, pFile);

	fclose(pFile);

	for (int i = 0; i < bi.biWidth * bi.biHeight; i++)//rgb�̓���ւ�
	{
		unsigned char keep = 0;
		keep = rgb[i].r;
		rgb[i].r = rgb[i].b;
		rgb[i].b = keep;

	}


	//for (i = 0; i<bi.biWidth*bi.biHeight; i++) {
	//	 r = pixels[i * 4 + 0]; /* R�v�f */
	//	int g = imageData[i * 4 + 1]; /* G�v�f */
	//	int b = imageData[i * 4 + 2]; /* B�v�f */
	//	if (r == ? ? && g == ? ? && b == ? ? ) { /* ??�ɒl�����ĔC�ӂ̐F����� */
	//		imageData[i * 4 + 3] = 0; /* ���߂��� */
	//	}
	//	else {
	//		imageData[i * 4 + 3] = 255; /* ���߂��Ȃ� */
	//	}
	//}

	//�摜�̓���ւ�
	for (int y = 0; y < bi.biHeight / 2; y++)
	{
		for (int x = 0; x < bi.biWidth; x++)
		{
			RGB keep = rgb[bi.biWidth * y + x];
			rgb[bi.biWidth * y + x] = rgb[bi.biWidth * (bi.biHeight - 1 - y) + x];
			rgb[bi.biWidth * (bi.biHeight - 1 - y) + x] = keep;

		}
	}

	/*�e�N�X�`���̃n���h���쐬*/
	glGenTextures(1, &tex_id);
	glBindTexture(GL_TEXTURE_2D, tex_id);


	return rgb;
}


Texture::~Texture()
{
	/*�e�N�X�`�����*/
	glDeleteTextures(1, &tex_id);
}


//�e�N�X�`���w��
void Texture::BindTexture() {

	glBindTexture(GL_TEXTURE_2D, tex_id);

}


void Texture::TexParam() {
	/*	�e�N�X�`���p�����[�^*/
	glTexImage2D(
		GL_TEXTURE_2D,      // GLenum target
		0,                  // GLint level�@�~�b�v�}�b�v�@�e�N�X�`���̊ȗ����@�������猩���Ƃ��ɐ؂�ւ�������@
		GL_RGB,             // GLint internalformat�@�e�N�X�`���̃t�H�[�}�b�g
		bi.biWidth, bi.biHeight,               // GLsizei width, height
		0,                  // GLint border
		GL_RGB,             // GLenum format�@�s�N�Z���̃t�H�[�}�b�g
		GL_UNSIGNED_BYTE,   // GLenum type
		pixels);            // const GLvoid *rgb

							//�k�����̃t�B���^�[
	glTexParameteri(
		GL_TEXTURE_2D,          // GLenum target
		GL_TEXTURE_MIN_FILTER,  // GLenum pname
		GL_NEAREST);            // GLint param

								//�g�厞�̃t�B���^�[
	glTexParameteri(
		GL_TEXTURE_2D,        // GLenum target
		GL_TEXTURE_MAG_FILTER,// GLenum pname
		GL_NEAREST);          // GLint param
}

void Texture::TexAlphaParam() {

	glBlendFunc(
		GL_SRC_ALPHA,           // GLenum sfactor
		GL_ONE_MINUS_SRC_ALPHA);// GLenum dfactor

	glEnable(GL_BLEND);//�u�����h�L���ɂ���

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

//�e�N�X�`���f�[�^������
void Texture::SynthesisTexture(RGB *mask) {
	rgba = (RGBA*)malloc(bi.biWidth*bi.biHeight * 4);//RGBA�@�������̊m��
	//RGBA��RGB�̉摜�����
	for (int i = 0; i < bi.biWidth * bi.biHeight; i++)//rgb�̃f�[�^����ꍞ��
	{
		rgba[i].r = pixels[i].r;
		rgba[i].b = pixels[i].b;
		rgba[i].g = pixels[i].g;

		rgba[i].a = mask[i].r;//���l
	}
}

void Texture::Run(const char* file_name,const char* mask_name) {

	//bmp�f�[�^�ǂݍ���
	pixels = LeadTexture(file_name);

	std::string str(mask_name);
	std::string str2("nomask");
	std::cout << "str : " << str << std::endl;
	//�}�X�N���Ȃ���Γ��ߏ������Ȃ�
	if	(str != str2)
	{
		RGB *mask = NULL;//�}�X�N�p

		//�}�X�N�f�[�^�ǂݍ���
		mask = LeadTexture(mask_name);
		//�}�X�N�f�[�^��RGBA�ɑ��
		SynthesisTexture(mask);
		//�p�����[�^
		TexAlphaParam();
	}
	else{
		//�p�����[�^
		TexParam();
	}
}