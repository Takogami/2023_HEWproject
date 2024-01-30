#pragma once
#include <time.h>

// タイマーの状態
enum class TIMER_STATE
{
	WAIT,
	UPDATE,
	PAUSE,
	END,
};

// カウントアップかカウントダウンか
enum class TIMER_MODE
{
	COUNT_UP,
	COUNT_DOWN,
};

// 
class CTimer
{
private:
	// タイマーの稼働状態
	TIMER_STATE state = TIMER_STATE::WAIT;
	// タイマーのモード
	TIMER_MODE mode;

	// スタートの時間
	time_t startTime;
	// 現在の時間
	time_t nowTime;
	// 経過時間時間
	time_t progressTime;
	// 現在のタイマーで計った時間
	time_t progressCountTime;
	// カウントする時間
	time_t countTime;
	// タイマーのモードに応じての更新処理
	void TimerModeUpdate();

public:
	// タイマーのセット(初期化)
	// 引数1 : カウントする時間 引数2 : モード設定
	void InitTimer(time_t CountTime, TIMER_MODE TimerMode);
	// タイマーの更新
	void Update();
	// タイマーを開始
	void StartTimer() { state = TIMER_STATE::UPDATE; }
	// タイマーを一時停止
	void PauseTimer() { state = TIMER_STATE::PAUSE; }
	// タイマーの再開
	void ResumeTimer();
	// 計った時間を取得
	time_t GetTime() { return progressCountTime; }
	// 経過時間を取得
	time_t GetProgressTime() { return progressTime; }
	// タイマーの状態をを取得
	TIMER_STATE GetTimerState() { return state; };
};

