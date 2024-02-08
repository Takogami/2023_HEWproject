#pragma once
#include "CScene.h"

// ステージ識別
enum class STAGE_NUM
{
	STAGE1 = 1,
	STAGE2 = 2,
	STAGE3 = 3,
	STAGE4,
	STAGE5,
};

class SelectScene :
    public CScene
{
private:
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
	STAGE_NUM userSelect = STAGE_NUM::STAGE1;

	// ステージのプレビュー
	CGameObject* StagePreview;
	CGameObject* StagePreview2;

	// ステージの選択オブジェクトのリスト
	std::vector<CGameObject*>StageList;
	// ステージリストの数
	const int listNum = 5;
	// 動きの終了位置
	std::vector<float> moveEndPos;
	// 動きの開始管理フラグ
	bool selectMoveUp = false;
	bool selectMoveDown = false;
	// ステージ選択のイージング
	std::vector<CEase*> selectEase;


public:
	SelectScene();
	~SelectScene() override;

	/* ------CSceneの関数のオーバーライド------ */
	void Update() override;
	void Draw() override;
};

