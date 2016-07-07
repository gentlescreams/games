#include "item.h"
#include "../glut.h"
#include "../manager/texture_manager.h"

Item::Item()
{
	//posをランダムセット
	float randomPos, rx, rz;
	randomPos = (float)rand() / RAND_MAX;//int だからキャストでfloatにする
	pos.x = randomPos * FIELD_SIZE;
	randomPos = (float)rand() / RAND_MAX;//int だからキャストでfloatにする
	pos.z = randomPos * FIELD_SIZE;
	pos.y = 0.5;

	is_generated = false;

}

Item::~Item()
{
}

void Item::Move() {
	yaw += 0.95;

}

void Item::SetFlag() {


}

void Item::Draw() {
	float size = 1.0;//板ポリのサイズ
	TextureManager::GetInstance()->SpecifyTexture("bomb");
	glEnable(GL_TEXTURE_2D);
	glPushMatrix();
	{
		glTranslatef(pos.x, pos.y, pos.z);
		glRotatef(yaw, 0, 1, 0);
		glBegin(GL_QUADS);
		{
			glTexCoord2f(0.0f, 0.0f);
			glVertex3f(-size, size, 0);
			glTexCoord2f(1.0f, 0.0f);
			glVertex3f(size, size, 0);
			glTexCoord2f(1.0f, 1.0f);
			glVertex3f(size, -size, 0);
			glTexCoord2f(0.0f, 1.0f);
			glVertex3f(-size, -size, 0);
		}
		glEnd();
	}
	glPopMatrix();
	glDisable(GL_TEXTURE_2D);
}