#include "ResultScene.h"
#include "CSceneManager.h"

ResultScene::ResultScene()
{
	// カメラオブジェクトの実体化
	Cam = new CCamera;

	/*---------------ゲームオーバー画面のオブジェクト-----------------------*/
	bg = new CGameObject(vertexBufferObject, CTextureLoader::GetInstance()->GetTex(TEX_ID::WINDRIGHT_POS));
	Objects.push_back(bg);
	bg->transform.scale = { 1920.0f * 0.0021f, 1080.0f * 0.0021f, 1.0f };
	bg->transform.position.z = 0.4f;
	bg->SetActive(false);

	GameOverObj = new CGameObject(vertexBufferObject, CTextureLoader::GetInstance()->GetTex(TEX_ID::GAMEOVER));
	Objects.push_back(GameOverObj);
	GameOverObj->transform.position = { -0.5f, 0.0f, -0.1f };
	GameOverObj->transform.scale = { 512.0f * 1.0f, 512.0f * 1.0f, 1.0f };
	GameOverObj->materialDiffuse.w = 0.0f;
	GameOverObj->SetActive(false);

	GameOverString = new CGameObject(vertexBufferObject, CTextureLoader::GetInstance()->GetTex(TEX_ID::GAMEOVER_STRING));
	Objects.push_back(GameOverString);
	GameOverString->transform.position = { -0.5f, 2.0f, -0.11f };
	GameOverString->transform.scale = { 512.0f * 0.0045f, 512.0f * 0.0045f, 1.0f };
	GameOverString->SetActive(false);

	retry = new CGameObject(vertexBufferObject, CTextureLoader::GetInstance()->GetTex(TEX_ID::RETRY));
	// オブジェクトをリストに登録
	Objects.push_back(retry);
	retry->transform.scale = { 1100.0f * 0.0007f, 447.0f * 0.0007f, 1.0f };;
	retry->transform.position = { 1.1f, -0.1f };
	retry->SetActive(false);

	goToSelect = new CGameObject(vertexBufferObject, CTextureLoader::GetInstance()->GetTex(TEX_ID::STAGE_SELECT));
	// オブジェクトをリストに登録
	Objects.push_back(goToSelect);
	goToSelect->transform.scale = { 1100.0f * 0.0007f, 447.0f * 0.0007f, 1.0f };
	goToSelect->transform.position = { 1.1f, -0.4f };
	goToSelect->SetActive(false);

	goToTitle = new CGameObject(vertexBufferObject, CTextureLoader::GetInstance()->GetTex(TEX_ID::GOTO_TITLE));
	// オブジェクトをリストに登録
	Objects.push_back(goToTitle);
	goToTitle->transform.scale = { 1100.0f * 0.0007f, 447.0f * 0.0007f, 1.0f };
	goToTitle->transform.position = { 1.1f, -0.7f };
	goToTitle->SetActive(false);

	// カーソルの実体化と初期化
	cursor = new CCursor(vertexBufferObject, CTextureLoader::GetInstance()->GetTex(TEX_ID::CURSOR));
	// オブジェクトをリストに登録
	Objects.push_back(cursor);
	cursor->transform.scale = { 186.0f * 0.0017f, 54.0f * 0.0017f, 1.0f };
	cursor->transform.position = { 0.624f, -0.1f, -0.2f };
	cursor->transform.rotation = -30.0f;
	cursor->Init({ cursor->transform.position.x, cursor->transform.position.y });
	cursor->SetActive(false);

	selectEaseX = new CEase;
	selectEaseY = new CEase;

	gameOverEase = new CEase;
	gameOverEase->Init(&GameOverString->transform.position.y, 0.0f, 1.5f, 0, EASE::easeOutBounce);
	gameOverObjEaseX = new CEase;
	gameOverObjEaseX->Init(&GameOverObj->transform.scale.x, 512.0f * 0.0045f, 2.0f, 0, EASE::easeOutQuint);
	gameOverObjEaseY = new CEase;
	gameOverObjEaseY->Init(&GameOverObj->transform.scale.y, 512.0f * 0.0045f, 2.0f, 0, EASE::easeOutQuint);
	/*---------------ゲームオーバー画面のオブジェクト-----------------------*/

	/*-------------------クリア画面のオブジェクト---------------------------*/
	c_bg = new CGameObject(vertexBufferObject, CTextureLoader::GetInstance()->GetTex(TEX_ID::CLEAR));
	Objects.push_back(c_bg);
	c_bg->transform.scale = { 1920.0f * 0.0021f, 1080.0f * 0.0021f, 1.0f };
	c_bg->transform.position.z = 0.4f;
	c_bg->SetActive(false);

	c_goToSelect = new CGameObject(vertexBufferObject, CTextureLoader::GetInstance()->GetTex(TEX_ID::STAGE_SELECT));
	// オブジェクトをリストに登録
	Objects.push_back(c_goToSelect);
	c_goToSelect->transform.scale = { 1100.0f * 0.0007f, 447.0f * 0.0007f, 1.0f };
	c_goToSelect->transform.position = { 1.03f, -0.5f };
	c_goToSelect->SetActive(false);

	c_goToTitle = new CGameObject(vertexBufferObject, CTextureLoader::GetInstance()->GetTex(TEX_ID::GOTO_TITLE));
	// オブジェクトをリストに登録
	Objects.push_back(c_goToTitle);
	c_goToTitle->transform.scale = { 1100.0f * 0.0007f, 447.0f * 0.0007f, 1.0f };
	c_goToTitle->transform.position = { 1.03f, -0.8f };
	c_goToTitle->SetActive(false);

	// カーソルの実体化と初期化
	c_cursor = new CCursor(vertexBufferObject, CTextureLoader::GetInstance()->GetTex(TEX_ID::CURSOR));
	// オブジェクトをリストに登録
	Objects.push_back(c_cursor);
	c_cursor->transform.scale = { 186.0f * 0.0017f, 54.0f * 0.0017f, 1.0f };
	c_cursor->transform.position = { 0.559f, -0.5f, -0.2f };
	c_cursor->transform.rotation = -30.0f;
	c_cursor->Init({ c_cursor->transform.position.x, c_cursor->transform.position.y }, 2);
	c_cursor->SetActive(false);

	scoreBoard = new CGameObject(vertexBufferObject, CTextureLoader::GetInstance()->GetTex(TEX_ID::BOARD));
	Objects.push_back(scoreBoard);
	scoreBoard->transform.position = { 1.0f, 0.2f, -0.1f };
	scoreBoard->transform.scale = { 772.0f * 0.002f, 472.0f * 0.002f, 1.0f };
	scoreBoard->SetActive(false);

	clearString = new CGameObject(vertexBufferObject, CTextureLoader::GetInstance()->GetTex(TEX_ID::CLEAR_STRING));
	Objects.push_back(clearString);
	clearString->transform.position = { -0.8f, 0.6f, -0.11f };
	clearString->transform.scale = { 0.0f, 0.0f, 1.0f };
	clearString->SetActive(false);

	clearStringEaseX = new CEase;
	clearStringEaseY = new CEase;
	clearStringEaseX->Init(&clearString->transform.scale.x, 1355.0f * 0.0015f, 1.0f, 2, EASE::easeOutBack);
	clearStringEaseY->Init(&clearString->transform.scale.y, 447.0f * 0.0015f, 1.0f, 2, EASE::easeOutBack);
	/*-------------------クリア画面のオブジェクト---------------------------*/
}

