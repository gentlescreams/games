#ifndef TEXTURE_H_
#define TEXTURE_H_
#include <map>
#include <string>
#include <Windows.h>
#include"../glm\glm.hpp"

#include"../util.h"
#include"../glut.h"

class Texture
{
public:
	Texture();
	Texture(const char *file_name);
	~Texture();

	 GLuint tex_id;//テクスチャー指定id

	BITMAPFILEHEADER bf;
	BITMAPINFOHEADER bi;
	RGB *pixels;
	A *alpha;

};



#endif TEXTURE_H_
