#ifndef _PAD_CONTROLLES_
#define _PAD_CONTROLLES_
//#pragma comment(linker, "/SUBSYSTEM:WINDOWS /ENTRY:mainCRTStartup")
#pragma comment(lib,"xinput.lib ")

#include <XInput.h>

#define MAX_CONTROLLERS  4  //XInputが認識できるのは4つまで
#define Threshold   65535/4 //しきい値


class  PadController
{
public:
	 PadController();
	~ PadController();
	float x, y;
	void Update();
	unsigned int pressedKeys;//今押されてるキー
	unsigned int releasedKeys;//今押されてないキー
	unsigned int lastKeys;//１フレーム前のキー
	unsigned int changedKeys;//変化のあったキー
	unsigned int upKeys;//今離されたキー
	unsigned int downKeys;//今押されたキー

private:
	//接続があるか調べる
	HRESULT UpdateControllerState();
	XINPUT_STATE state;
	bool isConnected;//接続の有無
};




#endif // !_PAD_CONTROLLES_
