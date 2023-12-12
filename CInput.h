#pragma once

//�L�[���͂𔻒肷��N���X
//�d�g�݁FWndProc�֐��ŃL�[�������ꂽ/�����ꂽ�C�x���g���ɂ�����L�^���Ă����B
//        �L�[�̏�Ԃ𔻒肷��֐����Ă΂ꂽ��A���̏�Ԃ�Ԃ��B

/* �C���N���[�h */
#include <Windows.h>	// WORD�^���܂܂�Ă���w�b�_�[�t�@�C��
#include <XInput.h>		// �R���g���[���[�̓��͊֘A�̃w�b�_�[�t�@�C��

//XInput���C�u�����̃����N�ݒ�
#pragma comment (lib,"XInput.lib")

class CInput
{
	//�����o�ϐ�
	int Presstime = 0;
	XINPUT_STATE oldState;  // �V�����ǉ�
	//�L�[��Ԃ̋L�^�̈�
	bool keyState[256] = { false };
	//�P�t���[���O�̃L�[���͏�Ԃ̋L���̈�
	bool oldKeyState[256] = { false };

	//	�f�b�h�]�[����臒l
	const float DEADZONE_THRESHOLD = 0.2f;

public:
	//�����o�֐�
	CInput();  // �R���X�g���N�^��ǉ�

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
	// Xbox�R���g���[���[�̃{�^���̏�Ԃ��擾���郁�\�b�h
	bool IsControllerButtonTrigger(WORD button);
	// Xbox�R���g���[���[�̃{�^���̏�Ԃ��擾���郁�\�b�h
	bool IsControllerButtonRepeat(WORD button, int cCount, int cTime);

	// �R���g���[���[�̍��X�e�B�b�N��X���̒l���擾
	float GetLeftStickX();
	// �R���g���[���[�̍��X�e�B�b�N��Y���̒l���擾
	float GetLeftStickY();
	// �R���g���[���[�̉E�X�e�B�b�N��X���̒l���擾
	float GetRightStickX();
	// �R���g���[���[�̉E�X�e�B�b�N��Y���̒l���擾
	float GetRightStickY();

	//	�R���g���[���[�̍��X�e�B�b�N��X���̒l���擾����i�f�b�h�]�[���l���j
	float GetLeftStickXWithDeadzone();
	//	�R���g���[���[�̍��X�e�B�b�N��Y���̒l���擾����i�f�b�h�]�[���l���j
	float GetLeftStickYWithDeadzone();
	//	�R���g���[���[�̉E�X�e�B�b�N��X���̒l���擾����i�f�b�h�]�[���l���j
	float GetRightStickXWithDeadzone();
	//	�R���g���[���[�̉E�X�e�B�b�N��Y���̒l���擾����i�f�b�h�]�[���l���j
	float GetRightStickYWithDeadzone();
};

//�B��̎��̕ϐ���extern�錾
extern CInput* gInput;

