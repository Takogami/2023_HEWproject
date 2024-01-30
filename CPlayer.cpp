#include "CPlayer.h"
#include "CScene.h"

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

	
	// �X�e�B�b�N�̓��͂�ۑ�
	input_stickX = gInput->GetLeftStickX();
	input_stickY = gInput->GetLeftStickY();
	switch (State)
	{
	case PState::NORMAL: //�ʏ���
		if (anim->GetIsAnimation() == false)
		{
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
			if (input_stickX < 0.0f)
			{
				SetAnimationPattern(ANIM_PATTERN::LEFTWALK);// ���ɕ����A�j���[�V�����Đ�
			}
			else if (input_stickX > 0.0f)
			{
				SetAnimationPattern(ANIM_PATTERN::RIGHTWALK);// �E�ɕ����A�j���[�V�����Đ�
			}

			if (input_stickX == 0)
			{
				SetAnimationPattern(ANIM_PATTERN::NO_ANIM);// �����Ȃ��A�j���[�V�����Đ�
			}
			if ((input_stickY < 0.0f) && prevFrameCorrect.y == 1)
			{
				SetState(PState::FALL);// �|���
				SetAnimationPattern(ANIM_PATTERN::FALLDOWN);// �|�ꂽ�A�j���[�V�����Đ�
				anim->SetIsAnimation(true);
			}
			// A�{�^�����͂łƂ肠�����̃W�����v����
			if (gInput->IsControllerButtonTrigger(XINPUT_GAMEPAD_A))
			{
				isJump = true;
				/*	this->transform.position.y = -0.2f;*/
			}
		}
		break;
	case PState::FALL:// �|�ꂽ���
		if (anim->GetIsAnimation() == false)
		{
			if ((input_stickY > 0.0f) && (old_input_stickY <= 0.0f))
			{
				SetState(PState::NORMAL);// �ʏ��Ԃɖ߂�
				SetAnimationPattern(ANIM_PATTERN::GETUP);// �N���オ��A�j���[�V�����Đ�
				anim->SetIsAnimation(true);
			}
			if (input_stickX <= -1.0f && (old_input_stickX > -1.0f))
			{
				SetState(PState::BREAKLEFT);// ���ɐ܂��
				SetAnimationPattern(ANIM_PATTERN::BREAKLEFT);// ���ɐ܂��A�j���[�V�����Đ�
				anim->SetIsAnimation(true);
			}
			if (input_stickX >= 1.0f && (old_input_stickX < 1.0f))
			{
				SetState(PState::BREAKRIGHT);// �E�ɐ܂��
				SetAnimationPattern(ANIM_PATTERN::BREAKRIGHT);// �E�ɐ܂��A�j���[�V�����Đ�
				anim->SetIsAnimation(true);
			}
			// B�{�^�����͂łƂ肠�����̃W�����v����
			if (gInput->IsControllerButtonTrigger(XINPUT_GAMEPAD_A))
			{
				isJump = true;
				/*	this->transform.position.y = -0.2f;*/
			}
		}
		break;
	case PState::BREAKLEFT:// ���ɐ܂ꂽ���
		if (anim->GetIsAnimation() == false)
		{
			if (input_stickX >= 1.0f && (old_input_stickX < 1.0f))
			{
				SetState(PState::FALL);// �|�ꂽ��Ԃɖ߂�
				SetAnimationPattern(ANIM_PATTERN::FIXLEFT);// �܂ꂽ�̂�����A�j���[�V�����Đ�
				anim->SetIsAnimation(true);
			}
		}
		break;
	case PState::BREAKRIGHT:// �E�ɐ܂ꂽ���
		if (anim->GetIsAnimation() == false)
		{
			if (input_stickX < -1.0f && (old_input_stickX >= -1.0f))
			{
				SetState(PState::FALL);// �|�ꂽ��Ԃɖ߂�
				SetAnimationPattern(ANIM_PATTERN::FIXRIGHT);// �܂ꂽ�̂�����A�j���[�V�����Đ�
				anim->SetIsAnimation(true);
			}
		}
		break;
	default:
		break;
	}
	old_input_stickX= input_stickX;
	old_input_stickY= input_stickY;
