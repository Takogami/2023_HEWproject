#pragma once

/* インクルード */
#include <list>
#include "CGameObject.h"
#include "CCamera.h"
#include "CTerrainLoader.h"
#include "CTextureLoader.h"
#include "CInput.h"

class CScene
{
private:

public:
	/* メソッド */

	// コンストラクタ
	CScene();
	// デスストラクタ
	virtual ~CScene();

	// オーバーライドする用の関数
	// シーンの更新処理
	virtual void Update() = 0;
	// 描画
	virtual void Draw() = 0;
};

