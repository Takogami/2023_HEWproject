#include "CSceneManager.h"

// �R���X�g���N�^
CSceneManager::CSceneManager()
{
	title = new TitleScene();	//�^�C�g���V�[����new
	result = new ResultScene();	//���U���g�V�[����new

	// �����V�[���ݒ�
	ChangeScene(SCENE_ID::TITLE);
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
	case SCENE_ID::TITLE:
		title->Update();
		title->Draw();
		break;

	// ���U���g
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
