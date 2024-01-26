#pragma once
#include "CScene.h"
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

	// 表示するステージの名前
	CDrawString* StageName;
	// 選択を促す文章
	CDrawString* StageSelect;

public:
	SelectScene();
	~SelectScene();

	/* ------CSceneの関数のオーバーライド------ */
	void Update() override;
	void Draw() override;
};

