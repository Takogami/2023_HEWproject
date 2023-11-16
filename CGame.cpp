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
}

CGame::~CGame()
{
	TextureLoader->UnloadTexture();
}

