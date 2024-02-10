#pragma once

#include "TitleScene.h"
#include "StageScene.h"
#include "StageScene2.h"
#include "SelectScene.h"
#include "ResultScene.h"

// シーンの種類（列挙型）
enum class SCENE_ID
{
	TITLE,
	SELECT,
	STAGE_1,
	STAGE_2,
	RESULT,
};

// フェード状態
enum class FADE_STATE
{
	NO_FADE,
	FADE_IN,
	FADE_OUT,
};

class CSceneManager
{
private:
	// 唯一のインスタンスを格納するためのポインタ
	static CSceneManager* instance;

	TitleScene* title = nullptr;			//タイトルシーン
	StageScene* stage1 = nullptr;			//ステージシーン1
	StageScene2* stage2 = nullptr;			//ステージシーン2
	SelectScene* select = nullptr;			//セレクトシーン
	ResultScene* result = nullptr;			//リザルトシーン

	// フェード用
	CGameObject* fade;
	ID3D11Buffer* vertexBuffer;

	CGameManager* GameManager;

	SCENE_ID NowScene = SCENE_ID::TITLE;		// 現在のシーンの状態
	SCENE_ID NewScene = SCENE_ID::TITLE;		// 新しいのシーン
	SCENE_ID retryLoadScene = SCENE_ID::TITLE;	// リトライ時に読み込むシーン

	FADE_STATE fadeState = FADE_STATE::NO_FADE;

	CSceneManager();
	~CSceneManager();
	// アプリケーション終了時にコールバックとして呼び出す(シングルトンの解放)
	static void CleanupSingleton();

public:
	// インスタンスを取得するためのメソッド
	static CSceneManager* GetInstance();

	void Update();							//シーンの管理
	void ChangeScene(SCENE_ID _inScene);	//シーンの変更

	// フェードステートを返す
	FADE_STATE GetFadeState() { return fadeState; }
};

