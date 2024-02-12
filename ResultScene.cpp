#include "ResultScene.h"
#include "CSceneManager.h"

ResultScene::ResultScene()
{
	// カメラオブジェクトの実体化
	Cam = new CCamera;

	GameOverObj = new CGameObject(vertexBufferObject, CTextureLoader::GetInstance()->GetTex(TEX_ID::GAMEOVER));
	Objects.push_back(GameOverObj);
	GameOverObj->transform.position = { -0.5f, 0.0f, 0.5f };
	GameOverObj->transform.scale = { 512.0f * 0.0045f, 512.0f * 0.0045f, 1.0f };

	retry = new CGameObject(vertexBufferObject, CTextureLoader::GetInstance()->GetTex(TEX_ID::BOARD));
	// オブジェクトをリストに登録
	Objects.push_back(retry);
	retry->transform.scale = { 1100.0f * 0.0007f, 447.0f * 0.0007f, 1.0f };;
	retry->transform.position = { 1.0f, 0.2f };

	goToSelect = new CGameObject(vertexBufferObject, CTextureLoader::GetInstance()->GetTex(TEX_ID::BOARD));
	// オブジェクトをリストに登録
	Objects.push_back(goToSelect);
	goToSelect->transform.scale = { 1100.0f * 0.0007f, 447.0f * 0.0007f, 1.0f };
	goToSelect->transform.position = { 1.0f, -0.1f };

	goToTitle = new CGameObject(vertexBufferObject, CTextureLoader::GetInstance()->GetTex(TEX_ID::BOARD));
	// オブジェクトをリストに登録
	Objects.push_back(goToTitle);
	goToTitle->transform.scale = { 1100.0f * 0.0007f, 447.0f * 0.0007f, 1.0f };
	goToTitle->transform.position = { 1.0f, -0.4f };

	// カーソルの実体化と初期化
	cursor = new CCursor(vertexBufferObject, CTextureLoader::GetInstance()->GetTex(TEX_ID::CURSOR));
	// オブジェクトをリストに登録
	Objects.push_back(cursor);
	cursor->transform.scale = { 186.0f * 0.0017f, 54.0f * 0.0017f, 1.0f };
	cursor->transform.position = { 0.524f, 0.2f, -0.2f };
	cursor->transform.rotation = -30.0f;
	cursor->Init({ cursor->transform.position.x, cursor->transform.position.y });

	selectEaseX = new CEase;
	selectEaseY = new CEase;
}

ResultScene::~ResultScene()
{
	SAFE_RELEASE(vertexBufferObject);

	// 各オブジェクトのメモリ解放
	for (auto it = Objects.begin(); it != Objects.end(); it++)
	{
		delete (*it);
	}

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
}

void ResultScene::UpdateGameOver()
{
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
			break;

		case CCursor_PointResult::SELECT:	// セレクトに戻る
			CSceneManager::GetInstance()->ChangeScene(SCENE_ID::SELECT);
			break;

		case CCursor_PointResult::TITLE:	// タイトルに戻る
			CSceneManager::GetInstance()->ChangeScene(SCENE_ID::TITLE);
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
		goToSelect->transform.scale = { 1100.0f * 0.0007f, 447.0f * 0.0007f, 1.0f };
		goToSelect->materialDiffuse.w = 1.0f;
		retry->transform.scale = { 1100.0f * 0.0006f, 447.0f * 0.0006f, 1.0f };
		retry->materialDiffuse.w = 0.5f;
		goToTitle->transform.scale = { 1100.0f * 0.0006f, 447.0f * 0.0006f, 1.0f };
		goToTitle->materialDiffuse.w = 0.5f;
		break;

	case CCursor_PointResult::TITLE:
		goToTitle->transform.scale = { 1100.0f * 0.0007f, 447.0f * 0.0007f, 1.0f };
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
