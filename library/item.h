#include "../glm/glm.hpp"

//
//
//


class  Item
{
public:
	 Item();
	~ Item();
	void Draw();
	void Move();
	void SetFlag();
private:
	bool is_generated;//生成してるかどうか
	glm::vec3 pos;//ポジション
	float yaw;//回転
};
