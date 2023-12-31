#pragma once

#include "TitleScene.h"
#include "ResultScene.h"

//	シーンの種類（列挙型）
enum class SCENE_ID
{
	TITLE,
	STAGE_01,
	RESULT,
};

class CSceneManager
{
private:
	// 唯一のインスタンスを格納するためのポインタ
	static CSceneManager* instance;

	TitleScene* title;						//タイトルシーンクラス
	ResultScene* result;					//リザルトシーンクラス

	SCENE_ID NowScene = SCENE_ID::RESULT;	//現在のシーンの状態

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

