#include "SelectScene.h"
#include "CSceneManager.h"

SelectScene::SelectScene()
{
	// �J�����I�u�W�F�N�g�̎��̉�
	Cam = new CCamera;

	// ������̐ݒ�
	StageSelect = new CDrawString;
	StageSelect->SetFont(FontID::KARAKAZE);
	StageSelect->SetString("�X�e�[�W�������ł�");
	StageSelect->SetPosition({ 0.0f, 50.0f });
	StageSelect->SetFontSize(100.0f);
	StageSelect->SetFontColor(1.0f, 1.0f, 1.0f);
	StageSelect->SetFontWeight(FONT_WEIGHT::ULTRA_BOLD);
	StageSelect->SetFontStyle(FONT_STYLE::ITALIC);

	StagePreview = new CGameObject(vertexBufferObject, CTextureLoader::GetInstance()->GetTex(TEX_ID::BOOK), { 0.2f,1.0f });
	Objects.push_back(StagePreview);
	StagePreview->transform.position = { -1.0f, -0.15f, 0.5f };
	StagePreview->transform * 2.5f; 

	StagePreview2 = new CGameObject(vertexBufferObject, CTextureLoader::GetInstance()->GetTex(TEX_ID::NUM));
	Objects.push_back(StagePreview2);
	StagePreview2->transform.position = { -1.0f, -0.15f, -0.1f };
	StagePreview2->transform * 1.0f;

	// �v�f���g��
	StageList.resize(listNum);
	// �X�e�[�W�̃I�u�W�F�N�g�̐����Ə�����
	for (int i = 0; i < StageList.size(); i++)
	{
		StageList[i] = new CGameObject(vertexBufferObject, CTextureLoader::GetInstance()->GetTex(TEX_ID::STAGE));
		StageList[i]->transform.scale = { 1.5f, 0.5f, 1.0f };
		StageList[i]->transform.position = { 0.9f, 0.0f - (0.7f * i), 0.0f};
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
	if ((gInput->IsControllerButtonTrigger(XINPUT_GAMEPAD_A) || gInput->GetKeyTrigger(VK_RETURN)) && !selectMoveUp && !selectMoveDown)
	{
		switch (stageNum)
		{
		case 1:
			CSceneManager::GetInstance()->ChangeScene(SCENE_ID::RESULT);
			break;
		case 2:
			CSceneManager::GetInstance()->ChangeScene(SCENE_ID::STAGE_01);
			break;
		case 3:
			break;
		case 4:
			break;
		case 5:
			break;
		default:
			break;
		}
	}

	// ��ړ�
	if ((gInput->GetKeyTrigger(VK_UP) || gInput->IsControllerButtonRepeat(XINPUT_GAMEPAD_DPAD_UP, 40, 5))
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
			selectEase[i]->Init(&StageList[i]->transform.position.y, moveEndPos[i], 0.5f, 0, EASE::easeInOutSine);
		}
		// �{�̃A�j���[�V�������Đ�
		StagePreview->InitAnimParameter(true, 5, ANIM_PATTERN::BOOK, 0.10f);
	}
	// ���ړ�
	else if ((gInput->GetKeyTrigger(VK_DOWN) || gInput->IsControllerButtonRepeat(XINPUT_GAMEPAD_DPAD_DOWN, 40, 5))
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
			selectEase[i]->Init(&StageList[i]->transform.position.y, moveEndPos[i], 0.5f, 0, EASE::easeInOutSine);
		}
		// �{�̃A�j���[�V�������Đ�
		StagePreview->InitAnimParameter(true, 5, ANIM_PATTERN::BOOK, 0.10f);
	}

	for(int i = 0; i < StageList.size(); i++)
	{
		// �ʒu��0�̑I�𒆂̃X�e�[�W�͑傫���\��
		if (StageList[i]->transform.position.y == 0.0f)
		{
			// �傫���𓙔{��
			StageList[i]->transform.scale.x = 1.5f * 1.0f;
			StageList[i]->transform.scale.y = 0.5f * 1.0f;
			// �s�����ɂ���
			StageList[i]->materialDiffuse.w = 1.0f;
		}
		// �I������Ă��Ȃ��X�e�[�W�͏������������ɂ���
		else
		{
			// �k������
			StageList[i]->transform.scale.x = 1.5f * 0.8f;
			StageList[i]->transform.scale.y = 0.5f * 0.8f;
			// �s�����x��������
			StageList[i]->materialDiffuse.w = 0.7f;
		}

		// ���X�g���ړ������ǂ����𔻒�
		if (selectMoveUp)
		{
			// �C�[�W���O�̍X�V
			selectEase[i]->Update();
			// ���X�g����ړ�������
			if (StageList[i]->transform.position.y <= moveEndPos[i])
			{
				// �ړ����I�����Ă���Ȃ�ŏI���W�������Ă���
				StageList[i]->transform.position.y = moveEndPos[i];
				// �����ɕ\������Ă���X�e�[�W��0�������Ă���
				StageList[stageNum - 1]->transform.position.y = 0.0f;
				// ��ړ��t���O�����낷
				selectMoveUp = false;
			}
		}
		else if (selectMoveDown)
		{
			// �C�[�W���O�̍X�V
			selectEase[i]->Update();
			// ���X�g�����ړ�������
			if (StageList[i]->transform.position.y >= moveEndPos[i])
			{
				// �ړ����I�����Ă���Ȃ�ŏI���W�������Ă���
				StageList[i]->transform.position.y = moveEndPos[i];
				// �����ɕ\������Ă���X�e�[�W��0�������Ă���
				StageList[stageNum - 1]->transform.position.y = 0.0f;
				// ��ړ��t���O�����낷
				selectMoveDown = false;
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
