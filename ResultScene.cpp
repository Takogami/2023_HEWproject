#include "ResultScene.h"
#include "CSceneManager.h"

ResultScene::ResultScene()
{
	// �J�����I�u�W�F�N�g�̎��̉�
	Cam = new CCamera;

	GameOverObj = new CGameObject(vertexBufferObject, CTextureLoader::GetInstance()->GetTex(TEX_ID::GAMEOVER));
	Objects.push_back(GameOverObj);
	GameOverObj->transform.position = { -0.5f, 0.0f, 0.5f };
	GameOverObj->transform.scale = { 512.0f * 0.0045f, 512.0f * 0.0045f, 1.0f };

	retry = new CGameObject(vertexBufferObject, CTextureLoader::GetInstance()->GetTex(TEX_ID::BOARD));
	// �I�u�W�F�N�g�����X�g�ɓo�^
	Objects.push_back(retry);
	retry->transform.scale = { 1100.0f * 0.0007f, 447.0f * 0.0007f, 1.0f };;
	retry->transform.position = { 1.0f, 0.2f };

	goToSelect = new CGameObject(vertexBufferObject, CTextureLoader::GetInstance()->GetTex(TEX_ID::BOARD));
	// �I�u�W�F�N�g�����X�g�ɓo�^
	Objects.push_back(goToSelect);
	goToSelect->transform.scale = { 1100.0f * 0.0007f, 447.0f * 0.0007f, 1.0f };
	goToSelect->transform.position = { 1.0f, -0.1f };

	goToTitle = new CGameObject(vertexBufferObject, CTextureLoader::GetInstance()->GetTex(TEX_ID::BOARD));
	// �I�u�W�F�N�g�����X�g�ɓo�^
	Objects.push_back(goToTitle);
	goToTitle->transform.scale = { 1100.0f * 0.0007f, 447.0f * 0.0007f, 1.0f };
	goToTitle->transform.position = { 1.0f, -0.4f };

	// �J�[�\���̎��̉��Ə�����
	cursor = new CCursor(vertexBufferObject, CTextureLoader::GetInstance()->GetTex(TEX_ID::CURSOR));
	// �I�u�W�F�N�g�����X�g�ɓo�^
	Objects.push_back(cursor);
	cursor->transform.scale = { 186.0f * 0.0017f, 54.0f * 0.0017f, 1.0f };
	cursor->transform.position = { 0.524f, 0.2f, -0.2f };
	cursor->transform.rotation = -30.0f;
	cursor->Init({ cursor->transform.position.x, cursor->transform.position.y });

	selectEaseX = new CEase;
	selectEaseY = new CEase;
}

ResultScene::~ResultScene()
{
	SAFE_RELEASE(vertexBufferObject);

	// �e�I�u�W�F�N�g�̃��������
	for (auto it = Objects.begin(); it != Objects.end(); it++)
	{
		delete (*it);
	}

	// �J�����I�u�W�F�N�g�̍폜
	delete Cam;
}

void ResultScene::SetPrevStage(int prev)
{
	prevScene = prev;
}


void ResultScene::Update()
{
	// ���ʂɉ����čX�V������ς���
	switch (state)
	{
	case RESULT_STATE::GAMEOVER:
		// �Q�[���I�[�o�[��ʂ̍X�V
		UpdateGameOver();
		break;

	case RESULT_STATE::CLEAR:
		// �N���A��ʂ̍X�V
		UpdateClear();
		break;

	default:

		break;
	}

	// �e�I�u�W�F�N�g�̕`��
	for (auto it = Objects.begin(); it != Objects.end(); it++)
	{
		(*it)->Update();
	}
}

void ResultScene::UpdateClear()
{
}

