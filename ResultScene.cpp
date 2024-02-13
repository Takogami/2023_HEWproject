#include "ResultScene.h"
#include "CSceneManager.h"

ResultScene::ResultScene()
{
	// �J�����I�u�W�F�N�g�̎��̉�
	Cam = new CCamera;

	/*---------------�Q�[���I�[�o�[��ʂ̃I�u�W�F�N�g-----------------------*/
	bg = new CGameObject(vertexBufferObject, CTextureLoader::GetInstance()->GetTex(TEX_ID::WINDRIGHT_POS));
	Objects.push_back(bg);
	bg->transform.scale = { 1920.0f * 0.0021f, 1080.0f * 0.0021f, 1.0f };
	bg->transform.position.z = 0.4f;
	bg->SetActive(false);

	GameOverObj = new CGameObject(vertexBufferObject, CTextureLoader::GetInstance()->GetTex(TEX_ID::GAMEOVER));
	Objects.push_back(GameOverObj);
	GameOverObj->transform.position = { -0.5f, 0.0f, -0.1f };
	GameOverObj->transform.scale = { 512.0f * 1.0f, 512.0f * 1.0f, 1.0f };
	GameOverObj->materialDiffuse.w = 0.0f;
	GameOverObj->SetActive(false);

	GameOverString = new CGameObject(vertexBufferObject, CTextureLoader::GetInstance()->GetTex(TEX_ID::GAMEOVER_STRING));
	Objects.push_back(GameOverString);
	GameOverString->transform.position = { -0.5f, 2.0f, -0.11f };
	GameOverString->transform.scale = { 512.0f * 0.0045f, 512.0f * 0.0045f, 1.0f };
	GameOverString->SetActive(false);

	retry = new CGameObject(vertexBufferObject, CTextureLoader::GetInstance()->GetTex(TEX_ID::RETRY));
	// �I�u�W�F�N�g�����X�g�ɓo�^
	Objects.push_back(retry);
	retry->transform.scale = { 1100.0f * 0.0007f, 447.0f * 0.0007f, 1.0f };;
	retry->transform.position = { 1.1f, -0.1f };
	retry->SetActive(false);

	goToSelect = new CGameObject(vertexBufferObject, CTextureLoader::GetInstance()->GetTex(TEX_ID::STAGE_SELECT));
	// �I�u�W�F�N�g�����X�g�ɓo�^
	Objects.push_back(goToSelect);
	goToSelect->transform.scale = { 1100.0f * 0.0007f, 447.0f * 0.0007f, 1.0f };
	goToSelect->transform.position = { 1.1f, -0.4f };
	goToSelect->SetActive(false);

	goToTitle = new CGameObject(vertexBufferObject, CTextureLoader::GetInstance()->GetTex(TEX_ID::GOTO_TITLE));
	// �I�u�W�F�N�g�����X�g�ɓo�^
	Objects.push_back(goToTitle);
	goToTitle->transform.scale = { 1100.0f * 0.0007f, 447.0f * 0.0007f, 1.0f };
	goToTitle->transform.position = { 1.1f, -0.7f };
	goToTitle->SetActive(false);

	// �J�[�\���̎��̉��Ə�����
	cursor = new CCursor(vertexBufferObject, CTextureLoader::GetInstance()->GetTex(TEX_ID::CURSOR));
	// �I�u�W�F�N�g�����X�g�ɓo�^
	Objects.push_back(cursor);
	cursor->transform.scale = { 186.0f * 0.0017f, 54.0f * 0.0017f, 1.0f };
	cursor->transform.position = { 0.624f, -0.1f, -0.2f };
	cursor->transform.rotation = -30.0f;
	cursor->Init({ cursor->transform.position.x, cursor->transform.position.y });
	cursor->SetActive(false);

	selectEaseX = new CEase;
	selectEaseY = new CEase;

	gameOverEase = new CEase;
	gameOverEase->Init(&GameOverString->transform.position.y, 0.0f, 1.5f, 0, EASE::easeOutBounce);
	gameOverObjEaseX = new CEase;
	gameOverObjEaseX->Init(&GameOverObj->transform.scale.x, 512.0f * 0.0045f, 2.0f, 0, EASE::easeOutQuint);
	gameOverObjEaseY = new CEase;
	gameOverObjEaseY->Init(&GameOverObj->transform.scale.y, 512.0f * 0.0045f, 2.0f, 0, EASE::easeOutQuint);
	/*---------------�Q�[���I�[�o�[��ʂ̃I�u�W�F�N�g-----------------------*/

	/*-------------------�N���A��ʂ̃I�u�W�F�N�g---------------------------*/
	c_bg = new CGameObject(vertexBufferObject, CTextureLoader::GetInstance()->GetTex(TEX_ID::CLEAR));
	Objects.push_back(c_bg);
	c_bg->transform.scale = { 1920.0f * 0.0021f, 1080.0f * 0.0021f, 1.0f };
	c_bg->transform.position.z = 0.4f;
	c_bg->SetActive(false);

	c_goToSelect = new CGameObject(vertexBufferObject, CTextureLoader::GetInstance()->GetTex(TEX_ID::STAGE_SELECT));
	// �I�u�W�F�N�g�����X�g�ɓo�^
	Objects.push_back(c_goToSelect);
	c_goToSelect->transform.scale = { 1100.0f * 0.0007f, 447.0f * 0.0007f, 1.0f };
	c_goToSelect->transform.position = { 1.03f, -0.5f };
	c_goToSelect->SetActive(false);

	c_goToTitle = new CGameObject(vertexBufferObject, CTextureLoader::GetInstance()->GetTex(TEX_ID::GOTO_TITLE));
	// �I�u�W�F�N�g�����X�g�ɓo�^
	Objects.push_back(c_goToTitle);
	c_goToTitle->transform.scale = { 1100.0f * 0.0007f, 447.0f * 0.0007f, 1.0f };
	c_goToTitle->transform.position = { 1.03f, -0.8f };
	c_goToTitle->SetActive(false);

	// �J�[�\���̎��̉��Ə�����
	c_cursor = new CCursor(vertexBufferObject, CTextureLoader::GetInstance()->GetTex(TEX_ID::CURSOR));
	// �I�u�W�F�N�g�����X�g�ɓo�^
	Objects.push_back(c_cursor);
	c_cursor->transform.scale = { 186.0f * 0.0017f, 54.0f * 0.0017f, 1.0f };
	c_cursor->transform.position = { 0.559f, -0.5f, -0.2f };
	c_cursor->transform.rotation = -30.0f;
	c_cursor->Init({ c_cursor->transform.position.x, c_cursor->transform.position.y }, 2);
	c_cursor->SetActive(false);

	scoreBoard = new CGameObject(vertexBufferObject, CTextureLoader::GetInstance()->GetTex(TEX_ID::BOARD));
	Objects.push_back(scoreBoard);
	scoreBoard->transform.position = { 1.0f, 0.2f, -0.1f };
	scoreBoard->transform.scale = { 772.0f * 0.002f, 472.0f * 0.002f, 1.0f };
	scoreBoard->SetActive(false);

	clearString = new CGameObject(vertexBufferObject, CTextureLoader::GetInstance()->GetTex(TEX_ID::CLEAR_STRING));
	Objects.push_back(clearString);
	clearString->transform.position = { -0.8f, 0.6f, -0.11f };
	clearString->transform.scale = { 0.0f, 0.0f, 1.0f };
	clearString->SetActive(false);

	clearStringEaseX = new CEase;
	clearStringEaseY = new CEase;
	clearStringEaseX->Init(&clearString->transform.scale.x, 1355.0f * 0.0015f, 1.0f, 2, EASE::easeOutBack);
	clearStringEaseY->Init(&clearString->transform.scale.y, 447.0f * 0.0015f, 1.0f, 2, EASE::easeOutBack);
	/*-------------------�N���A��ʂ̃I�u�W�F�N�g---------------------------*/
}

