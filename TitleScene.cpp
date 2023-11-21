/* �C���N���[�h */
#include "TitleScene.h"
#include "CSceneManager.h"

// �R���X�g���N�^
TitleScene::TitleScene()
{
	// �J�����I�u�W�F�N�g�̎��̉�
	Cam = new CCamera;

	// �v���C���[�̎��̉��Ə�����
	player = new CGameObject(vertexBufferCharacter, CTextureLoader::GetInstance()->GetTex(TEX_ID::CHAR1), {0.33f ,0.25f});
	// �I�u�W�F�N�g�����X�g�ɓo�^
	Objects.push_back(player);
	//���g�̓��e�Ɏg���J�����̐ݒ�
	player->SetUseingCamera(Cam);
	player->transform * 0.5f;

	//�v���C���[�̎��̉��Ə�����
	player2 = new CGameObject(vertexBufferCharacter, CTextureLoader::GetInstance()->GetTex(TEX_ID::TAKO));
	// �I�u�W�F�N�g�����X�g�ɓo�^
	Objects.push_back(player2);
	//���g�̓��e�ɃJ�������g�p���Ȃ�
	//player2->SetUseingCamera(Cam);
	player2->transform * 0.15f;
	player2->transform.position = { -1.924f, 1.051f };
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
	// �Ƃ肠�����e�X�g�p�̓��͏���
	if (gInput->IsControllerButtonPressed(XINPUT_GAMEPAD_A) || gInput->GetKeyTrigger(VK_RETURN))
	{
		CSceneManager::GetInstance()->ChangeScene(SCENE_ID::RESULT);
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
	D3D_ClearScreen();

	// �e�I�u�W�F�N�g�̕`��
	for (auto it = Objects.begin(); it != Objects.end(); it++)
	{
		(*it)->Draw();
	}

	// ��ʍX�V
	D3D_UpdateScreen();
}

