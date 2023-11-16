#include "ResultScene.h"

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
}

void ResultScene::Draw()
{
	D3D_ClearScreen();
	//画面更新
	D3D_UpdateScreen();
}
