#ifndef _PAD_CONTROLLES_
#define _PAD_CONTROLLES_
//#pragma comment(linker, "/SUBSYSTEM:WINDOWS /ENTRY:mainCRTStartup")
#pragma comment(lib,"xinput.lib ")

#include <XInput.h>

#define MAX_CONTROLLERS  4  //XInput���F���ł���̂�4�܂�
#define Threshold   65535/4 //�������l


class  PadController
{
public:
	 PadController();
	~ PadController();
	float x, y;
	void Update();
	unsigned int pressedKeys;//��������Ă�L�[
	unsigned int releasedKeys;//��������ĂȂ��L�[
	unsigned int lastKeys;//�P�t���[���O�̃L�[
	unsigned int changedKeys;//�ω��̂������L�[
	unsigned int upKeys;//�������ꂽ�L�[
	unsigned int downKeys;//�������ꂽ�L�[

private:
	//�ڑ������邩���ׂ�
	HRESULT UpdateControllerState();
	XINPUT_STATE state;
	bool isConnected;//�ڑ��̗L��
};




#endif // !_PAD_CONTROLLES_
