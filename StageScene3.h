#pragma once
#include "CScene.h"
#include"CSmoothing.h"

class StageScene3 :
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
	StageScene3();
	~StageScene3();

	/* ------CSceneの関数のオーバーライド------ */
	void Update() override;
	void Draw() override;
};

