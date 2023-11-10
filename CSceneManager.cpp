#include "CSceneManager.h"

CSceneManager::CSceneManager()
{
	//コンストラクタ
	titleS = new TitleScene();
	resultS = new ResultScene();
	NowScene = SceneList:: TITLE;
}

CSceneManager::~CSceneManager()
{
	//デスストラクタ

}

void CSceneManager::Update()
{

	switch (NowScene)
	{
	case SceneList::TITLE:
		titleS->Draw();
		break;
	case SceneList::RESULT:
		resultS->Draw();
		break;
	}
}

void CSceneManager::ChangeScene(SceneList _inScene)
{
	NowScene = _inScene;
}

void CSceneManager::Exit()
{
	//終了処理
}
