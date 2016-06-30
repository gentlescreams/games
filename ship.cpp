#define _USE_MATH_DEFINES

#include <math.h>
#include <list>
#include "ship.h"
#include "./library/util.h"
#include "bullet.h"
#include "camera.h"
#include "glut.h"
#include "model.h"
#include "./manager/texture_manager.h"
#include "./manager/sounds_manager.h"
#include <Xinput.h>

extern std::list<Bullet> bulletList;
extern int leftTime;
extern Camera camera;

Ship::Ship(glm::vec3& _pos, int _team, int _bodyColor ,int _playerID,const char* file_name){
	pos = _pos;
	speed = glm::vec3(0, 0, 0);
	team = _team;
	bodyColor = _bodyColor;
	playerID = _playerID;
	isDead = 0;
	yaw = 0;
	yawSpeed = 0;
	deceleration = 0.95;
	targetPoint = _pos;
	startPoint = _pos;
	scr_pos = glm::vec3(0, 0, 0);
	scale = 0.3;
	model = Model::Model(file_name);
}


void Ship::Draw(){
	//���@
	if (isDead == 0)
	{

		glPushMatrix();
		{
			//�ˉe�s��̏�����
			glMatrixMode(GL_PROJECTION);//GLenum mode
			glLoadIdentity();//������

			//���s���e
			glOrtho(
				0, 800,  // GLdouble left, right
				0, 680,  // GLdouble bottom, top,
				1, -1); // GLdouble zNear, zFar

			//�r���[�s�񏉊���
			glMatrixMode(GL_MODELVIEW);//GLenum mode	�J�����̐ݒ�
			glLoadIdentity();


			//�v���C���[�̖��O�\�L
			if (playerID == PLAYER_1){
				glDisable(GL_DEPTH_TEST);

				glPushMatrix();
				{
					glColor3f(1, 0, 0);
					glTranslatef(scr_pos.x, scr_pos.y-100, scr_pos.z);
					glScalef(scale ,scale, scale);
					drawStroke("P1");
				}glPopMatrix();
			}
	
			if (playerID == PLAYER_2)
			{
				glPushMatrix();
				{
					glColor3f(0, 0, 1);
					glTranslatef(scr_pos.x, scr_pos.y-100 , scr_pos.z);
					glScalef(scale, scale, scale);
					drawStroke("P2");
				}glPopMatrix();

				glEnable(GL_DEPTH_TEST);

			}


			glMatrixMode(GL_PROJECTION);//GLenum mode
			glLoadIdentity();
			gluPerspective(
				45,		//GLdouble fovy,�p�x
				(float)640 / (480 / 2),		//GLdouble aspect,��ʂ̕�
				0.1,	//Ldouble zNear,�J��������̋����@���̐��l���߂����͕̂`�悳��Ȃ�
				100);	// GLdouble zFar�J��������̋����@���̐��l��艓�����͕̂`�悳��Ȃ�

			glMatrixMode(GL_MODELVIEW);//GLenum mode	�J�����̐ݒ�
			glLoadIdentity();
			gluLookAt(
				pos.x - sin(yaw*M_PI / 180) * 8, 4, pos.z - cos(yaw*M_PI / 180) * 8,//GLdouble eyex, eyey, eyez,
				pos.x, pos.y + 1.3, pos.z,//GLdouble centerx, centery, centerz,
				0, 1, 0);//GLdouble upx, upy, upz

			
		}
		glPopMatrix();

		scale = 0.25;
		glPushMatrix(); 
		{//���@�̉e

			//�ړ�
			glTranslatef(pos.x, 0.15, pos.z);//GLfloat x, GLfloat y, GLfloat z
											//��]
			glRotatef(yaw+180, 0, 1, 0);//GLfloat angle, GLfloat x, GLfloat y, GLfloat z
			glScalef(scale, 0,scale);
			glColor3f(1.f / 255 * 144, 1.f / 255 * 144, 1.f / 255 * 144);

			model.modelCreate();

		}
		glPopMatrix();

		glPushMatrix(); {//���@

			//�ړ�
			glTranslatef(pos.x, pos.y+1, pos.z);//GLfloat x, GLfloat y, GLfloat z
			//��]
			glRotatef(yaw+180, 0, 1, 0);//GLfloat angle, GLfloat x, GLfloat y, GLfloat z
			//
			glScalef(scale,scale, scale);
											
			glEnable(GL_DEPTH_TEST);

			glColor3f(1, 1, 1);

			if (team == TEAM_PLAYER)
			{

				TextureManager::GetInstance()->SpecifyTexture("player");
			}
			else if (team == TEAM_ENEMY)
			{
				TextureManager::GetInstance()->SpecifyTexture("enemy");
			}

			model.Draw();
		}
		glPopMatrix();
	}
}

