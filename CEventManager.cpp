#include "CEventManager.h"
#include "CTimer.h"
#include <cstdlib>

// �C���X�^���X�̏�����
CEventManager* CEventManager::instance = nullptr;

CEventManager::CEventManager()
{
	// �^�C�}�[
	gameTime = new CTimer;
}

CEventManager::~CEventManager()
{
	delete gameTime;
}

CEventManager* CEventManager::GetInstance()
{
	// �C���X�^���X�����݂��Ă��Ȃ��Ȃ琶������
	if (instance == nullptr)
	{
		instance = new CEventManager;
		// �R�[���o�b�N�Ƃ��ēo�^
		std::atexit(CleanupSingleton);
	}

	return instance;
}

// �V���O���g���̉������
void CEventManager::CleanupSingleton()
{
	//�C���X�^���X������Ȃ�������
	if (instance)
	{
		delete instance;
		instance = nullptr;
	}
}

void CEventManager::Init()
{
	// �Q�[���̐i�s��Ԃ̃��Z�b�g
	state = GAME_STATE::READY;
	// �X�R�A�̏�����
	score = 0;
	// �^�C�}�[�̏�����
	gameTime->InitTimer(5, TIMER_MODE::COUNT_DOWN);
	// �v���C���[�̗̑͂�������
	playerHP = PLAYER_HP;
}

void CEventManager::Update()
{
	// �Q�[���̐i�s�󋵂ɉ����čX�V������ύX
	switch (state)
	{
	case GAME_STATE::READY:
		break;

	case GAME_STATE::START:
		// �v���C���[��HP��0�Ȃ�
		if (playerHP == 0)
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
		break;

	case GAME_STATE::TIME_UP:
		break;

	case GAME_STATE::ZERO_HP:
		break;

	default:
		break;
	}
}

void CEventManager::AddScore(int addScore)
{
	score += addScore;
}

GAME_STATE CEventManager::GetGameState()
{
	return state;
}