ResultScene::~ResultScene()
{
	SAFE_RELEASE(vertexBufferObject);

	// 各オブジェクトのメモリ解放
	for (auto it = Objects.begin(); it != Objects.end(); it++)
	{
		delete (*it);
	}

	// イージングの解放
	delete selectEaseX;
	delete selectEaseY;
	delete gameOverObjEaseX;
	delete gameOverObjEaseY;
	delete gameOverEase;
	delete clearStringEaseX;
	delete clearStringEaseY;

	// カメラオブジェクトの削除
	delete Cam;
}

void ResultScene::SetPrevStage(int prev)
{
	prevScene = prev;
}


void ResultScene::Update()
{
	// 結果に応じて更新処理を変える
	switch (state)
	{
	case RESULT_STATE::GAMEOVER:
		// ゲームオーバー画面の更新
		UpdateGameOver();
		break;

	case RESULT_STATE::CLEAR:
		// クリア画面の更新
		UpdateClear();
		break;

	default:

		break;
	}

	// 各オブジェクトの描画
	for (auto it = Objects.begin(); it != Objects.end(); it++)
	{
		(*it)->Update();
	}
}

void ResultScene::UpdateClear()
{
	// クリア画面に使うオブジェクトを有効化する
	c_bg->SetActive(true);
	clearString->SetActive(true);
	scoreBoard->SetActive(true);

	// クリア文字列のイージングの更新
	clearStringEaseX->Update();
	clearStringEaseY->Update();
	// イージングが終了したなら
	if (clearStringEaseX->GetState() == STATE::END)
	{
		// 演出が終わったので選択肢を有効化する
		c_goToSelect->SetActive(true);
		c_goToTitle->SetActive(true);
		c_cursor->SetActive(true);
	}

	// カーソルの入力処理を実行
	c_cursor->CursorInput();

	// CCursorでの列挙型のSceneを取得する
	c_cursorPoint = (CCursor_PointClear)c_cursor->GetCursorPoint();

	if (gInput->IsControllerButtonTrigger(XINPUT_GAMEPAD_B) || gInput->GetKeyTrigger(VK_RETURN))
	{
		// カーソルのポイント位置で遷移先のシーンを変更
		switch (c_cursorPoint)
		{
		case CCursor_PointClear::SELECT:	// セレクトに戻る
			CSceneManager::GetInstance()->ChangeScene(SCENE_ID::SELECT);
			selectEaseX->Init(&c_goToSelect->transform.scale.x, 1100.0f * 0.00065f, 0.1f, 0, EASE::easeInCubic);
			selectEaseY->Init(&c_goToSelect->transform.scale.y, 447.0f * 0.00065f, 0.1f, 0, EASE::easeInCubic);
			selectFlg = true;
			break;

		case CCursor_PointClear::TITLE:	// タイトルに戻る
			CSceneManager::GetInstance()->ChangeScene(SCENE_ID::TITLE);
			selectEaseX->Init(&c_goToTitle->transform.scale.x, 1100.0f * 0.00065f, 0.1f, 0, EASE::easeInCubic);
			selectEaseY->Init(&c_goToTitle->transform.scale.y, 447.0f * 0.00065f, 0.1f, 0, EASE::easeInCubic);
			selectFlg = true;
			break;

		default:
			break;
		}
	}

	// カーソル位置に応じて大きさを変更する
	switch (c_cursorPoint)
	{
	case CCursor_PointClear::SELECT:
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
				selectEaseX->Init(&c_goToSelect->transform.scale.x, 1100.0f * 0.0007f, 0.1f, 0, EASE::easeOutCubic);
				selectEaseY->Init(&c_goToSelect->transform.scale.y, 447.0f * 0.0007f, 0.1f, 0, EASE::easeOutCubic);
				// フラグを立てて二重で初期化が行われないようにする
				selectEnd = true;
			}
		}
		else
		{
			c_goToSelect->transform.scale = { 1100.0f * 0.0007f, 447.0f * 0.0007f, 1.0f };
		}
		c_goToSelect->materialDiffuse.w = 1.0f;
		c_goToTitle->transform.scale = { 1100.0f * 0.0006f, 447.0f * 0.0006f, 1.0f };
		c_goToTitle->materialDiffuse.w = 0.5f;
		break;

	case CCursor_PointClear::TITLE:
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
				selectEaseX->Init(&c_goToTitle->transform.scale.x, 1100.0f * 0.0007f, 0.1f, 0, EASE::easeOutCubic);
				selectEaseY->Init(&c_goToTitle->transform.scale.y, 447.0f * 0.0007f, 0.1f, 0, EASE::easeOutCubic);
				// フラグを立てて二重で初期化が行われないようにする
				selectEnd = true;
			}
		}
		else
		{
			c_goToTitle->transform.scale = { 1100.0f * 0.0007f, 447.0f * 0.0007f, 1.0f };
		}
		c_goToTitle->materialDiffuse.w = 1.0f;
		c_goToSelect->transform.scale = { 1100.0f * 0.0006f, 447.0f * 0.0006f, 1.0f };
		c_goToSelect->materialDiffuse.w = 0.5f;
		break;

	default:
		break;
	}
}

