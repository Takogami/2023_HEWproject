/* インクルード */
#include "CGame.h"

//コンストラクタ
CGame::CGame()
{
	// TextureLoaderの唯一のインスタンスを生成
	TextureLoader = CTextureLoader::GetInstance();
	TextureLoader->LoadTexture();

	// TerrainLoaderの唯一のインスタンスを生成
	TerrainLoader = CTerrainLoader::GetInstance();

	// SceneManagerの唯一のインスタンスを生成
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

