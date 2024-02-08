#include <cstdlib>
#include "CGameManager.h"
#include "CTimer.h"
#include "CGameObject.h"
#include "CTextureLoader.h"
#include "CEase.h"

// �C���X�^���X�̏�����
CGameManager* CGameManager::instance = nullptr;

CGameManager::CGameManager()
{
	// �^�C�}�[
	gameTime = new CTimer;

	// UI�I�u�W�F�N�g�̎��̉�
	UI_timer = new CGameObject(vertexBufferUI, CTextureLoader::GetInstance()->GetTex(TEX_ID::TIMER));
	Objects.push_back(UI_timer);
	UI_timer->transform.position = { 1.75f, 0.85f, -0.4f };
	UI_timer->transform.scale = {466.0f * 0.00085f, 517.0f * 0.00085f, 1.0f};
	UI_timer->transform.rotation = -25.0f;

	UI_hpBoard = new CGameObject(vertexBufferUI, CTextureLoader::GetInstance()->GetTex(TEX_ID::SCORE_BOARD));
	Objects.push_back(UI_hpBoard);
	UI_hpBoard->transform.position = { -1.6f, 0.85f, -0.4f };
	UI_hpBoard->transform.scale = { 1101.0f * 0.0007f, 750.0f * 0.0007f, 1.0f };

	for (int i = 0; i < 3; i++)
	{
		UI_hp[i] = new CGameObject(vertexBufferUI, CTextureLoader::GetInstance()->GetTex(TEX_ID::HEART), {0.333333f, 1.0f});
		Objects.push_back(UI_hp[i]);
		UI_hp[i]->transform.position = { -1.78f + ((286.0f * 0.00065f + 0.01f) * i), 0.84f, -0.45f};
		UI_hp[i]->transform.scale = { 286.0f * 0.00065f, 252.0f * 0.00065f, 1.0f };
	}
	for (int i = 0; i < 3; i++)
	{
		UI_breakHeart_R[i] = new CGameObject(vertexBufferUI, CTextureLoader::GetInstance()->GetTex(TEX_ID::HALF_HEART_R));
		Objects.push_back(UI_breakHeart_R[i]);
		UI_breakHeart_R[i]->transform.position = { -1.74f + ((286.0f * 0.00065f + 0.01f) * i), 0.84f, -0.46f };
		UI_breakHeart_R[i]->transform.scale = { 155.0f * 0.00065f, 252.0f * 0.00065f, 1.0f };
		UI_breakHeart_R[i]->materialDiffuse.w = 0.0f;
		breakHeart_R_ease[i] = new CEase;
		breakHeart_R_ease[i]->Init(&UI_breakHeart_R[i]->transform.position.y, UI_breakHeart_R[i]->transform.position.y - 0.3f, 1.0f, 0, EASE::easeOutBounce);
	}
	for (int i = 0; i < 3; i++)
	{
		UI_breakHeart_L[i] = new CGameObject(vertexBufferUI, CTextureLoader::GetInstance()->GetTex(TEX_ID::HALF_HEART_L));
		Objects.push_back(UI_breakHeart_L[i]);
		UI_breakHeart_L[i]->transform.position = { -1.821f + ((286.0f * 0.00065f + 0.01f) * i), 0.84f, -0.47f };
		UI_breakHeart_L[i]->transform.scale = { 155.0f * 0.00065f, 252.0f * 0.00065f, 1.0f };
		UI_breakHeart_L[i]->materialDiffuse.w = 0.0f;
		breakHeart_L_ease[i] = new CEase;
		breakHeart_L_ease[i]->Init(&UI_breakHeart_L[i]->transform.position.y, UI_breakHeart_L[i]->transform.position.y - 0.3f, 1.0f, 0, EASE::easeOutBounce);
	}
}

CGameManager::~CGameManager()
{
	// �^�C�}�[�̉��
	delete gameTime;

	// ���_�o�b�t�@�̉��
	SAFE_RELEASE(vertexBufferUI);

	// �e�I�u�W�F�N�g�̉��
	for (auto it = Objects.begin(); it != Objects.end(); it++)
	{
		delete (*it);
	}
}

CGameManager* CGameManager::GetInstance()
{
	// �C���X�^���X�����݂��Ă��Ȃ��Ȃ琶������
	if (instance == nullptr)
	{
		instance = new CGameManager;
		// �R�[���o�b�N�Ƃ��ēo�^
		std::atexit(CleanupSingleton);
	}

	return instance;
}