ResultScene::~ResultScene()
{
	SAFE_RELEASE(vertexBufferObject);

	// �e�I�u�W�F�N�g�̃��������
	for (auto it = Objects.begin(); it != Objects.end(); it++)
	{
		delete (*it);
	}

	// �C�[�W���O�̉��
	delete selectEaseX;
	delete selectEaseY;
	delete gameOverObjEaseX;
	delete gameOverObjEaseY;
	delete gameOverEase;
	delete clearStringEaseX;
	delete clearStringEaseY;

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
	// �N���A��ʂɎg���I�u�W�F�N�g��L��������
	c_bg->SetActive(true);
	clearString->SetActive(true);
	scoreBoard->SetActive(true);

	// �N���A������̃C�[�W���O�̍X�V
	clearStringEaseX->Update();
	clearStringEaseY->Update();
	// �C�[�W���O���I�������Ȃ�
	if (clearStringEaseX->GetState() == STATE::END)
	{
		// ���o���I������̂őI������L��������
		c_goToSelect->SetActive(true);
		c_goToTitle->SetActive(true);
		c_cursor->SetActive(true);
	}

	// �J�[�\���̓��͏��������s
	c_cursor->CursorInput();

	// CCursor�ł̗񋓌^��Scene���擾����
	c_cursorPoint = (CCursor_PointClear)c_cursor->GetCursorPoint();

	if (gInput->IsControllerButtonTrigger(XINPUT_GAMEPAD_B) || gInput->GetKeyTrigger(VK_RETURN))
	{
		// �J�[�\���̃|�C���g�ʒu�őJ�ڐ�̃V�[����ύX
		switch (c_cursorPoint)
		{
		case CCursor_PointClear::SELECT:	// �Z���N�g�ɖ߂�
			CSceneManager::GetInstance()->ChangeScene(SCENE_ID::SELECT);
			selectEaseX->Init(&c_goToSelect->transform.scale.x, 1100.0f * 0.00065f, 0.1f, 0, EASE::easeInCubic);
			selectEaseY->Init(&c_goToSelect->transform.scale.y, 447.0f * 0.00065f, 0.1f, 0, EASE::easeInCubic);
			selectFlg = true;
			break;

		case CCursor_PointClear::TITLE:	// �^�C�g���ɖ߂�
			CSceneManager::GetInstance()->ChangeScene(SCENE_ID::TITLE);
			selectEaseX->Init(&c_goToTitle->transform.scale.x, 1100.0f * 0.00065f, 0.1f, 0, EASE::easeInCubic);
			selectEaseY->Init(&c_goToTitle->transform.scale.y, 447.0f * 0.00065f, 0.1f, 0, EASE::easeInCubic);
			selectFlg = true;
			break;

		default:
			break;
		}
	}

	// �J�[�\���ʒu�ɉ����đ傫����ύX����
	switch (c_cursorPoint)
	{
	case CCursor_PointClear::SELECT:
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
				selectEaseX->Init(&c_goToSelect->transform.scale.x, 1100.0f * 0.0007f, 0.1f, 0, EASE::easeOutCubic);
				selectEaseY->Init(&c_goToSelect->transform.scale.y, 447.0f * 0.0007f, 0.1f, 0, EASE::easeOutCubic);
				// �t���O�𗧂Ăē�d�ŏ��������s���Ȃ��悤�ɂ���
				selectEnd = true;
			}
		}
		else
		{
			c_goToSelect->transform.scale = { 1100.0f * 0.0007f, 447.0f * 0.0007f, 1.0f };
		}
		c_goToSelect->materialDiffuse.w = 1.0f;
		c_goToTitle->transform.scale = { 1100.0f * 0.0006f, 447.0f * 0.0006f, 1.0f };
		c_goToTitle->materialDiffuse.w = 0.5f;
		break;

	case CCursor_PointClear::TITLE:
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
				selectEaseX->Init(&c_goToTitle->transform.scale.x, 1100.0f * 0.0007f, 0.1f, 0, EASE::easeOutCubic);
				selectEaseY->Init(&c_goToTitle->transform.scale.y, 447.0f * 0.0007f, 0.1f, 0, EASE::easeOutCubic);
				// �t���O�𗧂Ăē�d�ŏ��������s���Ȃ��悤�ɂ���
				selectEnd = true;
			}
		}
		else
		{
			c_goToTitle->transform.scale = { 1100.0f * 0.0007f, 447.0f * 0.0007f, 1.0f };
		}
		c_goToTitle->materialDiffuse.w = 1.0f;
		c_goToSelect->transform.scale = { 1100.0f * 0.0006f, 447.0f * 0.0006f, 1.0f };
		c_goToSelect->materialDiffuse.w = 0.5f;
		break;

	default:
		break;
	}
}

