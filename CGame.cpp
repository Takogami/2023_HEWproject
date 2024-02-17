/* インクルード */
#include "CGame.h"
#include "xa2.h"

//コンストラクタ
CGame::CGame()
{
	// TextureLoaderの唯一のインスタンスを生成
	TextureLoader = CTextureLoader::GetInstance();
	TextureLoader->LoadTexture();

	// TerrainLoaderの唯一のインスタンスを生成
	TerrainLoader = CTerrainLoader::GetInstance();

	HRESULT hr;
	hr = XA_Initialize();
	if (FAILED(hr))
	{
		MessageBoxA(NULL, "サウンド読み込みに失敗", "エラー", MB_OK | MB_ICONERROR);
	}

	// SceneManagerの唯一のインスタンスを生成
	SceneManager = CSceneManager::GetInstance();
}

void CGame::Update()
{
	SceneManager->Update();

	// escapeキーでゲームを終了
	if (gInput->GetKeyPress(VK_ESCAPE))
	{
		PostQuitMessage(0);
	}
}

CGame::~CGame()
{
	TextureLoader->UnloadTexture();
	XA_Release();
}

