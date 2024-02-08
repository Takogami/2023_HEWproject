#include <cstdlib>
#include "CGameManager.h"
#include "CTimer.h"
#include "CGameObject.h"
#include "CTextureLoader.h"
#include "CEase.h"

// インスタンスの初期化
CGameManager* CGameManager::instance = nullptr;

CGameManager::CGameManager()
{
	// タイマー
	gameTime = new CTimer;

	// UIオブジェクトの実体化
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
	// タイマーの解放
	delete gameTime;

	// 頂点バッファの解放
	SAFE_RELEASE(vertexBufferUI);

	// 各オブジェクトの解放
	for (auto it = Objects.begin(); it != Objects.end(); it++)
	{
		delete (*it);
	}
}

CGameManager* CGameManager::GetInstance()
{
	// インスタンスが存在していないなら生成する
	if (instance == nullptr)
	{
		instance = new CGameManager;
		// コールバックとして登録
		std::atexit(CleanupSingleton);
	}

	return instance;
}

// シングルトンの解放処理
void CGameManager::CleanupSingleton()
{
	//インスタンスがあるなら解放する
	if (instance)
	{
		delete instance;
		instance = nullptr;
	}
}

void CGameManager::Init()
{
	// ゲームの進行状態のリセット
	state = GAME_STATE::READY;
	// スコアの初期化
	score = 0;
	// タイマーの初期化
	gameTime->InitTimer(50, TIMER_MODE::COUNT_DOWN);
	// プレイヤーの体力を初期化
	playerHP = PLAYER_HP;
	// UIの初期化
	for (int i = 0; i < 3; i++)
	{
		// 切り抜き位置を元に戻す
		UI_hp[i]->TextureCutout(0, 0);
	}
}

void CGameManager::Update()
{
	// ゲームの進行状況に応じて更新処理を変更
	switch (state)
	{
	case GAME_STATE::READY:
		// タイマーの開始
		gameTime->StartTimer();
		state = GAME_STATE::START;
		break;

	case GAME_STATE::START:
		// プレイヤーのHPが0なら
		if (playerHP <= 0)
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

		// 体力のUI管理
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

	// タイマーの更新
	gameTime->Update();

	// ゲーム関連UIの更新
	for (auto it = Objects.begin(); it != Objects.end(); it++)
	{
		(*it)->Update();
	}
}

void CGameManager::Draw()
{
	// ゲーム関連UIの描画
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
	// 値を1~6でクランプ
	addDamage = addDamage < 1 ? 1 : addDamage;
	addDamage = addDamage > 6 ? 6 : addDamage;

	// プレイヤーのHPからダメージを引く
	playerHP -= addDamage;
	// 0以下にならないように調整
	playerHP = playerHP < 0 ? 0 : playerHP;
}

GAME_STATE CGameManager::GetGameState()
{
	return state;
}
