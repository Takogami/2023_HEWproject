#include "CSceneManager.h"
#include "CScene.h"

// シーン解放の簡易化
#define RELEASE_SCENE(scene){ if (scene != nullptr){ delete scene; } }

// CTextureLoaderクラスのstaticメンバ変数の初期化
CSceneManager* CSceneManager::instance = nullptr;

// コンストラクタ
CSceneManager::CSceneManager()
{
	// デフォルトのシーンを初期化します
	ChangeScene(SCENE_ID::TITLE);

	// フェード用オブジェクトの実体化
	fade = new CGameObject(vertexBuffer, CTextureLoader::GetInstance()->GetTex(TEX_ID::WINDRIGHT_POS));
	fade->transform.scale = { 1920.0f * 0.0021f, 1080.0f * 0.0021f, 1.0f };
	fade->transform.position.z = -0.5f;

	// ゲームマネージャ唯一のインスタンスを取得
	gameManager = CGameManager::GetInstance();
}

// デストラクタ
CSceneManager::~CSceneManager()
{
	// フェード用の頂点バッファとオブジェクトの解放
	SAFE_RELEASE(vertexBuffer);
	delete fade;

	// 各シーンの解放
	RELEASE_SCENE(title);
	RELEASE_SCENE(select);
	RELEASE_SCENE(stage1);
	RELEASE_SCENE(stage2);
	RELEASE_SCENE(stage3);
	RELEASE_SCENE(stage4);
	RELEASE_SCENE(result);
}

void CSceneManager::CleanupSingleton()
{
	// インスタンスがあるなら解放する
	if (instance)
	{
		delete instance;
		instance = nullptr;
	}
}

CSceneManager* CSceneManager::GetInstance()
{
	// シングルトンが存在していないなら生成する
	if (!instance)
	{
		// シングルトンの生成
		instance = new CSceneManager();
		//コールバックとして登録
		std::atexit(CleanupSingleton);
	}
	//唯一のインスタンスを返す
	return instance;
}

// Update & Draw
void CSceneManager::Update()
{
	// フェード中は入力を受け付けないように設定
	if (fadeState != FADE_STATE::NO_FADE)
	{
		// 入力をロック
		gInput->InputLock(true);
	}
	else
	{
		// 入力ロックを解除
		gInput->InputLock(false);
	}

	// フェードイン
	if (fadeState == FADE_STATE::FADE_IN)
	{
		// フェード用ポリゴンをだんだん透明に
		fade->materialDiffuse.w -= 0.01f;
		// フェード用ポリゴンが完全に透明なら
		if (fade->materialDiffuse.w <= 0.0f)
		{
			// フェードの状態をフェード無し状態に設定
			fadeState = FADE_STATE::NO_FADE;
		}
	}
	// フェードアウト
	else if (fadeState == FADE_STATE::FADE_OUT)
	{
		// フェード用ポリゴンをだんだん不透明に
		fade->materialDiffuse.w += 0.01f;
		// フェード用ポリゴンが完全に不透明なら
		if (fade->materialDiffuse.w >= 1.0f)
		{
			// 設定されていた次のシーンに切り替える
			ChangeScene(NewScene);
		}
	}

	// 画面をクリア
	D3D_ClearScreen();

	// シーンごとのUpdate,Drawを実行
	switch (NowScene)
	{
	// タイトル
	case SCENE_ID::TITLE:
		title->Update();
		title->Draw();
		break;

	// ステージ選択画面
	case SCENE_ID::SELECT:
		select->Update();
		select->Draw();
		break;

	// ステージ01
	case SCENE_ID::STAGE_1:
		stage1->Update();
		stage1->Draw();
		break;

	// ステージ02
	case SCENE_ID::STAGE_2:
		stage2->Update();
		stage2->Draw();
		break;

		// ステージ03
	case SCENE_ID::STAGE_3:
		stage3->Update();
		stage3->Draw();
		break;

		// ステージ04
	case SCENE_ID::STAGE_4:
		stage4->Update();
		stage4->Draw();
		break;

	// リザルト
	case SCENE_ID::RESULT:
		result->Update();
		result->Draw();
		break;
	}

	// フェード用ポリゴンの描画
	fade->Draw();

	// 画面の更新
	D3D_UpdateScreen();
}

void CSceneManager::ChangeScene(SCENE_ID _inScene)
{
	if (NewScene != _inScene)
	{
		NewScene = _inScene;
		fadeState = FADE_STATE::FADE_OUT;
		// リトライ時に読み込むシーンとして現在のシーンを保存する
		retryLoadScene = NowScene;
	}
	else
	{
		// ステージを読み込んでいたなら解放する
		CScene::DestroyStage();
		fadeState = FADE_STATE::FADE_IN;

		// 1. 現在のシーンに関連するリソースを解放する
		switch (_inScene)
		{
		case SCENE_ID::TITLE:
			// もし現在のシーンがTITLEなら、TITLEシーンを解放する
			delete title;
			title = nullptr;
			break;

		case SCENE_ID::SELECT:
			// もし現在のシーンがSELECTなら、SELECTシーンを解放する
			delete select;
			select = nullptr;
			break;

		case SCENE_ID::STAGE_1:
			// もし現在のシーンがSTAGE_01なら、STAGE_01シーンを解放する
			delete stage1;
			stage1 = nullptr;
			break;

		case SCENE_ID::STAGE_2:
			// もし現在のシーンがSTAGE_2なら、STAGE_2シーンを解放する
			delete stage2;
			stage2 = nullptr;
			break;

		case SCENE_ID::STAGE_3:
			// もし現在のシーンがSTAGE_3なら、STAGE_3シーンを解放する
			delete stage3;
			stage3 = nullptr;
			break;

		case SCENE_ID::STAGE_4:
			// もし現在のシーンがSTAGE_4なら、STAGE_4シーンを解放する
			delete stage4;
			stage4 = nullptr;
			break;

		case SCENE_ID::RESULT:
			// もし現在のシーンがRESULTなら、RESULTシーンを解放する
			delete result;
			result = nullptr;
			break;
		}

		// 2. 新しいシーンの識別子を設定する
		NowScene = _inScene;

		// 3. 新しいシーンのリソースを作成し設定する
		switch (NowScene)
		{
		case SCENE_ID::TITLE:
			// もし新しいシーンがTITLEなら、新しいTITLEシーンを作成する
			title = new TitleScene();
			break;

		case SCENE_ID::SELECT:
			// もし新しいシーンがSELECTなら、新しいSELECTシーンを作成する
			select = new SelectScene();
			break;

		case SCENE_ID::STAGE_1:
			// もし新しいシーンがSTAGE_01なら、新しいSTAGE_01シーンを作成する
			stage1 = new StageScene();
			break;

		case SCENE_ID::STAGE_2:
			// もし新しいシーンがTAGE_2なら、新しいSTAGE_2シーンを作成する
			stage2 = new StageScene2();
			break;

		case SCENE_ID::STAGE_3:
			// もし新しいシーンがTAGE_3なら、新しいSTAGE_3シーンを作成する
			stage3 = new StageScene3();
			break;

		case SCENE_ID::STAGE_4:
			// もし新しいシーンがTAGE_4なら、新しいSTAGE_4シーンを作成する
			stage4 = new StageScene4();
			break;

		case SCENE_ID::RESULT:
			// もし新しいシーンがRESULTなら、新しいRESULTシーンを作成する
			result = new ResultScene();
			// 前のシーンをリザルトシーンに設定
			result->SetPrevStage((int)retryLoadScene);
			break;
		}
	}
}
