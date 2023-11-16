#pragma once

//�L�[���͂𔻒肷��N���X
//�d�g�݁FWndProc�֐��ŃL�[�������ꂽ/�����ꂽ�C�x���g���ɂ�����L�^���Ă����B
//        �L�[�̏�Ԃ𔻒肷��֐����Ă΂ꂽ��A���̏�Ԃ�Ԃ��B
#include <Windows.h>  // WORD�^���܂܂�Ă���w�b�_�[�t�@�C��
class CInput
{
	//�����o�ϐ�
	

	//�L�[��Ԃ̋L�^�̈�
	bool keyState[256] = { false };
	//�P�t���[���O�̃L�[���͏�Ԃ̋L���̈�
	bool oldKeyState[256] = { false };

public:
	//�����o�֐�

	//�L�[�������ꂽ�̂��L�^����֐�
	void SetKeyDownState(int key);

	//�L�[�������ꂽ�̂��L�^����֐�
	void SetKeyUpState(int key);

	//�L�[�v���X���������Ă��邩�Ԃ��֐�
	bool GetKeyPress(int key);

	//�L�[�g���K�[���������Ă��邩�Ԃ��֐�
	bool GetKeyTrigger(int key);

	//�Q�[�����[�v�̍Ō�ŃL�[��Ԃ�oldKeyState���X�V����֐�
	void Update();

	// Xbox�R���g���[���[�̃{�^���̏�Ԃ��擾���郁�\�b�h
	bool IsControllerButtonPressed(WORD button);
};

//�B��̎��̕ϐ���extern�錾
extern CInput* gInput;

