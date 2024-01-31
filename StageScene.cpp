#include "StageScene.h"
#include "CSceneManager.h"	// シーン切り替えのためにインクルード

StageScene::StageScene()
{
	// カメラオブジェクトの実体化
	Cam = new CCamera;

	// プレイヤーの実体化と初期化
	player = new CPlayer(vertexBufferCharacter, CTextureLoader::GetInstance()->GetTex(TEX_ID::TAKO), { 0.33f ,0.25f });
	// オブジェクトをリストに登録
	Objects.push_back(player);
	// 自身の投影に使うカメラの設定
	player->SetUseingCamera(Cam);
	// スケールの設定
	player->transform * 0.2f;
	player->transform.position.z = -0.3f;
	// コライダーの設定
	player->Bcol = { player->transform.position.x, player->transform.position.y, 0.2f, 0.2f };

	// 構成するステージと使用するカメラのポインタを指定
	CScene::CreateStage(TERRAIN_ID::STAGE_2, Cam);
}

StageScene::~StageScene()
{
	// 頂点バッファの解放
	SAFE_RELEASE(vertexBufferCharacter);

	// 各オブジェクトのメモリ解放
	for (auto it = Objects.begin(); it != Objects.end(); it++)
	{
		delete (*it);
	}

	// カメラオブジェクトの削除
	delete Cam;

	// ステージの後片付け
	CScene::DestroyStage();
}

void StageScene::Update()
{
	if (gInput->IsControllerButtonTrigger(XINPUT_GAMEPAD_B) || gInput->GetKeyTrigger(VK_RETURN))
	{
		CSceneManager::GetInstance()->ChangeScene(SCENE_ID::TITLE);
	}

	// 各オブジェクトの更新
	for (auto it = Objects.begin(); it != Objects.end(); it++)
	{
		(*it)->Update();
	}

	Cam->cameraPos.x = player->transform.position.x;
	Cam->Update();
}

void StageScene::Draw()
{
	D3D_ClearScreen();

	// 地形の描画
	DrawTerrain();

	// 各オブジェクトの描画
	for (auto it = Objects.begin(); it != Objects.end(); it++)
	{
		(*it)->Draw();
	}

	// 画面更新
	D3D_UpdateScreen();
}
