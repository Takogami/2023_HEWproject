#include "CEventManager.h"
#include "CTimer.h"
#include <cstdlib>

// インスタンスの初期化
CEventManager* CEventManager::instance = nullptr;

CEventManager::CEventManager()
{
	// タイマー
	gameTime = new CTimer;
}

CEventManager::~CEventManager()
{
	delete gameTime;
}

CEventManager* CEventManager::GetInstance()
{
	// インスタンスが存在していないなら生成する
	if (instance == nullptr)
	{
		instance = new CEventManager;
		// コールバックとして登録
		std::atexit(CleanupSingleton);
	}

	return instance;
}

// シングルトンの解放処理
void CEventManager::CleanupSingleton()
{
	//インスタンスがあるなら解放する
	if (instance)
	{
		delete instance;
		instance = nullptr;
	}
}

void CEventManager::Init()
{
	// ゲームの進行状態のリセット
	state = GAME_STATE::READY;
	// スコアの初期化
	score = 0;
	// タイマーの初期化
	gameTime->InitTimer(5, TIMER_MODE::COUNT_DOWN);
	// プレイヤーの体力を初期化
	playerHP = PLAYER_HP;
}

void CEventManager::Update()
{
	// ゲームの進行状況に応じて更新処理を変更
	switch (state)
	{
	case GAME_STATE::READY:
		break;

	case GAME_STATE::START:
		// プレイヤーのHPが0なら
		if (playerHP == 0)
		{
			// 状態をHP0に
			state = GAME_STATE::ZERO_HP;
		}
		// タイムが0になったなら
		else if (gameTime->GetTimerState() == TIMER_STATE::END)
		{
			// 状態をタイムアップに
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
