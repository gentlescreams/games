

#include <stdio.h>
#include <windows.h>
#include <vector>
#include <XInput.h>

#include "pad_controller.h"
#include "../glut.h"

//CONTROLER_STATE GAME_PAD[MAX_CONTROLLERS];
PadController gamePad[MAX_CONTROLLERS];
std::vector<PadController*> pad;
//�ڑ������邩���ׂ�
HRESULT PadController::UpdateControllerState()
{
	DWORD dwResult;
	for (DWORD i = 0; i < MAX_CONTROLLERS; i++)
	{
		//�p�b�h�̏�Ԃ��擾
		dwResult = XInputGetState(i, &gamePad[i].state);
		//�ڑ�����Ă���ꍇtrue
		if (dwResult == ERROR_SUCCESS)
			gamePad[i].isConnected = true;
		else
			gamePad[i].isConnected = false;
	}

	return S_OK;
}


void PadController::Update()
{
	//�ڑ��m�F
	UpdateControllerState();

	if (isConnected) {
		WORD Buttons = state.Gamepad.wButtons;

		pressedKeys = Buttons;//��������Ă���L�[
		releasedKeys = ~pressedKeys;//��������Ă���L�[�̕␔
		changedKeys = lastKeys ^ pressedKeys;//�ω��̂������L�[
		downKeys = changedKeys & pressedKeys;//�������ꂽ�L�[
		upKeys = changedKeys & releasedKeys;//���͂Ȃ��ꂽ�L�[

		if (Buttons & XINPUT_GAMEPAD_A) {
		}

		//�A�i���O�����L�[
		x = state.Gamepad.sThumbLX / 10000.0f;
		y = state.Gamepad.sThumbLY / 10000.0f;


		lastKeys = pressedKeys;//�P�t���[���O�̃L�[

	}
	else
	{
		//�ڑ�����Ă��Ȃ��ꍇ
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
