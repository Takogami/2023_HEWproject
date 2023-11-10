#pragma once
#include"CScene.h"

class ResultScene : public CScene
{
private:

public:
	ResultScene();
	~ResultScene();
	//CSceneの関数のオーバーライド------//
	virtual void Update() override {
		//実体化
	}
	virtual void Draw() override {
		//実体化
		D3D_ClearScreen();
		//画面更新
		D3D_UpdateScreen();

	}
};

