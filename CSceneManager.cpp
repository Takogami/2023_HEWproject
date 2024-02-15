#include "CSceneManager.h"
#include "CScene.h"

// �V�[������̊ȈՉ�
#define RELEASE_SCENE(scene){ if (scene != nullptr){ delete scene; } }

// CTextureLoader�N���X��static�����o�ϐ��̏�����
CSceneManager* CSceneManager::instance = nullptr;

// �R���X�g���N�^
CSceneManager::CSceneManager()
{
	// �f�t�H���g�̃V�[�������������܂�
	ChangeScene(SCENE_ID::TITLE);

	// �t�F�[�h�p�I�u�W�F�N�g�̎��̉�
	fade = new CGameObject(vertexBuffer, CTextureLoader::GetInstance()->GetTex(TEX_ID::FADE));
	fade->transform.scale = { 1920.0f * 0.0021f, 1080.0f * 0.0021f, 1.0f };
	fade->transform.position.z = -0.49f;

	fade_eraser = new CGameObject(vertexBuffer, CTextureLoader::GetInstance()->GetTex(TEX_ID::FADE_ANIM), { 0.04761905f, 0.5f });
	fade_eraser->transform.scale = { 1920.0f * 0.0022f, 1080.0f * 0.0022f, 1.0f };
	fade_eraser->transform.position.z = -0.5f;
	fade_eraser->InitAnimParameter(false, 21, 2, ANIM_PATTERN::FADEOUT_ANIM, 0.32f);
	fade_eraser->SetActive(false);
}

// �f�X�g���N�^
CSceneManager::~CSceneManager()
{
	// �t�F�[�h�p�̒��_�o�b�t�@�ƃI�u�W�F�N�g�̉��
	SAFE_RELEASE(vertexBuffer);
	delete fade;
	delete fade_eraser;

	// �e�V�[���̉��
	RELEASE_SCENE(title);
	RELEASE_SCENE(select);
	RELEASE_SCENE(stage1);
	RELEASE_SCENE(stage2);
	RELEASE_SCENE(stage3);
	RELEASE_SCENE(stage4);
	RELEASE_SCENE(result);
}

void CSceneManager::CleanupSingleton()
{
	// �C���X�^���X������Ȃ�������
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
	// �t�F�[�h���͓��͂��󂯕t���Ȃ��悤�ɐݒ�
	if (fadeState != FADE_STATE::NO_FADE)
	{
		// ���͂����b�N
		gInput->InputLock(true);
	}
	else
	{
		// ���̓��b�N������
		gInput->InputLock(false);
	}

	// �t�F�[�h�C��
	if (fadeState == FADE_STATE::FADE_IN)
	{
		if (fadeType == FADE_TYPE::ERASER)
		{
			if (fade_eraser_counter <= 0.0f)
			{
				//	�T�E���h�Đ�
				XA_Play(SOUND_LABEL_FADEIN);
			}

			// �����S���t�F�[�h�C�����J�n�����̂Ōv���J�n
			fade_eraser_counter++;

			// �w��̃t���[�������o�߂��Ă���Ȃ�
			if (fade_eraser_counter > fade_eraser_flame)
			{
				// �t�F�[�h�̏�Ԃ��t�F�[�h������Ԃɐݒ�
				fadeState = FADE_STATE::NO_FADE;
				// �J�E���^�[��0�ɖ߂�
				fade_eraser_counter = 0;
				// �����S���̃t�F�[�h�A�E�g�̃A�j���[�V�����ɖ߂�
				fade_eraser->SetAnimationPattern(ANIM_PATTERN::FADEOUT_ANIM);
				// �A�j���[�V�������~
				fade_eraser->StopAnimation();
			}
		}
		else
		{
			// �t�F�[�h�p�|���S�������񂾂񓧖���
			fade->materialDiffuse.w -= 0.01f;
			// �t�F�[�h�p�|���S�������S�ɓ����Ȃ�
			if (fade->materialDiffuse.w <= 0.0f)
			{
				// �t�F�[�h�̏�Ԃ��t�F�[�h������Ԃɐݒ�
				fadeState = FADE_STATE::NO_FADE;
			}
		}
	}
	// �t�F�[�h�A�E�g
	else if (fadeState == FADE_STATE::FADE_OUT)
	{
		if (fadeType == FADE_TYPE::ERASER)
		{
			if (fade_eraser_counter <= 0.0f)
			{
				//	�T�E���h�Đ�
				XA_Play(SOUND_LABEL_FADEOUT);
			}

			fade_eraser->SetActive(true);
			fade_eraser->PlayAnimation();
			// �����S���t�F�[�h�A�E�g���J�n�����̂Ōv���J�n
			fade_eraser_counter++;

			// �w��̃t���[�������o�߂��Ă���Ȃ�
			if (fade_eraser_counter > fade_eraser_flame)
			{
				// �ݒ肳��Ă������̃V�[���ɐ؂�ւ���
				ChangeScene(NewScene);
				// �����S���̃t�F�[�h�C���̃A�j���[�V�����ɐ؂�ς���
				fade_eraser->SetAnimationPattern(ANIM_PATTERN::FADEIN_ANIM);
				// �J�E���^�[��0�ɖ߂�
				fade_eraser_counter = 0;
			}
		}
		else
		{
			// �t�F�[�h�p�|���S�������񂾂�s������
			fade->materialDiffuse.w += 0.01f;
			// �t�F�[�h�p�|���S�������S�ɕs�����Ȃ�
			if (fade->materialDiffuse.w >= 1.0f)
			{
				// �ݒ肳��Ă������̃V�[���ɐ؂�ւ���
				ChangeScene(NewScene);
			}
		}
	}

	// ��ʂ��N���A
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

		// �X�e�[�W03
	case SCENE_ID::STAGE_3:
		stage3->Update();
		stage3->Draw();
		break;

		// �X�e�[�W04
	case SCENE_ID::STAGE_4:
		stage4->Update();
		stage4->Draw();
		break;

	// ���U���g
	case SCENE_ID::RESULT:
		result->Update();
		result->Draw();
		break;
	}

	// �t�F�[�h�p�|���S���̕`��
	fade->Draw();
	fade_eraser->Update();
	fade_eraser->Draw();

	// ��ʂ̍X�V
	D3D_UpdateScreen();
}

