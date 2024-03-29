#include "ResultScene.h"
#include "CSceneManager.h"

ResultScene::ResultScene()
{
	// カメラオブジェクトの実体化
	Cam = new CCamera;

	/*---------------ゲームオーバー画面のオブジェクト-----------------------*/
	bg = new CGameObject(vertexBufferObject, CTextureLoader::GetInstance()->GetTex(TEX_ID::FADE));
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
	scoreBoard->transform.position = { 1.0f, 2.0f, -0.1f };
	scoreBoard->transform.scale = { 772.0f * 0.002f, 472.0f * 0.002f, 1.0f };
	scoreBoard->SetActive(false);

	// 時間数字テクスチャ
	for (int i = 0; i < 3; i++)
	{
		timeNum[i] = new CGameObject(vertexBufferObject, CTextureLoader::GetInstance()->GetTex(TEX_ID::NUM), { 0.1f ,1.0f });
		timeNum[i]->transform.scale = { 0.2f, 0.25f, 1.0f };
		timeNum[i]->transform.position = { 0.6f + (0.21f * i), 0.05f, -0.46f };
		Objects.push_back(timeNum[i]);
		timeNum[i]->SetActive(false);
	}

	clearString = new CGameObject(vertexBufferObject, CTextureLoader::GetInstance()->GetTex(TEX_ID::CLEAR_STRING));
	Objects.push_back(clearString);
	clearString->transform.position = { -0.8f, 0.6f, -0.11f };
	clearString->transform.scale = { 0.0f, 0.0f, 1.0f };
	clearString->SetActive(false);

	enemyObj = new CGameObject(vertexBufferObject, CTextureLoader::GetInstance()->GetTex(TEX_ID::ENEMY),{ 0.333333f, 0.5f });
	Objects.push_back(enemyObj);
	enemyObj->transform.position = { -1.7f, -2.0f, -0.1f };
	enemyObj->transform.rotation = 20.0f;
	enemyObj->transform.scale = { 794.0f * 0.0013f, 793.0f * 0.0013f, 1.0f };
	enemyObj->TextureCutout(1,1);
	enemyEase = new CEase();
	enemyEase->Init(&enemyObj->transform.position.y, -1.0f, 1.0f, 3, EASE::easeOutSine);

	enemyObj2 = new CGameObject(vertexBufferObject, CTextureLoader::GetInstance()->GetTex(TEX_ID::ENEMY), { 0.333333f, 0.5f });
	Objects.push_back(enemyObj2);
	enemyObj2->transform.position = { 0.1f, -2.0f, -0.1f };
	enemyObj2->transform.rotation = -20.0f;
	enemyObj2->transform.scale = { 794.0f * 0.0013f, 793.0f * 0.0013f, 1.0f };
	enemyObj2->TextureCutout(1, 0);
	enemyEase2 = new CEase();
	enemyEase2->Init(&enemyObj2->transform.position.y, -1.0f, 1.0f, 4, EASE::easeOutSine);

	enemyHappyEase = new CEase;
	enemyHappyEase2 = new CEase;

	clearStringEaseX = new CEase;
	clearStringEaseY = new CEase;
	clearStringEaseX->Init(&clearString->transform.scale.x, 1355.0f * 0.0015f, 1.0f, 1, EASE::easeOutBack);
	clearStringEaseY->Init(&clearString->transform.scale.y, 447.0f * 0.0015f, 1.0f, 1, EASE::easeOutBack);

	scoreBoardEase = new CEase;
	scoreBoardEase->Init(&scoreBoard->transform.position.y, 0.2f, 1.5f, 2, EASE::easeOutSine);

	//	クリアタイム文字表示
	strClearTime = new CGameObject(vertexBufferObject, CTextureLoader::GetInstance()->GetTex(TEX_ID::CLEARTIME));
	Objects.push_back(strClearTime);
	strClearTime->transform.position = { 1.0f, 0.35f, 0.1f };
	strClearTime->transform.scale = { 985.0f * 0.001f, 163.0f * 0.001f, 0.0f };
	strClearTime->SetActive(false);

	cTime = new CGameObject(vertexBufferObject, CTextureLoader::GetInstance()->GetTex(TEX_ID::TIME));
	Objects.push_back(cTime);
	cTime->transform.position = { 1.36f, 0.04f, 0.1f };
	cTime->transform.scale = { 314.0f * 0.0007f, 304.0f * 0.0007f, 0.0f };
	cTime->SetActive(false);

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
	delete scoreBoardEase;
	delete enemyEase;
	delete enemyEase2;
	delete enemyHappyEase;
	delete enemyHappyEase2;

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

	// スコアボード降下のイージングの更新
	scoreBoardEase->Update();
	// 敵イージングの更新
	enemyEase->Update();
	enemyEase2->Update();

	// スコアボードの移動が完了したならクリア時間のカウントを行う
	if (scoreBoardEase->GetState() == STATE::END)
	{
		// 時間を位ごとに格納する
		int temp = clearTimeCount;
		for (int i = 2; i >= 0; i--)
		{
			// 上の桁の数から順番に桁の値を格納していく
			int digit = temp % 10;
			timeRankNum[i] = digit;
			// 格納した数値と同じテクスチャを切り抜く
			timeNum[i]->SetActive(true);
			timeNum[i]->TextureCutout(timeRankNum[i], 0);
			// 次の桁に移動
			temp /= 10;
		}

		if (timeRankNum[0] == 0 && timeRankNum[1] == 0)
		{
			timeNum[0]->SetActive(false);
			timeNum[1]->SetActive(false);
			if (!uiTimePositionSet[0])
			{
				timeNum[2]->transform.position.x = timeNum[2]->transform.position.x - 0.2f;
				uiTimePositionSet[0] = true;
			}
		}
		else if(timeRankNum[0] == 0)
		{
			timeNum[0]->SetActive(false);

			if (!uiTimePositionSet[1])
			{
				timeNum[2]->transform.position.x = timeNum[2]->transform.position.x + 0.1f;
				timeNum[1]->transform.position.x = timeNum[1]->transform.position.x - 0.1f;
				uiTimePositionSet[1] = true;
			}
		}
		else
		{
			if (!uiTimePositionSet[2])
			{
				timeNum[2]->transform.position.x = timeNum[2]->transform.position.x + 0.1f;
				timeNum[1]->transform.position.x = timeNum[1]->transform.position.x + 0.1f;
				uiTimePositionSet[2] = true;
			}
		}

		strClearTime->SetActive(true);
		cTime->SetActive(true);

		//  カウント効果音の再生
		if (clearTimeCount == 0)
		{
			XA_Play(SOUND_LABEL_SCORE_COUNT);
		}
		// スコアのカウントを行う
		clearTimeCount = clearTimeCount < clearTime ? clearTimeCount + 1 : clearTimeCount;

		// カウントが終了しているなら
		if (clearTimeCount == clearTime)
		{
			// 音を鳴らすまでのフレームを計算
			seFlameCounter = seFlameCounter < 60 ? seFlameCounter + 1 : seFlameCounter;
			// フラグが立っていないかつ60フレーム経過したならSEを再生
			if (sePlayFlg == false && seFlameCounter == 60
				&& enemyEase->GetState() == STATE::END && enemyEase2->GetState() == STATE::END)
			{
				// 同時にイージングの初期化を行う
				enemyHappyEase->Init(&enemyObj->transform.position.y, -0.8f, 1.0f, 0, EASE::easeInBounce);
				enemyHappyEase2->Init(&enemyObj2->transform.position.y, -0.8f, 1.0f, 0, EASE::easeInBounce);
				XA_Play(SOUND_LABEL_CLEAR);
				sePlayFlg = true;
			}
			// カウント効果音の停止
			XA_Stop(SOUND_LABEL_SCORE_COUNT);
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
				selectOK = true;

				// 敵の喜びの動きのイージング
				// 交互にジャンプさせる
				if (!endJumpEnemy)
				{
					// 左の敵のイージングの更新
					enemyHappyEase->Update();
					if (enemyHappyEase->GetState() == STATE::END && enemyHappyEaseFlg)
					{
						enemyHappyEase->Init(&enemyObj->transform.position.y, -0.8f, 1.0f, 0, EASE::easeInBounce);
						enemyHappyEaseFlg = false;
						// 左の敵のイージングが完了したのでフラグを上げる
						endJumpEnemy = true;
					}
					else if (enemyHappyEase->GetState() == STATE::END && !enemyHappyEaseFlg)
					{
						enemyHappyEase->Init(&enemyObj->transform.position.y, -1.0f, 0.3f, 0, EASE::easeInQuad);
						enemyHappyEaseFlg = true;
					}
				}
				else
				{
					// 右の敵のイージングの更新
					enemyHappyEase2->Update();
					if (enemyHappyEase2->GetState() == STATE::END && enemyHappyEaseFlg2)
					{
						enemyHappyEase2->Init(&enemyObj2->transform.position.y, -0.8f, 1.0f, 0, EASE::easeInBounce);
						enemyHappyEaseFlg2 = false;
						// 右の敵のイージングが完了したのでフラグを下げる
						endJumpEnemy = false;
					}
					else if (enemyHappyEase2->GetState() == STATE::END && !enemyHappyEaseFlg2)
					{
						enemyHappyEase2->Init(&enemyObj2->transform.position.y, -1.0f, 0.3f, 0, EASE::easeInQuad);
						enemyHappyEaseFlg2 = true;
					}
				}
			}
		}
	}

	// クリア時間描画用の一時変数を宣言
	std::string comvartStrTime;	// 文字列に変換した時間を格納
	int digit_rank;				// 現在の時間の桁数を格納
	// 時間を文字列型に変換
	comvartStrTime = std::to_string(clearTimeCount);
	// 時間の文字列をセット
	//strClearTimeNum->SetString(comvartStrTime);
	// 文字列の長さから桁数を取得
	digit_rank = comvartStrTime.length();
	// 桁数に応じて表示位置を変更する
	//strClearTimeNum->SetPosition({ 980.0f + (56 / digit_rank), 340.0f });

	// カーソルの入力処理を実行
	c_cursor->CursorInput();

	// CCursorでの列挙型のSceneを取得する
	c_cursorPoint = (CCursor_PointClear)c_cursor->GetCursorPoint();

	if (gInput->IsControllerButtonTrigger(XINPUT_GAMEPAD_B) && selectOK)
	{
		// サウンド再生
		XA_Play(SOUND_LABEL_PRESS);

		gInput->ControllerVibration(5, 40000);
		// カーソルのポイント位置で遷移先のシーンを変更
		switch (c_cursorPoint)
		{
		case CCursor_PointClear::SELECT:	// セレクトに戻る
			CSceneManager::GetInstance()->ChangeScene(SCENE_ID::SELECT, FADE_TYPE::ERASER);
			selectEaseX->Init(&c_goToSelect->transform.scale.x, 1100.0f * 0.00065f, 0.1f, 0, EASE::easeInCubic);
			selectEaseY->Init(&c_goToSelect->transform.scale.y, 447.0f * 0.00065f, 0.1f, 0, EASE::easeInCubic);
			selectFlg = true;
			break;

		case CCursor_PointClear::TITLE:	// タイトルに戻る
			CSceneManager::GetInstance()->ChangeScene(SCENE_ID::TITLE, FADE_TYPE::ERASER);
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
		selectOK = true;
	}

	// 前回のシーンからリトライで読み込むシーンを決定
	// int型で設定されたものをSCENE_ID型に変換する
	SCENE_ID loadScene = (SCENE_ID)prevScene;

	// カーソルの入力処理を実行
	cursor->CursorInput();

	// CCursorでの列挙型のSceneを取得する
	cursorPoint = (CCursor_PointResult)cursor->GetCursorPoint();

	if ((gInput->IsControllerButtonTrigger(XINPUT_GAMEPAD_B) || gInput->GetKeyTrigger(VK_RETURN)) && selectOK)
	{
		//	サウンド再生
		XA_Play(SOUND_LABEL_PRESS);

		//	サウンド停止
		XA_Stop(SOUND_LABEL_GAMEOVER);

		gInput->ControllerVibration(5, 40000);
		// カーソルのポイント位置で遷移先のシーンを変更
		switch (cursorPoint)
		{
		case CCursor_PointResult::RETRY:	// コンティニュー
			// 前回のステージに遷移する
			switch (loadScene)
			{
			case SCENE_ID::STAGE_1:
				CSceneManager::GetInstance()->ChangeScene(SCENE_ID::STAGE_1, FADE_TYPE::ERASER);
				break;

			case SCENE_ID::STAGE_2:
				CSceneManager::GetInstance()->ChangeScene(SCENE_ID::STAGE_2, FADE_TYPE::ERASER);
				break;

			case SCENE_ID::STAGE_3:
				CSceneManager::GetInstance()->ChangeScene(SCENE_ID::STAGE_3, FADE_TYPE::ERASER);
				break;
			default:
				break;
			}
			selectEaseX->Init(&retry->transform.scale.x, 1100.0f * 0.00065f, 0.1f, 0, EASE::easeInCubic);
			selectEaseY->Init(&retry->transform.scale.y, 447.0f * 0.00065f, 0.1f, 0, EASE::easeInCubic);
			selectFlg = true;
			break;

		case CCursor_PointResult::SELECT:	// セレクトに戻る
			CSceneManager::GetInstance()->ChangeScene(SCENE_ID::SELECT, FADE_TYPE::ERASER);
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