#else
	switch (State)
	{
	case PState::NORMAL:// �ʏ��Ԃ̏���
		//SetAnimationPattern(ANIM_PATTERN::NO_ANIM);
		//else if (gInput->GetKeyPress(VK_UP) && prevFrameCorrect.y != -1)
		//{
		//	if (!gInput->GetKeyPress(VK_DOWN))
		//	{
		//		//dir.y = 1.0f;
		//		prevFrameDir.y = dir.y;
		//	}
		//	else
		//	{
		//		dir.y = prevFrameDir.y;
		//	}
		//}
		if (anim->GetIsAnimation() == false)
		{
			if (gInput->GetKeyPress(VK_LEFT) && prevFrameCorrect.x != 1)
			{
				if (!gInput->GetKeyPress(VK_RIGHT))
				{
					dir.x = -1.0f;
					prevFrameDir.x = dir.x;
					SetAnimationPattern(ANIM_PATTERN::LEFTWALK);// ���ɕ����A�j���[�V�����Đ�
				}
				else
				{
					dir.x = prevFrameDir.x;
				}
			}
			else if (gInput->GetKeyPress(VK_RIGHT) && prevFrameCorrect.x != -1)
			{
				//dir.y = prevFrameDir.y;
				if (!gInput->GetKeyPress(VK_LEFT))
				{
					dir.x = 1.0f;
					prevFrameDir.x = dir.x;
					SetAnimationPattern(ANIM_PATTERN::RIGHTWALK);// �E�ɕ����A�j���[�V�����Đ�
				}
				else
				{
					dir.x = prevFrameDir.x;
				}
			}
			if (gInput->GetKeyPress(VK_DOWN) && prevFrameCorrect.y == 1)
			{
				if (!gInput->GetKeyPress(VK_UP))
				{
					/*dir.y = -1.0f;
					prevFrameDir.y = dir.y;*/

					SetState(PState::FALL);// �|�ꂽ���
					SetAnimationPattern(ANIM_PATTERN::FALLDOWN);// �|�ꂽ�A�j���[�V�����Đ�
					anim->SetIsAnimation(true);
				}
				else
				{
					/*dir.y = prevFrameDir.y;*/
				}
			}
			else if (!gInput->GetKeyPress(VK_RIGHT) && !gInput->GetKeyPress(VK_LEFT) && !gInput->GetKeyPress(VK_UP) && !gInput->GetKeyPress(VK_DOWN))
			{
				SetAnimationPattern(ANIM_PATTERN::NO_ANIM);// �����Ȃ��A�j���[�V�����Đ�
			}

			if (gInput->GetKeyPress(VK_TAB))
			{
				isJump = true;
			}
		}
		break;

	case PState::FALL:// �|�ꂽ��Ԃ̏���
		if (anim->GetIsAnimation() == false)
		{
			if (gInput->GetKeyPress(VK_UP))
			{
				if (!gInput->GetKeyPress(VK_DOWN))
				{
					SetState(PState::NORMAL);// �ʏ���
					SetAnimationPattern(ANIM_PATTERN::GETUP);// �N���オ��A�j���[�V�����Đ�
					anim->SetIsAnimation(true);
				}
				else
				{

				}
			}
			if (gInput->GetKeyTrigger(VK_LEFT))
			{
				if (!gInput->GetKeyTrigger(VK_RIGHT))
				{
					SetState(PState::BREAKLEFT);// ���ɐ܂����
					SetAnimationPattern(ANIM_PATTERN::BREAKLEFT);// ���ɐ܂��A�j���[�V�����Đ�
					anim->SetIsAnimation(true);
				}
				else
				{

				}
			}
			else if (gInput->GetKeyTrigger(VK_RIGHT))
			{
				if (!gInput->GetKeyTrigger(VK_LEFT))
				{
					SetState(PState::BREAKRIGHT);// �E�ɐ܂����
					SetAnimationPattern(ANIM_PATTERN::BREAKRIGHT);// �E�ɐ܂��A�j���[�V�����Đ�
					anim->SetIsAnimation(true);
				}
				else
				{

				}
			}
		}
		break;

	case PState::BREAKLEFT:
		if (anim->GetIsAnimation() == false)
		{
			if (gInput->GetKeyTrigger(VK_RIGHT))
			{
				if (!gInput->GetKeyTrigger(VK_LEFT))
				{
					SetState(PState::FALL);// �|�ꂽ���
					SetAnimationPattern(ANIM_PATTERN::FIXLEFT);// �܂ꂽ�̂�����A�j���[�V�����Đ�
					anim->SetIsAnimation(true);
				}
				else
				{

				}
			}
		}
		break;

	case PState::BREAKRIGHT:
		if (anim->GetIsAnimation() == false)
		{
			if (gInput->GetKeyTrigger(VK_LEFT))
			{
				if (!gInput->GetKeyTrigger(VK_RIGHT))
				{
					SetState(PState::FALL);// �|�ꂽ���
					SetAnimationPattern(ANIM_PATTERN::FIXRIGHT);// �܂ꂽ�̂�����A�j���[�V�����Đ�
					anim->SetIsAnimation(true);
				}
				else
				{

				}
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

			case OBJECT_TYPE::WIND:
				//	�I�u�W�F�N�g�ɓ���������true
				isWind = true;

				
				break;

			default:
				break;
			}
		}
	}
}

void CPlayer::Wind()
{
	//	�v���C���[�̏�Ԃ��܂�Ă��ĕ��������Ă�I�u�W�F�N�g�ɓ���������c
	if (isWind == true && (State == PState::BREAKLEFT || State == PState::BREAKRIGHT))
	{
		//	�E�����x�N�g��
		dir.x = 1.0f;

		//	�����N���Ă�悤�Ȍv�Z
		this->transform.position.x += dir.x * velocity.x * 1.1f;

		//	�n�ʂɓ���������c
		if (prevFrameCorrect.y == 1)
		{
			//	�ړ����I��
			isWind = false;
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
