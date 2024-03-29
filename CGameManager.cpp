#include <cstdlib>
#include "CGameManager.h"
#include "CTimer.h"
#include "CGameObject.h"
#include "CTextureLoader.h"
#include "CEase.h"
#include "CSceneManager.h"

// インスタンスの初期化
CGameManager* CGameManager::instance = nullptr;

CGameManager::CGameManager()
{
	// タイマー
	gameTime = new CTimer;

	// UIオブジェクトの実体化
	UI_timer = new CGameObject(vertexBufferUI, CTextureLoader::GetInstance()->GetTex(TEX_ID::TIMER));
	Objects.push_back(UI_timer);
	UI_timer->transform.position = { 1.75f, 0.85f, -0.44f };
	UI_timer->transform.scale = {466.0f * 0.00085f, 517.0f * 0.00085f, 1.0f};
	UI_timer->transform.rotation = -25.0f;

	UI_hpBoard = new CGameObject(vertexBufferUI, CTextureLoader::GetInstance()->GetTex(TEX_ID::SCORE_BOARD));
	Objects.push_back(UI_hpBoard);
	UI_hpBoard->transform.position = { -1.6f, 0.85f, -0.44f };
	UI_hpBoard->transform.scale = { 1101.0f * 0.0007f, 750.0f * 0.0007f, 1.0f };

	// hpのUIの実体化
	for (int i = 0; i < 3; i++)
	{
		UI_hp[i] = new CGameObject(vertexBufferUI, CTextureLoader::GetInstance()->GetTex(TEX_ID::HEART), {0.333333f, 1.0f});
		Objects.push_back(UI_hp[i]);
		UI_hp[i]->transform.position = { -1.78f + ((286.0f * 0.00065f + 0.01f) * i), 0.84f, -0.45f};
		UI_hp[i]->transform.scale = { 286.0f * 0.00065f, 252.0f * 0.00065f, 1.0f };

		breakHeart_R_ease[i] = new CEase;
		UI_breakHeart_R[i] = new CGameObject(vertexBufferUI, CTextureLoader::GetInstance()->GetTex(TEX_ID::HALF_HEART_R));
		Objects.push_back(UI_breakHeart_R[i]);
		UI_breakHeart_R[i]->transform.scale = { 155.0f * 0.00065f, 252.0f * 0.00065f, 1.0f };

		breakHeart_L_ease[i] = new CEase;
		UI_breakHeart_L[i] = new CGameObject(vertexBufferUI, CTextureLoader::GetInstance()->GetTex(TEX_ID::HALF_HEART_L));
		Objects.push_back(UI_breakHeart_L[i]);
		UI_breakHeart_L[i]->transform.scale = { 161.0f * 0.00065f, 252.0f * 0.00065f, 1.0f };
	}

	strBg = new CGameObject(vertexBufferUI, CTextureLoader::GetInstance()->GetTex(TEX_ID::BOARD));
	Objects.push_back(strBg);
	strBg->transform.position = { 0.0f, 0.93f, -0.44f };
	strBg->transform.scale = { 772.0f * 0.0013f, 472.0f * 0.0007f, 1.0f };

	strStage = new CGameObject(vertexBufferUI, CTextureLoader::GetInstance()->GetTex(TEX_ID::STR_STAGE));
	Objects.push_back(strStage);
	strStage->transform.position = { -0.11f, 0.93f, -0.45f };
	strStage->transform.scale = { 700.0f * 0.00085f, 283.0f * 0.00085f, 1.0f };

	stageNum = new CGameObject(vertexBufferUI, CTextureLoader::GetInstance()->GetTex(TEX_ID::NUM), { 0.1f ,1.0f });
	// オブジェクトをリストに登録
	Objects.push_back(stageNum);
	// スケールの設定
	stageNum->transform * 0.18f;
	stageNum->transform.rotation = -10.0f;
	stageNum->transform.position = { 0.285f, 0.93f, -0.45f };
	
	// 時間数字テクスチャ
	for (int i = 0; i < 3; i++)
	{
		timeNum[i] = new CGameObject(vertexBufferUI, CTextureLoader::GetInstance()->GetTex(TEX_ID::NUM), { 0.1f ,1.0f });
		timeNum[i]->transform.scale = { 0.15f, 0.2f, 1.0f };
		timeNum[i]->transform.position = { 1.59f + (0.151f * i), 0.82f, -0.46f};
		Objects.push_back(timeNum[i]);
	}

	// 実体化の後、初期化を行う
	this->Init();
}

