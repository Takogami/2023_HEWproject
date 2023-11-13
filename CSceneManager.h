#pragma once
#include "CTerrainLoader.h"
#include "TitleScene.h"
#include "ResultScene.h"

//	シーンの種類（列挙型）
enum class SCENE_LIST
{
	TITLE,
	STAGE_01,
	RESULT,
};

class CSceneManager
{
private:

	TitleScene* title;						//タイトルシーンクラス
	ResultScene* result;					//リザルトシーンクラス

	SCENE_LIST NowScene = SCENE_LIST::RESULT;	//現在のシーンの状態

public:

	CSceneManager();
	~CSceneManager();

	void Update();							//シーンの管理
	void ChangeScene(SCENE_LIST _inScene);	//シーンの変更
};

