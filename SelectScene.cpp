#include "SelectScene.h"
#include "CSceneManager.h"

SelectScene::SelectScene()
{
	// カメラオブジェクトの実体化
	Cam = new CCamera;

	// 背景の設定
	bg = new CGameObject(vertexBufferObject, CTextureLoader::GetInstance()->GetTex(TEX_ID::TITLE_BG), { 1.0f ,1.0f });
	bg->transform.scale = { 1920.0f * 0.0021f, 1080.0f * 0.0021f, 1.0f };
	// オブジェクトをリストに登録
	Objects.push_back(bg);

	// 文字列の設定
	StageSelect = new CDrawString;
	StageSelect->SetFont(FontID::UZURA);
	StageSelect->SetString("ステージを選んでね");
	StageSelect->SetPosition({ 80.0f, 100.0f });
	StageSelect->SetFontSize(80.0f);
	StageSelect->SetFontColor(0.0f, 0.0f, 0.0f);
	StageSelect->SetFontWeight(FONT_WEIGHT::ULTRA_BOLD);
	StageSelect->SetShadow({ -3.0f, -2.0f }, 1.0f, 0.3f, 0.0f, 0.4f);

	goToTitle = new CDrawString;
	goToTitle->SetFont(FontID::UZURA);
	goToTitle->SetString("start : タイトルへ");
	goToTitle->SetPosition({ 80.0f, 780.0f });
	goToTitle->SetFontSize(40.0f);
	goToTitle->SetFontColor(0.0f, 0.0f, 0.0f);
	goToTitle->SetFontWeight(FONT_WEIGHT::ULTRA_BOLD);
	goToTitle->SetShadow({ -3.0f, -2.0f }, 1.0f, 0.7f, 0.0f, 1.0f);

	StagePreview = new CGameObject(vertexBufferObject, CTextureLoader::GetInstance()->GetTex(TEX_ID::BOOK), { 0.2f, 1.0f });
	Objects.push_back(StagePreview);
	StagePreview->transform.position = { -0.97f, -0.07f, 0.2f };
	StagePreview->transform.scale = { 693.0f * 0.003f, 900.0f * 0.003f};
	StagePreview->InitAnimParameter(false, 5, 1, ANIM_PATTERN::BOOK, 0.2f);

	StageView = new CGameObject(vertexBufferObject, CTextureLoader::GetInstance()->GetTex(TEX_ID::STAGE_VIEW), { 0.333333f, 1.0f });
	Objects.push_back(StageView);
	StageView->transform.position = { -0.95f, -0.13f, 0.15f };
	StageView->transform.rotation = 1.4f;
	StageView->transform.scale = { 1.2f, 1.2f };
	StageView->materialDiffuse.w = 0.0f;
	StageView->TextureCutout(0,0);

	// 要素を拡張
	StageList.resize(listNum);

	// ステージのオブジェクトの生成
	StageList[0] = new CGameObject(vertexBufferObject, CTextureLoader::GetInstance()->GetTex(TEX_ID::S1_SELECT_FLAME));
	StageList[1] = new CGameObject(vertexBufferObject, CTextureLoader::GetInstance()->GetTex(TEX_ID::S2_SELECT_FLAME));
	StageList[2] = new CGameObject(vertexBufferObject, CTextureLoader::GetInstance()->GetTex(TEX_ID::S3_SELECT_FLAME));

	// 初期化
	for (int i = 0; i < StageList.size(); i++)
	{
		StageList[i]->transform.scale = { 646.0f * 0.0025f, 277.0f * 0.0025f, 1.0f };
		StageList[i]->transform.position = { 1.0f, 0.0f - (0.7f * i), -0.1f };
		moveEndPos.resize(StageList.size());
		Objects.push_back(StageList[i]);
		// ステージの数だけイージングを作る
		selectEase.push_back(new CEase);
	}

	StagePreview2 = new CGameObject(vertexBufferObject, CTextureLoader::GetInstance()->GetTex(TEX_ID::STRING_BG));
	Objects.push_back(StagePreview2);
	StagePreview2->transform.position = { -0.8f, 0.76f, 0.05f };
	StagePreview2->transform.scale = { 700.0f * 0.0035f, 283.0f * 0.002f};
	StagePreview2->materialDiffuse.w = 0.7f;

	stringBg = new CGameObject(vertexBufferObject, CTextureLoader::GetInstance()->GetTex(TEX_ID::STRING_BG));
	Objects.push_back(stringBg);
	stringBg->transform.position = { -1.33f, -0.97f, 0.05f };
	stringBg->transform.scale = { 700.0f * 0.00148f, 283.0f * 0.0007f };
	stringBg->materialDiffuse.w = 0.85f;

	kami = new CGameObject(vertexBufferObject, CTextureLoader::GetInstance()->GetTex(TEX_ID::PLAYER), { 0.2f ,0.1f });
	Objects.push_back(kami);
	kami->transform.position = { 1.85f, -0.85f, -0.11f };
	kami->transform.rotation = -20.0f;
	kami->transform * 1.0f;
	// アニメーションの初期化
	kami->InitAnimParameter(true, 5, 10, ANIM_PATTERN::IDOL_L, 0.15f);

	// プレビューのイージング
	viewEase = new CEase;
	viewEase->Init(&StageView->materialDiffuse.w, 1.0f, 0.7f, 0, EASE::easeInOutCubic);
}

