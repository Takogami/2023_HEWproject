/* �C���N���[�h */
#include "TitleScene.h"
#include "CTextureLoader.h"

// �R���X�g���N�^
TitleScene::TitleScene()
{
	// �J�����I�u�W�F�N�g�̎��̉�
	Cam = new CCamera;

	//�v���C���[�̎��̉��Ə�����
	player = new CGameObject(vertexBufferCharacter, CTextureLoader::GetInstance()->GetTex(TEX_ID::CHAR1), {0.33f ,0.25f});
	//���g�̓��e�Ɏg���J�����̐ݒ�
	player->SetUseingCamera(Cam);
	player->transform * 0.5f;

	//�v���C���[�̎��̉��Ə�����
	player2 = new CGameObject(vertexBufferCharacter, CTextureLoader::GetInstance()->GetTex(TEX_ID::TAKO));
	//���g�̓��e�ɃJ�������g�p���Ȃ�
	//player2->SetUseingCamera(Cam);
	player2->transform * 0.15f;
	player2->transform.position = { -1.924f, 1.051f };
}

// �f�X�X�g���N�^
TitleScene::~TitleScene()
{
	SAFE_RELEASE(vertexBufferCharacter);

	delete player;
	delete player2;
	delete Cam;
}

void TitleScene::Update()
{
	// �v���C���[�P�̍X�V
	player->Update();
	// �v���C���[�Q�̍X�V(�J�����s�g�p)
	player2->Update();
}

void TitleScene::Draw()
{
	D3D_ClearScreen();

	// �v���C���[�P�̕`��
	player->Draw();
	// �v���C���[�Q�̕`��
	player2->Draw();

	// ��ʍX�V
	D3D_UpdateScreen();
}

