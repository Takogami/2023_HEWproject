#pragma once
#include "CScene.h"

// リザルト画面の状態
enum class RESULT_STATE
{
	GAMEOVER,
	CLEAR,
};

class ResultScene :
    public CScene
{
private:

	CCursor* cursor;
	CGameObject* retry;
	CGameObject* goToSelect;
	CGameObject* goToTitle;

	CCursor_PointResult cursorPoint = CCursor_PointResult::RETRY;

	// ゲームオーバーであるかクリアであるかを識別
	RESULT_STATE state = RESULT_STATE::GAMEOVER;

	// クリア画面の更新
	void UpdateClear();
	// ゲームオーバー画面の更新
	void UpdateGameOver();

public:
	CCamera* Cam;

	// 使うオブジェクトのリスト
	// まとめてUpdateとDrawを行うために使用
	std::list<CGameObject*>Objects;

	// オブジェクトの描画
	ID3D11Buffer* vertexBufferObject;

	// ステージのプレビュー
	CGameObject* GameOverObj;

	// リザルト遷移前のステージが何だったか
	int prevScene = 0;

	ResultScene();
	~ResultScene() override;

	// リザルト遷移前のステージの設定
	// ※SCENE_ID型が相互インクルードで使えないためint型で指定してください
	void SetPrevStage(int prev);

	/* ------CSceneの関数のオーバーライド------ */
	void Update() override;
	void Draw() override;
};

