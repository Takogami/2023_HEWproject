#include "StageScene4.h"
#include "CSceneManager.h"	// シーン切り替えのためにインクルード
#include "CGameManager.h"

StageScene4::StageScene4()
{
	// カメラオブジェクトの実体化
	Cam = new CCamera;

	// プレイヤーの実体化と初期化
	bg = new CGameObject(vertexBufferObject, CTextureLoader::GetInstance()->GetTex(TEX_ID::BG), { 1.0f ,1.0f });
	// オブジェクトをリストに登録
	Objects.push_back(bg);
	// プレイヤーの実体化と初期化
	player = new CPlayer(vertexBufferCharacter, CTextureLoader::GetInstance()->GetTex(TEX_ID::PLAYER), { 0.2f ,0.1f });
	// オブジェクトをリストに登録
	Objects.push_back(player);
	// 自身の投影に使うカメラの設定
	player->SetUseingCamera(Cam);
	// スケールの設定
	player->transform * 0.2f;
	// コライダーの設定
	player->Bcol = { player->transform.position.x, player->transform.position.y, 0.2f, 0.15f };
	// アニメーションの初期化
	player->InitAnimParameter(true, 5, 10, ANIM_PATTERN::NO_ANIM, 0.2f);

	player->transform.position.x += 0.5f;
	player->transform.position.y += 0.5f;

	// 背景の設定
	bg->SetUseingCamera(Cam);
	bg->transform.scale = { 1920.0f * 0.0021f, 1080.0f * 0.0021f, 1.0f };
	bg->transform.position.z = 0.99f;

	// スムージングの実体化
	camSmoothX = new CSmoothing;
	camSmoothY = new CSmoothing;
	camSmoothX->InitSmooth(&player->transform.position.x, &Cam->cameraPos.x, 0.1f);
	camSmoothY->InitSmooth(&player->transform.position.y, &Cam->cameraPos.y, 0.1f);

	// 文字列の設定
	drawStringTest = new CDrawString;
	drawStringTest->SetFont(FontID::KARAKAZE);
	drawStringTest->SetString("これはテストです。abc あいうえお アイウエオ 漢字");
	drawStringTest->SetPosition({ 0.0f, 100.0f });
	drawStringTest->SetFontSize(40.0f);
	drawStringTest->SetFontColor(1.0f, 0.0f, 1.0f);
	drawStringTest->SetFontWeight(FONT_WEIGHT::HEAVY);
	drawStringTest->SetFontStyle(FONT_STYLE::ITALIC);

	drawStringTest2 = new CDrawString;
	drawStringTest2->SetFont(FontID::LETROGO);
	drawStringTest2->SetString("これはテストです。\nabc\nあいうえお\nアイウエオ\n漢字");
	drawStringTest2->SetPosition({ 0.0f, 400.0f });
	drawStringTest2->SetFontSize(30.0f);
	drawStringTest2->SetLineSpacing(20.0f);
	drawStringTest2->SetShadow({ -2.0f, -1.0f }, 0.0f, 0.0f, 0.0f, 0.5f);

	// 構成するステージと使用するカメラのポインタを指定
	CScene::CreateStage(TERRAIN_ID::STAGE_4, Cam);
}

StageScene4::~StageScene4()
{
	// 頂点バッファの解放
	SAFE_RELEASE(vertexBufferCharacter);
	SAFE_RELEASE(vertexBufferObject);

	// 各オブジェクトのメモリ解放
	for (auto it = Objects.begin(); it != Objects.end(); it++)
	{
		delete (*it);
	}

	// カメラオブジェクトの削除
	delete Cam;
	delete camSmoothX;
	delete camSmoothY;

	delete drawStringTest;
	delete drawStringTest2;

	// ステージの後片付け
	CScene::DestroyStage();
}

void StageScene4::Update()
{

	if (gInput->GetKeyTrigger(VK_DELETE))
	{
		CGameManager::GetInstance()->AddDamage(1);
	}

	// タイムアップ、またはHPが0で強制シーン遷移
	if ((CGameManager::GetInstance()->GetGameState() == GAME_STATE::TIME_UP ||
		CGameManager::GetInstance()->GetGameState() == GAME_STATE::ZERO_HP) && !changeSceneFlg)
	{
		CSceneManager::GetInstance()->ChangeScene(SCENE_ID::RESULT);
		changeSceneFlg = true;
	}

	if (gInput->IsControllerButtonTrigger(XINPUT_GAMEPAD_B) || gInput->GetKeyTrigger(VK_RETURN))
	{
		CSceneManager::GetInstance()->ChangeScene(SCENE_ID::RESULT);
	}

	// 各オブジェクトの更新
	for (auto it = Objects.begin(); it != Objects.end(); it++)
	{
		(*it)->Update();
	}

	UpdateTerrain();
	camSmoothX->Update();
	camSmoothY->Update();
	Cam->Update();

	// 背景追従
	bg->transform.position.x = Cam->cameraPos.x;
}

void StageScene4::Draw()
{
	D3D_ClearScreen();

	// 各オブジェクトの描画
	for (auto it = Objects.begin(); it != Objects.end(); it++)
	{
		(*it)->Draw();
	}

	// 地形の描画
	DrawTerrain();

	CGameManager::GetInstance()->Draw();

	// 文字列の描画
	drawStringTest->Draw();
	drawStringTest2->Draw();

	// 画面更新
	D3D_UpdateScreen();
}
