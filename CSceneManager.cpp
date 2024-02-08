#include "CSceneManager.h"
#include "CScene.h"

// CTextureLoader�N���X��static�����o�ϐ��̏�����
CSceneManager* CSceneManager::instance = nullptr;

// �R���X�g���N�^
CSceneManager::CSceneManager()
{
	// �f�t�H���g�̃V�[�������������܂�
	ChangeScene(SCENE_ID::TITLE);

	// �t�F�[�h�p�I�u�W�F�N�g�̎��̉�
	fade = new CGameObject(vertexBuffer,CTextureLoader::GetInstance()->GetTex(TEX_ID::WINDRIGHT_POS));
	fade->transform.scale = {1920.0f * 0.0021f, 1080.0f * 0.0021f, 1.0f};
	// �őO�ʂɕ\��
	fade->transform.position.z = -0.5f;

	// GameManager�̗B��̃C���X�^���X�𐶐�
	GameManager = CGameManager::GetInstance();
}

// �f�X�g���N�^
CSceneManager::~CSceneManager()
{
	// �t�F�[�h�p�̒��_�o�b�t�@�̉��
	SAFE_RELEASE(vertexBuffer);
	delete fade;
	
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
	//�t�F�[�h�C����
	if (fadeState == FADE_STATE::FADE_IN)
	{
		//�|���S�������񂾂񓧖���
		fade->materialDiffuse.w -= 0.01f;

		//���S�ɓ����ɂȂ������H
		if (fade->materialDiffuse.w <= 0.0f)
		{
			fadeState = FADE_STATE::NO_FADE;	//�t�F�[�h��Ԃ��u�Ȃ��v�ɐݒ�
		}
	}
	//�t�F�[�h�A�E�g��
	else if (fadeState == FADE_STATE::FADE_OUT)
	{
		//�|���S�������񂾂�s������
		fade->materialDiffuse.w += 0.01f;

		//���S�ɕs�����ɂȂ������H
		if (fade->materialDiffuse.w >= 1.0f)
		{
			//���ۂɉ�ʂ�؂�ւ���
			ChangeScene(NewScene);
		}
	}

	D3D_ClearScreen();

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

	// �Ō�Ƀt�F�[�h�p�I�u�W�F�N�g��`�悷��
	fade->Draw();

	// ��ʍX�V
	D3D_UpdateScreen();
}

void CSceneManager::ChangeScene(SCENE_ID _inScene)
{
	// ��ʑJ�ڊJ�n��
	if (NewScene != _inScene)
	{
		// �J�ڐ��ʂ�ۑ�
		NewScene = _inScene;
		// �t�F�[�h�A�E�g���J�n
		fadeState = FADE_STATE::FADE_OUT;
		// ���g���C���ɓǂݍ��ރV�[���Ƃ��Č��݂̃V�[����ۑ�����
		retryLoadScene = NowScene;
	}
	// �t�F�[�h�A�E�g�I���Ŏ��ۂɃV�[����؂�ւ���
	else
	{
		// ��ʂ̐؂�ւ�
		NowScene = _inScene;
		// �؂�ւ����̂Ńt�F�[�h�C���̊J�n
		fadeState = FADE_STATE::FADE_IN;

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
}
