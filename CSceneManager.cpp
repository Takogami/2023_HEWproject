#include "CSceneManager.h"

// �R���X�g���N�^
CSceneManager::CSceneManager()
{
	title = new TitleScene();	//�^�C�g���V�[����new
	result = new ResultScene();	//���U���g�V�[����new
}

// �f�X�g���N�^
CSceneManager::~CSceneManager()
{
	delete title;
	delete result;
}

// Update & Draw
void CSceneManager::Update()
{
	// �V�[�����Ƃ�Update,Draw�����s
	switch (NowScene)
	{
	// �^�C�g��
	case SCENE_LIST::TITLE:
		title->Update();
		title->Draw();
		break;

	// ���U���g
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
