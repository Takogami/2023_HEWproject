#include "CPlayer.h"
#include "CScene.h"

// �R���g���[���[���g���ꍇ��true���w��
#define USE_CONTROLLER (true)

//�����I�ɐe�N���X�̃R���X�g���N�^���Ăяo��
CPlayer::CPlayer(ID3D11Buffer* vb, ID3D11ShaderResourceView* tex, FLOAT_XY uv) : CGameObject(vb, tex, uv)
{
	// �����X�s�[�h�ݒ�
	SetMoveSpeed(0.05f);
	// �d�͂������l�Ƃ���
	velocity.y = gravity;
}

void CPlayer::PlayerInput()
{
#if USE_CONTROLLER == true

	// �X�e�B�b�N���͈ꎞ�ۑ��p
	float input_stickX;

	// �X�e�B�b�N�̓��͂�ۑ�
	input_stickX = gInput->GetLeftStickX();

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
	// B�{�^�����͂łƂ肠�����̃W�����v����
	if (gInput->IsControllerButtonTrigger(XINPUT_GAMEPAD_A))
	{
		isJump = true;
	}

#else

	if (gInput->GetKeyPress(VK_DOWN) && prevFrameCorrect.y != 1)
	{
		// �����ɔ��΂̃L�[��������Ă��Ȃ���
		if (!gInput->GetKeyPress(VK_UP))
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
	else if (gInput->GetKeyPress(VK_UP) && prevFrameCorrect.y != -1)
	{
		// �����ɔ��΂̃L�[��������Ă��Ȃ���
		if (!gInput->GetKeyPress(VK_DOWN))
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

	if (gInput->GetKeyPress(VK_LEFT) && prevFrameCorrect.x != 1)
	{
		// �����ɔ��΂̃L�[��������Ă��Ȃ���
		if (!gInput->GetKeyPress(VK_RIGHT))
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
	else if (gInput->GetKeyPress(VK_RIGHT) && prevFrameCorrect.x != -1)
	{
		// �����ɔ��΂̃L�[��������Ă��Ȃ���
		if (!gInput->GetKeyPress(VK_LEFT))
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

#endif
}

float CPlayer::Jump()
{
	// ��������ɂ���
	dir.y = 1.0f;
	// �W�����v�͂��d�͂ɏ]���čX�V
	jumpStrength -= gravity;
	// �v�Z�����W�����v�͂�K��
	return jumpStrength;
}

void CPlayer::Update()
{
	// ������߂�
	dir.x = 0.0f;
	dir.y = 0.0f;

	// �v���C���[����֘A�̓��͏���
	PlayerInput();

	// �O�t���[���̕␳������������
	prevFrameCorrect = { 0 };

	// �P�ʃx�N�g����(�����P�ɂ���) = ���K��
	DirectX::XMVECTOR v = DirectX::XMLoadFloat3(&dir);	// �x�N�g���v�Z�p�̌^�ɓ����
	v = DirectX::XMVector3Normalize(v);					// ���K������
	DirectX::XMStoreFloat3(&dir, v);					// ���̕ϐ�dir�ɖ߂�
	
	// �d�͂̉e�����󂯂�Y�������̑��x���X�V
	// �W�����v���Ȃ�W�����v�͂̍X�V�������s��
	velocity.y = isJump ? Jump() : velocity.y -= gravity;

	// �x�N�g���ɑ��x�������Ĉʒu��ύX
	this->transform.position.x += dir.x * velocity.x;
	this->transform.position.y += velocity.y;

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

			// �V��ɂԂ����Ă����Ȃ�W�����v�͂�0�ɂ���
			if (prevFrameCorrect.y == -1)
			{
				dir.y = -1.0f;		// ���������ɂ���
				jumpStrength = 0;	// �W�����v�͂�0�ɂ���
			}
			// �d�͂ɂ���Ēn�ʂɏՓ˂��Ă����Ȃ�
			if (prevFrameCorrect.y == 1)
			{
				dir.y = -1.0f;
				velocity.y = 0.0f;				// ���xY��0�ɖ߂�
				jumpStrength = ini_jumpStrength;
				isJump = false;
			}

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
