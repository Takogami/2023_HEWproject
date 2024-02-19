#include "SelectScene.h"
#include "CSceneManager.h"

SelectScene::SelectScene()
{
	// �J�����I�u�W�F�N�g�̎��̉�
	Cam = new CCamera;

	// �w�i�̐ݒ�
	bg = new CGameObject(vertexBufferObject, CTextureLoader::GetInstance()->GetTex(TEX_ID::TITLE_BG), { 1.0f ,1.0f });
	bg->transform.scale = { 1920.0f * 0.0021f, 1080.0f * 0.0021f, 1.0f };
	// �I�u�W�F�N�g�����X�g�ɓo�^
	Objects.push_back(bg);

	// ������̐ݒ�
	StageSelect = new CDrawString;
	StageSelect->SetFont(FontID::UZURA);
	StageSelect->SetString("�X�e�[�W��I��ł�");
	StageSelect->SetPosition({ 80.0f, 100.0f });
	StageSelect->SetFontSize(80.0f);
	StageSelect->SetFontColor(0.0f, 0.0f, 0.0f);
	StageSelect->SetFontWeight(FONT_WEIGHT::ULTRA_BOLD);
	StageSelect->SetShadow({ -3.0f, -2.0f }, 1.0f, 0.3f, 0.0f, 0.4f);

	goToTitle = new CDrawString;
	goToTitle->SetFont(FontID::UZURA);
	goToTitle->SetString("start : �^�C�g����");
	goToTitle->SetPosition({ 80.0f, 780.0f });
	goToTitle->SetFontSize(40.0f);
	goToTitle->SetFontColor(0.0f, 0.0f, 0.0f);
	goToTitle->SetFontWeight(FONT_WEIGHT::ULTRA_BOLD);
	goToTitle->SetShadow({ -3.0f, -2.0f }, 1.0f, 0.7f, 0.0f, 1.0f);

	StagePreview = new CGameObject(vertexBufferObject, CTextureLoader::GetInstance()->GetTex(TEX_ID::BOOK), { 0.2f, 1.0f });
	Objects.push_back(StagePreview);
	StagePreview->transform.position = { -0.97f, -0.07f, 0.2f };
	StagePreview->transform.scale = { 693.0f * 0.003f, 900.0f * 0.003f};
	StagePreview->InitAnimParameter(false, 5, 1, ANIM_PATTERN::BOOK, 0.2f);

	StageView = new CGameObject(vertexBufferObject, CTextureLoader::GetInstance()->GetTex(TEX_ID::STAGE_VIEW), { 0.333333f, 1.0f });
	Objects.push_back(StageView);
	StageView->transform.position = { -0.95f, -0.13f, 0.15f };
	StageView->transform.rotation = 1.4f;
	StageView->transform.scale = { 1.2f, 1.2f };
	StageView->materialDiffuse.w = 0.0f;
	StageView->TextureCutout(0,0);

	// �v�f���g��
	StageList.resize(listNum);

	// �X�e�[�W�̃I�u�W�F�N�g�̐���
	StageList[0] = new CGameObject(vertexBufferObject, CTextureLoader::GetInstance()->GetTex(TEX_ID::S1_SELECT_FLAME));
	StageList[1] = new CGameObject(vertexBufferObject, CTextureLoader::GetInstance()->GetTex(TEX_ID::S2_SELECT_FLAME));
	StageList[2] = new CGameObject(vertexBufferObject, CTextureLoader::GetInstance()->GetTex(TEX_ID::S3_SELECT_FLAME));

	// ������
	for (int i = 0; i < StageList.size(); i++)
	{
		StageList[i]->transform.scale = { 646.0f * 0.0025f, 277.0f * 0.0025f, 1.0f };
		StageList[i]->transform.position = { 1.0f, 0.0f - (0.7f * i), -0.1f };
		moveEndPos.resize(StageList.size());
		Objects.push_back(StageList[i]);
		// �X�e�[�W�̐������C�[�W���O�����
		selectEase.push_back(new CEase);
	}

	StagePreview2 = new CGameObject(vertexBufferObject, CTextureLoader::GetInstance()->GetTex(TEX_ID::STRING_BG));
	Objects.push_back(StagePreview2);
	StagePreview2->transform.position = { -0.8f, 0.76f, 0.05f };
	StagePreview2->transform.scale = { 700.0f * 0.0035f, 283.0f * 0.002f};
	StagePreview2->materialDiffuse.w = 0.7f;

	stringBg = new CGameObject(vertexBufferObject, CTextureLoader::GetInstance()->GetTex(TEX_ID::STRING_BG));
	Objects.push_back(stringBg);
	stringBg->transform.position = { -1.33f, -0.97f, 0.05f };
	stringBg->transform.scale = { 700.0f * 0.00148f, 283.0f * 0.0007f };
	stringBg->materialDiffuse.w = 0.85f;

	kami = new CGameObject(vertexBufferObject, CTextureLoader::GetInstance()->GetTex(TEX_ID::PLAYER), { 0.2f ,0.1f });
	Objects.push_back(kami);
	kami->transform.position = { 1.85f, -0.85f, -0.11f };
	kami->transform.rotation = -20.0f;
	kami->transform * 1.0f;
	// �A�j���[�V�����̏�����
	kami->InitAnimParameter(true, 5, 10, ANIM_PATTERN::IDOL_L, 0.15f);

	// �v���r���[�̃C�[�W���O
	viewEase = new CEase;
	viewEase->Init(&StageView->materialDiffuse.w, 1.0f, 0.7f, 0, EASE::easeInOutCubic);
}

