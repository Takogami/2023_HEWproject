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
	bg->transform.scale = { 1920.0f * 0.0021f, 1080.0f * 0.0021f, 1.0f };
	bg->transform.position.z = 0.1f;

	Title->transform.scale = { 1271.0f * 0.0021f , 299.0f * 0.0021f, 1.0f};
	Title->transform.position.y = 0.55f;

	//プレイヤーの実体化と初期化
	cursor = new CCursor(vertexBufferObject, CTextureLoader::GetInstance()->GetTex(TEX_ID::CURSOR));
	// オブジェクトをリストに登録
	Objects.push_back(cursor);
	cursor->transform.scale = { 186.0f * 0.0017f, 54.0f * 0.0017f, 1.0f };
	cursor->transform.rotation = -30.0f;
	cursor->transform.position = { -0.424f, -0.3f };
	cursor->Init({ cursor->transform.position.x, cursor->transform.position.y });

	//プレイヤーの実体化と初期化
	goToSelect = new CGameObject(vertexBufferObject, CTextureLoader::GetInstance()->GetTex(TEX_ID::STAGE));
	// オブジェクトをリストに登録
	Objects.push_back(goToSelect);
	goToSelect->transform * 0.5f;
	goToSelect->transform.position = { 0.0f, -0.3f};

	//プレイヤーの実体化と初期化
	goToOption = new CGameObject(vertexBufferObject, CTextureLoader::GetInstance()->GetTex(TEX_ID::STAGE));
	// オブジェクトをリストに登録
	Objects.push_back(goToOption);
	goToOption->transform * 0.5f;
	goToOption->transform.position = { 0.0f, -0.6f};

	//プレイヤーの実体化と初期化
	exitGame = new CGameObject(vertexBufferObject, CTextureLoader::GetInstance()->GetTex(TEX_ID::STAGE));
	// オブジェクトをリストに登録
	Objects.push_back(exitGame);
	exitGame->transform * 0.5f;
	exitGame->transform.position = { 0.0f, -0.9f};

	titleEase = new CEase();
	titleEase->Init(&Title->transform.position.y, 0.5f, 1.0f, 0, EASE::easeOutBounce);
}

// デスストラクタ
TitleScene::~TitleScene()
{
	// 頂点バッファの解放
	SAFE_RELEASE(vertexBufferObject);

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
		titleEase->Init(&Title->transform.position.y, 0.5f, 1.0f, 0, EASE::easeOutBounce);
		TitleEaseFg = false;
	}
	else if (titleEase->GetState() == STATE::END && !TitleEaseFg)
	{
		titleEase->Init(&Title->transform.position.y, 0.55f, 1.0f, 0, EASE::easeInOutQuint);
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
	// 各オブジェクトの描画
	for (auto it = Objects.begin(); it != Objects.end(); it++)
	{
		(*it)->Draw();
	}
}

