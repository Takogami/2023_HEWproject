#pragma once

/* インクルード */
#include"CScene.h"
#include"CSmoothing.h"

class StageScene2 : public CScene
{
private:
	CCamera* Cam;

	// 使うオブジェクトのリスト
	// まとめてUpdateとDrawを行うために使用
	std::list<CGameObject*>Objects;

	// 背景
	CGameObject* bg;

	CGameObject* zyougi;
	CGameObject* zyougi2;
	CGameObject* book;
	CGameObject* pencil;

	CPlayer* player;

	// シーン遷移中か判定するフラグ
	bool changeSceneFlg = false;

	// カメラ追従のスムージング
	CSmoothing* camSmooth;

	ID3D11Buffer* vertexBufferCharacter;
	ID3D11Buffer* vertexBufferObject;

public:
	StageScene2();
	~StageScene2();

	/* ------CSceneの関数のオーバーライド------ */
	void Update() override;
	void Draw() override;
};

