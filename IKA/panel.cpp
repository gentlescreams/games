#include"panel.h"
#include<stdio.h>
#include"util.h"
#include"glut.h"

//
//フィールドのパネルの作成、描画関数
//


Panel panels[FIELD_SIZE][FIELD_SIZE];

void Panel::setPanel(){

	for (int z = 0; z < FIELD_SIZE; z++)
	for (int x = 0; x < FIELD_SIZE; x++)
	panels[z][x].pos = glm::vec3(x, 0, z);
}

void Panel::draw(){
	glPushMatrix();
	{
		glTranslatef(pos.x, 0, pos.z);

		setColor(team);
		glBegin(GL_QUADS);
		{
			glVertex3f(0, 0, 0);
			glVertex3f(0, 0, 1);
			glVertex3f(1, 0, 1);
			glVertex3f(1, 0, 0);

		}
		glEnd();
	}
	glPopMatrix();

}
