#pragma once
#include"CScene.h"

class TitleScene : public CScene
{
private:
	

public:
	TitleScene();
	~TitleScene();
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


