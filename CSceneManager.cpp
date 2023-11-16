#include "CSceneManager.h"

// CTextureLoader�N���X��static�����o�ϐ��̏�����
CSceneManager* CSceneManager::instance = nullptr;

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

void CSceneManager::CleanupSingleton()
{
	//�C���X�^���X������Ȃ�������
	if (instance)
	{
		delete instance;
		instance = nullptr;
	}
}

CSceneManager* CSceneManager::GetInstance()
{
	// �V���O���g�������݂��Ă��Ȃ��Ȃ琶������
	if (!instance)
	{
		// �V���O���g���̐���
		instance = new CSceneManager();
		//�R�[���o�b�N�Ƃ��ēo�^
		std::atexit(CleanupSingleton);
	}
	//�B��̃C���X�^���X��Ԃ�
	return instance;
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
