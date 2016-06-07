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

	pixels = (RGB*)malloc(bi.biWidth*bi.biHeight * 3);//RGB�@�������̊m��

	fread(pixels, bi.biWidth*bi.biHeight * 3, 1, pFile);

	fclose(pFile);

	for (int i = 0; i < bi.biWidth * bi.biHeight; i++)//rgb�̓���ւ�
	{
		unsigned char keep = 0;
		keep = pixels[i].r;
		pixels[i].r = pixels[i].b;
		pixels[i].b = keep;

	}
	//�摜�̓���ւ�
	for (int y = 0; y < bi.biHeight / 2; y++)
	{
		for (int x = 0; x < bi.biWidth; x++)
		{
			RGB keep = pixels[bi.biWidth * y + x];
			pixels[bi.biWidth * y + x] = pixels[bi.biWidth * (bi.biHeight - 1 - y) + x];
			pixels[bi.biWidth * (bi.biHeight - 1 - y) + x] = keep;

		}
	}
	//���̃������m��
	alpha = (A*)malloc(sizeof(A)*bi.biWidth*bi.biHeight);
	for (int i = 0; i < bi.biWidth * bi.biHeight; i++)//rgb�̓���ւ�
	{
		alpha[i].a = pixels[i].r;
	}

	/*�e�N�X�`���̃n���h���쐬*/
	glGenTextures(1, &tex_id);
	glBindTexture(GL_TEXTURE_2D, tex_id);

	/*	�e�N�X�`���p�����[�^*/
	glTexImage2D(
		GL_TEXTURE_2D,      // GLenum target
		0,                  // GLint level�@�~�b�v�}�b�v�@�e�N�X�`���̊ȗ����@�������猩���Ƃ��ɐ؂�ւ�������@
		GL_RGB,             // GLint internalformat�@�e�N�X�`���̃t�H�[�}�b�g
		bi.biWidth, bi.biHeight,               // GLsizei width, height
		0,                  // GLint border
		GL_RGB,             // GLenum format�@�s�N�Z���̃t�H�[�}�b�g
		GL_UNSIGNED_BYTE,   // GLenum type
		pixels);            // const GLvoid *pixels

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


Texture::~Texture()
{
	/*�e�N�X�`�����*/
	glDeleteTextures(1, &tex_id);
}






