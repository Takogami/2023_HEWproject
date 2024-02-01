/* �C���N���[�h */
#include "TitleScene.h"
#include "CSceneManager.h"
#include "CCursor.h"
//extern enum Cursor_Point cursor;

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
	// �v���C���[�̎��̉��Ə�����
	player = new CGameObject(vertexBufferCharacter, CTextureLoader::GetInstance()->GetTex(TEX_ID::CHAR1), {0.33f ,0.25f});


	// �I�u�W�F�N�g�����X�g�ɓo�^
	Objects.push_back(player);
	//���g�̓��e�Ɏg���J�����̐ݒ�
	player->SetUseingCamera(Cam);
	player->transform * 0.5f;

	// �w�i�̐ݒ�
	bg->SetUseingCamera(Cam);
	bg->transform.scale = { 1920.0f * 0.0021f, 1080.0f * 0.0021f, 1.0f };
	bg->transform.position.z = 0.99f;

	Title->SetUseingCamera(Cam);
	Title->transform.scale = { 1271.0f * 0.0021f , 299.0f * 0.0021f, 1.0f};
	Title->transform.position.z = 0.98f;
	Title->transform.position.y = 0.5f;

	//�v���C���[�̎��̉��Ə�����
	player2 = new CCursor(vertexBufferCharacter, CTextureLoader::GetInstance()->GetTex(TEX_ID::TAKO));
	// �I�u�W�F�N�g�����X�g�ɓo�^
	Objects.push_back(player2);
	//���g�̓��e�ɃJ�������g�p���Ȃ�
	//player2->SetUseingCamera(Cam);
	player2->transform * 0.15f;
	player2->transform.position = { -0.424f, -0.3f };

	//�v���C���[�̎��̉��Ə�����
	player3 = new CGameObject(vertexBufferCharacter, CTextureLoader::GetInstance()->GetTex(TEX_ID::STAGE));
	// �I�u�W�F�N�g�����X�g�ɓo�^
	Objects.push_back(player3);
	//���g�̓��e�ɃJ�������g�p���Ȃ�
	player3->transform * 0.5f;
	player3->transform.position = { 0.0f, -0.3f };

	//�v���C���[�̎��̉��Ə�����
	player4 = new CGameObject(vertexBufferCharacter, CTextureLoader::GetInstance()->GetTex(TEX_ID::STAGE));
	// �I�u�W�F�N�g�����X�g�ɓo�^
	Objects.push_back(player4);
	//���g�̓��e�ɃJ�������g�p���Ȃ�
	player4->transform * 0.5f;
	player4->transform.position = { 0.0f, -0.6f };

	//�v���C���[�̎��̉��Ə�����
	player5 = new CGameObject(vertexBufferCharacter, CTextureLoader::GetInstance()->GetTex(TEX_ID::STAGE));
	// �I�u�W�F�N�g�����X�g�ɓo�^
	Objects.push_back(player5);
	//���g�̓��e�ɃJ�������g�p���Ȃ�
	player5->transform * 0.5f;
	player5->transform.position = { 0.0f, -0.9f };

	ease = new CEase();
	ease->Init(&Title->transform.scale.x, 1271.0f * 0.0021f * 1.3f, 1.0f, 0.0f, EASE::easeInBounce);

	flg = true;

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
	if (gInput->IsControllerButtonRepeat(XINPUT_GAMEPAD_B, 60, 5) || gInput->GetKeyTrigger(VK_RETURN))
	{
		CSceneManager::GetInstance()->ChangeScene(SCENE_ID::STAGE_01);
	}

	if (gInput->IsControllerButtonTrigger(XINPUT_GAMEPAD_A) || gInput->GetKeyTrigger(VK_RETURN))
	{
		//CCursor�ł̗񋓌^��Scene���擾����
		cursorPoint = player2->GetCursorPoint();

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
	ease->Update();

	if (ease->GetState() == STATE::END && flg == true)
	{
		ease->Init(&Title->transform.scale.x, 1271.0f * 0.0021f * 1.0f, 1.0f, 0.0f, EASE::easeInBounce);
		flg = false;
	}
	else if (ease->GetState() == STATE::END && flg == false)
	{
		ease->Init(&Title->transform.scale.x, 1271.0f * 0.0021f * 1.3f, 1.0f, 0.0f, EASE::easeInBounce);
		flg = true;
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

