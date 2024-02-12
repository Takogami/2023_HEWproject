/* �C���N���[�h */
#include "TitleScene.h"
#include "CSceneManager.h"

// �R���X�g���N�^
TitleScene::TitleScene()
{
	// �J�����I�u�W�F�N�g�̎��̉�
	Cam = new CCamera;

	bg = new CGameObject(vertexBufferObject, CTextureLoader::GetInstance()->GetTex(TEX_ID::BG), { 1.0f ,1.0f });
	// �I�u�W�F�N�g�����X�g�ɓo�^
	Objects.push_back(bg);

	// �w�i�̐ݒ�
	bg->transform.scale = { 1920.0f * 0.0021f, 1080.0f * 0.0021f, 1.0f };
	bg->transform.position.z = 0.4f;

	enemyObj = new CGameObject(vertexBufferObject, CTextureLoader::GetInstance()->GetTex(TEX_ID::ENEMY), { 0.5f ,1.0f });
	Objects.push_back(enemyObj);
	enemyObj->transform.position = { 3.5f, 0.2f, 0.3f };
	enemyObj->transform.scale = { 809.0f * 0.0008f, 573.0f * 0.0008f, 1.0f };
	enemyObj->InitAnimParameter(true, 2, 1, ANIM_PATTERN::ENEMY_MOVE, 0.08f);

	enemyObj_reverse = new CGameObject(vertexBufferObject, CTextureLoader::GetInstance()->GetTex(TEX_ID::ENEMY_R), { 0.5f ,1.0f });
	Objects.push_back(enemyObj_reverse);
	enemyObj_reverse->transform.position = { -3.5f, -0.5f, 0.3f };
	enemyObj_reverse->transform.scale = { 809.0f * 0.0008f, 573.0f * 0.0008f, 1.0f };
	enemyObj_reverse->InitAnimParameter(true, 2, 1, ANIM_PATTERN::ENEMY_MOVE, 0.08f);

	playerObj = new CGameObject(vertexBufferObject, CTextureLoader::GetInstance()->GetTex(TEX_ID::PLAYER), { 0.2f ,0.1f });
	// �I�u�W�F�N�g�����X�g�ɓo�^
	Objects.push_back(playerObj);
	playerObj->transform.position = { 2.5f, 0.2f, 0.3f };
	playerObj->transform.scale = {435.0f * 0.0012f, 326.0f * 0.0012f, 1.0f };
	// �A�j���[�V�����̏�����
	playerObj->InitAnimParameter(true, 5, 10, ANIM_PATTERN::LEFTWALK, 0.2f);

	ruler = new CGameObject(vertexBufferObject, CTextureLoader::GetInstance()->GetTex(TEX_ID::RULER), { 1.0f ,1.0f });
	Objects.push_back(ruler);
	ruler->transform.scale = { 416.0f * 0.001f , 1688.0f * 0.001f, 1.0f };
	ruler->transform.position = { -1.4f, 0.7f, 0.2f };
	ruler->transform.rotation = -45.0f;

	ruler2 = new CGameObject(vertexBufferObject, CTextureLoader::GetInstance()->GetTex(TEX_ID::RULER), { 1.0f ,1.0f });
	Objects.push_back(ruler2);
	ruler2->transform.scale = { 416.0f * 0.0007f , 1688.0f * 0.0007f, 1.0f };
	ruler2->transform.position = { 1.7f, -0.8f, 0.2f };
	ruler2->transform.rotation = 60.0f;

	Title = new CGameObject(vertexBufferObject, CTextureLoader::GetInstance()->GetTex(TEX_ID::TITLE), { 1.0f ,1.0f });
	Objects.push_back(Title);
	Title->transform.scale = { 1271.0f * 0.0021f , 299.0f * 0.0021f, 1.0f};
	Title->transform.position.y = 0.55f;

	//�v���C���[�̎��̉��Ə�����
	goToSelect = new CGameObject(vertexBufferObject, CTextureLoader::GetInstance()->GetTex(TEX_ID::PLAY));
	// �I�u�W�F�N�g�����X�g�ɓo�^
	Objects.push_back(goToSelect);
	goToSelect->transform.scale = { 1100.0f * 0.0007f, 447.0f * 0.0007f, 1.0f };
	goToSelect->transform.position = { 0.0f, -0.3f};

	//�v���C���[�̎��̉��Ə�����
	goToOption = new CGameObject(vertexBufferObject, CTextureLoader::GetInstance()->GetTex(TEX_ID::OPTION));
	// �I�u�W�F�N�g�����X�g�ɓo�^
	Objects.push_back(goToOption);
	goToOption->transform.scale = { 1100.0f * 0.0007f, 447.0f * 0.0007f, 1.0f };
	goToOption->transform.position = { 0.0f, -0.6f};

	//�v���C���[�̎��̉��Ə�����
	exitGame = new CGameObject(vertexBufferObject, CTextureLoader::GetInstance()->GetTex(TEX_ID::EXIT));
	// �I�u�W�F�N�g�����X�g�ɓo�^
	Objects.push_back(exitGame);
	exitGame->transform.scale = { 1100.0f * 0.0007f, 447.0f * 0.0007f, 1.0f };
	exitGame->transform.position = { 0.0f, -0.9f};

	// �J�[�\���̎��̉��Ə�����
	cursor = new CCursor(vertexBufferObject, CTextureLoader::GetInstance()->GetTex(TEX_ID::CURSOR));
	// �I�u�W�F�N�g�����X�g�ɓo�^
	Objects.push_back(cursor);
	cursor->transform.scale = { 186.0f * 0.0017f, 54.0f * 0.0017f, 1.0f };
	cursor->transform.rotation = -30.0f;
	cursor->transform.position = { -0.5f, -0.3f, -0.1f };
	cursor->Init({ cursor->transform.position.x, cursor->transform.position.y });

	// �C�[�W���O�̎��̉�
	titleEase = new CEase();
	titleEase->Init(&Title->transform.position.y, 0.5f, 1.0f, 0, EASE::easeOutBounce);
	enemyEase = new CEase();
	enemyEase->Init(&enemyObj->transform.position.x, 0.0f, 3.0f, 4, EASE::easeOutCubic);
	enemyEaseR = new CEase();
	enemyEaseR->Init(&enemyObj_reverse->transform.position.x, 0.0f, 3.0f, 4, EASE::easeOutCubic);
	playerFlyEase = new CEase();
	selectEaseX = new CEase();
	selectEaseY = new CEase();
}

