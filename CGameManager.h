#pragma once
#include "direct3d.h"
#include <list>

// プレイヤーの体力
#define PLAYER_HP (6)

/* 前方宣言 */
class CTimer;
class CGameObject;
class CEase;

// ゲームの進行状態
enum class GAME_STATE
{
	READY,	// スタート前
	START,	// ゲーム開始(中)
	TIME_UP,// タイムアップ
	ZERO_HP,// プレイヤーのHPが0
	CLEAR,	// クリア
};

class CGameManager
{
private:
	// プレイヤーのHP
	int playerHP = PLAYER_HP;
	// スコア
	int score = 0;
	// ゲームの進行状態
	GAME_STATE state = GAME_STATE::READY;

	// UI用の頂点バッファ
	ID3D11Buffer* vertexBufferUI;

	// スコアボード
	CGameObject* UI_hpBoard;
	// タイマーの背景
	CGameObject* UI_timer;
	// HPのUI
	CGameObject* UI_hp[3];
	// ダメージを受けたときのハート
	CGameObject* UI_breakHeart_R[3];
	CGameObject* UI_breakHeart_L[3];
	// ハートが落ちる演出のイージング
	CEase* breakHeart_R_ease[3];
	CEase* breakHeart_L_ease[3];
	// ハートの透明度を変更したかのフラグ
	bool heartAlpha_R[3] = { false };
	bool heartAlpha_L[3] = { false };

	// 制限時間
	int nowTime = 0;
	int timeRankNum[3];
	// ゲームの時間管理
	CTimer* gameTime;

	// 時間や文字のオブジェクト
	CGameObject* strBg;
	CGameObject* strStage;
	CGameObject* stageNum;
	CGameObject* timeNum[3];
	// 位置セットのフラグ
	bool uiTimePositionSet[2] = { false };

	// オブジェクトのリスト
	std::list<CGameObject*> Objects;
	
	// ステージの番号
	int stageNumber = 1;
	// 時間でサウンドを制御するためのフレームカウンター
	int soundFlameCounter = 0;

	// 唯一のインスタンス
	static CGameManager* instance;

	// コンストラクタ
	CGameManager();
	// デストラクタ
	~CGameManager();

	// 体力UIの更新
	void UpdateUIhp();

	//アプリケーション終了時にコールバックとして呼び出す(シングルトンの解放)
	static void CleanupSingleton();

public:
	// インスタンスの取得
	static CGameManager* GetInstance();

	// 初期化
	void Init();
	// 更新
	void Update();
	// ゲームシステム関連のUIの描画
	void Draw();

	// スコアの加算
	// 引数1 : 加算するスコア
	void AddScore(int addScore);
	// 現在のスコアを取得
	int GetScore() { return score; }
	// ダメージの加算
	// 引数1 : ダメージ値(1~6)
	void AddDamage(int addDamage);
	// ゲームクリアの信号を送る
	void SetGameClear() { state = GAME_STATE::CLEAR; }
	// ステージ番号をセットする
	void SetStageNum(int sNum) { stageNumber = sNum; }
	// ゲームの進行状態を取得
	GAME_STATE GetGameState();

	// クリアタイムの取得
	int GetClearTime();
};

