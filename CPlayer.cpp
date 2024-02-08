#include "CPlayer.h"
#include "CScene.h"
#include "CWind.h"

// �R���g���[���[���g���ꍇ��true���w��
#define USE_CONTROLLER (false)

//�����I�ɐe�N���X�̃R���X�g���N�^���Ăяo��
CPlayer::CPlayer(ID3D11Buffer* vb, ID3D11ShaderResourceView* tex, FLOAT_XY uv, OBJECT_TYPE type) : CGameObject(vb, tex, uv, type)
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
	float input_stickY;

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
	/*	this->transform.position.y = -0.2f;*/
	}

#else
	switch (State)
	{
	case PState::NORMAL:
		if (gInput->GetKeyPress(VK_DOWN) /*&& prevFrameCorrect.y != 1*/)
		{
			if (!gInput->GetKeyPress(VK_UP))
			{
				/*dir.y = -1.0f;
				prevFrameDir.y = dir.y;*/

				SetState(PState::FALL);
				transform.scale.y *= 0.1f;
				this->Bcol.sizeY *= 0.1f;
				transform.position.y -= 0.1f;
			}
			else
			{
				/*dir.y = prevFrameDir.y;*/
			}
		}
		else if (gInput->GetKeyPress(VK_UP) && prevFrameCorrect.y != -1)
		{
			if (!gInput->GetKeyPress(VK_DOWN))
			{
				//dir.y = 1.0f;
				prevFrameDir.y = dir.y;
			}
			else
			{
				dir.y = prevFrameDir.y;
			}
		}
		if (gInput->GetKeyPress(VK_LEFT) && prevFrameCorrect.x != 1)
		{
			if (!gInput->GetKeyPress(VK_RIGHT))
			{
				dir.x = -1.0f;
				prevFrameDir.x = dir.x;
			}
			else
			{
				dir.x = prevFrameDir.x;
			}
		}
		else if (gInput->GetKeyPress(VK_RIGHT) && prevFrameCorrect.x != -1)
		{
			dir.y = prevFrameDir.y;
			if (!gInput->GetKeyPress(VK_LEFT))
			{
				dir.x = 1.0f;
				prevFrameDir.x = dir.x;
			}
			else
			{
				dir.x = prevFrameDir.x;
			}
		}
		if (gInput->GetKeyPress(VK_TAB))
		{
			isJump = true;
		}
		if (prevFrameCorrect.x != 0)
		{

			SetState(PState::FALL);
			transform.scale.y *= 0.1f;
			this->Bcol.sizeY *= 0.1f;
			transform.position.y -= 0.1f;
		}
		break;

	case PState::FALL:
		if (gInput->GetKeyPress(VK_UP))
		{
			if (!gInput->GetKeyPress(VK_DOWN))
			{
				SetState(PState::NORMAL);
				transform.scale.y *= 10.0;
				this->Bcol.sizeY *= 10.0f;
				transform.position.y += 0.1f;
			}
			else
			{

			}
			if (gInput->GetKeyTrigger(VK_LEFT))
			{
				if (!gInput->GetKeyTrigger(VK_RIGHT))
				{
					SetState(PState::BREAKLEFT);
				}
				else
				{

				}
			}
			else if (gInput->GetKeyTrigger(VK_RIGHT))
			{
				if (!gInput->GetKeyTrigger(VK_LEFT))
				{
					SetState(PState::BREAKRIGHT);
				}
				else
				{

				}
			}
			if (gInput->GetKeyPress(VK_TAB))
			{
				isJump = true;
			}
		}
			break;

	case PState::BREAKLEFT:
		if (gInput->GetKeyTrigger(VK_RIGHT))
		{
			if (!gInput->GetKeyTrigger(VK_LEFT))
			{
				SetState(PState::FALL);
			}
			else
			{

			}
		}
		break;

	case PState::BREAKRIGHT:
		if (gInput->GetKeyTrigger(VK_LEFT))
		{
			if (!gInput->GetKeyTrigger(VK_RIGHT))
			{
				SetState(PState::FALL);
			}
			else
			{

			}
		}
		break;

	default:
		break;
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
	// ���̉e�����󂯂Ă��Ȃ��Ȃ������߂�
	if (dir_wind.x == 0.0f)
	{
		// ������߂�
		dir.x = 0.0f;
	}
	if (dir_wind.y == 0.0f)
	{
		// ������߂�
		dir.y = -1.0f;
	}

	// �v���C���[����֘A�̓��͏���
	PlayerInput();

	// �O�t���[���̕␳������������
	prevFrameCorrect = { 0 };

	// �P�ʃx�N�g����(�����P�ɂ���) = ���K��
	DirectX::XMVECTOR v = DirectX::XMLoadFloat3(&dir);	// �x�N�g���v�Z�p�̌^�ɓ����
	v = DirectX::XMVector3Normalize(v);					// ���K������
	DirectX::XMStoreFloat3(&dir, v);					// ���̕ϐ�dir�ɖ߂�

	// ���̉e���ł�y�����̑��x�����E�l�𒴂��Ȃ��悤�ɂ���
	if ((dir_wind.y == 1.0f || dir_wind.y == -1.0f) && velocity.y > velocityY_limit)
	{
		velocity.y = velocityY_limit;
	}

	// �d�͂̉e�����󂯂�Y�������̑��x���X�V
	// �W�����v���Ȃ�W�����v�͂̍X�V�������s��
	velocity.y = isJump ? Jump() : velocity.y += gravity;

	// �x�N�g���ɑ��x�������Ĉʒu��ύX
	this->transform.position.x += dir.x * velocity.x;
	this->transform.position.y += dir.y * velocity.y;

	// �ړ��ʂɕ��̌v�Z��������
	if (dir_wind.x == 1.0f)
	{
		windStrength -= 0.001f;
		if (windStrength <= 0.0f)
		{
			dir_wind.x = 0.0f;
			windStrength = 0.0f;
		}
		this->transform.position.x += windStrength;
	}
	// 
	if (dir_wind.y == 1.0f)
	{
		windStrength -= 0.001f;
		if (windStrength <= 0.0f)
		{
			dir_wind.y = 0.0f;
			windStrength = 0.0f;
		}
		this->transform.position.y += windStrength;
	}


	// �e�N���X��Update()�𖾎��I�ɌĂяo��
	// �S�ẴQ�[���I�u�W�F�N�g���ʂ̍X�V�������s��
	CGameObject::Update();

	// �n�`�Ƃ̓����蔻��ƕ␳
	for (auto it = CScene::map_object.begin(); it != CScene::map_object.end(); it++)
	{
		if (CCollision::TestBoxCollision(this->Bcol, (*it)->Bcol))
		{
			switch ((*it)->GetObjectType())
			{
			case OBJECT_TYPE::NORMAL:
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
				break;

			case OBJECT_TYPE::WIND_RIGHT:	//	���i�E�����j
				dir_wind.x = 1.0f;
				dir.x = 1.0f;
				windStrength = 0.01f;
				// �I�u�W�F�N�g�̈ʒu�ƃR���C�_�[�̒��S�����킹��
				this->Bcol.centerX = this->transform.position.x;
				this->Bcol.centerY = this->transform.position.y;
				break;

			case OBJECT_TYPE::WIND_UP:		//	���i������j
				dir_wind.y = 1.0f;
				dir.y = 1.0f;
				windStrength = 0.01f;
				break;

			default:
				break;
			}
		}
	}
}

PState CPlayer::GetState()
{
	return State;
}

void CPlayer::SetState(PState state)
{
	State = state;
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
