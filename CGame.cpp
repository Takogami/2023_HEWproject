#include "CGame.h"
#include "CInput.h"

//�R���X�g���N�^
CGame::CGame()
{
	// TextureLoader�̗B��̃C���X�^���X�𐶐�
	TextureLoader = CTextureLoader::GetInstance();
	TextureLoader->LoadTexture();

	// TerrainLoader�̗B��̃C���X�^���X�𐶐�
	TerrainLoader = CTerrainLoader::GetInstance();

	// �V�[���}�l�[�W���[�̎��̉�
	SceneManager = new CSceneManager;
}

void CGame::Update()
{
	// ���̓��͏��� (�{�^�����͂��\�ɂȂ���)
	if (gInput->IsControllerButtonPressed(XINPUT_GAMEPAD_A))
	{
		SceneManager->ChangeScene(SCENE_ID::RESULT);
	}
	else if (gInput->IsControllerButtonPressed(XINPUT_GAMEPAD_B))
	{
		SceneManager->ChangeScene(SCENE_ID::TITLE);
	}

	SceneManager->Update();
}

CGame::~CGame()
{
	delete SceneManager;

	TextureLoader->UnloadTexture();
}

