/* インクルード */
#include "TitleScene.h"
#include "CSceneManager.h"

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

	// 背景の設定
	bg->SetUseingCamera(Cam);
	bg->transform.scale = { 1920.0f * 0.0021f, 1080.0f * 0.0021f, 1.0f };
	bg->transform.position.z = 0.99f;

	Title->SetUseingCamera(Cam);
	Title->transform.scale = { 1271.0f * 0.0021f , 299.0f * 0.0021f, 1.0f};
	Title->transform.position.z = 0.98f;
	Title->transform.position.y = 0.55f;

	//プレイヤーの実体化と初期化
	cursor = new CCursor(vertexBufferCharacter, CTextureLoader::GetInstance()->GetTex(TEX_ID::TAKO));
	// オブジェクトをリストに登録
	Objects.push_back(cursor);
	cursor->transform * 0.15f;
	cursor->transform.position = { -0.424f, -0.3f };

	//プレイヤーの実体化と初期化
	goToSelect = new CGameObject(vertexBufferCharacter, CTextureLoader::GetInstance()->GetTex(TEX_ID::STAGE));
	// オブジェクトをリストに登録
	Objects.push_back(goToSelect);
	goToSelect->transform * 0.5f;
	goToSelect->transform.position = { 0.0f, -0.3f };

	//プレイヤーの実体化と初期化
	goToOption = new CGameObject(vertexBufferCharacter, CTextureLoader::GetInstance()->GetTex(TEX_ID::STAGE));
	// オブジェクトをリストに登録
	Objects.push_back(goToOption);
	goToOption->transform * 0.5f;
	goToOption->transform.position = { 0.0f, -0.6f };

	//プレイヤーの実体化と初期化
	exitGame = new CGameObject(vertexBufferCharacter, CTextureLoader::GetInstance()->GetTex(TEX_ID::STAGE));
	// オブジェクトをリストに登録
	Objects.push_back(exitGame);
	exitGame->transform * 0.5f;
	exitGame->transform.position = { 0.0f, -0.9f };

	titleEase = new CEase();
	titleEase->Init(&Title->transform.position.y, 0.5f, 1.0f, 0.0f, EASE::easeOutBounce);
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
	if (gInput->IsControllerButtonTrigger(XINPUT_GAMEPAD_B) || gInput->GetKeyTrigger(VK_RETURN))
	{
		//CCursorでの列挙型のSceneを取得する
		cursorPoint = cursor->GetCursorPoint();

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
	titleEase->Update();

	if (titleEase->GetState() == STATE::END && TitleEaseFg)
	{
		titleEase->Init(&Title->transform.position.y, 0.5f, 1.0f, 0.0f, EASE::easeOutBounce);
		TitleEaseFg = false;
	}
	else if (titleEase->GetState() == STATE::END && !TitleEaseFg)
	{
		titleEase->Init(&Title->transform.position.y, 0.55f, 1.0f, 0.0f, EASE::easeInOutQuint);
		TitleEaseFg = true;
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

