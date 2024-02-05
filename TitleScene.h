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

	CCursor* cursor;
	CGameObject* goToSelect;
	CGameObject* goToOption;
	CGameObject* exitGame;
	CGameObject* bg;
	CGameObject* Title;

	// タイトルのイージング
	CEase* titleEase;
	bool TitleEaseFg = false;

	ID3D11Buffer* vertexBufferObject;

	CCursor_Point cursorPoint = CCursor_Point::STAGE;

public:
	// コンストラクタ
	TitleScene();
	// デストラクタ
	~TitleScene() override;

	/* ------CSceneの関数のオーバーライド------ */
	void Update() override;
	void Draw() override;
};


