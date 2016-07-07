#include <array>
#include <string>
#include "texture_Manager.h"

const int texnum = 8;
//テクスチャ画像のパス
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
//テクスチャ登録の名前
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

//インスタンスの初期化
TextureManager* TextureManager::instance = nullptr;

TextureManager* TextureManager::GetInstance()
{
	//インスタンスがなければメモリを確保
	if (instance == nullptr)
	{
		instance = new TextureManager();
	}


	return instance;
}

//テクスチャデータ作成
void TextureManager::ResourceCreate() {
	/*テクスチャ読み込み*/
	for (int i = 0; i < texnum; i++)
	{
		Texture* temp = new Texture();
		temp->Run(texPass[i].c_str(), maskPass[i].c_str());
		tex_date.insert(std::make_pair(texName[i], temp));
	}


}

void TextureManager::SpecifyTexture(std::string tex_name) {

	//データがあるか検索　なければNULLを返す
	std::map<std::string, Texture*>::iterator it = tex_date.find(tex_name);

	//テクスチャの指定
	(*it).second->BindTexture();

}

TextureManager::TextureManager()
{

}

TextureManager::~TextureManager()
{
}

