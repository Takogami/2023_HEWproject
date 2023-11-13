#include "CSceneManager.h"

// コンストラクタ
CSceneManager::CSceneManager()
{
	title = new TitleScene();	//タイトルシーンのnew
	result = new ResultScene();	//リザルトシーンのnew
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
	case SCENE_LIST::TITLE:
		title->Update();
		title->Draw();
		break;

	// リザルト
	case SCENE_LIST::RESULT:
		result->Update();
		result->Draw();
		break;
	}
}

void CSceneManager::ChangeScene(SCENE_LIST _inScene)
{
	NowScene = _inScene;
}
