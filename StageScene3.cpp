#include "StageScene3.h"
#include "CSceneManager.h"	// シーン切り替えのためにインクルード
#include "CGameManager.h"

StageScene3::StageScene3()
{
	// カメラオブジェクトの実体化
	Cam = new CCamera;

	// プレイヤーの実体化と初期化
	bg = new CGameObject(vertexBufferObject, CTextureLoader::GetInstance()->GetTex(TEX_ID::BG3), { 1.0f ,1.0f });
	// 背景の設定
	bg->SetUseingCamera(Cam);
	bg->transform.scale = { 1920.0f * 0.0021f, 1080.0f * 0.0021f, 1.0f };
	bg->transform.position.z = 0.4f;

	//	ゲームオブジェクトの実体化と初期化
	//	ものさし（スタート）
	ruler[0] = new CGameObject(vertexBufferObject, CTextureLoader::GetInstance()->GetTex(TEX_ID::RULER), {1.0f,1.0f});
	ruler[0]->SetUseingCamera(Cam);
	ruler[0]->transform.scale = { 0.3f, 2.5f, 1.0f };
	ruler[0]->transform.position = { -2.0f, 0.0f, 0.3f };
	Objects.push_back(ruler[0]);

	//	ものさし（ゴール）
	ruler[1] = new CGameObject(vertexBufferObject, CTextureLoader::GetInstance()->GetTex(TEX_ID::RULER), { 1.0f,1.0f });
	ruler[1]->SetUseingCamera(Cam);
	ruler[1]->transform.scale = { 0.3f, 2.5f, 1.0f };
	ruler[1]->transform.position = { 18.55f, 0.0f, 0.3f };
	ruler[1]->transform.rotation = 180.0f;
	Objects.push_back(ruler[1]);

	// 障害物
	pencil = new CGameObject(vertexBufferObject, CTextureLoader::GetInstance()->GetTex(TEX_ID::PENCIL));
	pencil->SetUseingCamera(Cam);
	pencil->transform.scale = { 0.07f, 0.5f, 1.0f };
	pencil->transform.position = { 0.45f, -0.8f, 0.3f };
	pencil->transform.rotation = { 50.0f };
	Objects.push_back(pencil);

	pencil3 = new CGameObject(vertexBufferObject, CTextureLoader::GetInstance()->GetTex(TEX_ID::PENCIL));
	pencil3->SetUseingCamera(Cam);
	pencil3->transform.scale = { 0.13f, 0.6f, 1.0f };
	pencil3->transform.position = { 10.98f, -0.525f, 0.3f };
	pencil3->transform.rotation = { 180 };
	Objects.push_back(pencil3);

	// プレイヤーの実体化と初期化
	player = new CPlayer(vertexBufferCharacter, CTextureLoader::GetInstance()->GetTex(TEX_ID::PLAYER), { 0.2f ,0.1f });
	// オブジェクトをリストに登録
	Objects.push_back(player);
	// 自身の投影に使うカメラの設定
	player->SetUseingCamera(Cam);
	// スケールの設定
	player->transform * 0.3f;
	player->transform.position.z = -0.1f;
	// コライダーの設定
	player->Bcol = { player->transform.position.x, player->transform.position.y, 0.13f, 0.3f };
	player->transform.position.x = -1.5f;
	// アニメーションの初期化
	player->InitAnimParameter(true, 5, 10, ANIM_PATTERN::NO_ANIM, 0.2f);

	// スムージングの実体化
	camSmooth = new CSmoothing;
	camSmooth->InitSmooth(&player->transform.position.x, &Cam->cameraPos.x, 0.1f);

	// 構成するステージと使用するカメラのポインタを指定
	CScene::CreateStage(TERRAIN_ID::STAGE_3, Cam);
}

StageScene3::~StageScene3()
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

void StageScene3::Update()
{
	// セレクト画面に戻る
	if (gInput->IsControllerButtonTrigger(XINPUT_GAMEPAD_START) &&
		CGameManager::GetInstance()->GetGameState() == GAME_STATE::START)
	{
		//	サウンドの停止
		XA_Stop(SOUND_LABEL_FLY);
		CSceneManager::GetInstance()->ChangeScene(SCENE_ID::SELECT, FADE_TYPE::ERASER);
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
	if (Cam->cameraPos.x > 16.65f)
	{
		Cam->cameraPos.x = 16.65f;
	}

	Cam->Update();

	CScene::UpdateTerrain();

	// 背景追従
	bg->transform.position.x = Cam->cameraPos.x;

}

void StageScene3::Draw()
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
