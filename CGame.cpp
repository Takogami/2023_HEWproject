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
	SceneManager->Update();
}


void CGame::SetScene(SCENE_STATE nextScene)
{
	//画面遷移開始時
	if (newScene != nextScene)
	{
		newScene = nextScene;	//遷移先画面を保存
		fadeState = FADE_OUT;	//フェードアウトを開始
	}
	//フェードアウト終了で実際にシーンを切り替える
	else
	{
		scene = nextScene;	//画面の切り替え
		fadeState = FADE_IN;//切り替えたのでフェードインの開始

		//シーンごとのBGM再生
		switch (scene)
		{
		case CGame::TITLE:
			break;

		case CGame::STAGE:
			break;

		case CGame::RESULT:
			break;
		}
	}
}

CGame::~CGame()
{
	delete SceneManager;

	TextureLoader->UnloadTexture();
}

void CGame::UpdateTitle()
{
	//画面塗りつぶしと設定
	D3D_ClearScreen();

	//画面更新
	D3D_UpdateScreen();
}

