/* インクルード */
#include "TitleScene.h"
#include "CSceneManager.h"
#include "CCursor.h"
//extern enum Cursor_Point cursor;

// コンストラクタ
TitleScene::TitleScene()
{
	// カメラオブジェクトの実体化
	Cam = new CCamera;

	bg = new CGameObject(vertexBufferObject, CTextureLoader::GetInstance()->GetTex(TEX_ID::BG), { 1.0f ,1.0f });
	// オブジェクトをリストに登録
	Objects.push_back(bg);

	Title = new CGameObject(vertexBufferObject, CTextureLoader::GetInstance()->GetTex(TEX_ID::TITLE), { 1.0f ,1.0f });
	Objects.push_back(Title);
	// プレイヤーの実体化と初期化
	player = new CGameObject(vertexBufferCharacter, CTextureLoader::GetInstance()->GetTex(TEX_ID::CHAR1), {0.33f ,0.25f});


	// オブジェクトをリストに登録
	Objects.push_back(player);
	//自身の投影に使うカメラの設定
	player->SetUseingCamera(Cam);
	player->transform * 0.5f;

	// 背景の設定
	bg->SetUseingCamera(Cam);
	bg->transform.scale = { 1920.0f * 0.0021f, 1080.0f * 0.0021f, 1.0f };
	bg->transform.position.z = 0.99f;

	Title->SetUseingCamera(Cam);
	Title->transform.scale = { 1271.0f * 0.0021f , 299.0f * 0.0021f, 1.0f};
	Title->transform.position.z = 0.98f;
	Title->transform.position.y = 0.5f;

	//プレイヤーの実体化と初期化
	player2 = new CCursor(vertexBufferCharacter, CTextureLoader::GetInstance()->GetTex(TEX_ID::TAKO));
	// オブジェクトをリストに登録
	Objects.push_back(player2);
	//自身の投影にカメラを使用しない
	//player2->SetUseingCamera(Cam);
	player2->transform * 0.15f;
	player2->transform.position = { -0.424f, -0.3f };

	//プレイヤーの実体化と初期化
	player3 = new CGameObject(vertexBufferCharacter, CTextureLoader::GetInstance()->GetTex(TEX_ID::STAGE));
	// オブジェクトをリストに登録
	Objects.push_back(player3);
	//自身の投影にカメラを使用しない
	player3->transform * 0.5f;
	player3->transform.position = { 0.0f, -0.3f };

	//プレイヤーの実体化と初期化
	player4 = new CGameObject(vertexBufferCharacter, CTextureLoader::GetInstance()->GetTex(TEX_ID::STAGE));
	// オブジェクトをリストに登録
	Objects.push_back(player4);
	//自身の投影にカメラを使用しない
	player4->transform * 0.5f;
	player4->transform.position = { 0.0f, -0.6f };

	//プレイヤーの実体化と初期化
	player5 = new CGameObject(vertexBufferCharacter, CTextureLoader::GetInstance()->GetTex(TEX_ID::STAGE));
	// オブジェクトをリストに登録
	Objects.push_back(player5);
	//自身の投影にカメラを使用しない
	player5->transform * 0.5f;
	player5->transform.position = { 0.0f, -0.9f };

	ease = new CEase();
	ease->Init(&Title->transform.scale.x, 1271.0f * 0.0021f * 1.3f, 1.0f, 0.0f, EASE::easeInBounce);

	flg = true;

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
	if (gInput->IsControllerButtonRepeat(XINPUT_GAMEPAD_B, 60, 5) || gInput->GetKeyTrigger(VK_RETURN))
	{
		CSceneManager::GetInstance()->ChangeScene(SCENE_ID::STAGE_01);
	}

	if (gInput->IsControllerButtonTrigger(XINPUT_GAMEPAD_A) || gInput->GetKeyTrigger(VK_RETURN))
	{
		//CCursorでの列挙型のSceneを取得する
		cursorPoint = player2->GetCursorPoint();

		switch (cursorPoint)
		{
		case CCursor_Point::STAGE:
			// ステージの場合の処理を書く
			CSceneManager::GetInstance()->ChangeScene(SCENE_ID::SELECT);
			break;
		case CCursor_Point::OPTION:
			// オプションの場合の処理を書く
			break;
		case CCursor_Point::EXIT:
			PostQuitMessage(0);
			// 終了の場合の処理を書く
			break;
		default:
			break;
		}
	}

	// カメラのアップデート
	Cam->Update();
	ease->Update();

	if (ease->GetState() == STATE::END && flg == true)
	{
		ease->Init(&Title->transform.scale.x, 1271.0f * 0.0021f * 1.0f, 1.0f, 0.0f, EASE::easeInBounce);
		flg = false;
	}
	else if (ease->GetState() == STATE::END && flg == false)
	{
		ease->Init(&Title->transform.scale.x, 1271.0f * 0.0021f * 1.3f, 1.0f, 0.0f, EASE::easeInBounce);
		flg = true;
	}


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

