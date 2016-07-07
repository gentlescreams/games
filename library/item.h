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
	bool is_generated;//¶¬‚µ‚Ä‚é‚©‚Ç‚¤‚©
	glm::vec3 pos;//ƒ|ƒWƒVƒ‡ƒ“
	float yaw;//‰ñ“]
};
