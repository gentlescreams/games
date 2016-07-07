#ifndef TEXTURE_H_
#define TEXTURE_H_
#include <map>
#include <string>
#include <Windows.h>
#include "../glm\glm.hpp"

#include "../library/util.h"
#include "../glut.h"

//
//テクスチャのデータクラス
//

class Texture
{
public:
	Texture();
	RGB* LeadTexture(const char *file_name );
	void BindTexture();
	~Texture();
	void SynthesisTexture(RGB *mask);
	 GLuint tex_id;//テクスチャー指定id
	 void Run(const char* file_name, const char* mask_name);
private:
	BITMAPFILEHEADER bf;
	BITMAPINFOHEADER bi;
	RGB *pixels;
	RGBA *rgba;
	void TexParam();
	void TexAlphaParam();
};



#endif TEXTURE_H_
