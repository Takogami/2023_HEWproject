#pragma once
#include "direct3d.h"

class CScene
{
private:

public:
	CScene();	//コンストラクタ
	virtual ~CScene();	//デスストラクタ

	//オーバーライドする用の関数
	virtual void Update() = 0;	//シーンの更新処理
	virtual void Draw() = 0;	//描画
};

