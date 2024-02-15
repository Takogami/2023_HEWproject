#pragma once

#include "TitleScene.h"
#include "StageScene.h"
#include "StageScene2.h"
#include "StageScene3.h"
#include "StageScene4.h"
#include "SelectScene.h"
#include "ResultScene.h"

//	シーンの種類（列挙型）
enum class SCENE_ID
{
	TITLE,
	SELECT,
	STAGE_1,
	STAGE_2,
	STAGE_3,
	STAGE_4,
	RESULT,
};

enum class FADE_STATE
{
	NO_FADE,
	FADE_IN,
	FADE_OUT,
};

enum class FADE_TYPE
{
	NORMAL,	// 通常フェード
	ERASER,	// 消しゴムフェード
};

class CSceneManager
{
private:
	// 唯一のインスタンスを格納するためのポインタ
	static CSceneManager* instance;

	TitleScene* title = nullptr;			//タイトルシーンクラス
	StageScene* stage1 = nullptr;			//ステージシーン1クラス
	StageScene2* stage2 = nullptr;			//ステージシーン2クラス
	StageScene3* stage3 = nullptr;			//ステージシーン3クラス
	StageScene4* stage4 = nullptr;			//ステージシーン4クラス
	SelectScene* select = nullptr;			//セレクトシーンクラス
	ResultScene* result = nullptr;			//リザルトシーンクラス

	CGameManager* gameManager;

	CGameObject* fade;					// 通常フェード用ポリゴン
	CGameObject* fade_eraser;			// 消しゴムフェード用ポリゴン
	int fade_eraser_counter = 0;		// 消しゴムのフェード時間を計測
	const int fade_eraser_flame = 80;	// 消しゴムのフェードにかける時間

	ID3D11Buffer* vertexBuffer;

	SCENE_ID NowScene = SCENE_ID::TITLE;
	SCENE_ID NewScene = SCENE_ID::TITLE;
	SCENE_ID retryLoadScene = SCENE_ID::TITLE;

	FADE_STATE fadeState = FADE_STATE::NO_FADE;
	FADE_TYPE fadeType = FADE_TYPE::NORMAL;

	CSceneManager();
	~CSceneManager();
	// アプリケーション終了時にコールバックとして呼び出す(シングルトンの解放)
	static void CleanupSingleton();

public:
	// インスタンスを取得するためのメソッド
	static CSceneManager* GetInstance();

	void Update();							//シーンの管理
	void ChangeScene(SCENE_ID _inScene, FADE_TYPE fadeType = FADE_TYPE::NORMAL);	//シーンの変更

	FADE_STATE GetFadeState() { return fadeState; }
};