// �f�X�X�g���N�^
TitleScene::~TitleScene()
{
	// ���_�o�b�t�@�̉��
	SAFE_RELEASE(vertexBufferObject);

	// �e�I�u�W�F�N�g�̃��������
	for (auto it = Objects.begin(); it != Objects.end(); it++)
	{
		delete (*it);
	}

	// �C�[�W���O�̉��
	delete titleEase;
	delete enemyEase;
	delete enemyEaseR;
	delete playerFlyEase;
	delete selectEaseX;
	delete selectEaseY;

	// �J�����̉��
	delete Cam;
}

void TitleScene::Update()
{
	// �J�[�\���̓��͏��������s
	cursor->CursorInput();

	//CCursor�ł̗񋓌^��Scene���擾����
	cursorPoint = cursor->GetCursorPoint();

	if (gInput->IsControllerButtonTrigger(XINPUT_GAMEPAD_B) || gInput->GetKeyTrigger(VK_RETURN))
	{
		switch (cursorPoint)
		{
		case CCursor_Point::STAGE:
			// �X�e�[�W�̏ꍇ�̏���������
			CSceneManager::GetInstance()->ChangeScene(SCENE_ID::SELECT);
			selectFlg = true;
			selectEaseX->Init(&goToSelect->transform.scale.x, 1100.0f * 0.00065f, 0.1f, 0, EASE::easeInCubic);
			selectEaseY->Init(&goToSelect->transform.scale.y, 447.0f * 0.00065f, 0.1f, 0, EASE::easeInCubic);
			break;

		case CCursor_Point::OPTION:
			// �I�v�V�����̏ꍇ�̏���������
			break;

		case CCursor_Point::EXIT:
			PostQuitMessage(0);
			// �I���̏ꍇ�̏���������
			break;

		default:
			break;
		}
	}

	// �J�[�\���ʒu�ɉ����đ傫����ύX����
	switch (cursorPoint)
	{
	case CCursor_Point::STAGE:
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
		goToOption->transform.scale = { 1100.0f * 0.0006f, 447.0f * 0.0006f, 1.0f };
		goToOption->materialDiffuse.w = 0.5f;
		exitGame->transform.scale = { 1100.0f * 0.0006f, 447.0f * 0.0006f, 1.0f };
		exitGame->materialDiffuse.w = 0.5f;
		break;

	case CCursor_Point::OPTION:
		goToOption->transform.scale = { 1100.0f * 0.0007f, 447.0f * 0.0007f, 1.0f };
		goToOption->materialDiffuse.w = 1.0f;
		goToSelect->transform.scale = { 1100.0f * 0.0006f, 447.0f * 0.0006f, 1.0f };
		goToSelect->materialDiffuse.w = 0.5f;
		exitGame->transform.scale = { 1100.0f * 0.0006f, 447.0f * 0.0006f, 1.0f };
		exitGame->materialDiffuse.w = 0.5f;
		break;

	case CCursor_Point::EXIT:
		exitGame->transform.scale = { 1100.0f * 0.0007f, 447.0f * 0.0007f, 1.0f };
		exitGame->materialDiffuse.w = 1.0f;
		goToSelect->transform.scale = { 1100.0f * 0.0006f, 447.0f * 0.0006f, 1.0f };
		goToSelect->materialDiffuse.w = 0.5f;
		goToOption->transform.scale = { 1100.0f * 0.0006f, 447.0f * 0.0006f, 1.0f };
		goToOption->materialDiffuse.w = 0.5f;
		break;

	default:
		break;
	}

	// ���o�p�̓G�������ʒu�ɂ���Ƃ�
	if (!moveDirNegative && !moveDirPositive)
	{
		// �G�𕉂̕����ɓ�����
		enemyEase->Update();
		if (enemyEase->GetState() == STATE::END)
		{
			enemyEase->Init(&enemyObj->transform.position.x, -3.5f, 2.0f, 0, EASE::easeInCubic);
		}
		playerObj->transform.position.x -= 0.01f;
		// �G�̕��̕����ւ̈ړ����I�������Ȃ�
		if (enemyObj->transform.position.x <= -3.5f)
		{
			// �ړ��I���t���O���グ��
			moveDirNegative = true;
			// playerObj�����̈ʒu�ɃZ�b�g����
			playerObj->transform.position.y = -0.5f;
			playerObj->transform.position.x = -2.5f;
			playerObj->SetAnimationPattern(ANIM_PATTERN::RIGHTWALK);
		}
	}
	else if(moveDirNegative && !moveDirPositive)
	{
		// ���]�����G�𐳂̕����ɓ�����
		enemyEaseR->Update();
		if (enemyEaseR->GetState() == STATE::END)
		{
			enemyEaseR->Init(&enemyObj_reverse->transform.position.x, 3.5f, 2.0f, 0, EASE::easeInCubic);
		}
		playerObj->transform.position.x += 0.01f;
		// ���]�����G�̐��̕����ւ̈ړ����I�������Ȃ�
		if (enemyObj_reverse->transform.position.x >= 3.5f)
		{
			// �ړ��I���t���O���グ��
			moveDirPositive = true;
			// �G�����̈ʒu�ɖ߂�
			enemyObj->transform.position.x = 3.5f;
			enemyObj_reverse->transform.position.x = -3.5f;
			// playerObj�����̈ʒu�ɃZ�b�g����
			playerObj->transform.position.x = -1.0f;
			playerObj->transform.position.y = -2.5f;
			playerObj->SetAnimationPattern(ANIM_PATTERN::FLAYING);
			playerObj->transform.scale = { 435.0f * 0.0017f, 326.0f * 0.0017f, 1.0f };
			playerObj->SetAnimationSpeed(0.15f);
			playerFlyEase->Init(&playerObj->transform.position.y, 2.5f, 8.0f, 0, EASE::easeInOutSine);
		}
	}
	else
	{
		playerObj->transform.position.x += 0.005f;
		playerFlyEase->Update();
		// �ړ����I�������Ȃ�
		if (playerObj->transform.position.y >= 2.5f)
		{
			// �t���O�����ɖ߂�
			moveDirNegative = false;
			moveDirPositive = false;
			// playerObj�����̈ʒu�ɖ߂�
			playerObj->transform.position.x = 2.5f;
			playerObj->transform.position.y = 0.2f;
			playerObj->SetAnimationPattern(ANIM_PATTERN::LEFTWALK);
			playerObj->SetAnimationSpeed(0.2f);
			playerObj->transform.scale = { 435.0f * 0.0012f, 326.0f * 0.0012f, 1.0f };
			// �C�[�W���O�����ɖ߂�
			enemyEase->Init(&enemyObj->transform.position.x, 0.0f, 3.0f, 4, EASE::easeOutCubic);
			enemyEaseR->Init(&enemyObj_reverse->transform.position.x, 0.0f, 3.0f, 4, EASE::easeOutCubic);
			playerFlyEase->Init(&playerObj->transform.position.y, 2.5f, 8.0f, 0, EASE::easeInOutSine);
		}
	}

	// �e��C�[�W���O�̍X�V
	titleEase->Update();
	if (titleEase->GetState() == STATE::END && TitleEaseFg)
	{
		titleEase->Init(&Title->transform.position.y, 0.5f, 1.0f, 0, EASE::easeOutBounce);
		TitleEaseFg = false;
	}
	else if (titleEase->GetState() == STATE::END && !TitleEaseFg)
	{
		titleEase->Init(&Title->transform.position.y, 0.55f, 1.0f, 0, EASE::easeInOutQuint);
		TitleEaseFg = true;
	}

	// �J�����̃A�b�v�f�[�g
	Cam->Update();

	// �e�I�u�W�F�N�g�̍X�V
	for (auto it = Objects.begin(); it != Objects.end(); it++)
	{
		(*it)->Update();
	}
}

void TitleScene::Draw()
{
	// �e�I�u�W�F�N�g�̕`��
	for (auto it = Objects.begin(); it != Objects.end(); it++)
	{
		(*it)->Draw();
	}
}

