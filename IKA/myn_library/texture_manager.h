#ifndef  _TEXTURE_MANAGER_H_
#define  _TEXTURE_MANAGER_H_
#include <map>
#include <string>
#include "../glut.h"
#include "../texture/texture.h"




using namespace std;

class TextureManager
{
public:
	TextureManager();
	~TextureManager();

	map<string, Texture*>id;//�e�N�X�`���̏��𕡐������

private:

};



#endif // ! _TEXTURE_Manager_H_
