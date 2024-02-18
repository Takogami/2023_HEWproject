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

	//	ゲームオブジェクト
	CGameObject* book;
	CGameObject* book2;
	CGameObject* book3;
	CGameObject* pencil;
	CGameObject* pencil2;
	CGameObject* pencil3;
	CGameObject* ruler[3];

	CPlayer* player;

	bool changeSceneFlg = false;

	// カメラ追従のスムージング
	CSmoothing* camSmooth;

	ID3D11Buffer* vertexBufferCharacter;
	ID3D11Buffer* vertexBufferObject;

public:
	StageScene3();
	~StageScene3();

	/* ------CSceneの関数のオーバーライド------ */
	void Update() override;
	void Draw() override;
};