void ResultScene::UpdateGameOver()
{
	// ゲームオーバー画面に使うオブジェクトを有効化する
	GameOverObj->SetActive(true);
	GameOverString->SetActive(true);
	bg->SetActive(true);

	// イージングの更新
	gameOverObjEaseX->Update();
	gameOverObjEaseY->Update();

	// 文字のイージングの更新
	if (gameOverObjEaseX->GetState() == STATE::END && gameOverObjEaseY->GetState() == STATE::END)
	{
		gameOverEase->Update();
	}

	// 透明度の更新
	GameOverObj->materialDiffuse.w = GameOverObj->materialDiffuse.w < 1.0f ?
		GameOverObj->materialDiffuse.w += 0.008f : 1.0f;

	// 演出が終了したなら入力を有効化する
	if (gameOverEase->GetState() == STATE::END)
	{
		cursor->SetActive(true);
		retry->SetActive(true);
		goToSelect->SetActive(true);
		goToTitle->SetActive(true);
	}

	// 前回のシーンからリトライで読み込むシーンを決定
	// int型で設定されたものをSCENE_ID型に変換する
	SCENE_ID loadScene = (SCENE_ID)prevScene;

	// カーソルの入力処理を実行
	cursor->CursorInput();

	// CCursorでの列挙型のSceneを取得する
	cursorPoint = (CCursor_PointResult)cursor->GetCursorPoint();

	if (gInput->IsControllerButtonTrigger(XINPUT_GAMEPAD_B) || gInput->GetKeyTrigger(VK_RETURN))
	{
		// カーソルのポイント位置で遷移先のシーンを変更
		switch (cursorPoint)
		{
		case CCursor_PointResult::RETRY:	// コンティニュー
			// 前回のステージに遷移する
			switch (loadScene)
			{
			case SCENE_ID::STAGE_1:
				CSceneManager::GetInstance()->ChangeScene(SCENE_ID::STAGE_1);
				break;

			case SCENE_ID::STAGE_2:
				CSceneManager::GetInstance()->ChangeScene(SCENE_ID::STAGE_2);
				break;

			default:
				break;
			}
			selectEaseX->Init(&retry->transform.scale.x, 1100.0f * 0.00065f, 0.1f, 0, EASE::easeInCubic);
			selectEaseY->Init(&retry->transform.scale.y, 447.0f * 0.00065f, 0.1f, 0, EASE::easeInCubic);
			selectFlg = true;
			break;

		case CCursor_PointResult::SELECT:	// セレクトに戻る
			CSceneManager::GetInstance()->ChangeScene(SCENE_ID::SELECT);
			selectEaseX->Init(&goToSelect->transform.scale.x, 1100.0f * 0.00065f, 0.1f, 0, EASE::easeInCubic);
			selectEaseY->Init(&goToSelect->transform.scale.y, 447.0f * 0.00065f, 0.1f, 0, EASE::easeInCubic);
			selectFlg = true;
			break;

		case CCursor_PointResult::TITLE:	// タイトルに戻る
			CSceneManager::GetInstance()->ChangeScene(SCENE_ID::TITLE);
			selectEaseX->Init(&goToTitle->transform.scale.x, 1100.0f * 0.00065f, 0.1f, 0, EASE::easeInCubic);
			selectEaseY->Init(&goToTitle->transform.scale.y, 447.0f * 0.00065f, 0.1f, 0, EASE::easeInCubic);
			selectFlg = true;
			break;

		default:
			break;
		}
	}

	// カーソル位置に応じて大きさを変更する
	switch (cursorPoint)
	{
	case CCursor_PointResult::RETRY:
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
				selectEaseX->Init(&retry->transform.scale.x, 1100.0f * 0.0007f, 0.1f, 0, EASE::easeOutCubic);
				selectEaseY->Init(&retry->transform.scale.y, 447.0f * 0.0007f, 0.1f, 0, EASE::easeOutCubic);
				// フラグを立てて二重で初期化が行われないようにする
				selectEnd = true;
			}
		}
		else
		{
			retry->transform.scale = { 1100.0f * 0.0007f, 447.0f * 0.0007f, 1.0f };
		}
		retry->materialDiffuse.w = 1.0f;
		goToSelect->transform.scale = { 1100.0f * 0.0006f, 447.0f * 0.0006f, 1.0f };
		goToSelect->materialDiffuse.w = 0.5f;
		goToTitle->transform.scale = { 1100.0f * 0.0006f, 447.0f * 0.0006f, 1.0f };
		goToTitle->materialDiffuse.w = 0.5f;
		break;

	case CCursor_PointResult::SELECT:
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
		retry->transform.scale = { 1100.0f * 0.0006f, 447.0f * 0.0006f, 1.0f };
		retry->materialDiffuse.w = 0.5f;
		goToTitle->transform.scale = { 1100.0f * 0.0006f, 447.0f * 0.0006f, 1.0f };
		goToTitle->materialDiffuse.w = 0.5f;
		break;

	case CCursor_PointResult::TITLE:
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
				selectEaseX->Init(&goToTitle->transform.scale.x, 1100.0f * 0.0007f, 0.1f, 0, EASE::easeOutCubic);
				selectEaseY->Init(&goToTitle->transform.scale.y, 447.0f * 0.0007f, 0.1f, 0, EASE::easeOutCubic);
				// フラグを立てて二重で初期化が行われないようにする
				selectEnd = true;
			}
		}
		else
		{
			goToTitle->transform.scale = { 1100.0f * 0.0007f, 447.0f * 0.0007f, 1.0f };
		}
		goToTitle->materialDiffuse.w = 1.0f;
		retry->transform.scale = { 1100.0f * 0.0006f, 447.0f * 0.0006f, 1.0f };
		retry->materialDiffuse.w = 0.5f;
		goToSelect->transform.scale = { 1100.0f * 0.0006f, 447.0f * 0.0006f, 1.0f };
		goToSelect->materialDiffuse.w = 0.5f;
		break;

	default:
		break;
	}
}

void ResultScene::Draw()
{
	// 各オブジェクトの描画
	for (auto it = Objects.begin(); it != Objects.end(); it++)
	{
		(*it)->Draw();
	}
}
