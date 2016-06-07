#include"bullet.h"
#include"panel.h"
#include"util.h"
#include"glut.h"


Bullet::Bullet(const glm::vec3& _pos, const glm::vec3& _speed, int _isDead,int _team,int _bodyColor, float _Yaw){
	pos = _pos;
	speed = _speed;
	isDead = _isDead;
	team = _team;	
	bodyColor = _bodyColor;
	yaw = _Yaw;
	deceleration = 1.0;
}
Bullet::Bullet(){ }
void Bullet::Draw(){

	glPushMatrix();//íe
	{
		setColor(bodyColor);
		glTranslatef(pos.x, pos.y, pos.z);
		glRotatef(yaw, 0, 1, 0);
		glutSolidSphere(
			0.2,//îºåa
			10,//ê¸
			10);//ì_
	}
	glPopMatrix();

	glPushMatrix();//íe
	{
		glColor3f(0, 0, 0);
		glTranslatef(pos.x, 0.1, pos.z);
		glRotatef(yaw, 0, 1, 0);
		glScalef(1, 0, 1);
		glutSolidSphere(
			0.2,//îºåa
			10,//ê¸
			10);//ì_
	}
	glPopMatrix();



}

