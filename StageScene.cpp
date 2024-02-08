#include "StageScene.h"
#include "CSceneManager.h"	// シーン切り替えのためにインクルード
#include "CGameManager.h"

StageScene::StageScene()
{
	// カメラオブジェクトの実体化
	Cam = new CCamera;

	// プレイヤーの実体化と初期化
	player = new CPlayer(vertexBufferCharacter, CTextureLoader::GetInstance()->GetTex(TEX_ID::BLOCK), { 0.33f ,0.25f });
	// オブジェクトをリストに登録
	Objects.push_back(player);
	// 自身の投影に使うカメラの設定
	player->SetUseingCamera(Cam);
	// スケールの設定
	player->transform * 0.2f;
	// コライダーの設定
	player->Bcol = { player->transform.position.x, player->transform.position.y, 0.2f, 0.2f };

	// ゲームマネージャの初期化
	CGameManager::GetInstance()->Init();

	// シーン遷移フラグの初期化
	changeSceneFlg = false;

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
	// テスト用ダメージ追加
	if (gInput->GetKeyTrigger(VK_DELETE))
	{
		CGameManager::GetInstance()->AddDamage(1);
	}

	// 各オブジェクトの更新
	for (auto it = Objects.begin(); it != Objects.end(); it++)
	{
		(*it)->Update();
	}

	// タイムアップ、またはHPが0で強制シーン遷移
	if (CGameManager::GetInstance()->GetGameState() == GAME_STATE::TIME_UP || 
		CGameManager::GetInstance()->GetGameState() == GAME_STATE::ZERO_HP && !changeSceneFlg)
	{
		CSceneManager::GetInstance()->ChangeScene(SCENE_ID::RESULT);
		changeSceneFlg = true;
	}

	CGameManager::GetInstance()->Update();

	Cam->cameraPos.x = player->transform.position.x;
	Cam->Update();
}

void StageScene::Draw()
{
	// 地形の描画
	DrawTerrain();

	// 各オブジェクトの描画
	for (auto it = Objects.begin(); it != Objects.end(); it++)
	{
		(*it)->Draw();
	}

	CGameManager::GetInstance()->Draw();
}
