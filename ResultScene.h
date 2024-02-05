#pragma once
#include "CScene.h"

// リザルト画面の状態
enum class RESULT_STATE
{
	GAMEOVER,
	CLEAR,
};

enum class RESULT_SELECT
{
	CONTINUE = 1,	//	コンテニュー
	TITLE,			//	タイトルシーン
};

class ResultScene :
    public CScene
{
private:

	CCursor* cursor;
	CGameObject* retry;
	CGameObject* goToSelect;
	CGameObject* goToTitle;

	CCursor_PointResult cursorPoint;

public:
	CCamera* Cam;

	// 使うオブジェクトのリスト
	// まとめてUpdateとDrawを行うために使用
	std::list<CGameObject*>Objects;

	// オブジェクトの描画
	ID3D11Buffer* vertexBufferObject;

	// 選択中のステージ番号
	int stageNum = 1;
	// 選択中のステージ
	RESULT_SELECT userSelect = RESULT_SELECT::CONTINUE;

	// ステージのプレビュー
	CGameObject* GameOverObj;

	// リザルト遷移前のステージが何だったか
	int prevScene = 0;

public:
	ResultScene();
	~ResultScene() override;

	// リザルト遷移前のステージの設定
	// ※SCENE_ID型が相互インクルードで使えないためint型で指定してください
	void SetPrevStage(int prev);

	/* ------CSceneの関数のオーバーライド------ */
	void Update() override;
	void Draw() override;
};