/*�W���C�X�e�B�b�N�ł̑��쏈��*/
void Ship::Control(float _x, float _y, unsigned int _downKeys,unsigned int _pressedKeys){
	//�����x�x�N�g��
	glm::vec3 acc(_y*sin(yaw*M_PI / 180), 0, _y*cos(yaw*M_PI / 180));

	float keep = 1.0f;
	if ((_y <keep) && (_y >-keep))//�����Ȑ��l���������Ƃ��̏���
	{
		acc = glm::vec3(0,0,0);
	}
	speed += acc / 80.0f;

	float YawAcc = _x / 20.0f;
	if ((_x <keep) && (_x >-keep))//�����Ȑ��l���������Ƃ��̏���
	{
		YawAcc = 0;

	}


	//��]�X�s�[�h
	yawSpeed -= YawAcc;

	if (_pressedKeys//_downKeys
		& XINPUT_GAMEPAD_A){//�ʏ�e
		if (leftTime % 10 == 0){
			//�R���X�g���N�^�ɓn������������n���āA���̒��ŃC���X�^���X������Ă��炤����
			bulletList.emplace_back(pos//pos[
				, glm::vec3(sin(yaw*M_PI / 180), 1, cos(yaw*M_PI / 180))* 0.2f+speed//speed
				, 0//isDead
				, team//team
				, bodyColor//bodyColor
				, yaw);//Yaw
		}
	}
}


/*�L�[�{�[�h�ł̈ړ�����*/
void Ship::KeysControl(unsigned char *keys,unsigned char *lastkeys){

	//�e
	if (keys[' ']== 1){
	//	sm.PlaySE(CRI_SE_SOUND_SE_BULLET);
		if (leftTime % 5 == 0)
		bulletList.emplace_back(pos, glm::vec3(sin(yaw*M_PI / 180), 1, cos(yaw*M_PI / 180))* 0.2f, 0,team,bodyColor, yaw);

	}

	if (keys['w']== 1)//���̈ړ�
	{
		float y1 = -1;
		glm::vec3 acc(y1*sin(yaw*M_PI / 180), 0, y1*cos(yaw*M_PI / 180));
		speed -= acc / 100.0f;
	}
	if (keys['s'] == 1)//���̈ړ�
	{
		float y1 = +1;
		glm::vec3 acc(y1*sin(yaw*M_PI / 180), 0, y1*cos(yaw*M_PI / 180));
		speed -= acc / 100.0f;

	}
	if (keys['a'] == 1)//���ړ�
	{
		float x = -1;
		float YawAcc = x / 20.0f;
		yawSpeed -= YawAcc;

	}
	if (keys['d'] == 1)//�E�ړ�
	{
		float x = 1;
		float YawAcc = x / 20.0f;
		yawSpeed -= YawAcc;
	}
}


/*NPC�̈ړ�����*/
void Ship::Control(){
	glm::vec3 v = targetPoint - pos;
	yaw = atan2f(v.x, v.z)* 180 /M_PI;

	glm::vec3 acc(sin(yaw*M_PI / 180), 0, cos(yaw*M_PI / 180));
	speed += acc / 120.0f;
	if (distance(pos,targetPoint)<1 )
	{
		float r, rx, rz;
		r = (float)rand() / RAND_MAX;//int ������L���X�g��float�ɂ���
		rx = r * FIELD_SIZE;
		r = (float)rand() / RAND_MAX;//int ������L���X�g��float�ɂ���
		rz = r * FIELD_SIZE;
		targetPoint = glm::vec3(rx, 0, rz);
	}
	if (leftTime % 5 ==0)
	{
		bulletList.emplace_back(pos, glm::vec3(sin(yaw*M_PI / 180), 0.5, cos(yaw*M_PI / 180))* 0.3f, 0, team,bodyColor, yaw);

	}
}


void Ship::Control(float x, float y){

	if ((y >0.3) || (y <-0.3))//�����Ȑ��l���������Ƃ��̏���
		yaw = camera.yaw - atan2f(x, y) * 180 / M_PI;

	if ((x >0.3) || (x <-0.3))//�����Ȑ��l���������Ƃ��̏���
		yaw = camera.yaw - atan2f(x, y) * 180 / M_PI;

//	printf("yaw : %d\n", yaw);
	float distance = sqrt(x * x + y * y);

	//�����x�x�N�g��
	glm::vec3 acc(distance*sin(yaw*M_PI / 180), 0, distance*cos(yaw*M_PI / 180));

	if ((distance <0.5) //&& (distance >-0.3)
		)//�����Ȑ��l���������Ƃ��̏���
	{
		acc = glm::vec3(0, 0, 0);
	}


	camera.yaw += camera.yawSpeed;
	camera.yawSpeed *= 0.8;
}


void Ship::playerArea(){

	///���@���t�B�[���h����łȂ��悤�ɂ���
	if (pos.x > FIELD_SIZE)
	{
		pos.x = FIELD_SIZE;
	}
	if (pos.x < 0) {
		pos.x = 0;
	}
	if (pos.z > FIELD_SIZE) {
		pos.z = FIELD_SIZE;
	}
	if (pos.z < 0){
		pos.z = 0;
	}
}