void ResultScene::UpdateGameOver()
{
	// �Q�[���I�[�o�[��ʂɎg���I�u�W�F�N�g��L��������
	GameOverObj->SetActive(true);
	GameOverString->SetActive(true);
	bg->SetActive(true);

	// �C�[�W���O�̍X�V
	gameOverObjEaseX->Update();
	gameOverObjEaseY->Update();

	// �����̃C�[�W���O�̍X�V
	if (gameOverObjEaseX->GetState() == STATE::END && gameOverObjEaseY->GetState() == STATE::END)
	{
		gameOverEase->Update();
	}

	// �����x�̍X�V
	GameOverObj->materialDiffuse.w = GameOverObj->materialDiffuse.w < 1.0f ?
		GameOverObj->materialDiffuse.w += 0.008f : 1.0f;

	// ���o���I�������Ȃ���͂�L��������
	if (gameOverEase->GetState() == STATE::END)
	{
		cursor->SetActive(true);
		retry->SetActive(true);
		goToSelect->SetActive(true);
		goToTitle->SetActive(true);
	}

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
			selectEaseX->Init(&retry->transform.scale.x, 1100.0f * 0.00065f, 0.1f, 0, EASE::easeInCubic);
			selectEaseY->Init(&retry->transform.scale.y, 447.0f * 0.00065f, 0.1f, 0, EASE::easeInCubic);
			selectFlg = true;
			break;

		case CCursor_PointResult::SELECT:	// �Z���N�g�ɖ߂�
			CSceneManager::GetInstance()->ChangeScene(SCENE_ID::SELECT);
			selectEaseX->Init(&goToSelect->transform.scale.x, 1100.0f * 0.00065f, 0.1f, 0, EASE::easeInCubic);
			selectEaseY->Init(&goToSelect->transform.scale.y, 447.0f * 0.00065f, 0.1f, 0, EASE::easeInCubic);
			selectFlg = true;
			break;

		case CCursor_PointResult::TITLE:	// �^�C�g���ɖ߂�
			CSceneManager::GetInstance()->ChangeScene(SCENE_ID::TITLE);
			selectEaseX->Init(&goToTitle->transform.scale.x, 1100.0f * 0.00065f, 0.1f, 0, EASE::easeInCubic);
			selectEaseY->Init(&goToTitle->transform.scale.y, 447.0f * 0.00065f, 0.1f, 0, EASE::easeInCubic);
			selectFlg = true;
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
				selectEaseX->Init(&goToSelect->transform.scale.x, 1100.0f * 0.0007f, 0.1f, 0, EASE::easeOutCubic);
				selectEaseY->Init(&goToSelect->transform.scale.y, 447.0f * 0.0007f, 0.1f, 0, EASE::easeOutCubic);
				// �t���O�𗧂Ăē�d�ŏ��������s���Ȃ��悤�ɂ���
				selectEnd = true;
			}
		}
		else
		{
			goToSelect->transform.scale = { 1100.0f * 0.0007f, 447.0f * 0.0007f, 1.0f };
		}
		goToSelect->materialDiffuse.w = 1.0f;
		retry->transform.scale = { 1100.0f * 0.0006f, 447.0f * 0.0006f, 1.0f };
		retry->materialDiffuse.w = 0.5f;
		goToTitle->transform.scale = { 1100.0f * 0.0006f, 447.0f * 0.0006f, 1.0f };
		goToTitle->materialDiffuse.w = 0.5f;
		break;

	case CCursor_PointResult::TITLE:
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
				selectEaseX->Init(&goToTitle->transform.scale.x, 1100.0f * 0.0007f, 0.1f, 0, EASE::easeOutCubic);
				selectEaseY->Init(&goToTitle->transform.scale.y, 447.0f * 0.0007f, 0.1f, 0, EASE::easeOutCubic);
				// �t���O�𗧂Ăē�d�ŏ��������s���Ȃ��悤�ɂ���
				selectEnd = true;
			}
		}
		else
		{
			goToTitle->transform.scale = { 1100.0f * 0.0007f, 447.0f * 0.0007f, 1.0f };
		}
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