// �V���O���g���̉������
void CGameManager::CleanupSingleton()
{
	//�C���X�^���X������Ȃ�������
	if (instance)
	{
		delete instance;
		instance = nullptr;
	}
}

void CGameManager::Init()
{
	// �Q�[���̐i�s��Ԃ̃��Z�b�g
	state = GAME_STATE::READY;
	// �X�R�A�̏�����
	score = 0;
	// �^�C�}�[�̏�����
	gameTime->InitTimer(50, TIMER_MODE::COUNT_DOWN);
	// �v���C���[�̗̑͂�������
	playerHP = PLAYER_HP;
	// UI�̏�����
	for (int i = 0; i < 3; i++)
	{
		// �؂蔲���ʒu�����ɖ߂�
		UI_hp[i]->TextureCutout(0, 0);
	}
}

void CGameManager::Update()
{
	// �Q�[���̐i�s�󋵂ɉ����čX�V������ύX
	switch (state)
	{
	case GAME_STATE::READY:
		// �^�C�}�[�̊J�n
		gameTime->StartTimer();
		state = GAME_STATE::START;
		break;

	case GAME_STATE::START:
		// �v���C���[��HP��0�Ȃ�
		if (playerHP <= 0)
		{
			// ��Ԃ�HP0��
			state = GAME_STATE::ZERO_HP;
		}
		// �^�C����0�ɂȂ����Ȃ�
		else if (gameTime->GetTimerState() == TIMER_STATE::END)
		{
			// ��Ԃ��^�C���A�b�v��
			state = GAME_STATE::TIME_UP;
		}

		// �̗͂�UI�Ǘ�
		if (playerHP == 5)
		{
			UI_hp[2]->TextureCutout(1, 0);
			UI_breakHeart_R[2]->materialDiffuse.w = 1.0f;
			breakHeart_R_ease[2]->Update();
		}
		if (playerHP == 4)
		{
			UI_hp[2]->TextureCutout(2, 0);
			UI_breakHeart_L[2]->materialDiffuse.w = 1.0f;
			breakHeart_L_ease[2]->Update();
		}
		if (playerHP == 3)
		{
			UI_hp[1]->TextureCutout(1, 0);
			UI_breakHeart_R[1]->materialDiffuse.w = 1.0f;
			breakHeart_R_ease[1]->Update();
		}
		if (playerHP == 2)
		{
			UI_hp[1]->TextureCutout(2, 0);
			UI_breakHeart_L[1]->materialDiffuse.w = 1.0f;
			breakHeart_L_ease[1]->Update();
		}
		if (playerHP == 1)
		{
			UI_hp[0]->TextureCutout(1, 0);
			UI_breakHeart_R[0]->materialDiffuse.w = 1.0f;
			breakHeart_R_ease[0]->Update();
		}
		if (playerHP == 0)
		{
			UI_hp[0]->TextureCutout(2, 0);
			UI_breakHeart_L[0]->materialDiffuse.w = 1.0f;
			breakHeart_L_ease[0]->Update();
		}

		break;

	case GAME_STATE::TIME_UP:
		break;

	case GAME_STATE::ZERO_HP:
		break;

	default:
		break;
	}

	// �^�C�}�[�̍X�V
	gameTime->Update();

	// �Q�[���֘AUI�̍X�V
	for (auto it = Objects.begin(); it != Objects.end(); it++)
	{
		(*it)->Update();
	}
}

void CGameManager::Draw()
{
	// �Q�[���֘AUI�̕`��
	for (auto it = Objects.begin(); it != Objects.end(); it++)
	{
		(*it)->Draw();
	}
}

void CGameManager::AddScore(int addScore)
{
	score += addScore;
}

void CGameManager::AddDamage(int addDamage)
{
	// �l��1~6�ŃN�����v
	addDamage = addDamage < 1 ? 1 : addDamage;
	addDamage = addDamage > 6 ? 6 : addDamage;

	// �v���C���[��HP����_���[�W������
	playerHP -= addDamage;
	// 0�ȉ��ɂȂ�Ȃ��悤�ɒ���
	playerHP = playerHP < 0 ? 0 : playerHP;
}

GAME_STATE CGameManager::GetGameState()
{
	return state;
}
