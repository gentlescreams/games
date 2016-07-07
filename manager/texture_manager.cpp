#include <array>
#include <string>
#include "texture_Manager.h"

const int texnum = 8;
//�e�N�X�`���摜�̃p�X
std::array < std::string, texnum> texPass = {
	"materials/gesotaso.bmp",
	"materials/gesotaso2.bmp",
	"materials/gesotaso3.bmp",
	"materials/game_title.bmp",
	"materials/game_resurt.bmp",
	"materials/game_rule.bmp",
	"materials/field.bmp",
	"materials/item.bmp"
};

std::array < std::string, texnum> maskPass = {
	"nomask",
	"nomask",
	"nomask",
	"nomask",
	"nomask",
	"nomask",
	"nomask",
	"materials/item_m.bmp"
};
//�e�N�X�`���o�^�̖��O
std::array < std::string, texnum> texName = {
	"player",
	"enemy",
	"samp",
	"title",
	"resurt",
	"rule",
	"field",
	"bomb"
};

//�C���X�^���X�̏�����
TextureManager* TextureManager::instance = nullptr;

TextureManager* TextureManager::GetInstance()
{
	//�C���X�^���X���Ȃ���΃��������m��
	if (instance == nullptr)
	{
		instance = new TextureManager();
	}


	return instance;
}

//�e�N�X�`���f�[�^�쐬
void TextureManager::ResourceCreate() {
	/*�e�N�X�`���ǂݍ���*/
	for (int i = 0; i < texnum; i++)
	{
		Texture* temp = new Texture();
		temp->Run(texPass[i].c_str(), maskPass[i].c_str());
		tex_date.insert(std::make_pair(texName[i], temp));
	}


}

void TextureManager::SpecifyTexture(std::string tex_name) {

	//�f�[�^�����邩�����@�Ȃ����NULL��Ԃ�
	std::map<std::string, Texture*>::iterator it = tex_date.find(tex_name);

	//�e�N�X�`���̎w��
	(*it).second->BindTexture();

}

TextureManager::TextureManager()
{

}

TextureManager::~TextureManager()
{
}

