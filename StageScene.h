#pragma once
#include "CScene.h"
#include"CSmoothing.h"

class StageScene :
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

	CGameObject* zyougi;
	CGameObject* zyougi2;
	CGameObject* book;
	CGameObject* book2;
	CGameObject* pencil2;
	CGameObject* eraser;
	CGameObject* pencil;
	CGameObject* kanban1;
	CGameObject* kanban2;
	CGameObject* kanban3;
	CGameObject* kanban4;
	CGameObject* kanban5;

	// シーン遷移中か判定するフラグ
	bool changeSceneFlg = false;

	// カメラ追従のスムージング
	CSmoothing* camSmooth;

	ID3D11Buffer* vertexBufferCharacter;
	ID3D11Buffer* vertexBufferObject;

public:
	StageScene();
	~StageScene();

	/* ------CSceneの関数のオーバーライド------ */
	void Update() override;
	void Draw() override;

};

