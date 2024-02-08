#include "CSceneManager.h"
#include "CScene.h"

// CTextureLoader�N���X��static�����o�ϐ��̏�����
CSceneManager* CSceneManager::instance = nullptr;

// �R���X�g���N�^
CSceneManager::CSceneManager()
{
	title = nullptr;
	stage = nullptr;
	result = nullptr;
	stage2 = nullptr;

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
	if (stage != nullptr)
	{
		delete stage;
	}
	if (result != nullptr)
	{
		delete result;
	}
	if (stage2 != nullptr)
	{
		delete stage2;
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
	case SCENE_ID::STAGE_01:
		stage->Update();
		stage->Draw();
		break;

	// ���U���g
	case SCENE_ID::RESULT:
		result->Update();
		result->Draw();
		break;

	// �X�e�[�W02
	case SCENE_ID::STAGE_02:
		stage2->Update();
		stage2->Draw();
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

	case SCENE_ID::STAGE_01:
		// �������݂̃V�[����STAGE_01�Ȃ�ASTAGE_01�V�[�����������
		delete stage;
		stage = nullptr;
		break;

	case SCENE_ID::RESULT:
		// �������݂̃V�[����RESULT�Ȃ�ARESULT�V�[�����������
		delete result;
		result = nullptr;
		break;
	case SCENE_ID::STAGE_02:
		// �������݂̃V�[����STAGE_02�Ȃ�ASTAGE_02�V�[�����������
		delete stage2;
		stage2 = nullptr;
		break;
	}

	// 2. �V�����V�[���̎��ʎq��ݒ肷��
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

	case SCENE_ID::STAGE_01:
		// �����V�����V�[����STAGE_01�Ȃ�A�V����STAGE_01�V�[�����쐬����
		stage = new StageScene();
		break;

	case SCENE_ID::RESULT:
		// �����V�����V�[����RESULT�Ȃ�A�V����RESULT�V�[�����쐬����
		result = new ResultScene();
		break;
	case SCENE_ID::STAGE_02:
		// �����V�����V�[����RESULT�Ȃ�A�V����RESULT�V�[�����쐬����
		stage2 = new Stage2Scene();
		break;
	}
}
