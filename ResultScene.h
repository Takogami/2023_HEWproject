#pragma once
#include"CScene.h"

class ResultScene : public CScene
{
private:

public:
	ResultScene();
	~ResultScene();

	/* ------CScene�̊֐��̃I�[�o�[���C�h------ */
	void Update() override;
	void Draw() override;
};

