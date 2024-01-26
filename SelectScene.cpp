#include "SelectScene.h"

SelectScene::SelectScene()
{
	// カメラオブジェクトの実体化
	Cam = new CCamera;
}

SelectScene::~SelectScene()
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

void SelectScene::Update()
{
}

void SelectScene::Draw()
{
	D3D_ClearScreen();

	// 各オブジェクトの描画
	for (auto it = Objects.begin(); it != Objects.end(); it++)
	{
		(*it)->Draw();
	}

	// 画面更新
	D3D_UpdateScreen();
}
