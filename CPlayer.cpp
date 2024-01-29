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

	time = new CTimer();
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

	// ������߂�
	dir.x = 0.0f;
	dir.y = -1.0f;

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
	velocity.y = isJump ? Jump() : velocity.y += gravity;

	// �x�N�g���ɑ��x�������Ĉʒu��ύX
	this->transform.position.x += dir.x * velocity.x;
	this->transform.position.y += dir.y * velocity.y;

	// �e�N���X��Update()�𖾎��I�ɌĂяo��
	// �S�ẴQ�[���I�u�W�F�N�g���ʂ̍X�V�������s��
	CGameObject::Update();
	time->Update();

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
				//	�I�u�W�F�N�g�ɓ���������true
				isWind_right = true;
				break;

			case OBJECT_TYPE::WIND_UP:	//	���i������j
				//	�I�u�W�F�N�g�ɓ�������true
				isWind_up = true;
				//	�^�C�}�[�̏�����
				time->InitTimer(3, TIMER_MODE::COUNT_DOWN);
				break;

			default:
				break;
			}
		}
	}

	//=======================//
	if (isWind_right)
	{
		if (time->GetTimerState() != TIMER_STATE::UPDATE)
		{
			time->StartTimer();
		}
		wind->Wind_Right(this, 0.8f);
	}

	if (time->GetTime() == 0)
	{
		isWind_right = false;
	}
	//=======================//
}

void CPlayer::WindUp()
{
	if (isWind_up)
	{
		// ������x�N�g��
		dir.y = 1.0f;
		// �����N���Ă���悤�Ȍv�Z
		this->transform.position.y += wind_power;
		if (prevFrameCorrect.y == 1)
		{
			isWind_up = false;
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
	delete time;
}
