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
	bool is_generated;//�������Ă邩�ǂ���
	glm::vec3 pos;//�|�W�V����
	float yaw;//��]
};
