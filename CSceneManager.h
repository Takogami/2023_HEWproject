#pragma once

#include "TitleScene.h"
#include "StageScene.h"
#include "StageScene2.h"
#include "SelectScene.h"
#include "ResultScene.h"

//	シーンの種類（列挙型）
enum class SCENE_ID
{
	TITLE,
	SELECT,
	STAGE_1,
	STAGE_2,
	RESULT,
};

class CSceneManager
{
private:
	// 唯一のインスタンスを格納するためのポインタ
	static CSceneManager* instance;

	TitleScene* title = nullptr;			//タイトルシーンクラス
	StageScene* stage1 = nullptr;			//ステージシーン1クラス
	StageScene2* stage2 = nullptr;			//ステージシーン2クラス
	SelectScene* select = nullptr;			//セレクトシーンクラス
	ResultScene* result = nullptr;			//リザルトシーンクラス

	CEventManager* eventManager;

	std::list<CScene*> scenes;

	SCENE_ID NowScene = SCENE_ID::TITLE;	//現在のシーンの状態

	CSceneManager();
	~CSceneManager();
	// アプリケーション終了時にコールバックとして呼び出す(シングルトンの解放)
	static void CleanupSingleton();

public:
	// インスタンスを取得するためのメソッド
	static CSceneManager* GetInstance();

	void Update();							//シーンの管理
	void ChangeScene(SCENE_ID _inScene);	//シーンの変更
};

