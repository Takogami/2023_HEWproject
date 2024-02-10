#include "CEnemy.h"
#include "CScene.h"
#include "CWind.h"

void CEnemy::EnemyPattern()
{
	switch (State)
	{
	case EState::NORMAL:
		SetState(EState::LEFTWALK);
		walkTime->InitTimer(5, TIMER_MODE::COUNT_DOWN);
		walkTime->StartTimer();
		break;
	case EState::LEFTWALK:
		dir.x = -1.0f;
		prevFrameDir.x = dir.x;
		if (walkTime->GetTimerState() == TIMER_STATE::END)//(prevFrameCorrect.x >= 1)
		{
			SetState(EState::RIGHTWALK);
			walkTime->InitTimer(5, TIMER_MODE::COUNT_DOWN);
			walkTime->StartTimer();
		}
		break;
	case EState::RIGHTWALK:
		dir.x = 1.0f;
		prevFrameDir.x = dir.x;
		if (walkTime->GetTimerState() == TIMER_STATE::END)//(prevFrameCorrect.x <= -1)
		{
			SetState(EState::LEFTWALK);
			walkTime->InitTimer(5, TIMER_MODE::COUNT_DOWN);
			walkTime->StartTimer();
		}
		break;
	default:
		break;
	}
}

CEnemy::CEnemy(ID3D11Buffer* vb, ID3D11ShaderResourceView* tex, FLOAT_XY uv, OBJECT_TYPE type) : CGameObject(vb, tex, uv, type)
{
	// �����X�s�[�h�ݒ�
	SetMoveSpeed(0.005f);
	// �d�͂������l�Ƃ���
	velocity.y = gravity;
	walkTime = new CTimer;
}

EState CEnemy::GetState()
{
	return State;
}

void CEnemy::SetState(EState state)
{
	State = state;
}

void CEnemy::Update()
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

	EnemyPattern();

	// �^�C�}�[�̍X�V
	walkTime->Update();

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

	velocity.y += gravity;

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
				CORRECT_DIR test = CCollision::CorrectPosition(this->Bcol, (*it)->Bcol);
				prevFrameCorrect.x += test.x;
				prevFrameCorrect.y += test.y;


				// �V��ɂԂ����Ă����Ȃ�W�����v�͂�0�ɂ���
				if (prevFrameCorrect.y == -1)
				{
					dir.y = -1.0f;		// ���������ɂ���
				}
				// �d�͂ɂ���Ēn�ʂɏՓ˂��Ă����Ȃ�
				if (prevFrameCorrect.y == 1)
				{
					dir.y = -1.0f;
					velocity.y = 0.0f;				// ���xY��0�ɖ߂�
					velocity.y -= gravity;				// ���xY��0�ɖ߂�
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

void CEnemy::Draw()
{
	// �e�N���X��Draw()�𖾎��I�ɌĂяo��
	// �S�ẴQ�[���I�u�W�F�N�g���ʂ̕`�揈�����s��
	CGameObject::Draw();
}

CEnemy::~CEnemy()
{
	delete walkTime;
	// �e�N���X�̃R���X�g���N�^�𖾎��I�ɌĂяo��
	// ���_�o�b�t�@�̉�����s��
	CGameObject::~CGameObject();
}
