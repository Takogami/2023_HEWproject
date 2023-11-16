#pragma once

/* インクルード */
#include"CScene.h"

// CTitleSceneクラス
class TitleScene : public CScene
{
private:
	// タイトルシーンのカメラ
	CCamera* Cam;

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


