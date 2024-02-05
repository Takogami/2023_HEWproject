//=============================================================================
//
// サウンド処理 [xa2.h]
//
//=============================================================================
#ifndef _XAUDIO2_H_
#define _XAUDIO2_H_

#include <xaudio2.h>
#include <vector>

// サウンドファイル
typedef enum
{
	SOUND_LABEL_FADE = 0,
	SOUND_LABEL_TITLE,
	SOUND_LABEL_STAGE,
	SOUND_LABEL_DORUM,
	SOUND_LABEL_RESULT,
	SOUND_LABEL_DONDON,
	SOUND_LABEL_CLEAR,
	SOUND_LABEL_CURSOR,
	SOUND_LABEL_PRESS,
	SOUND_LABEL_SELECT,
	SOUND_LABEL_BEEP,
	SOUND_LABEL_HIT,
	SOUND_LABEL_HAMMER,
	SOUND_LABEL_BLACK,
	SOUND_LABEL_CLEAN,
	SOUND_LABEL_NOHIT,
	SOUND_LABEL_START,
	SOUND_LABEL_COUNT,
	SOUND_LABEL_END,
	SOUND_LABEL_EVENT,
	SOUND_LABEL_MAX,
} SOUND_LABEL;

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************

// ゲームループ開始前に呼び出すサウンドの初期化処理
HRESULT XA_Initialize(void);

// ゲームループ終了後に呼び出すサウンドの解放処理
void XA_Release(void);

// 引数で指定したサウンドを再生する
void XA_Play(SOUND_LABEL label);

// 引数で指定したサウンドを停止する
void XA_Stop(SOUND_LABEL label);

// 引数で指定したサウンドの再生を再開する
void XA_Resume(SOUND_LABEL label);

#endif
