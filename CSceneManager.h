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

	CGameObject* fade;
	ID3D11Buffer* vertexBuffer;

	SCENE_ID NowScene = SCENE_ID::TITLE;
	SCENE_ID NewScene = SCENE_ID::TITLE;
	SCENE_ID retryLoadScene = SCENE_ID::TITLE;

	// 前回のゲームのクリアタイム
	int prevGameClearTime = 0;

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

	FADE_STATE GetFadeState() { return fadeState; }
};