CGameManager::~CGameManager()
{
	// タイマーの解放
	delete gameTime;

	// 頂点バッファの解放
	SAFE_RELEASE(vertexBufferUI);

	for (int i = 0; i < 3; i++)
	{

	}
	// 各オブジェクトの解放
	for (auto it = Objects.begin(); it != Objects.end(); it++)
	{
		delete (*it);
	}
}

void CGameManager::UpdateUIhp()
{
	// 体力のUI管理
	if (playerHP <= 5)
	{
		UI_hp[2]->TextureCutout(1, 0);
		// ハーフハートが透明なら不透明に戻す
		if (!heartAlpha_R[2])
		{
			// 半分のハートの透明度を0に
			UI_breakHeart_R[2]->materialDiffuse.w = 1.0f;
			heartAlpha_R[2] = true;
		}
		// すでに不透明なら徐々に透明にする
		else
		{
			UI_breakHeart_R[2]->materialDiffuse.w =
				UI_breakHeart_R[2]->materialDiffuse.w > 0.0f ?
				UI_breakHeart_R[2]->materialDiffuse.w -= 0.02f : UI_breakHeart_R[2]->materialDiffuse.w;
		}
		// ハートのイージングの更新
		breakHeart_R_ease[2]->Update();
		// 回転率を変更する
		UI_breakHeart_R[2]->transform.rotation =
			UI_breakHeart_R[2]->transform.rotation > -45.0f ?
			UI_breakHeart_R[2]->transform.rotation - 2.0f : UI_breakHeart_R[2]->transform.rotation;
	}
	if (playerHP <= 4)
	{
		UI_hp[2]->TextureCutout(2, 0);
		// ハーフハートが透明なら不透明に戻す
		if (!heartAlpha_L[2])
		{
			// 半分のハートの透明度を0に
			UI_breakHeart_L[2]->materialDiffuse.w = 1.0f;
			heartAlpha_L[2] = true;
		}
		// すでに不透明なら徐々に透明にする
		else
		{
			UI_breakHeart_L[2]->materialDiffuse.w =
				UI_breakHeart_L[2]->materialDiffuse.w > 0.0f ?
				UI_breakHeart_L[2]->materialDiffuse.w -= 0.02f : UI_breakHeart_L[2]->materialDiffuse.w;
		}
		// ハートのイージングの更新
		breakHeart_L_ease[2]->Update();
		// 回転率を変更する
		UI_breakHeart_L[2]->transform.rotation =
			UI_breakHeart_L[2]->transform.rotation < 45.0f ?
			UI_breakHeart_L[2]->transform.rotation + 2.0f : UI_breakHeart_L[2]->transform.rotation;
	}
	if (playerHP <= 3)
	{
		UI_hp[1]->TextureCutout(1, 0);
		// ハーフハートが透明なら不透明に戻す
		if (!heartAlpha_R[1])
		{
			// 半分のハートの透明度を0に
			UI_breakHeart_R[1]->materialDiffuse.w = 1.0f;
			heartAlpha_R[1] = true;
		}
		// すでに不透明なら徐々に透明にする
		else
		{
			UI_breakHeart_R[1]->materialDiffuse.w =
				UI_breakHeart_R[1]->materialDiffuse.w > 0.0f ?
				UI_breakHeart_R[1]->materialDiffuse.w -= 0.02f : UI_breakHeart_R[1]->materialDiffuse.w;
		}
		// ハートのイージングの更新
		breakHeart_R_ease[1]->Update();
		// 回転率を変更する
		UI_breakHeart_R[1]->transform.rotation =
			UI_breakHeart_R[1]->transform.rotation > -45.0f ?
			UI_breakHeart_R[1]->transform.rotation - 2.0f : UI_breakHeart_R[1]->transform.rotation;
	}
	if (playerHP <= 2)
	{
		UI_hp[1]->TextureCutout(2, 0);
		// ハーフハートが透明なら不透明に戻す
		if (!heartAlpha_L[1])
		{
			// 半分のハートの透明度を0に
			UI_breakHeart_L[1]->materialDiffuse.w = 1.0f;
			heartAlpha_L[1] = true;
		}
		// すでに不透明なら徐々に透明にする
		else
		{
			UI_breakHeart_L[1]->materialDiffuse.w =
				UI_breakHeart_L[1]->materialDiffuse.w > 0.0f ?
				UI_breakHeart_L[1]->materialDiffuse.w -= 0.02f : UI_breakHeart_L[1]->materialDiffuse.w;
		}
		// ハートのイージングの更新
		breakHeart_L_ease[1]->Update();
		// 回転率を変更する
		UI_breakHeart_L[1]->transform.rotation =
			UI_breakHeart_L[1]->transform.rotation < 45.0f ?
			UI_breakHeart_L[1]->transform.rotation + 2.0f : UI_breakHeart_L[1]->transform.rotation;
	}
	if (playerHP <= 1)
	{
		UI_hp[0]->TextureCutout(1, 0);
		// ハーフハートが透明なら不透明に戻す
		if (!heartAlpha_R[0])
		{
			// 半分のハートの透明度を0に
			UI_breakHeart_R[0]->materialDiffuse.w = 1.0f;
			heartAlpha_R[0] = true;
		}
		// すでに不透明なら徐々に透明にする
		else
		{
			UI_breakHeart_R[0]->materialDiffuse.w =
				UI_breakHeart_R[0]->materialDiffuse.w > 0.0f ?
				UI_breakHeart_R[0]->materialDiffuse.w -= 0.02f : UI_breakHeart_R[0]->materialDiffuse.w;
		}
		// ハートのイージングの更新
		breakHeart_R_ease[0]->Update();
		// 回転率を変更する
		UI_breakHeart_R[0]->transform.rotation =
			UI_breakHeart_R[0]->transform.rotation > -45.0f ?
			UI_breakHeart_R[0]->transform.rotation - 2.0f : UI_breakHeart_R[0]->transform.rotation;
	}
	if (playerHP <= 0)
	{
		UI_hp[0]->TextureCutout(2, 0);
		// ハーフハートが透明なら不透明に戻す
		if (!heartAlpha_L[0])
		{
			// 半分のハートの透明度を0に
			UI_breakHeart_L[0]->materialDiffuse.w = 1.0f;
			heartAlpha_L[0] = true;
		}
		// すでに不透明なら徐々に透明にする
		else
		{
			UI_breakHeart_L[0]->materialDiffuse.w =
				UI_breakHeart_L[0]->materialDiffuse.w > 0.0f ?
				UI_breakHeart_L[0]->materialDiffuse.w -= 0.02f : UI_breakHeart_L[2]->materialDiffuse.w;
		}
		// ハートのイージングの更新
		breakHeart_L_ease[0]->Update();
		// 回転率を変更する
		UI_breakHeart_L[0]->transform.rotation =
			UI_breakHeart_L[0]->transform.rotation < 45.0f ?
			UI_breakHeart_L[0]->transform.rotation + 2.0f : UI_breakHeart_L[0]->transform.rotation;
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
	gameTime->InitTimer(240, TIMER_MODE::COUNT_DOWN);
	nowTime = 240;
	// プレイヤーの体力を初期化
	playerHP = PLAYER_HP;

	// 位置調整フラグの初期化
	for (int i = 0; i < 2; i++)
	{
		uiTimePositionSet[i] = false;
	}
	// 時間数字テクスチャの再表示
	for (int i = 0; i < 3; i++)
	{
		timeNum[i]->SetActive(true);
		timeNum[i]->transform.position = { 1.59f + (0.151f * i), 0.82f, -0.46f };
	}

	// UIの初期化
	for (int i = 0; i < 3; i++)
	{
		// 切り抜き位置を元に戻す
		UI_hp[i]->TextureCutout(0, 0);
		// ダメージ演出用のハーフハートの初期化
		// 位置の初期化
		UI_breakHeart_L[i]->transform.position = { -1.821f + ((286.0f * 0.00065f + 0.01f) * i), 0.84f, -0.47f };
		UI_breakHeart_R[i]->transform.position = { -1.74f + ((286.0f * 0.00065f + 0.01f) * i), 0.84f, -0.46f };
		// 回転率の初期化
		UI_breakHeart_L[i]->transform.rotation = 0.0f;
		UI_breakHeart_R[i]->transform.rotation = 0.0f;
		// 透明度の初期化
		UI_breakHeart_L[i]->materialDiffuse.w = 0.0f;
		UI_breakHeart_R[i]->materialDiffuse.w = 0.0f;
		// イージングの初期化
		breakHeart_L_ease[i]->Init(&UI_breakHeart_L[i]->transform.position.y, UI_breakHeart_L[i]->transform.position.y - 0.3f, 0.7f, 0, EASE::easeOutBounce);
		breakHeart_R_ease[i]->Init(&UI_breakHeart_R[i]->transform.position.y, UI_breakHeart_R[i]->transform.position.y - 0.3f, 0.7f, 0, EASE::easeOutBounce);
		// 落下フラグの初期化
		heartAlpha_L[i] = false;
		heartAlpha_R[i] = false;
	}
	soundFlameCounter = 0;
}

void CGameManager::Update()
{
	// ステージ番号の設定
	stageNum->TextureCutout(stageNumber, 0);

	// タイマーの更新
	gameTime->Update();

	// スタートが押されたらタイマーを停止
	if (gInput->IsControllerButtonTrigger(XINPUT_GAMEPAD_START))
	{
		gameTime->PauseTimer();
	}

	// 体力UIの管理
	UpdateUIhp();

	// 時間
	nowTime = (int)gameTime->GetTime();
	// 時間を位ごとに格納する
	int temp = nowTime;
	for (int i = 2; i >= 0; i--)
	{
		// 上の桁の数から順番に桁の値を格納していく
		int digit = temp % 10;
		timeRankNum[i] = digit;
		// 格納した数値と同じテクスチャを切り抜く
		timeNum[i]->TextureCutout(timeRankNum[i], 0);
		// 次の桁に移動
		temp /= 10;
	}

	// 桁の位置合わせ
	if (timeRankNum[0] == 0 && timeRankNum[1] == 0)
	{
		timeNum[0]->SetActive(false);
		timeNum[1]->SetActive(false);
		if (!uiTimePositionSet[0])
		{
			timeNum[2]->transform.position.x = timeNum[2]->transform.position.x - 0.083f;
			uiTimePositionSet[0] = true;
		}
	}
	else if (timeRankNum[0] == 0)
	{
		timeNum[0]->SetActive(false);

		if (!uiTimePositionSet[1])
		{
			timeNum[2]->transform.position.x = timeNum[2]->transform.position.x - 0.083f;
			timeNum[1]->transform.position.x = timeNum[1]->transform.position.x - 0.083f;
			uiTimePositionSet[1] = true;
		}
	}

	// ゲームの進行状況に応じて更新処理を変更
	switch (state)
	{
	case GAME_STATE::READY:
		// フェードが終了してからタイマーを開始する
		if (CSceneManager::GetInstance()->GetFadeState() == FADE_STATE::NO_FADE)
		{
			// タイマーの開始
			gameTime->StartTimer();
			// ゲームステートの変更
			state = GAME_STATE::START;
		}
		break;

	case GAME_STATE::START:
		// プレイヤーのHPが0なら
		if (playerHP <= 0)
		{
			//	サウンド停止
			XA_Stop(SOUND_LABEL_STAGE1_BGM);
			XA_Stop(SOUND_LABEL_STAGE2_BGM);
			XA_Stop(SOUND_LABEL_STAGE3_BGM);
			XA_Stop(SOUND_LABEL_FLY);
			//サウンド再生
			XA_Play(SOUND_LABEL_DOWN);
			// 状態をHP0に
			state = GAME_STATE::ZERO_HP;
			// タイマーのストップする
			gameTime->PauseTimer();
		}
		// タイムが0になったなら
		else if (gameTime->GetTimerState() == TIMER_STATE::END)
		{
			// 状態をタイムアップに
			state = GAME_STATE::TIME_UP;
			//	サウンド停止
			XA_Stop(SOUND_LABEL_STAGE1_BGM);
			XA_Stop(SOUND_LABEL_STAGE2_BGM);
			XA_Stop(SOUND_LABEL_STAGE3_BGM);
			XA_Stop(SOUND_LABEL_FLY);
			//サウンド再生
			XA_Play(SOUND_LABEL_DOWN);
		}
		break;

	case GAME_STATE::TIME_UP:
		// フレームをカウント
		soundFlameCounter++;
		// 170フレーム
		if (soundFlameCounter == 170)
		{
			//倒れるサウンド再生
			XA_Play(SOUND_LABEL_GETUP);
		}
		// 200フレーム
		if (soundFlameCounter == 200)
		{
			XA_Play(SOUND_LABEL_GAMEOVER_2);
		}
		break;

	case GAME_STATE::ZERO_HP:
		// フレームをカウント
		soundFlameCounter++;
		// 170フレーム
		if (soundFlameCounter == 170)
		{
			//倒れるサウンド再生
			XA_Play(SOUND_LABEL_GETUP);
		}
		// 200フレーム
		if (soundFlameCounter == 200)
		{
			XA_Play(SOUND_LABEL_GAMEOVER_2);
		}
		break;

	case GAME_STATE::CLEAR:
		// タイマーのストップする
		gameTime->PauseTimer();
		break;

	default:
		break;
	}

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

int CGameManager::GetClearTime()
{
	// タイマーが停止していないなら、クリアしていないとみなし0を返す
	if (gameTime->GetTimerState() != TIMER_STATE::PAUSE)
	{
		return 0;
	}

	// 経過時間を返す
	return (int)gameTime->GetProgressTime();
}
