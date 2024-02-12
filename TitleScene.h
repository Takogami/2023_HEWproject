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

	// オブジェクト
	CCursor* cursor;
	CGameObject* goToSelect;
	CGameObject* goToOption;
	CGameObject* exitGame;
	CGameObject* bg;
	CGameObject* Title;
	CGameObject* ruler;
	CGameObject* ruler2;

	// タイトル演出用
	CGameObject* enemyObj;
	CGameObject* enemyObj_reverse;
	CGameObject* playerObj;
	// 演出用の敵が負の方向の移動が終了したか管理するフラグ
	bool moveDirNegative = false;
	// 演出用の敵が正の方向の移動が終了したか管理するフラグ
	bool moveDirPositive = false;
	// 敵の移動イージング
	CEase* enemyEase;
	CEase* enemyEaseR;
	CEase* playerFlyEase;

	// 選択のイージング
	CEase* selectEaseX;
	CEase* selectEaseY;

	// 選択ボタンが押されたかどうかを判定するフラグ
	bool selectFlg = false;
	// 選択されたときのイージングが完了しているか判定するフラグ
	bool selectEnd = false;

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