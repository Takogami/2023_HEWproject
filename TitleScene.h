#pragma once
#include"CScene.h"

class TitleScene : public CScene
{
private:
	CScene* scene;

public:
	TitleScene();
	~TitleScene();

	/* ------CSceneの関数のオーバーライド------ */
	void Update() override
	{

	}
	void Draw() override
	{
		D3D_ClearScreen();
		// 画面更新
		D3D_UpdateScreen();
	}
};


