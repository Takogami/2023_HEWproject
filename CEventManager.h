#pragma once

// プレイヤーの体力
#define PLAYER_HP (6)

/* 前方宣言 */
class CTimer;

// ゲームの進行状態
enum class GAME_STATE
{
	READY,	// スタート前
	START,	// ゲーム開始(中)
	TIME_UP,// タイムアップ
	ZERO_HP,// プレイヤーのHPが0
};

class CEventManager
{
private:
	// ゲームの時間管理
	CTimer* gameTime;
	// プレイヤーのHP
	int playerHP = PLAYER_HP;
	// スコア
	int score = 0;
	// ゲームの進行状態
	GAME_STATE state = GAME_STATE::READY;

	// 唯一のインスタンス
	static CEventManager* instance;

	// コンストラクタ
	CEventManager();
	// デストラクタ
	~CEventManager();
	//アプリケーション終了時にコールバックとして呼び出す(シングルトンの解放)
	static void CleanupSingleton();

public:
	// インスタンスの取得
	static CEventManager* GetInstance();

	// 初期化
	void Init();
	// 更新
	void Update();

	// スコアの加算
	// 引数1 : 加算するスコア
	void AddScore(int addScore);

	// ゲームの進行状態を取得
	GAME_STATE GetGameState();
};