SelectScene::~SelectScene()
{
	SAFE_RELEASE(vertexBufferObject);

	// �e�I�u�W�F�N�g�̃��������
	for (auto it = Objects.begin(); it != Objects.end(); it++)
	{
		delete (*it);
	}
	// �C�[�W���O�̉��
	for (int i = 0; i < listNum; i++)
	{
		delete selectEase[i];
	}
	delete viewEase;

	// �J�����I�u�W�F�N�g�̍폜
	delete Cam;
}

void SelectScene::Update()
{
	// �^�C�g����ʂɖ߂�
	if (gInput->IsControllerButtonTrigger(XINPUT_GAMEPAD_START))
	{
		CSceneManager::GetInstance()->ChangeScene(SCENE_ID::TITLE, FADE_TYPE::ERASER);
	}

	// ��ړ�
	if ((gInput->GetKeyTrigger(VK_UP) || gInput->IsControllerButtonRepeat(XINPUT_GAMEPAD_DPAD_UP, 90, 1))
		&& stageNum > 1 && !selectMoveUp && !selectMoveDown)
	{
		// �X�e�[�W�r���[�̃C�[�W���O�̏�����
		StageView->materialDiffuse.w = 0.0f;
		viewEase->Init(&StageView->materialDiffuse.w, 1.0f, 0.7f, 0, EASE::easeInOutCubic);

		//	�T�E���h�Đ�
		XA_Play(SOUND_LABEL_BOOKSE);

		// �I�𒆂̃X�e�[�W�̍X�V
		stageNum -= 1;
		// �X�e�[�W�ԍ���񋓌^�N���X�ɕϊ�����
		userSelect = (STAGE_NUM)stageNum;
		// �X�e�[�W�I�����X�g�̈ړ�
		for (int i = 0; i < StageList.size(); i++)
		{
			// �ړ��̍ŏI���W��ۑ�
			moveEndPos[i] = StageList[i]->transform.position.y - 0.7f;
			selectMoveUp = true;
			// �C�[�W���O�̏�����
			selectEase[i]->Init(&StageList[i]->transform.position.y, moveEndPos[i], 0.5f, 0, EASE::easeOutBack);
		}
		StagePreview->SetAnimationPattern(ANIM_PATTERN::BOOK_REVERSE);
		StagePreview->ResetAnimation();
		StagePreview->PlayAnimation();
	}
	// ���ړ�
	else if ((gInput->GetKeyTrigger(VK_DOWN) || gInput->IsControllerButtonRepeat(XINPUT_GAMEPAD_DPAD_DOWN, 90, 1))
		&& stageNum < listNum && !selectMoveUp && !selectMoveDown)
	{
		// �X�e�[�W�r���[�̃C�[�W���O�̏�����
		StageView->materialDiffuse.w = 0.0f;
		viewEase->Init(&StageView->materialDiffuse.w, 1.0f, 0.7f, 0, EASE::easeInOutCubic);

		//	�T�E���h�Đ�
		XA_Play(SOUND_LABEL_BOOKSE);

		// �I�𒆂̃X�e�[�W�̍X�V
		stageNum += 1;
		// �X�e�[�W�ԍ���񋓌^�N���X�ɕϊ�����
		userSelect = (STAGE_NUM)stageNum;
		// �X�e�[�W�I�����X�g�̈ړ�
		for (int i = 0; i < StageList.size(); i++)
		{
			moveEndPos[i] = StageList[i]->transform.position.y + 0.7f;
			selectMoveDown = true;
			// �C�[�W���O�̏�����
			selectEase[i]->Init(&StageList[i]->transform.position.y, moveEndPos[i], 0.5f, 0, EASE::easeOutBack);
		}
		StagePreview->SetAnimationPattern(ANIM_PATTERN::BOOK);
		StagePreview->ResetAnimation();
		StagePreview->PlayAnimation();
	}
	if (gInput->IsControllerButtonTrigger(XINPUT_GAMEPAD_B) || gInput->GetKeyTrigger(VK_RETURN))
	{
		// �T�E���h�Đ�
		XA_Play(SOUND_LABEL_PRESS);
		gInput->ControllerVibration(5, 40000);
		switch (userSelect)
		{
		case STAGE_NUM::STAGE1:
			// �X�e�[�W1�ɑJ��
			CSceneManager::GetInstance()->ChangeScene(SCENE_ID::STAGE_1, FADE_TYPE::ERASER);
			break;

		case STAGE_NUM::STAGE2:
			// �X�e�[�W2�ɑJ��
			CSceneManager::GetInstance()->ChangeScene(SCENE_ID::STAGE_2, FADE_TYPE::ERASER);
			break;

		case STAGE_NUM::STAGE3:
			//	�X�e�[�W3�ɑJ��
			CSceneManager::GetInstance()->ChangeScene(SCENE_ID::STAGE_3, FADE_TYPE::ERASER);
			break;

		default:
			break;
		}
	}
	// �X�e�[�W�v���r���[�̍X�V
	StageView->TextureCutout(stageNum - 1, 0);

	for(int i = 0; i < StageList.size(); i++)
	{
		// �ʒu��0�̑I�𒆂̃X�e�[�W�͑傫���\��
		if (StageList[i]->transform.position.y == 0.0f)
		{
			// �傫���𓙔{��
			StageList[i]->transform.scale.x = 646.0f * 0.0025f * 1.0f;
			StageList[i]->transform.scale.y = 277.0f * 0.0025f * 1.0f;
			// �s�����ɂ���
			StageList[i]->materialDiffuse.w = 1.0f;
		}
		// �I������Ă��Ȃ��X�e�[�W�͏������������ɂ���
		else
		{
			// �k������
			StageList[i]->transform.scale.x = 646.0f * 0.0025f * 0.8f;
			StageList[i]->transform.scale.y = 277.0f * 0.0025f * 0.8f;
			// �s�����x��������
			StageList[i]->materialDiffuse.w = 0.7f;
		}

		// ���X�g���ړ������ǂ����𔻒�
		if (selectMoveUp)
		{
			// �C�[�W���O�̍X�V
			selectEase[i]->Update();
			// ���X�g����ړ�������
			if (StageList[i]->transform.position.y <= moveEndPos[i] && selectEase[i]->GetState() == STATE::END)
			{
				// �ړ����I�����Ă���Ȃ�ŏI���W�������Ă���
				StageList[i]->transform.position.y = moveEndPos[i];
				// �����ɕ\������Ă���X�e�[�W��0�������Ă���
				StageList[stageNum - 1]->transform.position.y = 0.0f;
				// ��ړ��t���O�����낷
				selectMoveUp = false;
				StagePreview->StopAnimation();
			}
		}
		else if (selectMoveDown)
		{
			// �C�[�W���O�̍X�V
			selectEase[i]->Update();
			// ���X�g�����ړ�������
			if (StageList[i]->transform.position.y >= moveEndPos[i] && selectEase[i]->GetState() == STATE::END)
			{
				// �ړ����I�����Ă���Ȃ�ŏI���W�������Ă���
				StageList[i]->transform.position.y = moveEndPos[i];
				// �����ɕ\������Ă���X�e�[�W��0�������Ă���
				StageList[stageNum - 1]->transform.position.y = 0.0f;
				// ��ړ��t���O�����낷
				selectMoveDown = false;
				StagePreview->StopAnimation();
			}
		}
	}

	// �v���r���[�̓����x�ύX�C�[�W���O�̍X�V
	viewEase->Update();

	// �e�I�u�W�F�N�g�̕`��
	for (auto it = Objects.begin(); it != Objects.end(); it++)
	{
		(*it)->Update();
	}
}

void SelectScene::Draw()
{
	// �e�I�u�W�F�N�g�̕`��
	for (auto it = Objects.begin(); it != Objects.end(); it++)
	{
		(*it)->Draw();
	}

	StageSelect->Draw();
	goToTitle->Draw();
}