void ResultScene::UpdateGameOver()
{
	// �O��̃V�[�����烊�g���C�œǂݍ��ރV�[��������
	// int�^�Őݒ肳�ꂽ���̂�SCENE_ID�^�ɕϊ�����
	SCENE_ID loadScene = (SCENE_ID)prevScene;

	// �J�[�\���̓��͏��������s
	cursor->CursorInput();

	// CCursor�ł̗񋓌^��Scene���擾����
	cursorPoint = (CCursor_PointResult)cursor->GetCursorPoint();

	if (gInput->IsControllerButtonTrigger(XINPUT_GAMEPAD_B) || gInput->GetKeyTrigger(VK_RETURN))
	{
		// �J�[�\���̃|�C���g�ʒu�őJ�ڐ�̃V�[����ύX
		switch (cursorPoint)
		{
		case CCursor_PointResult::RETRY:	// �R���e�B�j���[
			// �O��̃X�e�[�W�ɑJ�ڂ���
			switch (loadScene)
			{
			case SCENE_ID::STAGE_1:
				CSceneManager::GetInstance()->ChangeScene(SCENE_ID::STAGE_1);
				break;

			case SCENE_ID::STAGE_2:
				CSceneManager::GetInstance()->ChangeScene(SCENE_ID::STAGE_2);
				break;

			default:
				break;
			}
			break;

		case CCursor_PointResult::SELECT:	// �Z���N�g�ɖ߂�
			CSceneManager::GetInstance()->ChangeScene(SCENE_ID::SELECT);
			break;

		case CCursor_PointResult::TITLE:	// �^�C�g���ɖ߂�
			CSceneManager::GetInstance()->ChangeScene(SCENE_ID::TITLE);
			break;

		default:
			break;
		}
	}

	// �J�[�\���ʒu�ɉ����đ傫����ύX����
	switch (cursorPoint)
	{
	case CCursor_PointResult::RETRY:
		// �I�����ꂽ�Ȃ�A�{�^���̃C�[�W���O���N��
		if (selectFlg)
		{
			// �C�[�W���O�̍X�V
			selectEaseX->Update();
			selectEaseY->Update();
			// ���̑傫���ɖ߂�C�[�W���O��ݒ肷��
			if (selectEaseX->GetState() == STATE::END && !selectEnd)
			{
				// ���̑傫����ݒ�
				selectEaseX->Init(&retry->transform.scale.x, 1100.0f * 0.0007f, 0.1f, 0, EASE::easeOutCubic);
				selectEaseY->Init(&retry->transform.scale.y, 447.0f * 0.0007f, 0.1f, 0, EASE::easeOutCubic);
				// �t���O�𗧂Ăē�d�ŏ��������s���Ȃ��悤�ɂ���
				selectEnd = true;
			}
		}
		else
		{
			retry->transform.scale = { 1100.0f * 0.0007f, 447.0f * 0.0007f, 1.0f };
		}
		retry->materialDiffuse.w = 1.0f;
		goToSelect->transform.scale = { 1100.0f * 0.0006f, 447.0f * 0.0006f, 1.0f };
		goToSelect->materialDiffuse.w = 0.5f;
		goToTitle->transform.scale = { 1100.0f * 0.0006f, 447.0f * 0.0006f, 1.0f };
		goToTitle->materialDiffuse.w = 0.5f;
		break;

	case CCursor_PointResult::SELECT:
		goToSelect->transform.scale = { 1100.0f * 0.0007f, 447.0f * 0.0007f, 1.0f };
		goToSelect->materialDiffuse.w = 1.0f;
		retry->transform.scale = { 1100.0f * 0.0006f, 447.0f * 0.0006f, 1.0f };
		retry->materialDiffuse.w = 0.5f;
		goToTitle->transform.scale = { 1100.0f * 0.0006f, 447.0f * 0.0006f, 1.0f };
		goToTitle->materialDiffuse.w = 0.5f;
		break;

	case CCursor_PointResult::TITLE:
		goToTitle->transform.scale = { 1100.0f * 0.0007f, 447.0f * 0.0007f, 1.0f };
		goToTitle->materialDiffuse.w = 1.0f;
		retry->transform.scale = { 1100.0f * 0.0006f, 447.0f * 0.0006f, 1.0f };
		retry->materialDiffuse.w = 0.5f;
		goToSelect->transform.scale = { 1100.0f * 0.0006f, 447.0f * 0.0006f, 1.0f };
		goToSelect->materialDiffuse.w = 0.5f;
		break;

	default:
		break;
	}
}

void ResultScene::Draw()
{
	// �e�I�u�W�F�N�g�̕`��
	for (auto it = Objects.begin(); it != Objects.end(); it++)
	{
		(*it)->Draw();
	}
}
