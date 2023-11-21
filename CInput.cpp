/* �C���N���[�h */
#include "CInput.h"
#include <WinError.h>	// ERROR_SUCCESS�Ȃǂ��܂܂�Ă���
#include <memory.h>		

CInput::CInput()
{
	ZeroMemory(&oldState, sizeof(XINPUT_STATE));
}

bool CInput::IsControllerButtonPressed(WORD button)
{
	XINPUT_STATE state;
	ZeroMemory(&state, sizeof(XINPUT_STATE));

	if (XInputGetState(0, &state) == ERROR_SUCCESS)
	{
		return (state.Gamepad.wButtons & button) != 0;
	}

	return false;
}

bool CInput::IsControllerButtonTrigger(WORD button)
{
	XINPUT_STATE state;
	ZeroMemory(&state, sizeof(XINPUT_STATE));

	if (XInputGetState(0, &state) == ERROR_SUCCESS)
	{
		bool wasPressed = oldState.Gamepad.wButtons & button;
		bool isPressed = state.Gamepad.wButtons & button;

		// �O��͉�����Ă��炸�A����͉����ꂽ�ꍇ�� true ��Ԃ�
		bool isTriggered = !wasPressed && isPressed;

		// �X�V�����ō��̏�Ԃ�ۑ�
		oldState = state;

		return isTriggered;
	}

	return false;
}

bool CInput::IsControllerButtonRepeat(WORD button)
{
	//�����Ă�J�E���g���v��
	Presstime++;
	//�ŏ��Ƀg���K�[�������s��
	if (IsControllerButtonTrigger(button))
	{
		Presstime = 0;//Presstime�̏�����
		return true;
	}
	else if (Presstime > 100)//100�J�E���g��������
	{
		//Press�����Ɉڍs����
		IsControllerButtonPressed(button);
	}
	else
	{
		return false;
	}
}

void CInput::SetKeyDownState(int key)
{
	keyState[key] = true;
}

void CInput::SetKeyUpState(int key)
{
	keyState[key] = false;
}

bool CInput::GetKeyPress(int key)
{
	return keyState[key];
}

bool CInput::GetKeyTrigger(int key)
{
	//�P�t���[���O�̏�Ԃ�false�ł����݂̃t���[���̉�����Ԃ�true
	//�������� return �� bool�^ �ŕԂ����
	return !oldKeyState[key] && keyState[key];
}

void CInput::Update()
{
	memcpy_s(oldKeyState, sizeof(oldKeyState), keyState, sizeof(keyState));
}
