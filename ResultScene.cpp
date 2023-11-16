/* インクルード */
#include "ResultScene.h"
#include "CSceneManager.h"	// シーン切り替えのためにインクルード

ResultScene::ResultScene()
{
}

ResultScene::~ResultScene()
{
	// 親クラスのデストラクタを明示的に呼び出す
	CScene::~CScene();
}

void ResultScene::Update()
{
	if (gInput->IsControllerButtonPressed(XINPUT_GAMEPAD_B))
	{
		CSceneManager::GetInstance()->ChangeScene(SCENE_ID::TITLE);
	}
}

void ResultScene::Draw()
{
	D3D_ClearScreen();
	//画面更新
	D3D_UpdateScreen();
}
