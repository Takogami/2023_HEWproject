#pragma once

/* �C���N���[�h */
#include"CScene.h"

class ResultScene : public CScene
{
private:
	CCamera* Cam;

public:
	ResultScene();
	~ResultScene();

	/* ------CScene�̊֐��̃I�[�o�[���C�h------ */
	void Update() override;
	void Draw() override;
};

