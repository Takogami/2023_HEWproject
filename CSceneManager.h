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

	TitleScene* title;						//タイトルシーンクラス
	ResultScene* result;					//リザルトシーンクラス

	SCENE_ID NowScene = SCENE_ID::RESULT;	//現在のシーンの状態

public:

	CSceneManager();
	~CSceneManager();

	void Update();							//シーンの管理
	void ChangeScene(SCENE_ID _inScene);	//シーンの変更
};

