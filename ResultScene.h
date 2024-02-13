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

	CCamera* Cam;

	// 使うオブジェクトのリスト
	// まとめてUpdateとDrawを行うために使用
	std::list<CGameObject*>Objects;

	// オブジェクトの描画
	ID3D11Buffer* vertexBufferObject;

	/*---------------ゲームオーバー画面のオブジェクト-----------------------*/
	CCursor* cursor;
	CGameObject* bg;
	CGameObject* retry;
	CGameObject* goToSelect;
	CGameObject* goToTitle;
	CGameObject* GameOverObj;
	CGameObject* GameOverString;
	/*---------------ゲームオーバー画面のオブジェクト-----------------------*/

	/*-------------------クリア画面のオブジェクト---------------------------*/
	CCursor* c_cursor;
	CGameObject* c_bg;
	CGameObject* c_goToSelect;
	CGameObject* c_goToTitle;
	CGameObject* clearString;
	CGameObject* scoreBoard;
	/*-------------------クリア画面のオブジェクト---------------------------*/

	// リザルト遷移前のステージが何だったか
	int prevScene = 0;

	CCursor_PointResult cursorPoint = CCursor_PointResult::RETRY;
	CCursor_PointClear c_cursorPoint = CCursor_PointClear::SELECT;

	// ゲームオーバーであるかクリアであるかを識別
	RESULT_STATE state = RESULT_STATE::CLEAR;

	// 選択のイージング
	CEase* selectEaseX;
	CEase* selectEaseY;

	CEase* gameOverObjEaseX;
	CEase* gameOverObjEaseY;
	// ゲームオーバー文字のイージング
	CEase* gameOverEase;

	CEase* clearStringEaseX;
	CEase* clearStringEaseY;

	// 選択ボタンが押されたかどうかを判定するフラグ
	bool selectFlg = false;
	// 選択されたときのイージングが完了しているか判定するフラグ
	bool selectEnd = false;

	// クリア画面の更新
	void UpdateClear();
	// ゲームオーバー画面の更新
	void UpdateGameOver();

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

