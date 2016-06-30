

#include <stdio.h>
#include <windows.h>
#include <vector>
#include <XInput.h>

#include "pad_controller.h"
#include "../glut.h"

//CONTROLER_STATE GAME_PAD[MAX_CONTROLLERS];
PadController gamePad[MAX_CONTROLLERS];
std::vector<PadController*> pad;
//接続があるか調べる
HRESULT PadController::UpdateControllerState()
{
	DWORD dwResult;
	for (DWORD i = 0; i < MAX_CONTROLLERS; i++)
	{
		//パッドの状態を取得
		dwResult = XInputGetState(i, &gamePad[i].state);
		//接続されている場合true
		if (dwResult == ERROR_SUCCESS)
			gamePad[i].isConnected = true;
		else
			gamePad[i].isConnected = false;
	}

	return S_OK;
}


void PadController::Update()
{
	//接続確認
	UpdateControllerState();

	if (isConnected) {
		WORD Buttons = state.Gamepad.wButtons;

		pressedKeys = Buttons;//今押されているキー
		releasedKeys = ~pressedKeys;//今押されているキーの補数
		changedKeys = lastKeys ^ pressedKeys;//変化のあったキー
		downKeys = changedKeys & pressedKeys;//今押されたキー
		upKeys = changedKeys & releasedKeys;//今はなされたキー

		if (Buttons & XINPUT_GAMEPAD_A) {
		}

		//アナログ方向キー
		x = state.Gamepad.sThumbLX / 10000.0f;
		y = state.Gamepad.sThumbLY / 10000.0f;


		lastKeys = pressedKeys;//１フレーム前のキー

	}
	else
	{
		//接続されていない場合
	}

	glutPostRedisplay();
}


PadController::PadController()
{
	x = 0;
	y = 0;
}

PadController::~PadController()
{
}
