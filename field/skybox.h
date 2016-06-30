#ifndef _SKYBOX_
#define _SKYBOX_

#include "../glm/glm.hpp"
//
//フィールドを囲うボックス
//

class SkyBox
{
public:
	SkyBox();
	~SkyBox();
	void Draw();//フィールドを囲む壁を描画
private:
};



#endif // !_SKYBOX_
