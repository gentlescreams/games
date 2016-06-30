#ifndef TEXTURE_H_
#define TEXTURE_H_
#include <map>
#include <string>
#include <Windows.h>
#include "../glm\glm.hpp"

#include "../library/util.h"
#include "../glut.h"

//
//�e�N�X�`���̃f�[�^�N���X
//

class Texture
{
public:
	Texture();
	Texture(const char *file_name);
	void BindTexture();
	~Texture();

	 GLuint tex_id;//�e�N�X�`���[�w��id

	BITMAPFILEHEADER bf;
	BITMAPINFOHEADER bi;
	RGB *pixels;
	A *alpha;

};



#endif TEXTURE_H_
