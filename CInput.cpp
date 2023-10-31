#include "CInput.h"
#include <memory.h>

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
