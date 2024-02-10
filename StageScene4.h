#pragma once
#include "CScene.h"
#include"CSmoothing.h"

class StageScene4 :
    public CScene
{
private:
	CCamera* Cam;

	// 使うオブジェクトのリスト
	// まとめてUpdateとDrawを行うために使用
	std::list<CGameObject*>Objects;

	// 背景
	CGameObject* bg;

	CPlayer* player;

	// カメラ追従のスムージング
	CSmoothing* camSmoothX;
	CSmoothing* camSmoothY;

	ID3D11Buffer* vertexBufferCharacter;
	ID3D11Buffer* vertexBufferObject;

	CDrawString* drawStringTest;
	CDrawString* drawStringTest2;

public:
	StageScene4();
	~StageScene4();

	/* ------CSceneの関数のオーバーライド------ */
	void Update() override;
	void Draw() override;
};

