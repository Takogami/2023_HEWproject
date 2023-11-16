#include "CSceneManager.h"

// CTextureLoaderクラスのstaticメンバ変数の初期化
CSceneManager* CSceneManager::instance = nullptr;

// コンストラクタ
CSceneManager::CSceneManager()
{
	title = new TitleScene();	//タイトルシーンのnew
	result = new ResultScene();	//リザルトシーンのnew

	// 初期シーン設定
	ChangeScene(SCENE_ID::TITLE);
}

// デストラクタ
CSceneManager::~CSceneManager()
{
	delete title;
	delete result;
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

	// リザルト
	case SCENE_ID::RESULT:
		result->Update();
		result->Draw();
		break;
	}
}

void CSceneManager::ChangeScene(SCENE_ID _inScene)
{
	NowScene = _inScene;
}
