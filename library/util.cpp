#define _CRT_SECURE_NO_WARNINGS


#include<assert.h>
#include<Windows.h>
#include<stdio.h>
#include"util.h"
#include<math.h>
#include"../glm/glm.hpp"
#include "../glut.h"
#include "../manager\texture_manager.h"

char parcalc(int panel_counter) {
	float p = (float)panel_counter / (float)(FIELD_SIZE*FIELD_SIZE) * 100.0f;
	int pp = p;
	char score[256];
	sprintf(score, "%d %%", pp);

	return *score;
}


//�����蔻��
float distance(glm::vec3 &_vec0, glm::vec3 &_vec1){
	//�e�ƓG�̍��̃x�N�g���i�����Ƌ����𒲂ׂ��j
	glm::vec3 v = _vec0 - _vec1;

	return sqrt(v.x * v.x + v.y * v.y + v.z * v.z);

}

void scrDraw(const char* name){
	float size = 1.0;
	glColor3f(1, 1, 1);

	TextureManager::GetInstance()->SpecifyTexture(name);
	glEnable(GL_TEXTURE_2D);
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
	glDisable(GL_TEXTURE_2D);
}


//�F�̕ω�
void setColor(const int _colorType){
	switch (_colorType)
	{
	case TEAM_PLAYER://����
		glColor3f(1.f, 1.f / 255 * 173, 1.f / 255 * 119);
		break;
	case TEAM_PLAYER_SHIP:
		glColor3f(1.f, 1.f / 255 * 127, 1.f / 255 * 39);
		break;
	case TEAM_ENEMY://�G
		glColor3f(1.f/255* 114, 1.f / 255 * 121, 1.f / 255 * 218);
		break;
	case TEAM_ENEMY_SHIP:
		glColor3f(1.f/255* 63, 1.f / 255 * 72, 1.f / 255 * 204);
		break;
	case TEAM_OTHER://����
		glColor3f(1.f, 1.f, 1.f);
		break;
	}
}


void drawStroke(const char* _str){//��������X�g���[�N�����ŕ\��

	for (int i = 0; _str[i] != 0; i++)
	{
		glutStrokeCharacter(
			GLUT_STROKE_ROMAN,	//void *font, �t�H���g�w��
			_str[i]);				//int character�@�����̎w��
	}
}

void drawBits(unsigned int _bits){//�n���ꂽ�l���i���ŕ\������
	unsigned int flag = 1 << 31;

	for (int i = 0; i < 32; i++)
	{
		if ((flag >> i)& _bits){
			glutBitmapCharacter(
				GLUT_BITMAP_9_BY_15,// void *font
				'1');               // int character	
		}
		else
		{
			glutBitmapCharacter(
				GLUT_BITMAP_9_BY_15,// void *font
				'0');               // int character	 
		}
		if ((i % 4 == 3) & (31 != i))
		{
			glutBitmapCharacter(
				GLUT_BITMAP_9_BY_15,// void *font
				',');               // int character	 }
		}
	}
}
