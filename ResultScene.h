#pragma once
#include"CScene.h"

class ResultScene : public CScene
{
private:

public:
	ResultScene();
	~ResultScene();

	/* CScene�̊֐��̃I�[�o�[���C�h------ */
	virtual void Update() override;
	virtual void Draw() override;
};

