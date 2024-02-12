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

	// 背景の設定
	bg->transform.scale = { 1920.0f * 0.0021f, 1080.0f * 0.0021f, 1.0f };
	bg->transform.position.z = 0.4f;

	enemyObj = new CGameObject(vertexBufferObject, CTextureLoader::GetInstance()->GetTex(TEX_ID::ENEMY), { 0.5f ,1.0f });
	Objects.push_back(enemyObj);
	enemyObj->transform.position = { 3.5f, 0.2f, 0.3f };
	enemyObj->transform.scale = { 809.0f * 0.0008f, 573.0f * 0.0008f, 1.0f };
	enemyObj->InitAnimParameter(true, 2, 1, ANIM_PATTERN::ENEMY_MOVE, 0.08f);

	enemyObj_reverse = new CGameObject(vertexBufferObject, CTextureLoader::GetInstance()->GetTex(TEX_ID::ENEMY_R), { 0.5f ,1.0f });
	Objects.push_back(enemyObj_reverse);
	enemyObj_reverse->transform.position = { -3.5f, -0.5f, 0.3f };
	enemyObj_reverse->transform.scale = { 809.0f * 0.0008f, 573.0f * 0.0008f, 1.0f };
	enemyObj_reverse->InitAnimParameter(true, 2, 1, ANIM_PATTERN::ENEMY_MOVE, 0.08f);

	playerObj = new CGameObject(vertexBufferObject, CTextureLoader::GetInstance()->GetTex(TEX_ID::PLAYER), { 0.2f ,0.1f });
	// オブジェクトをリストに登録
	Objects.push_back(playerObj);
	playerObj->transform.position = { 2.5f, 0.2f, 0.3f };
	playerObj->transform.scale = {435.0f * 0.0012f, 326.0f * 0.0012f, 1.0f };
	// アニメーションの初期化
	playerObj->InitAnimParameter(true, 5, 10, ANIM_PATTERN::LEFTWALK, 0.2f);

	ruler = new CGameObject(vertexBufferObject, CTextureLoader::GetInstance()->GetTex(TEX_ID::RULER), { 1.0f ,1.0f });
	Objects.push_back(ruler);
	ruler->transform.scale = { 416.0f * 0.001f , 1688.0f * 0.001f, 1.0f };
	ruler->transform.position = { -1.4f, 0.7f, 0.2f };
	ruler->transform.rotation = -45.0f;

	ruler2 = new CGameObject(vertexBufferObject, CTextureLoader::GetInstance()->GetTex(TEX_ID::RULER), { 1.0f ,1.0f });
	Objects.push_back(ruler2);
	ruler2->transform.scale = { 416.0f * 0.0007f , 1688.0f * 0.0007f, 1.0f };
	ruler2->transform.position = { 1.7f, -0.8f, 0.2f };
	ruler2->transform.rotation = 60.0f;

	Title = new CGameObject(vertexBufferObject, CTextureLoader::GetInstance()->GetTex(TEX_ID::TITLE), { 1.0f ,1.0f });
	Objects.push_back(Title);
	Title->transform.scale = { 1271.0f * 0.0021f , 299.0f * 0.0021f, 1.0f};
	Title->transform.position.y = 0.55f;

	//プレイヤーの実体化と初期化
	goToSelect = new CGameObject(vertexBufferObject, CTextureLoader::GetInstance()->GetTex(TEX_ID::PLAY));
	// オブジェクトをリストに登録
	Objects.push_back(goToSelect);
	goToSelect->transform.scale = { 1100.0f * 0.0007f, 447.0f * 0.0007f, 1.0f };
	goToSelect->transform.position = { 0.0f, -0.3f};

	//プレイヤーの実体化と初期化
	goToOption = new CGameObject(vertexBufferObject, CTextureLoader::GetInstance()->GetTex(TEX_ID::OPTION));
	// オブジェクトをリストに登録
	Objects.push_back(goToOption);
	goToOption->transform.scale = { 1100.0f * 0.0007f, 447.0f * 0.0007f, 1.0f };
	goToOption->transform.position = { 0.0f, -0.6f};

	//プレイヤーの実体化と初期化
	exitGame = new CGameObject(vertexBufferObject, CTextureLoader::GetInstance()->GetTex(TEX_ID::EXIT));
	// オブジェクトをリストに登録
	Objects.push_back(exitGame);
	exitGame->transform.scale = { 1100.0f * 0.0007f, 447.0f * 0.0007f, 1.0f };
	exitGame->transform.position = { 0.0f, -0.9f};

	// カーソルの実体化と初期化
	cursor = new CCursor(vertexBufferObject, CTextureLoader::GetInstance()->GetTex(TEX_ID::CURSOR));
	// オブジェクトをリストに登録
	Objects.push_back(cursor);
	cursor->transform.scale = { 186.0f * 0.0017f, 54.0f * 0.0017f, 1.0f };
	cursor->transform.rotation = -30.0f;
	cursor->transform.position = { -0.5f, -0.3f, -0.1f };
	cursor->Init({ cursor->transform.position.x, cursor->transform.position.y });

	// イージングの実体化
	titleEase = new CEase();
	titleEase->Init(&Title->transform.position.y, 0.5f, 1.0f, 0, EASE::easeOutBounce);
	enemyEase = new CEase();
	enemyEase->Init(&enemyObj->transform.position.x, 0.0f, 3.0f, 4, EASE::easeOutCubic);
	enemyEaseR = new CEase();
	enemyEaseR->Init(&enemyObj_reverse->transform.position.x, 0.0f, 3.0f, 4, EASE::easeOutCubic);
	playerFlyEase = new CEase();
	selectEaseX = new CEase();
	selectEaseY = new CEase();
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

	// イージングの解放
	delete titleEase;
	delete enemyEase;
	delete enemyEaseR;
	delete playerFlyEase;
	delete selectEaseX;
	delete selectEaseY;

	// カメラの解放
	delete Cam;
}

