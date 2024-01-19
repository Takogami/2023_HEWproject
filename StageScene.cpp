#include "StageScene.h"
#include "CSceneManager.h"	// �V�[���؂�ւ��̂��߂ɃC���N���[�h

StageScene::StageScene()
{
	// �J�����I�u�W�F�N�g�̎��̉�
	Cam = new CCamera;

	// �v���C���[�̎��̉��Ə�����
	player = new CPlayer(vertexBufferCharacter, CTextureLoader::GetInstance()->GetTex(TEX_ID::TAKO), { 0.33f ,0.25f });
	// �I�u�W�F�N�g�����X�g�ɓo�^
	Objects.push_back(player);
	// ���g�̓��e�Ɏg���J�����̐ݒ�
	player->SetUseingCamera(Cam);
	// �X�P�[���̐ݒ�
	player->transform * 0.1f;
	// �R���C�_�[�̐ݒ�
	player->Bcol = { player->transform.position.x, player->transform.position.y, 0.1f, 0.1f };

	// �\������X�e�[�W�Ǝg�p����J�����̃|�C���^���w��
	CScene::CreateStage(TERRAIN_ID::STAGE_2, Cam);
}

StageScene::~StageScene()
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

void StageScene::Update()
{
	if (gInput->IsControllerButtonRepeat(XINPUT_GAMEPAD_B, 60, 5) || gInput->GetKeyTrigger(VK_RETURN))
	{
		CSceneManager::GetInstance()->ChangeScene(SCENE_ID::RESULT);
	}

	// �e�I�u�W�F�N�g�̍X�V
	for (auto it = Objects.begin(); it != Objects.end(); it++)
	{
		(*it)->Update();
	}

	//	���N����֐�
	player->Wind();

	Cam->cameraPos.x = player->transform.position.x;
	Cam->Update();
}

void StageScene::Draw()
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
