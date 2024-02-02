#pragma once
#include "CScene.h"
class StageScene :
    public CScene
{
private:
	CCamera* Cam;

	// 使うオブジェクトのリスト
	// まとめてUpdateとDrawを行うために使用
	std::list<CGameObject*>Objects;

	CPlayer* player;

	ID3D11Buffer* vertexBufferCharacter;

public:
	StageScene();
	~StageScene();

	/* ------CSceneの関数のオーバーライド------ */
	void Update() override;
	void Draw() override;

};

