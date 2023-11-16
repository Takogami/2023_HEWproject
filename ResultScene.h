#pragma once
#include"CScene.h"

class ResultScene : public CScene
{
private:

public:
	ResultScene();
	~ResultScene();

	/* ------CSceneの関数のオーバーライド------ */
	void Update() override;
	void Draw() override;
};

