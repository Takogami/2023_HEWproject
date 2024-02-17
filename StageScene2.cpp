/* インクルード */
#include "StageScene2.h"
#include "CSceneManager.h"	// シーン切り替えのためにインクルード
#include "CGameManager.h"

StageScene2::StageScene2()
{
	// カメラオブジェクトの実体化
	Cam = new CCamera;

	// プレイヤーの実体化と初期化
	bg = new CGameObject(vertexBufferObject, CTextureLoader::GetInstance()->GetTex(TEX_ID::BG2), { 1.0f ,1.0f });
	// 背景の設定
	bg->SetUseingCamera(Cam);
	bg->transform.scale = { 1920.0f * 0.0021f, 1080.0f * 0.0021f, 1.0f };
	bg->transform.position.z = 0.4f;

	// 障害物
	zyougi = new CGameObject(vertexBufferObject, CTextureLoader::GetInstance()->GetTex(TEX_ID::RULER));
	zyougi->SetUseingCamera(Cam);
	zyougi->transform.scale = { 0.3f, 2.3f, 1.0f };
	zyougi->transform.position = { -1.95f, 0.0f, 0.3f };
	Objects.push_back(zyougi);

	zyougi2 = new CGameObject(vertexBufferObject, CTextureLoader::GetInstance()->GetTex(TEX_ID::RULER));
	zyougi2->SetUseingCamera(Cam);
	zyougi2->transform.scale = { 0.3f, 2.3f, 1.0f };
	zyougi2->transform.position = { 10.2f, 0.0f, 0.3f };
	Objects.push_back(zyougi2);

	// 障害物
	book = new CGameObject(vertexBufferObject, CTextureLoader::GetInstance()->GetTex(TEX_ID::BOOK_OBJ2));
	book->SetUseingCamera(Cam);
	book->transform.scale = { 0.6f, 0.3f, 1.0f };
	book->transform.position = { 2.6f, -0.84f, 0.3f };
	Objects.push_back(book);

	// 障害物
	pencil = new CGameObject(vertexBufferObject, CTextureLoader::GetInstance()->GetTex(TEX_ID::PENCIL));
	pencil->SetUseingCamera(Cam);
	pencil->transform.scale = { 0.13f, 1.0f, 1.0f };
	pencil->transform.position = { 6.025f, -0.1f, 0.3f };
	Objects.push_back(pencil);

	// プレイヤーの実体化と初期化
	player = new CPlayer(vertexBufferCharacter, CTextureLoader::GetInstance()->GetTex(TEX_ID::PLAYER), { 0.2f ,0.1f });
	// オブジェクトをリストに登録
	Objects.push_back(player);
	// 自身の投影に使うカメラの設定
	player->SetUseingCamera(Cam);
	// スケールの設定
	player->transform * 0.25f;
	player->transform.position.z = -0.1f;
	// コライダーの設定
	player->Bcol = { player->transform.position.x, player->transform.position.y, 0.15f, 0.25f};
	player->transform.position.x = -1.5f;
	player->transform.position.y = 0.5f;
	// アニメーションの初期化
	player->InitAnimParameter(true, 5, 10, ANIM_PATTERN::NO_ANIM, 0.2f);

	// スムージングの実体化
	camSmooth = new CSmoothing;
	camSmooth->InitSmooth(&player->transform.position.x, &Cam->cameraPos.x, 0.1f);

	// 構成するステージと使用するカメラのポインタを指定
	CScene::CreateStage(TERRAIN_ID::STAGE_1, Cam);
}

StageScene2::~StageScene2()
{
	// 頂点バッファの解放
	SAFE_RELEASE(vertexBufferCharacter);
	SAFE_RELEASE(vertexBufferObject);

	delete bg;

	// 各オブジェクトのメモリ解放
	for (auto it = Objects.begin(); it != Objects.end(); it++)
	{
		delete (*it);
	}

	// カメラオブジェクトの削除
	delete Cam;
	delete camSmooth;

	// ステージの後片付け
	CScene::DestroyStage();
}

void StageScene2::Update()
{
	if (gInput->GetKeyTrigger(VK_DELETE))
	{
		CGameManager::GetInstance()->AddDamage(1);
	}

	// クリア、ゲームオーバーでシーン遷移
	if (player->GetState() == PState::CLEAR_GAMEOVER && !changeSceneFlg)
	{
		// クリアなら、シーン遷移演出を変える
		if (CGameManager::GetInstance()->GetGameState() == GAME_STATE::CLEAR)
		{
			CSceneManager::GetInstance()->ChangeScene(SCENE_ID::RESULT, FADE_TYPE::ERASER);
		}
		else
		{
			CSceneManager::GetInstance()->ChangeScene(SCENE_ID::RESULT);
		}
		changeSceneFlg = true;
	}

	// 各オブジェクトの更新
	for (auto it = Objects.begin(); it != Objects.end(); it++)
	{
		(*it)->Update();
	}

	CGameManager::GetInstance()->Update();

	camSmooth->Update();
	// カメラ移動の限界
	if (Cam->cameraPos.x < 0.0f)
	{
		Cam->cameraPos.x = 0.0f;
	}

	Cam->Update();

	CScene::UpdateTerrain();

	// 背景追従
	bg->transform.position.x = Cam->cameraPos.x;

}

void StageScene2::Draw()
{
	// 背景の描画
	bg->Draw();

	// ゲームオーバーの演出が行われていないなら
	if (CGameManager::GetInstance()->GetGameState() != GAME_STATE::TIME_UP &&
		CGameManager::GetInstance()->GetGameState() != GAME_STATE::ZERO_HP)
	{
		// 地形の描画
		DrawTerrain();
	}
	// 各オブジェクトの描画
	for (auto it = Objects.begin(); it != Objects.end(); it++)
	{
		(*it)->Draw();
	}

	CGameManager::GetInstance()->Draw();

}