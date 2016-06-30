#ifndef  _TEXTURE_MANAGER_H_
#define  _TEXTURE_MANAGER_H_
#include <map>
#include <string>
#include "../glut.h"
#include "../library/util.h"
#include "../texture/texture.h"

//
//テクスチャの情報を取得してmapで管理
//






class TextureManager
{
private:
	TextureManager();
	static TextureManager* instance;
	std::map<std::string, Texture*>tex_date;//テクスチャの情報を複数いれる




public:
	~TextureManager();
	//外からアクセスするための関数
	static TextureManager* GetInstance();
	//テクスチャを作成
	void ResourceCreate();
	//テクスチャを指定
	void SpecifyTexture(std::string tex_name);
};



#endif // ! _TEXTURE_Manager_H_