void TitleScene::Update()
{
	// カーソルの入力処理を実行
	cursor->CursorInput();

	//CCursorでの列挙型のSceneを取得する
	cursorPoint = cursor->GetCursorPoint();

	if (gInput->IsControllerButtonTrigger(XINPUT_GAMEPAD_B) || gInput->GetKeyTrigger(VK_RETURN))
	{
		switch (cursorPoint)
		{
		case CCursor_Point::STAGE:
			// ステージの場合の処理を書く
			CSceneManager::GetInstance()->ChangeScene(SCENE_ID::SELECT);
			selectFlg = true;
			selectEaseX->Init(&goToSelect->transform.scale.x, 1100.0f * 0.00065f, 0.1f, 0, EASE::easeInCubic);
			selectEaseY->Init(&goToSelect->transform.scale.y, 447.0f * 0.00065f, 0.1f, 0, EASE::easeInCubic);
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

	// カーソル位置に応じて大きさを変更する
	switch (cursorPoint)
	{
	case CCursor_Point::STAGE:
		// 選択されたなら、ボタンのイージングを起動
		if (selectFlg)
		{
			// イージングの更新
			selectEaseX->Update();
			selectEaseY->Update();
			// 元の大きさに戻るイージングを設定する
			if (selectEaseX->GetState() == STATE::END && !selectEnd)
			{
				// 元の大きさを設定
				selectEaseX->Init(&goToSelect->transform.scale.x, 1100.0f * 0.0007f, 0.1f, 0, EASE::easeOutCubic);
				selectEaseY->Init(&goToSelect->transform.scale.y, 447.0f * 0.0007f, 0.1f, 0, EASE::easeOutCubic);
				// フラグを立てて二重で初期化が行われないようにする
				selectEnd = true;
			}
		}
		else
		{
			goToSelect->transform.scale = { 1100.0f * 0.0007f, 447.0f * 0.0007f, 1.0f };
		}
		goToSelect->materialDiffuse.w = 1.0f;
		goToOption->transform.scale = { 1100.0f * 0.0006f, 447.0f * 0.0006f, 1.0f };
		goToOption->materialDiffuse.w = 0.5f;
		exitGame->transform.scale = { 1100.0f * 0.0006f, 447.0f * 0.0006f, 1.0f };
		exitGame->materialDiffuse.w = 0.5f;
		break;

	case CCursor_Point::OPTION:
		goToOption->transform.scale = { 1100.0f * 0.0007f, 447.0f * 0.0007f, 1.0f };
		goToOption->materialDiffuse.w = 1.0f;
		goToSelect->transform.scale = { 1100.0f * 0.0006f, 447.0f * 0.0006f, 1.0f };
		goToSelect->materialDiffuse.w = 0.5f;
		exitGame->transform.scale = { 1100.0f * 0.0006f, 447.0f * 0.0006f, 1.0f };
		exitGame->materialDiffuse.w = 0.5f;
		break;

	case CCursor_Point::EXIT:
		exitGame->transform.scale = { 1100.0f * 0.0007f, 447.0f * 0.0007f, 1.0f };
		exitGame->materialDiffuse.w = 1.0f;
		goToSelect->transform.scale = { 1100.0f * 0.0006f, 447.0f * 0.0006f, 1.0f };
		goToSelect->materialDiffuse.w = 0.5f;
		goToOption->transform.scale = { 1100.0f * 0.0006f, 447.0f * 0.0006f, 1.0f };
		goToOption->materialDiffuse.w = 0.5f;
		break;

	default:
		break;
	}

	// 演出用の敵が初期位置にいるとき
	if (!moveDirNegative && !moveDirPositive)
	{
		// 敵を負の方向に動かす
		enemyEase->Update();
		if (enemyEase->GetState() == STATE::END)
		{
			enemyEase->Init(&enemyObj->transform.position.x, -3.5f, 2.0f, 0, EASE::easeInCubic);
		}
		playerObj->transform.position.x -= 0.01f;
		// 敵の負の方向への移動が終了したなら
		if (enemyObj->transform.position.x <= -3.5f)
		{
			// 移動終了フラグを上げる
			moveDirNegative = true;
			// playerObjを次の位置にセットする
			playerObj->transform.position.y = -0.5f;
			playerObj->transform.position.x = -2.5f;
			playerObj->SetAnimationPattern(ANIM_PATTERN::RIGHTWALK);
		}
	}
	else if(moveDirNegative && !moveDirPositive)
	{
		// 反転した敵を正の方向に動かす
		enemyEaseR->Update();
		if (enemyEaseR->GetState() == STATE::END)
		{
			enemyEaseR->Init(&enemyObj_reverse->transform.position.x, 3.5f, 2.0f, 0, EASE::easeInCubic);
		}
		playerObj->transform.position.x += 0.01f;
		// 反転した敵の正の方向への移動が終了したなら
		if (enemyObj_reverse->transform.position.x >= 3.5f)
		{
			// 移動終了フラグを上げる
			moveDirPositive = true;
			// 敵を元の位置に戻す
			enemyObj->transform.position.x = 3.5f;
			enemyObj_reverse->transform.position.x = -3.5f;
			// playerObjを次の位置にセットする
			playerObj->transform.position.x = -1.0f;
			playerObj->transform.position.y = -2.5f;
			playerObj->SetAnimationPattern(ANIM_PATTERN::FLAYING);
			playerObj->transform.scale = { 435.0f * 0.0017f, 326.0f * 0.0017f, 1.0f };
			playerObj->SetAnimationSpeed(0.15f);
			playerFlyEase->Init(&playerObj->transform.position.y, 2.5f, 8.0f, 0, EASE::easeInOutSine);
		}
	}
	else
	{
		playerObj->transform.position.x += 0.005f;
		playerFlyEase->Update();
		// 移動が終了したなら
		if (playerObj->transform.position.y >= 2.5f)
		{
			// フラグを元に戻す
			moveDirNegative = false;
			moveDirPositive = false;
			// playerObjを元の位置に戻す
			playerObj->transform.position.x = 2.5f;
			playerObj->transform.position.y = 0.2f;
			playerObj->SetAnimationPattern(ANIM_PATTERN::LEFTWALK);
			playerObj->SetAnimationSpeed(0.2f);
			playerObj->transform.scale = { 435.0f * 0.0012f, 326.0f * 0.0012f, 1.0f };
			// イージングを元に戻す
			enemyEase->Init(&enemyObj->transform.position.x, 0.0f, 3.0f, 4, EASE::easeOutCubic);
			enemyEaseR->Init(&enemyObj_reverse->transform.position.x, 0.0f, 3.0f, 4, EASE::easeOutCubic);
			playerFlyEase->Init(&playerObj->transform.position.y, 2.5f, 8.0f, 0, EASE::easeInOutSine);
		}
	}

	// 各種イージングの更新
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

	// カメラのアップデート
	Cam->Update();

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

