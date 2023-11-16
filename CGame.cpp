#include "CGame.h"
#include "CInput.h"

//コンストラクタ
CGame::CGame()
{
	// TextureLoaderの唯一のインスタンスを生成
	TextureLoader = CTextureLoader::GetInstance();
	TextureLoader->LoadTexture();

	// TerrainLoaderの唯一のインスタンスを生成
	TerrainLoader = CTerrainLoader::GetInstance();

	// シーンマネージャーの実体化
	SceneManager = new CSceneManager;
}

void CGame::Update()
{
	// 仮の入力処理 (ボタン入力が可能になった)
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