void CSceneManager::ChangeScene(SCENE_ID _inScene, FADE_TYPE fadeType)
{
	if (NewScene != _inScene)
	{
		NewScene = _inScene;
		fadeState = FADE_STATE::FADE_OUT;
		this->fadeType = fadeType;
		// ���g���C���ɓǂݍ��ރV�[���Ƃ��Č��݂̃V�[����ۑ�����
		retryLoadScene = NowScene;
	}
	else
	{
		// �X�e�[�W��ǂݍ���ł����Ȃ�������
		CScene::DestroyStage();
		// �t�F�[�h�C����ݒ�
		fadeState = FADE_STATE::FADE_IN;
		// �������̑O�ɃN���A�^�C�����󂯎��
		prevGameClearTime = CGameManager::GetInstance()->GetClearTime();
		// �Q�[���}�l�[�W����������
		CGameManager::GetInstance()->Init();

		// 1. ���݂̃V�[���Ɋ֘A���郊�\�[�X���������
		switch (_inScene)
		{
		case SCENE_ID::TITLE:
			// �������݂̃V�[����TITLE�Ȃ�ATITLE�V�[�����������
			delete title;
			title = nullptr;
			break;

		case SCENE_ID::SELECT:
			// �������݂̃V�[����SELECT�Ȃ�ASELECT�V�[�����������
			//	�T�E���h�Đ��̒�~
			XA_Stop(SOUND_LABEL_TITLEBGM);
			delete select;
			select = nullptr;
			break;

		case SCENE_ID::STAGE_1:
			// �������݂̃V�[����STAGE_01�Ȃ�ASTAGE_01�V�[�����������
			delete stage1;
			stage1 = nullptr;
			break;

		case SCENE_ID::STAGE_2:
			// �������݂̃V�[����STAGE_2�Ȃ�ASTAGE_2�V�[�����������
			delete stage2;
			stage2 = nullptr;
			break;

		case SCENE_ID::STAGE_3:
			// �������݂̃V�[����STAGE_3�Ȃ�ASTAGE_3�V�[�����������
			delete stage3;
			stage3 = nullptr;
			break;

		case SCENE_ID::STAGE_4:
			// �������݂̃V�[����STAGE_4�Ȃ�ASTAGE_4�V�[�����������
			delete stage4;
			stage4 = nullptr;
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
			XA_Play(SOUND_LABEL_TITLEBGM);
			break;

		case SCENE_ID::STAGE_1:
			// �����V�����V�[����STAGE_01�Ȃ�A�V����STAGE_01�V�[�����쐬����
			stage1 = new StageScene();
			break;

		case SCENE_ID::STAGE_2:
			// �����V�����V�[����TAGE_2�Ȃ�A�V����STAGE_2�V�[�����쐬����
			stage2 = new StageScene2();
			break;

		case SCENE_ID::STAGE_3:
			// �����V�����V�[����TAGE_3�Ȃ�A�V����STAGE_3�V�[�����쐬����
			stage3 = new StageScene3();
			break;

		case SCENE_ID::STAGE_4:
			// �����V�����V�[����TAGE_4�Ȃ�A�V����STAGE_4�V�[�����쐬����
			stage4 = new StageScene4();
			break;

		case SCENE_ID::RESULT:
			// �����V�����V�[����RESULT�Ȃ�A�V����RESULT�V�[�����쐬����
			result = new ResultScene();
			// �O�̃V�[�������U���g�V�[���ɐݒ�
			result->SetPrevStage((int)retryLoadScene);
			// �N���A�^�C����n��
			//result->SetClearTime(prevGameClearTime);
			break;
		}
	}
}
