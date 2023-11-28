/* �C���N���[�h */
#include "ResultScene.h"
#include "CSceneManager.h"	// �V�[���؂�ւ��̂��߂ɃC���N���[�h

ResultScene::ResultScene()
{
	// �J�����I�u�W�F�N�g�̎��̉�
	Cam = new CCamera;

	// �v���C���[�̎��̉��Ə�����
	player = new CGameObject(vertexBufferCharacter, CTextureLoader::GetInstance()->GetTex(TEX_ID::TAKO), { 0.33f ,0.25f });
	// �I�u�W�F�N�g�����X�g�ɓo�^
	Objects.push_back(player);
	// ���g�̓��e�Ɏg���J�����̐ݒ�
	player->SetUseingCamera(Cam);
	// �X�P�[���̐ݒ�
	player->transform * 0.2f;
	// �R���C�_�[�̐ݒ�
	player->Bcol = { player->transform.position.x, player->transform.position.y, 0.2f, 0.2f};

	// �\������X�e�[�W�Ǝg�p����J�����̃|�C���^���w��
	CScene::CreateStage(TERRAIN_ID::STAGE_1, Cam);
}

ResultScene::~ResultScene()
{
	// ���_�o�b�t�@�̉��
	SAFE_RELEASE(vertexBufferCharacter);

	// �e�I�u�W�F�N�g�̃��������
	for (auto it = Objects.begin(); it != Objects.end(); it++)
	{
		delete (*it);
	}

	// �J�����I�u�W�F�N�g�̍폜
	delete Cam;

	// �X�e�[�W�̌�Еt��
	CScene::DestroyStage();
}

void ResultScene::Update()
{
	if (gInput->IsControllerButtonRepeat(XINPUT_GAMEPAD_A, 100, 10) || gInput->GetKeyTrigger(VK_RETURN))
	{
		CSceneManager::GetInstance()->ChangeScene(SCENE_ID::TITLE);
	}

	/* �� �����v���C���[���� ���Player�N���X�ɈڐA�\�� �� */

	// ������߂�
	dirX = 0.0f;
	dirY = 0.0f;

	// �ړ�����
	//	�R���g���[���[�p�̓���
	if (gInput->GetLeftStickY() > 0.0f || gInput->GetLeftStickY() < 0.0f || gInput->GetKeyPress(VK_DOWN))
	{
		dirY = gInput->GetLeftStickY();

	}
	else if (gInput->GetRightStickY() > 0.0f || gInput->GetRightStickY() < 0.0f || gInput->GetKeyPress(VK_UP))
	{
		dirY = gInput->GetRightStickY();
	}
	if (gInput->GetLeftStickX() > 0.0f || gInput->GetLeftStickX() < 0.0f || gInput->GetKeyPress(VK_LEFT))
	{
		dirX = gInput->GetLeftStickX();
	}
	else if (gInput->GetRightStickX() > 0.0f || gInput->GetRightStickX() < 0.0f || gInput->GetKeyPress(VK_RIGHT))
	{
		dirX = gInput->GetRightStickX();
	}

	//	�ړ����́i�L�[�{�[�h�j
	if (gInput->GetKeyPress(VK_DOWN))
	{
		dirY = -1.0f;
	}
	else if (gInput->GetKeyPress(VK_UP))
	{
		dirY = 1.0f;
	}

	if (gInput->GetKeyPress(VK_LEFT))
	{
		dirX = -1.0f;
	}
	else if (gInput->GetKeyPress(VK_RIGHT))
	{
		dirX = 1.0f;
	}

	// �x�N�g���ɑ��x�������Ĉʒu��ύX
	player->transform.position.x += dirX * 0.03f;
	player->transform.position.y += dirY * 0.03f;

	/* �� �����v���C���[���� ���Player�N���X�ɈڐA�\�� �� */

	Cam->Update();

	// �e�I�u�W�F�N�g�̍X�V
	for (auto it = Objects.begin(); it != Objects.end(); it++)
	{
		(*it)->Update();
	}

	// �}�b�v�̃I�u�W�F�N�g�Ƃ̓����蔻������
	for (auto it = CScene::map_object.begin(); it != CScene::map_object.end(); it++)
	{
		// �n�`�ƃv���C���[�̓����蔻��
		if (TestBoxCollision(player->Bcol, (*it)->Bcol))
		{
			// �ʒu��␳����
			CorrectPosition(player, *it);
		}
	}

}

void ResultScene::Draw()
{
	D3D_ClearScreen();

	// �n�`�̕`��
	DrawTerrain();

	// �e�I�u�W�F�N�g�̕`��
	for (auto it = Objects.begin(); it != Objects.end(); it++)
	{
		(*it)->Draw();
	}

	// ��ʍX�V
	D3D_UpdateScreen();
}
