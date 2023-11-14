#include "CInput.h"
#include <Windows.h>  // ZeroMemory関数などが含まれている
#include <WinError.h>  // ERROR_SUCCESSなどが含まれている
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
	//１フレーム前の状態がfalseでかつ現在のフレームの押下状態がtrue
	//条件式の return は bool型 で返される
	return !oldKeyState[key] && keyState[key];
}

void CInput::Update()
{
	memcpy_s(oldKeyState, sizeof(oldKeyState), keyState, sizeof(keyState));
}
