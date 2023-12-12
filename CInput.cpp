/* インクルード */
#include "CInput.h"
#include <WinError.h>	// ERROR_SUCCESSなどが含まれている
#include <memory.h>		
#include <cmath>

CInput::CInput()
{
	ZeroMemory(&state, sizeof(XINPUT_STATE));
	ZeroMemory(&oldState, sizeof(XINPUT_STATE));
}

bool CInput::IsControllerButtonPressed(WORD button)
{
	if (XInputGetState(0, &state) == ERROR_SUCCESS)
	{
		return (state.Gamepad.wButtons & button) != 0;
	}

	return false;
}

bool CInput::IsControllerButtonTrigger(WORD button)
{
	if (XInputGetState(0, &state) == ERROR_SUCCESS)
	{
		bool wasPressed = oldState.Gamepad.wButtons & button;
		bool isPressed = state.Gamepad.wButtons & button;

		// 前回は押されておらず、今回は押された場合に true を返す
		bool isTriggered = !wasPressed && isPressed;

		return isTriggered;
	}

	return false;
}

bool CInput::IsControllerButtonRepeat(WORD button, int cCount, int cTime)
{
	//押してるカウントを計る
	Presstime++;
	//最初にトリガー処理を行う
	if (IsControllerButtonTrigger(button))
	{
		Presstime = 0;//Presstimeの初期化
		return true;
	}
	else if (Presstime > cCount && Presstime % cTime == 0)//100カウント押したら
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

	// 更新処理で今の状態を保存
	oldState = state;
}

float CInput::GetLeftStickX()
{
	if (XInputGetState(0, &state) == ERROR_SUCCESS)
	{
		// スティックのX軸の値を取得
		return state.Gamepad.sThumbLX / static_cast<float>(32767);
	}

	return 0.0f; // エラー時は0を返す
}

float CInput::GetLeftStickY()
{
	if (XInputGetState(0, &state) == ERROR_SUCCESS)
	{
		// スティックのY軸の値を取得
		return state.Gamepad.sThumbLY / static_cast<float>(32767);
	}

	return 0.0f; // エラー時は0を返す
}

float CInput::GetRightStickX()
{
	if (XInputGetState(0, &state) == ERROR_SUCCESS)
	{
		// 右スティックのX軸の値を取得
		return state.Gamepad.sThumbRX / static_cast<float>(32767);
	}

	return 0.0f; // エラー時は0を返す
}

float CInput::GetRightStickY()
{
	if (XInputGetState(0, &state) == ERROR_SUCCESS)
	{
		// 右スティックのY軸の値を取得
		return state.Gamepad.sThumbRY / static_cast<float>(32767);
	}

	return 0.0f; // エラー時は0を返す
}


float CInput::GetLeftStickXWithDeadzone()
{
	float value = GetLeftStickX();
	//	デッドゾーンの範囲より大きければ、その値を返す。小さければ0を返す。
	if (std::fabs(value) > DEADZONE_THRESHOLD)
	{
		return value;
	}
	else
	{
		return 0.0f;
	}
}

float CInput::GetLeftStickYWithDeadzone()
{
	float value = GetLeftStickY();
	//	デッドゾーンの範囲より大きければ、その値を返す。小さければ0を返す。
	if (std::fabs(value) > DEADZONE_THRESHOLD)
	{
		return value;
	}
	else
	{
		return 0.0f;
	}
}

float CInput::GetRightStickXWithDeadzone()
{
	float value = GetRightStickX();
	//	デッドゾーンの範囲より大きければ、その値を返す。小さければ0を返す。
	if (std::fabs(value) > DEADZONE_THRESHOLD)
	{
		return value;
	}
	else
	{
		return 0.0f;
	}
}

float CInput::GetRightStickYWithDeadzone()
{
	float value = GetRightStickY();
	//	デッドゾーンの範囲より大きければ、その値を返す。小さければ0を返す。
	if (std::fabs(value) > DEADZONE_THRESHOLD)
	{
		return value;
	}
	else 
	{
		return 0.0f;
	}
}
