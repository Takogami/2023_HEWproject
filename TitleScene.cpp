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

	Title = new CGameObject(vertexBufferObject, CTextureLoader::GetInstance()->GetTex(TEX_ID::TITLE), { 1.0f ,1.0f });
	Objects.push_back(Title);

	// �w�i�̐ݒ�
	bg->SetUseingCamera(Cam);
	bg->transform.scale = { 1920.0f * 0.0021f, 1080.0f * 0.0021f, 1.0f };
	bg->transform.position.z = 0.99f;

	Title->SetUseingCamera(Cam);
	Title->transform.scale = { 1271.0f * 0.0021f , 299.0f * 0.0021f, 1.0f};
	Title->transform.position.z = 0.98f;
	Title->transform.position.y = 0.55f;

	//�v���C���[�̎��̉��Ə�����
	cursor = new CCursor(vertexBufferCharacter, CTextureLoader::GetInstance()->GetTex(TEX_ID::TAKO));
	// �I�u�W�F�N�g�����X�g�ɓo�^
	Objects.push_back(cursor);
	cursor->transform * 0.15f;
	cursor->transform.position = { -0.424f, -0.3f };

	//�v���C���[�̎��̉��Ə�����
	goToSelect = new CGameObject(vertexBufferCharacter, CTextureLoader::GetInstance()->GetTex(TEX_ID::STAGE));
	// �I�u�W�F�N�g�����X�g�ɓo�^
	Objects.push_back(goToSelect);
	goToSelect->transform * 0.5f;
	goToSelect->transform.position = { 0.0f, -0.3f };

	//�v���C���[�̎��̉��Ə�����
	goToOption = new CGameObject(vertexBufferCharacter, CTextureLoader::GetInstance()->GetTex(TEX_ID::STAGE));
	// �I�u�W�F�N�g�����X�g�ɓo�^
	Objects.push_back(goToOption);
	goToOption->transform * 0.5f;
	goToOption->transform.position = { 0.0f, -0.6f };

	//�v���C���[�̎��̉��Ə�����
	exitGame = new CGameObject(vertexBufferCharacter, CTextureLoader::GetInstance()->GetTex(TEX_ID::STAGE));
	// �I�u�W�F�N�g�����X�g�ɓo�^
	Objects.push_back(exitGame);
	exitGame->transform * 0.5f;
	exitGame->transform.position = { 0.0f, -0.9f };

	titleEase = new CEase();
	titleEase->Init(&Title->transform.position.y, 0.5f, 1.0f, 0.0f, EASE::easeOutBounce);
}

// �f�X�X�g���N�^
TitleScene::~TitleScene()
{
	// ���_�o�b�t�@�̉��
	SAFE_RELEASE(vertexBufferCharacter);

	// �e�I�u�W�F�N�g�̃��������
	for (auto it = Objects.begin(); it != Objects.end(); it++)
	{
		delete (*it);
	}

	// �J�����̍폜
	delete Cam;
}

void TitleScene::Update()
{
	if (gInput->IsControllerButtonTrigger(XINPUT_GAMEPAD_B) || gInput->GetKeyTrigger(VK_RETURN))
	{
		//CCursor�ł̗񋓌^��Scene���擾����
		cursorPoint = cursor->GetCursorPoint();

		switch (cursorPoint)
		{
		case CCursor_Point::STAGE:
			// �X�e�[�W�̏ꍇ�̏���������
			CSceneManager::GetInstance()->ChangeScene(SCENE_ID::SELECT);
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

	// �J�����̃A�b�v�f�[�g
	Cam->Update();
	titleEase->Update();

	if (titleEase->GetState() == STATE::END && TitleEaseFg)
	{
		titleEase->Init(&Title->transform.position.y, 0.5f, 1.0f, 0.0f, EASE::easeOutBounce);
		TitleEaseFg = false;
	}
	else if (titleEase->GetState() == STATE::END && !TitleEaseFg)
	{
		titleEase->Init(&Title->transform.position.y, 0.55f, 1.0f, 0.0f, EASE::easeInOutQuint);
		TitleEaseFg = true;
	}


	// �e�I�u�W�F�N�g�̍X�V
	for (auto it = Objects.begin(); it != Objects.end(); it++)
	{
		(*it)->Update();
	}
}

void TitleScene::Draw()
{
	D3D_ClearScreen();

	// �e�I�u�W�F�N�g�̕`��
	for (auto it = Objects.begin(); it != Objects.end(); it++)
	{
		(*it)->Draw();
	}

	// ��ʍX�V
	D3D_UpdateScreen();
}

