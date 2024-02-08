#include "CSceneManager.h"
#include "CScene.h"

// CTextureLoaderクラスのstaticメンバ変数の初期化
CSceneManager* CSceneManager::instance = nullptr;

// コンストラクタ
CSceneManager::CSceneManager()
{
	title = nullptr;
	stage = nullptr;
	result = nullptr;
	stage2 = nullptr;

	// デフォルトのシーンを初期化します
	ChangeScene(SCENE_ID::TITLE);
}

// デストラクタ
CSceneManager::~CSceneManager()
{
	// 各シーンの解放
	if (title != nullptr)
	{
		delete title;
	}
	if (select != nullptr)
	{
		delete select;
	}
	if (stage != nullptr)
	{
		delete stage;
	}
	if (result != nullptr)
	{
		delete result;
	}
	if (stage2 != nullptr)
	{
		delete stage2;
	}
}

void CSceneManager::CleanupSingleton()
{
	//インスタンスがあるなら解放する
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
	case SCENE_ID::STAGE_01:
		stage->Update();
		stage->Draw();
		break;

	// リザルト
	case SCENE_ID::RESULT:
		result->Update();
		result->Draw();
		break;

	// ステージ02
	case SCENE_ID::STAGE_02:
		stage2->Update();
		stage2->Draw();
		break;

	}
}

void CSceneManager::ChangeScene(SCENE_ID _inScene)
{
	// 1. 現在のシーンに関連するリソースを解放する

	// ステージを読み込んでいたなら解放する
	CScene::DestroyStage();

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

	case SCENE_ID::STAGE_01:
		// もし現在のシーンがSTAGE_01なら、STAGE_01シーンを解放する
		delete stage;
		stage = nullptr;
		break;

	case SCENE_ID::RESULT:
		// もし現在のシーンがRESULTなら、RESULTシーンを解放する
		delete result;
		result = nullptr;
		break;
	case SCENE_ID::STAGE_02:
		// もし現在のシーンがSTAGE_02なら、STAGE_02シーンを解放する
		delete stage2;
		stage2 = nullptr;
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

	case SCENE_ID::STAGE_01:
		// もし新しいシーンがSTAGE_01なら、新しいSTAGE_01シーンを作成する
		stage = new StageScene();
		break;

	case SCENE_ID::RESULT:
		// もし新しいシーンがRESULTなら、新しいRESULTシーンを作成する
		result = new ResultScene();
		break;
	case SCENE_ID::STAGE_02:
		// もし新しいシーンがRESULTなら、新しいRESULTシーンを作成する
		stage2 = new Stage2Scene();
		break;
	}
}
