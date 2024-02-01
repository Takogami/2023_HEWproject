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
	CCursor* player2;
	CGameObject* player3;
	CGameObject* player4;
	CGameObject* player5;
	CGameObject* bg;
	CGameObject* Title;
	CEase* ease;

	ID3D11Buffer* vertexBufferCharacter;
	ID3D11Buffer* vertexBufferObject;

	CCursor_Point cursorPoint;

	bool flg;

public:
	// コンストラクタ
	TitleScene();
	// デストラクタ
	~TitleScene() override;

	/* ------CSceneの関数のオーバーライド------ */
	void Update() override;
	void Draw() override;
};


