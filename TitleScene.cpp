/* インクルード */
#include "TitleScene.h"
#include "CTextureLoader.h"

// コンストラクタ
TitleScene::TitleScene()
{
	// カメラオブジェクトの実体化
	Cam = new CCamera;

	//プレイヤーの実体化と初期化
	player = new CGameObject(vertexBufferCharacter, CTextureLoader::GetInstance()->GetTex(TEX_ID::CHAR1), {0.33f ,0.25f});
	//自身の投影に使うカメラの設定
	player->SetUseingCamera(Cam);
	player->transform * 0.5f;

	//プレイヤーの実体化と初期化
	player2 = new CGameObject(vertexBufferCharacter, CTextureLoader::GetInstance()->GetTex(TEX_ID::TAKO));
	//自身の投影にカメラを使用しない
	//player2->SetUseingCamera(Cam);
	player2->transform * 0.15f;
	player2->transform.position = { -1.924f, 1.051f };
}

// デスストラクタ
TitleScene::~TitleScene()
{
	SAFE_RELEASE(vertexBufferCharacter);

	delete player;
	delete player2;
	delete Cam;
}

void TitleScene::Update()
{
	// プレイヤー１の更新
	player->Update();
	// プレイヤー２の更新(カメラ不使用)
	player2->Update();
}

void TitleScene::Draw()
{
	D3D_ClearScreen();

	// プレイヤー１の描画
	player->Draw();
	// プレイヤー２の描画
	player2->Draw();

	// 画面更新
	D3D_UpdateScreen();
}

