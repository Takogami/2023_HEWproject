#pragma once
#include"CScene.h"

class TitleScene : public CScene
{
private:
	

public:
	TitleScene();
	~TitleScene();
	//CScene�̊֐��̃I�[�o�[���C�h------//
	virtual void Update() override {
		//���̉�
	}
	virtual void Draw() override {
		//���̉�
		D3D_ClearScreen();
		//��ʍX�V
		D3D_UpdateScreen();

	}
};


