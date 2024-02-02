#include "CGameOverScene.h"
#include "CSceneManager.h"

CGameOverScene::CGameOverScene()
{
	// カメラオブジェクトの実体化
	Cam = new CCamera;

	// 文字列の設定
	StageSelect = new CDrawString;
	StageSelect->SetFont(FontID::KARAKAZE);
	StageSelect->SetString(" ");
	StageSelect->SetPosition({ 0.0f, 50.0f });
	StageSelect->SetFontSize(100.0f);
	StageSelect->SetFontColor(1.0f, 1.0f, 1.0f);
	StageSelect->SetFontWeight(FONT_WEIGHT::ULTRA_BOLD);
	StageSelect->SetFontStyle(FONT_STYLE::ITALIC);

	StagePreview = new CGameObject(vertexBufferObject, CTextureLoader::GetInstance()->GetTex(TEX_ID::GAMEOVER));
	Objects.push_back(StagePreview);
	StagePreview->transform.position = { 0.0f, 0.1f, 0.5f };
	StagePreview->transform * 2.0f;
	StagePreview->transform.scale.x *= 2.0f;

	// 要素を拡張
	StageList.resize(listNum);
	// ステージのオブジェクトの生成と初期化
	for (int i = 0; i < StageList.size(); i++)
	{
		StageList[i] = new CGameObject(vertexBufferObject, CTextureLoader::GetInstance()->GetTex(TEX_ID::TAKO));
		StageList[i]->transform.scale = { 0.5f, 1.0f, 1.0f };
		StageList[i]->transform.position = { 0.0f - (1.5f * i), -0.5f, 0.0f };
		moveEndPos.resize(StageList.size());
		Objects.push_back(StageList[i]);
		// ステージの数だけイージングを作る
		selectEase.push_back(new CEase);
	}
}

CGameOverScene::~CGameOverScene()
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

	// カメラオブジェクトの削除
	delete Cam;
}

void CGameOverScene::Update()
{
	if (gInput->IsControllerButtonTrigger(XINPUT_GAMEPAD_A) || gInput->GetKeyTrigger(VK_RETURN))
	{
		CSceneManager::GetInstance()->ChangeScene(SCENE_ID::TITLE);
	}

	// 右移動
	if ((gInput->GetKeyTrigger(VK_RIGHT) || gInput->IsControllerButtonRepeat(XINPUT_GAMEPAD_DPAD_LEFT, 40, 5))
		&& stageNum > 1 && !selectMoveUp && !selectMoveDown)
	{
		// 選択中のステージの更新
		stageNum -= 1;
		// ステージ番号を列挙型クラスに変換する
		userSelect = (SELECT_NUM)stageNum;
		// ステージ選択リストの移動
		for (int i = 0; i < StageList.size(); i++)
		{
			// 移動の最終座標を保存
			moveEndPos[i] = StageList[i]->transform.position.x - 1.5f;
			selectMoveUp = true;
			// イージングの初期化
			selectEase[i]->Init(&StageList[i]->transform.position.x, moveEndPos[i], 0.5f, 0, EASE::easeInOutSine);
		}
	}
	// 左移動
	else if ((gInput->GetKeyTrigger(VK_LEFT) || gInput->IsControllerButtonRepeat(XINPUT_GAMEPAD_DPAD_RIGHT, 40, 5))
		&& stageNum < listNum && !selectMoveUp && !selectMoveDown)
	{
		// 選択中のステージの更新
		stageNum += 1;
		// ステージ番号を列挙型クラスに変換する
		userSelect = (SELECT_NUM)stageNum;
		// ステージ選択リストの移動
		for (int i = 0; i < StageList.size(); i++)
		{
			moveEndPos[i] = StageList[i]->transform.position.x + 1.5f;
			selectMoveDown = true;
			// イージングの初期化
			selectEase[i]->Init(&StageList[i]->transform.position.x, moveEndPos[i], 0.5f, 0, EASE::easeInOutSine);
		}
	}

	for (int i = 0; i < StageList.size(); i++)
	{
		// 位置が0の選択中のステージは大きく表示
		if (StageList[i]->transform.position.x == 0.0f)
		{
			// 大きさを等倍に
			StageList[i]->transform.scale.y = 0.5f * 1.0f;
			StageList[i]->transform.scale.x = 1.5f * 1.0f;
			// 不透明にする
			StageList[i]->materialDiffuse.w = 1.0f;
		}
		// 選択されていないステージは小さく半透明にする
		else
		{
			// 縮小する
			StageList[i]->transform.scale.y = 0.5f * 0.8f;
			StageList[i]->transform.scale.x = 1.5f * 0.8f;
			// 不透明度を下げる
			StageList[i]->materialDiffuse.w = 0.7f;
		}

		// リストが移動中かどうかを判定
		if (selectMoveUp)
		{
			// イージングの更新
			selectEase[i]->Update();
			// リストを上移動させる
			if (StageList[i]->transform.position.x <= moveEndPos[i])
			{
				// 移動が終了しているなら最終座標を代入しておく
				StageList[i]->transform.position.x = moveEndPos[i];
				// 中央に表示されているステージに0を代入しておく
				StageList[stageNum - 1]->transform.position.x = 0.0f;
				// 上移動フラグをおろす
				selectMoveUp = false;
			}
		}
		else if (selectMoveDown)
		{
			// イージングの更新
			selectEase[i]->Update();
			// リストを下移動させる
			if (StageList[i]->transform.position.x >= moveEndPos[i])
			{
				// 移動が終了しているなら最終座標を代入しておく
				StageList[i]->transform.position.x = moveEndPos[i];
				// 中央に表示されているステージに0を代入しておく
				StageList[stageNum - 1]->transform.position.x = 0.0f;
				// 上移動フラグをおろす
				selectMoveDown = false;
			}
		}
	}

	// 各オブジェクトの描画
	for (auto it = Objects.begin(); it != Objects.end(); it++)
	{
		(*it)->Update();
	}
}

void CGameOverScene::Draw()
{
	D3D_ClearScreen();

	// 各オブジェクトの描画
	for (auto it = Objects.begin(); it != Objects.end(); it++)
	{
		(*it)->Draw();
	}

	StageSelect->Draw();

	// 画面更新
	D3D_UpdateScreen();
}
