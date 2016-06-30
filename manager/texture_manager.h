#ifndef  _TEXTURE_MANAGER_H_
#define  _TEXTURE_MANAGER_H_
#include <map>
#include <string>
#include "../glut.h"
#include "../library/util.h"
#include "../texture/texture.h"

//
//�e�N�X�`���̏����擾����map�ŊǗ�
//






class TextureManager
{
private:
	TextureManager();
	static TextureManager* instance;
	std::map<std::string, Texture*>tex_date;//�e�N�X�`���̏��𕡐������




public:
	~TextureManager();
	//�O����A�N�Z�X���邽�߂̊֐�
	static TextureManager* GetInstance();
	//�e�N�X�`�����쐬
	void ResourceCreate();
	//�e�N�X�`�����w��
	void SpecifyTexture(std::string tex_name);
};



#endif // ! _TEXTURE_Manager_H_
