/* �C���N���[�h */
#include "ResultScene.h"
#include "CSceneManager.h"	// �V�[���؂�ւ��̂��߂ɃC���N���[�h

ResultScene::ResultScene()
{
	// �J�����I�u�W�F�N�g�̎��̉�
	Cam = new CCamera;

	// �\������X�e�[�W�Ǝg�p����J�����̃|�C���^���w��
	CScene::CreateStage(TERRAIN_ID::STAGE_1, Cam);
}

ResultScene::~ResultScene()
{
	// �J�����I�u�W�F�N�g�̍폜
	delete Cam;
	// �X�e�[�W�̌�Еt��
	CScene::DestroyStage();
}

void ResultScene::Update()
{
	// �J�������������쓮���Ă��邩�̃e�X�g
	static float test_x = 0.0f;
	test_x += 0.001f;
	Cam->SetCameraPosition(test_x, 0);
	Cam->Update();

	if (gInput->IsControllerButtonRepeat(XINPUT_GAMEPAD_A) || gInput->GetKeyTrigger(VK_RETURN))
	{
		CSceneManager::GetInstance()->ChangeScene(SCENE_ID::TITLE);
	}
}

void ResultScene::Draw()
{
	D3D_ClearScreen();

	// CScene��Draw�𖾎��I�ɌĂяo��(�n�`�̕`��)
	CScene::Draw();

	// ��ʍX�V
	D3D_UpdateScreen();
}
