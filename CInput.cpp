#include "CInput.h"
#include <Windows.h>  // ZeroMemory�֐��Ȃǂ��܂܂�Ă���
#include <WinError.h>  // ERROR_SUCCESS�Ȃǂ��܂܂�Ă���
#include <XInput.h>	
#include <memory.h>


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
