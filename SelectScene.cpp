#include "SelectScene.h"
#include "CSceneManager.h"

SelectScene::SelectScene()
{
	// �J�����I�u�W�F�N�g�̎��̉�
	Cam = new CCamera;

	// �w�i�̐ݒ�
	bg = new CGameObject(vertexBufferObject, CTextureLoader::GetInstance()->GetTex(TEX_ID::BG), { 1.0f ,1.0f });
	bg->transform.scale = { 1920.0f * 0.0021f, 1080.0f * 0.0021f, 1.0f };
	bg->transform.position.z = 0.99f;
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

	StagePreview = new CGameObject(vertexBufferObject, CTextureLoader::GetInstance()->GetTex(TEX_ID::BOOK), { 0.3333333f, 1.0f });
	Objects.push_back(StagePreview);
	StagePreview->transform.position = { -0.97f, -0.07f, 0.5f };
	StagePreview->transform.scale = { 693.0f * 0.003f, 900.0f * 0.003f, 0.5f };
	StagePreview->InitAnimParameter(false, 3, 1, ANIM_PATTERN::BOOK, 0.1f);

	StagePreview2 = new CGameObject(vertexBufferObject, CTextureLoader::GetInstance()->GetTex(TEX_ID::STRING_BG));
	Objects.push_back(StagePreview2);
	StagePreview2->transform.position = { -0.8f, 0.76f, 0.4f };
	StagePreview2->transform.scale = { 700.0f * 0.0035f, 283.0f * 0.002f, 0.5f };

	// �v�f���g��
	StageList.resize(listNum);
	// �X�e�[�W�̃I�u�W�F�N�g�̐����Ə�����
	for (int i = 0; i < StageList.size(); i++)
	{
		StageList[i] = new CGameObject(vertexBufferObject, CTextureLoader::GetInstance()->GetTex(TEX_ID::SELECT_FLAME));
		StageList[i]->transform.scale = { 646.0f * 0.0025f, 277.0f * 0.0025f, 1.0f };
		StageList[i]->transform.position = { 1.0f, 0.0f - (0.7f * i), 0.0f};
		moveEndPos.resize(StageList.size());
		Objects.push_back(StageList[i]);
		// �X�e�[�W�̐������C�[�W���O�����
		selectEase.push_back(new CEase);
	}
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

	// �J�����I�u�W�F�N�g�̍폜
	delete Cam;
}

void SelectScene::Update()
{
	// ��ړ�
	if ((gInput->GetKeyTrigger(VK_UP) || gInput->IsControllerButtonRepeat(XINPUT_GAMEPAD_DPAD_UP, 90, 1))
		&& stageNum > 1 && !selectMoveUp && !selectMoveDown)
	{
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
		switch (userSelect)
		{
		case STAGE_NUM::STAGE1:
			// �X�e�[�W1�ɑJ��
			CSceneManager::GetInstance()->ChangeScene(SCENE_ID::STAGE_1);
			break;

		case STAGE_NUM::STAGE2:
			// �X�e�[�W2�ɑJ��
			CSceneManager::GetInstance()->ChangeScene(SCENE_ID::STAGE_2);
			break;

		case STAGE_NUM::STAGE3:
			//	�X�e�[�W3�ɑJ��
			CSceneManager::GetInstance()->ChangeScene(SCENE_ID::STAGE_3);
			break;

		case STAGE_NUM::STAGE4:
			CSceneManager::GetInstance()->ChangeScene(SCENE_ID::STAGE_4);
			break;

		case STAGE_NUM::STAGE5:
			break;

		default:
			break;
		}
	}

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

	// �e�I�u�W�F�N�g�̕`��
	for (auto it = Objects.begin(); it != Objects.end(); it++)
	{
		(*it)->Update();
	}
}

void SelectScene::Draw()
{
	D3D_ClearScreen();

	// �e�I�u�W�F�N�g�̕`��
	for (auto it = Objects.begin(); it != Objects.end(); it++)
	{
		(*it)->Draw();
	}

	StageSelect->Draw();

	// ��ʍX�V
	D3D_UpdateScreen();
}
