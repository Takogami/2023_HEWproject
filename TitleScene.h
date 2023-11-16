#pragma once

/* インクルード */
#include"CScene.h"

// CTitleSceneクラス
class TitleScene : public CScene
{
private:
	// タイトルシーンのカメラ
	CCamera* Cam;

	// 使うオブジェクトのリスト
	// まとめてUpdateとDrawを行うために使用
	std::list<CGameObject*>Objects;

	CGameObject* player;
	CGameObject* player2;

	ID3D11Buffer* vertexBufferCharacter;

public:
	// コンストラクタ
	TitleScene();
	// デストラクタ
	~TitleScene() override;

	/* ------CSceneの関数のオーバーライド------ */
	void Update() override;
	void Draw() override;
};


