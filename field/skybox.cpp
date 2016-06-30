#include "skybox.h"
#include "../glut.h"
#include "../manager/texture_manager.h"


SkyBox::SkyBox()
{
}


void SkyBox::Draw() {//フィールド周りの壁
	TextureManager::GetInstance()->SpecifyTexture("field");

	glEnable(GL_TEXTURE_2D);
	glColor3f(1.0f, 1.0f, 1.0f);
	glBegin(GL_QUADS);
	{
		glTexCoord2f(1.0f, 0.0f);
		glVertex3f(-50, -1, 150);
		glTexCoord2f(1.0f, 1.0f);
		glVertex3f(-50, -1, -50);
		glTexCoord2f(0.0f, 1.0f);
		glVertex3f(150, -1, -50);
		glTexCoord2f(0.0f, 0.0f);
		glVertex3f(150, -1, 150);
	}//床の周り
	glEnd();
	glBegin(GL_QUADS);
	{
		glTexCoord2d(1, 0);
		glVertex3f(150, 50, -50);
		glTexCoord2d(1, 1);
		glVertex3f(150, -1, -50);
		glTexCoord2d(0, 1);
		glVertex3f(-50, -1, -50);
		glTexCoord2d(0, 0);
		glVertex3f(-50, 50, -50);
	}//裏
	glEnd();
	glBegin(GL_QUADS);
	{
		glTexCoord2d(1, 0);
		glVertex3f(-50, 50, 150);
		glTexCoord2d(1, 1);
		glVertex3f(-50, -1, 150);
		glTexCoord2d(0, 1);
		glVertex3f(150, -1, 150);
		glTexCoord2d(0, 0);
		glVertex3f(150, 50, 150);
	}//前
	glEnd();
	glBegin(GL_QUADS);
	{
		glTexCoord2d(1, 0);
		glVertex3f(150, 50, 150);
		glTexCoord2d(1, 1);
		glVertex3f(150, -1, 150);
		glTexCoord2d(0, 1);
		glVertex3f(150, -1, -50);
		glTexCoord2d(0, 0);
		glVertex3f(150, 50, -50);
	}
	glEnd();
	glBegin(GL_QUADS);
	{
		glTexCoord2d(1, 0);
		glVertex3f(-50, 50, -50);
		glTexCoord2d(1, 1);
		glVertex3f(-50, -1, -50);
		glTexCoord2d(0, 1);
		glVertex3f(-50, -1, 150);
		glTexCoord2d(0, 0);
		glVertex3f(-50, 50, 150);
	}//横
	glEnd();
	glDisable(GL_TEXTURE_2D);
	//////周りの囲い
}

SkyBox::~SkyBox()
{
}

