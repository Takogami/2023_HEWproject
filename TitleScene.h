#pragma once
#include"CScene.h"

class TitleScene : public CScene
{
private:
	CScene* scene;

public:
	TitleScene();
	~TitleScene();
	//CScene�̊֐��̃I�[�o�[���C�h------//
	virtual void Update() override {
		//���̉�

	}
	virtual void Draw() override {
		//���̉�
		D3D_ClearScreen(0);
		//��ʍX�V
		D3D_UpdateScreen();

	}
};


