#pragma once

/* インクルード */
#include"CScene.h"

class ResultScene : public CScene
{
private:
	CCamera* Cam;

public:
	ResultScene();
	~ResultScene();

	/* ------CSceneの関数のオーバーライド------ */
	void Update() override;
	void Draw() override;
};

