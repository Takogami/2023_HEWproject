/* �C���N���[�h */
#include "ResultScene.h"
#include "CSceneManager.h"	// �V�[���؂�ւ��̂��߂ɃC���N���[�h

ResultScene::ResultScene()
{
}

ResultScene::~ResultScene()
{
	// �e�N���X�̃f�X�g���N�^�𖾎��I�ɌĂяo��
	CScene::~CScene();
}

void ResultScene::Update()
{
	if (gInput->IsControllerButtonPressed(XINPUT_GAMEPAD_B))
	{
		CSceneManager::GetInstance()->ChangeScene(SCENE_ID::TITLE);
	}
}

void ResultScene::Draw()
{
	D3D_ClearScreen();
	//��ʍX�V
	D3D_UpdateScreen();
}
