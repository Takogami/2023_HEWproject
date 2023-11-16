#include "CSceneManager.h"

// コンストラクタ
CSceneManager::CSceneManager()
{
	title = new TitleScene();	//タイトルシーンのnew
	result = new ResultScene();	//リザルトシーンのnew

	// 初期シーン設定
	ChangeScene(SCENE_ID::TITLE);
}

// デストラクタ
CSceneManager::~CSceneManager()
{
	delete title;
	delete result;
}

// Update & Draw
void CSceneManager::Update()
{
	// シーンごとのUpdate,Drawを実行
	switch (NowScene)
	{
	// タイトル
	case SCENE_ID::TITLE:
		title->Update();
		title->Draw();
		break;

	// リザルト
	case SCENE_ID::RESULT:
		result->Update();
		result->Draw();
		break;
	}
}

void CSceneManager::ChangeScene(SCENE_ID _inScene)
{
	NowScene = _inScene;
}
