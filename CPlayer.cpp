#include "CPlayer.h"
#include "CInput.h"
#include "CScene.h"

//�����I�ɐe�N���X�̃R���X�g���N�^���Ăяo��
CPlayer::CPlayer(ID3D11Buffer* vb, ID3D11ShaderResourceView* tex, FLOAT_XY uv) : CGameObject(vb, tex, uv)
{
	// �����X�s�[�h�ݒ�
	SetMoveSpeed(0.05f);
}

void CPlayer::Input()
{
	if (gInput->IsControllerButtonPressed(XINPUT_GAMEPAD_DPAD_DOWN) || gInput->GetKeyPress(VK_DOWN) && prevFrameCorrect.y != 1)
	{
		// �����ɔ��΂̃L�[��������Ă��Ȃ���
		if (!gInput->IsControllerButtonPressed(XINPUT_GAMEPAD_DPAD_UP) && !gInput->GetKeyPress(VK_UP))
		{
			// ������Ă��Ȃ��Ȃ�������X�V����
			dir.y = -1.0f;
			prevFrameDir.y = dir.y;
		}
		else
		{
			// ������Ă��܂��Ă���Ȃ�O�̕��������̂܂ܓK��
			dir.y = prevFrameDir.y;
		}
	}
	else if ((gInput->IsControllerButtonPressed(XINPUT_GAMEPAD_DPAD_UP) || gInput->GetKeyPress(VK_UP)) && prevFrameCorrect.y != -1)
	{
		// �����ɔ��΂̃L�[��������Ă��Ȃ���
		if (!gInput->IsControllerButtonPressed(XINPUT_GAMEPAD_DPAD_DOWN) && !gInput->GetKeyPress(VK_DOWN))
		{
			// ������Ă��Ȃ��Ȃ�������X�V����
			dir.y = 1.0f;
			prevFrameDir.y = dir.y;
		}
		else
		{
			// ������Ă��܂��Ă���Ȃ�O�̕��������̂܂ܓK��
			dir.y = prevFrameDir.y;
		}
	}

	if ((gInput->IsControllerButtonPressed(XINPUT_GAMEPAD_DPAD_LEFT) || gInput->GetKeyPress(VK_LEFT)) && prevFrameCorrect.x != 1)
	{
		// �����ɔ��΂̃L�[��������Ă��Ȃ���
		if (!gInput->IsControllerButtonPressed(XINPUT_GAMEPAD_DPAD_RIGHT) && !gInput->GetKeyPress(VK_RIGHT))
		{
			// ������Ă��Ȃ��Ȃ�������X�V����
			dir.x = -1.0f;
			prevFrameDir.x = dir.x;
		}
		else
		{
			// ������Ă��܂��Ă���Ȃ�O�̕��������̂܂ܓK��
			dir.x = prevFrameDir.x;
		}
	}
	else if ((gInput->IsControllerButtonPressed(XINPUT_GAMEPAD_DPAD_RIGHT) || gInput->GetKeyPress(VK_RIGHT)) && prevFrameCorrect.x != -1)
	{
		// �����ɔ��΂̃L�[��������Ă��Ȃ���
		if (!gInput->IsControllerButtonPressed(XINPUT_GAMEPAD_DPAD_LEFT) && !gInput->GetKeyPress(VK_LEFT))
		{
			// ������Ă��Ȃ��Ȃ�������X�V����
			dir.x = 1.0f;
			prevFrameDir.x = dir.x;
		}
		else
		{
			// ������Ă��܂��Ă���Ȃ�O�̕��������̂܂ܓK��
			dir.x = prevFrameDir.x;
		}
	}

	// �X�e�B�b�N���͈ꎞ�ۑ��p
	float input_stickX, input_stickY;

	// �X�e�B�b�N�̓��͂�ۑ�
	input_stickX = gInput->GetRightStickX();
	input_stickY = gInput->GetRightStickY();

	// �O�̃t���[���ł߂荞�񂾕����łȂ��Ȃ�ړ��ʂ�K������
	if ((input_stickX > 0.0f && prevFrameCorrect.x != -1) ||
		(input_stickX < 0.0f && prevFrameCorrect.x != 1))
	{
		dir.x = input_stickX;
	}
	// �O�̃t���[���ł߂荞�񂾕����Ɉړ����悤�Ƃ��Ă�Ȃ�ړ��ʂ�K�����Ȃ�
	else
	{
		dir.x = 0;
	}
	// �O�̃t���[���ł߂荞�񂾕����łȂ��Ȃ������K��
	if ((input_stickY > 0.0f && prevFrameCorrect.y != -1) ||
		(input_stickY < 0.0f && prevFrameCorrect.y != 1))
	{
		dir.y = input_stickY;
	}
	else
	{
		dir.y = 0;
	}
}

void CPlayer::Update()
{
	// ������߂�
	dir.x = 0.0f;
	dir.y = 0.0f;

	Input();

	// �O�t���[���̕␳������������
	prevFrameCorrect = { 0 };

	// �P�ʃx�N�g����(�����P�ɂ���) = ���K��
	DirectX::XMVECTOR v = DirectX::XMLoadFloat3(&dir);	// �x�N�g���v�Z�p�̌^�ɓ����
	v = DirectX::XMVector3Normalize(v);					// ���K������
	DirectX::XMStoreFloat3(&dir, v);					// ���̕ϐ�dir�ɖ߂�

	// �x�N�g���ɑ��x�������Ĉʒu��ύX
	this->transform.position.x += dir.x * moveSpeed;
	this->transform.position.y += dir.y * moveSpeed;

	// �e�N���X��Update()�𖾎��I�ɌĂяo��
	// �S�ẴQ�[���I�u�W�F�N�g���ʂ̍X�V�������s��
	CGameObject::Update();

	// �n�`�Ƃ̓����蔻��ƕ␳
	for (auto it = CScene::map_object.begin(); it != CScene::map_object.end(); it++)
	{
		if (CCollision::TestBoxCollision(this->Bcol, (*it)->Bcol))
		{
			// �R���C�_�[�̈ʒu��␳���A�␳�����������󂯎��
			prevFrameCorrect = CCollision::CorrectPosition(this->Bcol, (*it)->Bcol);
			// �I�u�W�F�N�g�̈ʒu�ƃR���C�_�[�̒��S�����킹��
			this->transform.position.x = this->Bcol.centerX;
			this->transform.position.y = this->Bcol.centerY;
		}
	}
}

void CPlayer::Draw()
{
	// �e�N���X��Draw()�𖾎��I�ɌĂяo��
	// �S�ẴQ�[���I�u�W�F�N�g���ʂ̕`�揈�����s��
	CGameObject::Draw();
}


CPlayer::~CPlayer()
{
	// �e�N���X�̃R���X�g���N�^�𖾎��I�ɌĂяo��
	// ���_�o�b�t�@�̉�����s��
	CGameObject::~CGameObject();
}
