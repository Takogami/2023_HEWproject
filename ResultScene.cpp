/* インクルード */
#include "ResultScene.h"
#include "CSceneManager.h"	// シーン切り替えのためにインクルード

ResultScene::ResultScene()
{
	// カメラオブジェクトの実体化
	Cam = new CCamera;

	// プレイヤーの実体化と初期化
	player = new CGameObject(vertexBufferCharacter, CTextureLoader::GetInstance()->GetTex(TEX_ID::TAKO), { 0.33f ,0.25f });
	// オブジェクトをリストに登録
	Objects.push_back(player);
	// 自身の投影に使うカメラの設定
	player->SetUseingCamera(Cam);
	// スケールの設定
	player->transform * 0.2f;
	// コライダーの設定
	player->Bcol = { player->transform.position.x, player->transform.position.y, 0.2f, 0.2f};

	// 構成するステージと使用するカメラのポインタを指定
	CScene::CreateStage(TERRAIN_ID::STAGE_1, Cam);
}

ResultScene::~ResultScene()
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

void ResultScene::Update()
{
	if (gInput->IsControllerButtonRepeat(XINPUT_GAMEPAD_A, 100, 10) || gInput->GetKeyTrigger(VK_RETURN))
	{
		CSceneManager::GetInstance()->ChangeScene(SCENE_ID::TITLE);
	}

	/* ↓ 仮説プレイヤー操作 後でPlayerクラスに移植予定 ↓ */

	// 向きを戻す
	dirX = 0.0f;
	dirY = 0.0f;

	// 移動入力
	//	コントローラー用の入力
	if (gInput->GetLeftStickY() > 0.0f || gInput->GetLeftStickY() < 0.0f || gInput->GetKeyPress(VK_DOWN))
	{
		dirY = gInput->GetLeftStickY();

	}
	else if (gInput->GetRightStickY() > 0.0f || gInput->GetRightStickY() < 0.0f || gInput->GetKeyPress(VK_UP))
	{
		dirY = gInput->GetRightStickY();
	}
	if (gInput->GetLeftStickX() > 0.0f || gInput->GetLeftStickX() < 0.0f || gInput->GetKeyPress(VK_LEFT))
	{
		dirX = gInput->GetLeftStickX();
	}
	else if (gInput->GetRightStickX() > 0.0f || gInput->GetRightStickX() < 0.0f || gInput->GetKeyPress(VK_RIGHT))
	{
		dirX = gInput->GetRightStickX();
	}

	//	移動入力（キーボード）
	if (gInput->GetKeyPress(VK_DOWN))
	{
		dirY = -1.0f;
	}
	else if (gInput->GetKeyPress(VK_UP))
	{
		dirY = 1.0f;
	}

	if (gInput->GetKeyPress(VK_LEFT))
	{
		dirX = -1.0f;
	}
	else if (gInput->GetKeyPress(VK_RIGHT))
	{
		dirX = 1.0f;
	}

	// ベクトルに速度をかけて位置を変更
	player->transform.position.x += dirX * 0.03f;
	player->transform.position.y += dirY * 0.03f;

	/* ↑ 仮説プレイヤー操作 後でPlayerクラスに移植予定 ↑ */

	Cam->Update();

	// 各オブジェクトの更新
	for (auto it = Objects.begin(); it != Objects.end(); it++)
	{
		(*it)->Update();
	}

	// マップのオブジェクトとの当たり判定を取る
	for (auto it = CScene::map_object.begin(); it != CScene::map_object.end(); it++)
	{
		// 地形とプレイヤーの当たり判定
		if (TestBoxCollision(player->Bcol, (*it)->Bcol))
		{
			// 位置を補正する
			CorrectPosition(player, *it);
		}
	}

}

void ResultScene::Draw()
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
