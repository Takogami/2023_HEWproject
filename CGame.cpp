/* �C���N���[�h */
#include "CGame.h"

//�R���X�g���N�^
CGame::CGame()
{
	// TextureLoader�̗B��̃C���X�^���X�𐶐�
	TextureLoader = CTextureLoader::GetInstance();
	TextureLoader->LoadTexture();

	// TerrainLoader�̗B��̃C���X�^���X�𐶐�
	TerrainLoader = CTerrainLoader::GetInstance();

	// SceneManager�̗B��̃C���X�^���X�𐶐�
	SceneManager = CSceneManager::GetInstance();
}

void CGame::Update()
{
	SceneManager->Update();

	// escape�L�[�ŃQ�[�����I��
	if (gInput->GetKeyPress(VK_ESCAPE))
	{
		PostQuitMessage(0);
	}
}

CGame::~CGame()
{
	TextureLoader->UnloadTexture();
}

