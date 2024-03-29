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

void CInput::InputLock(bool lock)
{
	inputLock = lock;
}

bool CInput::IsControllerButtonPressed(WORD button)
{
	// 入力を受け付けないなら処理せずに返す
	if (inputLock)
	{
		return false;
	}

	if (XInputGetState(0, &state) == ERROR_SUCCESS)
	{
		return (state.Gamepad.wButtons & button) != 0;
	}

	return false;
}

bool CInput::IsControllerButtonTrigger(WORD button)
{
	// 入力を受け付けないなら処理せずに返す
	if (inputLock)
	{
		return false;
	}

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
	// 入力を受け付けないなら処理せずに返す
	if (inputLock)
	{
		return false;
	}

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
		//押され続けていないならfalseを返す
		if (!IsControllerButtonPressed(button))
		{
			return false;
		}
		else
		{
			return true;
		}
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
	// 入力を受け付けないなら処理せずに返す
	if (inputLock)
	{
		return false;
	}

	return keyState[key];
}

bool CInput::GetKeyTrigger(int key)
{
	// 入力を受け付けないなら処理せずに返す
	if (inputLock)
	{
		return false;
	}

	//１フレーム前の状態がfalseでかつ現在のフレームの押下状態がtrue
	//条件式の return は bool型 で返される
	return !oldKeyState[key] && keyState[key];
}

void CInput::Update()
{
	memcpy_s(oldKeyState, sizeof(oldKeyState), keyState, sizeof(keyState));

	// 更新処理で今の状態を保存
	oldState = state;

	// 振動がONになっているなら更新
	if (vibrationFlg)
	{
		NowVibrationFlame++;
		// バイブレーションを設定されたフレーム数だけ行ったならバイブレーションを止める
		if (NowVibrationFlame > vibrationFlame)
		{
			// 振動パラメータを0に設定
			vibrationPalam.wLeftMotorSpeed = 0;	// 左側のモーターの速度 (0から65535まで)
			vibrationPalam.wRightMotorSpeed = 0;// 右側のモーターの速度 (0から65535まで)
			// 振動を停止
			XInputSetState(0, &vibrationPalam);
			// フラグを下げる
			vibrationFlg = false;
		}
	}
}

float CInput::GetLeftStickX()
{
	// 入力を受け付けないなら処理せずに返す
	if (inputLock)
	{
		return 0.0f;
	}

	if (XInputGetState(0, &state) == ERROR_SUCCESS)
	{
		// スティックのX軸の値を取得
		return state.Gamepad.sThumbLX / static_cast<float>(32767);
	}

	return 0.0f; // エラー時は0を返す
}

float CInput::GetLeftStickY()
{
	// 入力を受け付けないなら処理せずに返す
	if (inputLock)
	{
		return 0.0f;
	}

	if (XInputGetState(0, &state) == ERROR_SUCCESS)
	{
		// スティックのY軸の値を取得
		return state.Gamepad.sThumbLY / static_cast<float>(32767);
	}

	return 0.0f; // エラー時は0を返す
}

float CInput::GetRightStickX()
{
	// 入力を受け付けないなら処理せずに返す
	if (inputLock)
	{
		return 0.0f;
	}

	if (XInputGetState(0, &state) == ERROR_SUCCESS)
	{
		// 右スティックのX軸の値を取得
		return state.Gamepad.sThumbRX / static_cast<float>(32767);
	}

	return 0.0f; // エラー時は0を返す
}

float CInput::GetRightStickY()
{
	// 入力を受け付けないなら処理せずに返す
	if (inputLock)
	{
		return 0.0f;
	}

	if (XInputGetState(0, &state) == ERROR_SUCCESS)
	{
		// 右スティックのY軸の値を取得
		return state.Gamepad.sThumbRY / static_cast<float>(32767);
	}

	return 0.0f; // エラー時は0を返す
}


float CInput::GetLeftStickXWithDeadzone()
{
	// 入力を受け付けないなら処理せずに返す
	if (inputLock)
	{
		return 0.0f;
	}

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
	// 入力を受け付けないなら処理せずに返す
	if (inputLock)
	{
		return 0.0f;
	}

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
	// 入力を受け付けないなら処理せずに返す
	if (inputLock)
	{
		return 0.0f;
	}

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
	// 入力を受け付けないなら処理せずに返す
	if (inputLock)
	{
		return 0.0f;
	}

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

void CInput::ControllerVibration(int vibration, int vibStrength)
{
	ZeroMemory(&vibrationPalam, sizeof(XINPUT_VIBRATION));

	// 値を0~65535でクランプ
	vibStrength = vibStrength < 0 ? 0 : vibStrength;
	vibStrength = vibStrength > 65535 ? 65535 : vibStrength;

	// 振動パラメータを設定
	vibrationPalam.wLeftMotorSpeed = vibStrength;	// 左側のモーターの速度 (0から65535まで)
	vibrationPalam.wRightMotorSpeed = vibStrength;	// 右側のモーターの速度 (0から65535まで)

	// 振動させる時間を設定
	vibrationFlame = vibration;
	// 振動のパラメータを渡す
	XInputSetState(0, &vibrationPalam);
	// 現在のフレームを0に初期化
	NowVibrationFlame = 0;
	// 振動フラグを上げる
	vibrationFlg = true;
}
