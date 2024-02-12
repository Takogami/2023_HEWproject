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

	CGameObject* player;

	ID3D11Buffer* vertexBufferCharacter;

	// シーン遷移中か判定するフラグ
	bool changeSceneFlg = false;

public:
	StageScene();
	~StageScene();

	/* ------CSceneの関数のオーバーライド------ */
	void Update() override;
	void Draw() override;

};

