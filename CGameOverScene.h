#pragma once
#include "CScene.h"


enum class SELECT_NUM
{
	CONTINUE = 1,	//	コンテニュー
	TITLE,		//	タイトルシーン
};


class CGameOverScene :
    public CScene
{
private:


public:
	CCamera* Cam;

	// 使うオブジェクトのリスト
	// まとめてUpdateとDrawを行うために使用
	std::list<CGameObject*>Objects;

	// オブジェクトの描画
	ID3D11Buffer* vertexBufferObject;

	// 選択を促す文章
	CDrawString* StageSelect;

	// 選択中のステージ番号
	int stageNum = 1;
	// 選択中のステージ
	SELECT_NUM userSelect = SELECT_NUM::CONTINUE;

	// ステージのプレビュー
	CGameObject* StagePreview;

	// ステージの選択オブジェクトのリスト
	std::vector<CGameObject*> StageList;
	// ステージリストの数
	const int listNum = 2;
	// 動きの終了位置
	std::vector<float> moveEndPos;
	// 動きの開始管理フラグ
	bool selectMoveUp = false;
	bool selectMoveDown = false;
	// ステージ選択のイージング
	std::vector<CEase*> selectEase;


public:
	CGameOverScene();
	~CGameOverScene() override;

	/* ------CSceneの関数のオーバーライド------ */
	void Update() override;
	void Draw() override;
};

