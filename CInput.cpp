/* インクルード */
#include "CInput.h"
#include <WinError.h>	// ERROR_SUCCESSなどが含まれている
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

		// 前回は押されておらず、今回は押された場合に true を返す
		bool isTriggered = !wasPressed && isPressed;

		// 更新処理で今の状態を保存
		oldState = state;

		return isTriggered;
	}

	return false;
}

bool CInput::IsControllerButtonRepeat(WORD button)
{
	//押してるカウントを計る
	Presstime++;
	//最初にトリガー処理を行う
	if (IsControllerButtonTrigger(button))
	{
		Presstime = 0;//Presstimeの初期化
		return true;
	}
	else if (Presstime > 100)//100カウント押したら
	{
		//Press処理に移行する
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
	//１フレーム前の状態がfalseでかつ現在のフレームの押下状態がtrue
	//条件式の return は bool型 で返される
	return !oldKeyState[key] && keyState[key];
}

void CInput::Update()
{
	memcpy_s(oldKeyState, sizeof(oldKeyState), keyState, sizeof(keyState));
}
