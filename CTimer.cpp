#include "CTimer.h"

void CTimer::InitTimer(time_t CountTime, TIMER_MODE TimerMode)
{
    // 各パラメータの設定
    countTime = CountTime;
    mode = TimerMode;

    // 初期化
    state = TIMER_STATE::WAIT;
    startTime = time(NULL);

    // モードに合わせて初期値を変更
    if (mode == TIMER_MODE::COUNT_DOWN)
    {
        progressCountTime = countTime;
    }
    else
    {
        progressCountTime = 0;
    }
    progressTime = 0;
}

void CTimer::Update()
{
    // 
    switch (state)
    {
        // 開始待ち
    case TIMER_STATE::WAIT:
        // スタートの時間を取得し続ける
        startTime = time(NULL);
        break;

        // 動作中
    case TIMER_STATE::UPDATE:
        // 各モードに応じた更新処理を行う
        TimerModeUpdate();
        break;

        // 1時停止中
    case TIMER_STATE::PAUSE:
        break;

        // 終了
    case TIMER_STATE::END:
        break;
    }
}

void CTimer::ResumeTimer()
{
    if (state == TIMER_STATE::PAUSE)
    {
        // 一時停止中の経過時間を計算し、開始時間を調整する
        // 一時停止中の時間
        time_t pauseDuration = time(NULL) - nowTime;
        // 開始時間を調整
        startTime += pauseDuration;
        // タイマーを再開
        state = TIMER_STATE::UPDATE;
    }
}

void CTimer::TimerModeUpdate()
{
    switch (mode)
    {
        // カウントアップ
    case TIMER_MODE::COUNT_UP:

        // 現在の時間を取得
        nowTime = time(NULL);
        // 経過時間を計算
        progressTime = nowTime - startTime;
        // 計った時間を保存
        progressCountTime = progressTime;

        // 設定された時間経過したなら終了状態にする
        if (progressCountTime >= countTime)
        {
            state = TIMER_STATE::END;
        }
        break;

        // カウントダウン
    case TIMER_MODE::COUNT_DOWN:

        // 現在の時間を取得
        nowTime = time(NULL);
        // 経過時間を計算
        progressTime = nowTime - startTime;

        // 計った時間を保存
        // 指定された時間から経過時間を引くことでカウントダウン
        progressCountTime = countTime - progressTime;

        // 設定された時間経過したなら終了状態にする
        if (progressCountTime <= 0)
        {
            state = TIMER_STATE::END;
            // 0以下ならないように調整
            progressCountTime = 0;
        }
        break;
    }
}