#include "CSceneManager.h"

CSceneManager::CSceneManager()
{
	//�R���X�g���N�^
	titleS = new TitleScene();
	resultS = new ResultScene();
	NowScene = SceneList:: TITLE;
}

CSceneManager::~CSceneManager()
{
	//�f�X�X�g���N�^

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
	//�I������
}
