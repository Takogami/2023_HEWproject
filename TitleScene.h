#pragma once
#include"CScene.h"

class TitleScene : public CScene
{
private:
	CScene* scene;

public:
	TitleScene();
	~TitleScene();

	/* ------CScene�̊֐��̃I�[�o�[���C�h------ */
	void Update() override
	{

	}
	void Draw() override
	{
		D3D_ClearScreen();
		// ��ʍX�V
		D3D_UpdateScreen();
	}
};


