#pragma once

/* インクルード */
#include"CScene.h"

class ResultScene : public CScene
{
private:
	CCamera* Cam;

	// 使うオブジェクトのリスト
	// まとめてUpdateとDrawを行うために使用
	std::list<CGameObject*>Objects;

	/* ↓ 仮設プレイヤー ↓ */
	CGameObject* player;
	float dirX = 0.0f;
	float dirY = 0.0f;
	/* ↑ 仮設プレイヤー ↑ */

	ID3D11Buffer* vertexBufferCharacter;

public:
	ResultScene();
	~ResultScene();

	/* ------CSceneの関数のオーバーライド------ */
	void Update() override;
	void Draw() override;
};

