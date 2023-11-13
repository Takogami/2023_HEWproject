#pragma once
#include"CScene.h"

class ResultScene : public CScene
{
private:

public:
	ResultScene();
	~ResultScene();

	/* CSceneの関数のオーバーライド------ */
	virtual void Update() override;
	virtual void Draw() override;
};