SelectScene::~SelectScene()
{
	SAFE_RELEASE(vertexBufferObject);

	// 各オブジェクトのメモリ解放
	for (auto it = Objects.begin(); it != Objects.end(); it++)
	{
		delete (*it);
	}
	// イージングの解放
	for (int i = 0; i < listNum; i++)
	{
		delete selectEase[i];
	}
	delete viewEase;

	// カメラオブジェクトの削除
	delete Cam;
}

void SelectScene::Update()
{
	// タイトル画面に戻る
	if (gInput->IsControllerButtonTrigger(XINPUT_GAMEPAD_START))
	{
		CSceneManager::GetInstance()->ChangeScene(SCENE_ID::TITLE, FADE_TYPE::ERASER);
	}

	// 上移動
	if ((gInput->GetKeyTrigger(VK_UP) || gInput->IsControllerButtonRepeat(XINPUT_GAMEPAD_DPAD_UP, 90, 1))
		&& stageNum > 1 && !selectMoveUp && !selectMoveDown)
	{
		// ステージビューのイージングの初期化
		StageView->materialDiffuse.w = 0.0f;
		viewEase->Init(&StageView->materialDiffuse.w, 1.0f, 0.7f, 0, EASE::easeInOutCubic);

		//	サウンド再生
		XA_Play(SOUND_LABEL_BOOKSE);

		// 選択中のステージの更新
		stageNum -= 1;
		// ステージ番号を列挙型クラスに変換する
		userSelect = (STAGE_NUM)stageNum;
		// ステージ選択リストの移動
		for (int i = 0; i < StageList.size(); i++)
		{
			// 移動の最終座標を保存
			moveEndPos[i] = StageList[i]->transform.position.y - 0.7f;
			selectMoveUp = true;
			// イージングの初期化
			selectEase[i]->Init(&StageList[i]->transform.position.y, moveEndPos[i], 0.5f, 0, EASE::easeOutBack);
		}
		StagePreview->SetAnimationPattern(ANIM_PATTERN::BOOK_REVERSE);
		StagePreview->ResetAnimation();
		StagePreview->PlayAnimation();
	}
	// 下移動
	else if ((gInput->GetKeyTrigger(VK_DOWN) || gInput->IsControllerButtonRepeat(XINPUT_GAMEPAD_DPAD_DOWN, 90, 1))
		&& stageNum < listNum && !selectMoveUp && !selectMoveDown)
	{
		// ステージビューのイージングの初期化
		StageView->materialDiffuse.w = 0.0f;
		viewEase->Init(&StageView->materialDiffuse.w, 1.0f, 0.7f, 0, EASE::easeInOutCubic);

		//	サウンド再生
		XA_Play(SOUND_LABEL_BOOKSE);

		// 選択中のステージの更新
		stageNum += 1;
		// ステージ番号を列挙型クラスに変換する
		userSelect = (STAGE_NUM)stageNum;
		// ステージ選択リストの移動
		for (int i = 0; i < StageList.size(); i++)
		{
			moveEndPos[i] = StageList[i]->transform.position.y + 0.7f;
			selectMoveDown = true;
			// イージングの初期化
			selectEase[i]->Init(&StageList[i]->transform.position.y, moveEndPos[i], 0.5f, 0, EASE::easeOutBack);
		}
		StagePreview->SetAnimationPattern(ANIM_PATTERN::BOOK);
		StagePreview->ResetAnimation();
		StagePreview->PlayAnimation();
	}
	if (gInput->IsControllerButtonTrigger(XINPUT_GAMEPAD_B) || gInput->GetKeyTrigger(VK_RETURN))
	{
		// サウンド再生
		XA_Play(SOUND_LABEL_PRESS);
		gInput->ControllerVibration(5, 40000);
		switch (userSelect)
		{
		case STAGE_NUM::STAGE1:
			// ステージ1に遷移
			CSceneManager::GetInstance()->ChangeScene(SCENE_ID::STAGE_1, FADE_TYPE::ERASER);
			break;

		case STAGE_NUM::STAGE2:
			// ステージ2に遷移
			CSceneManager::GetInstance()->ChangeScene(SCENE_ID::STAGE_2, FADE_TYPE::ERASER);
			break;

		case STAGE_NUM::STAGE3:
			//	ステージ3に遷移
			CSceneManager::GetInstance()->ChangeScene(SCENE_ID::STAGE_3, FADE_TYPE::ERASER);
			break;

		default:
			break;
		}
	}
	// ステージプレビューの更新
	StageView->TextureCutout(stageNum - 1, 0);

	for(int i = 0; i < StageList.size(); i++)
	{
		// 位置が0の選択中のステージは大きく表示
		if (StageList[i]->transform.position.y == 0.0f)
		{
			// 大きさを等倍に
			StageList[i]->transform.scale.x = 646.0f * 0.0025f * 1.0f;
			StageList[i]->transform.scale.y = 277.0f * 0.0025f * 1.0f;
			// 不透明にする
			StageList[i]->materialDiffuse.w = 1.0f;
		}
		// 選択されていないステージは小さく半透明にする
		else
		{
			// 縮小する
			StageList[i]->transform.scale.x = 646.0f * 0.0025f * 0.8f;
			StageList[i]->transform.scale.y = 277.0f * 0.0025f * 0.8f;
			// 不透明度を下げる
			StageList[i]->materialDiffuse.w = 0.7f;
		}

		// リストが移動中かどうかを判定
		if (selectMoveUp)
		{
			// イージングの更新
			selectEase[i]->Update();
			// リストを上移動させる
			if (StageList[i]->transform.position.y <= moveEndPos[i] && selectEase[i]->GetState() == STATE::END)
			{
				// 移動が終了しているなら最終座標を代入しておく
				StageList[i]->transform.position.y = moveEndPos[i];
				// 中央に表示されているステージに0を代入しておく
				StageList[stageNum - 1]->transform.position.y = 0.0f;
				// 上移動フラグをおろす
				selectMoveUp = false;
				StagePreview->StopAnimation();
			}
		}
		else if (selectMoveDown)
		{
			// イージングの更新
			selectEase[i]->Update();
			// リストを下移動させる
			if (StageList[i]->transform.position.y >= moveEndPos[i] && selectEase[i]->GetState() == STATE::END)
			{
				// 移動が終了しているなら最終座標を代入しておく
				StageList[i]->transform.position.y = moveEndPos[i];
				// 中央に表示されているステージに0を代入しておく
				StageList[stageNum - 1]->transform.position.y = 0.0f;
				// 上移動フラグをおろす
				selectMoveDown = false;
				StagePreview->StopAnimation();
			}
		}
	}

	// プレビューの透明度変更イージングの更新
	viewEase->Update();

	// 各オブジェクトの描画
	for (auto it = Objects.begin(); it != Objects.end(); it++)
	{
		(*it)->Update();
	}
}

void SelectScene::Draw()
{
	// 各オブジェクトの描画
	for (auto it = Objects.begin(); it != Objects.end(); it++)
	{
		(*it)->Draw();
	}

	StageSelect->Draw();
	goToTitle->Draw();
}
