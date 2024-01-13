/* �C���N���[�h */
#include "CInput.h"
#include <WinError.h>	// ERROR_SUCCESS�Ȃǂ��܂܂�Ă���
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

		// �O��͉�����Ă��炸�A����͉����ꂽ�ꍇ�� true ��Ԃ�
		bool isTriggered = !wasPressed && isPressed;

		return isTriggered;
	}

	return false;
}

bool CInput::IsControllerButtonRepeat(WORD button, int cCount, int cTime)
{
	//�����Ă�J�E���g���v��
	Presstime++;
	//�ŏ��Ƀg���K�[�������s��
	if (IsControllerButtonTrigger(button))
	{
		Presstime = 0;//Presstime�̏�����
		return true;
	}
	else if (Presstime > cCount && Presstime % cTime == 0)//100�J�E���g��������
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

	// �X�V�����ō��̏�Ԃ�ۑ�
	oldState = state;
}

float CInput::GetLeftStickX()
{
	if (XInputGetState(0, &state) == ERROR_SUCCESS)
	{
		// �X�e�B�b�N��X���̒l���擾
		return state.Gamepad.sThumbLX / static_cast<float>(32767);
	}

	return 0.0f; // �G���[����0��Ԃ�
}

float CInput::GetLeftStickY()
{
	if (XInputGetState(0, &state) == ERROR_SUCCESS)
	{
		// �X�e�B�b�N��Y���̒l���擾
		return state.Gamepad.sThumbLY / static_cast<float>(32767);
	}

	return 0.0f; // �G���[����0��Ԃ�
}

float CInput::GetRightStickX()
{
	if (XInputGetState(0, &state) == ERROR_SUCCESS)
	{
		// �E�X�e�B�b�N��X���̒l���擾
		return state.Gamepad.sThumbRX / static_cast<float>(32767);
	}

	return 0.0f; // �G���[����0��Ԃ�
}

float CInput::GetRightStickY()
{
	if (XInputGetState(0, &state) == ERROR_SUCCESS)
	{
		// �E�X�e�B�b�N��Y���̒l���擾
		return state.Gamepad.sThumbRY / static_cast<float>(32767);
	}

	return 0.0f; // �G���[����0��Ԃ�
}


float CInput::GetLeftStickXWithDeadzone()
{
	float value = GetLeftStickX();
	//	�f�b�h�]�[���͈̔͂��傫����΁A���̒l��Ԃ��B���������0��Ԃ��B
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
	//	�f�b�h�]�[���͈̔͂��傫����΁A���̒l��Ԃ��B���������0��Ԃ��B
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
	//	�f�b�h�]�[���͈̔͂��傫����΁A���̒l��Ԃ��B���������0��Ԃ��B
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
	//	�f�b�h�]�[���͈̔͂��傫����΁A���̒l��Ԃ��B���������0��Ԃ��B
	if (std::fabs(value) > DEADZONE_THRESHOLD)
	{
		return value;
	}
	else 
	{
		return 0.0f;
	}
}
