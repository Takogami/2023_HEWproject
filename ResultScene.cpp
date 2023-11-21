/* インクルード */
#include "ResultScene.h"
#include "CSceneManager.h"	// シーン切り替えのためにインクルード

ResultScene::ResultScene()
{
	// カメラオブジェクトの実体化
	Cam = new CCamera;

	// 構成するステージと使用するカメラのポインタを指定
	CScene::CreateStage(TERRAIN_ID::STAGE_1, Cam);
}

ResultScene::~ResultScene()
{
	// カメラオブジェクトの削除
	delete Cam;
	// ステージの後片付け
	CScene::DestroyStage();
}

void ResultScene::Update()
{
	// カメラが正しく作動しているかのテスト
	static float test_x = 0.0f;
	test_x += 0.001f;
	Cam->SetCameraPosition(test_x, 0);
	Cam->Update();

	if (gInput->IsControllerButtonRepeat(XINPUT_GAMEPAD_A) || gInput->GetKeyTrigger(VK_RETURN))
	{
		CSceneManager::GetInstance()->ChangeScene(SCENE_ID::TITLE);
	}
}

void ResultScene::Draw()
{
	D3D_ClearScreen();

	// CSceneのDrawを明示的に呼び出す(地形の描画)
	CScene::Draw();

	// 画面更新
	D3D_UpdateScreen();
}
