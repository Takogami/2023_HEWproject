/* インクルード */
#include "TitleScene.h"
#include "CSceneManager.h"

// コンストラクタ
TitleScene::TitleScene()
{
	// カメラオブジェクトの実体化
	Cam = new CCamera;

	// プレイヤーの実体化と初期化
	player = new CGameObject(vertexBufferCharacter, CTextureLoader::GetInstance()->GetTex(TEX_ID::CHAR1), {0.33f ,0.25f});
	// オブジェクトをリストに登録
	Objects.push_back(player);
	//自身の投影に使うカメラの設定
	player->SetUseingCamera(Cam);
	player->transform * 0.5f;

	//プレイヤーの実体化と初期化
	player2 = new CGameObject(vertexBufferCharacter, CTextureLoader::GetInstance()->GetTex(TEX_ID::TAKO));
	// オブジェクトをリストに登録
	Objects.push_back(player2);
	//自身の投影にカメラを使用しない
	//player2->SetUseingCamera(Cam);
	player2->transform * 0.15f;
	player2->transform.position = { -1.924f, 1.051f };
}

// デスストラクタ
TitleScene::~TitleScene()
{
	// 頂点バッファの解放
	SAFE_RELEASE(vertexBufferCharacter);

	// 各オブジェクトのメモリ解放
	for (auto it = Objects.begin(); it != Objects.end(); it++)
	{
		delete (*it);
	}

	// カメラの削除
	delete Cam;
}

void TitleScene::Update()
{
	// とりあえずテスト用の入力処理
	if (gInput->IsControllerButtonPressed(XINPUT_GAMEPAD_A) || gInput->GetKeyTrigger(VK_RETURN))
	{
		CSceneManager::GetInstance()->ChangeScene(SCENE_ID::RESULT);
	}

	// カメラのアップデート
	Cam->Update();

	// 各オブジェクトの更新
	for (auto it = Objects.begin(); it != Objects.end(); it++)
	{
		(*it)->Update();
	}
}

void TitleScene::Draw()
{
	D3D_ClearScreen();

	// 各オブジェクトの描画
	for (auto it = Objects.begin(); it != Objects.end(); it++)
	{
		(*it)->Draw();
	}

	// 画面更新
	D3D_UpdateScreen();
}

