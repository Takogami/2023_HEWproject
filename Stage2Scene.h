#pragma once
#include "CScene.h"

class Stage2Scene :
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
	Stage2Scene();
	~Stage2Scene();

	/* ------CSceneの関数のオーバーライド------ */
	void Update() override;
	void Draw() override;

};

