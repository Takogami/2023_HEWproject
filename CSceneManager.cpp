#include "CSceneManager.h"
#include "CScene.h"

// CTextureLoader�N���X��static�����o�ϐ��̏�����
CSceneManager* CSceneManager::instance = nullptr;

// �R���X�g���N�^
CSceneManager::CSceneManager()
{
	// �f�t�H���g�̃V�[�������������܂�
	ChangeScene(SCENE_ID::TITLE);
}

// �f�X�g���N�^
CSceneManager::~CSceneManager()
{
	// �e�V�[���̉��
	if (title != nullptr)
	{
		delete title;
	}
	if (select != nullptr)
	{
		delete select;
	}
	if (stage1 != nullptr)
	{
		delete stage1;
	}
	if (stage2 != nullptr)
	{
		delete stage2;
	}
	if (result != nullptr)
	{
		delete result;
	}
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

	// �X�e�[�W�I�����
	case SCENE_ID::SELECT:
		select->Update();
		select->Draw();
		break;

	// �X�e�[�W01
	case SCENE_ID::STAGE_1:
		stage1->Update();
		stage1->Draw();
		break;

	// �X�e�[�W02
	case SCENE_ID::STAGE_2:
		stage2->Update();
		stage2->Draw();
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
	// 1. ���݂̃V�[���Ɋ֘A���郊�\�[�X���������

	// �X�e�[�W��ǂݍ���ł����Ȃ�������
	CScene::DestroyStage();

	switch (_inScene)
	{
	case SCENE_ID::TITLE:
		// �������݂̃V�[����TITLE�Ȃ�ATITLE�V�[�����������
		delete title;
		title = nullptr;
		break;

	case SCENE_ID::SELECT:
		// �������݂̃V�[����SELECT�Ȃ�ASELECT�V�[�����������
		delete select;
		select = nullptr;
		break;

	case SCENE_ID::STAGE_1:
		// �������݂̃V�[����STAGE_01�Ȃ�ASTAGE_01�V�[�����������
		delete stage1;
		stage1 = nullptr;
		break;

	case SCENE_ID::STAGE_2:
		// �������݂̃V�[����RESULT�Ȃ�ARESULT�V�[�����������
		delete stage2;
		stage2 = nullptr;
		break;

	case SCENE_ID::RESULT:
		// �������݂̃V�[����RESULT�Ȃ�ARESULT�V�[�����������
		delete result;
		result = nullptr;
		break;
	}

	// 2. �V�����V�[���̎��ʎq��ݒ肷��
	// ���g���C���ɓǂݍ��ރV�[���Ƃ��Č��݂̃V�[����ۑ�����
	SCENE_ID retryLoadScene = NowScene;
	NowScene = _inScene;

	// 3. �V�����V�[���̃��\�[�X���쐬���ݒ肷��
	switch (NowScene)
	{
	case SCENE_ID::TITLE:
		// �����V�����V�[����TITLE�Ȃ�A�V����TITLE�V�[�����쐬����
		title = new TitleScene();
		break;

	case SCENE_ID::SELECT:
		// �����V�����V�[����SELECT�Ȃ�A�V����SELECT�V�[�����쐬����
		select = new SelectScene();
		break;

	case SCENE_ID::STAGE_1:
		// �����V�����V�[����STAGE_01�Ȃ�A�V����STAGE_01�V�[�����쐬����
		stage1 = new StageScene();
		break;

	case SCENE_ID::STAGE_2:
		// �����V�����V�[����RESULT�Ȃ�A�V����RESULT�V�[�����쐬����
		stage2 = new StageScene2();
		break;

	case SCENE_ID::RESULT:
		// �����V�����V�[����RESULT�Ȃ�A�V����RESULT�V�[�����쐬����
		result = new ResultScene();
		// �O�̃V�[�������U���g�V�[���ɐݒ�
		result->SetPrevStage((int)retryLoadScene);
		break;
	}
}
