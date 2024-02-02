#pragma once

/* インクルード */
#include <list>
#include "CPlayer.h"
#include "CCursor.h"
#include "CWind.h"
#include "Cdamagetile.h"
#include "CCamera.h"
#include "CTerrainLoader.h"
#include "CTextureLoader.h"
#include "CInput.h"
#include "CDrawString.h"
#include "CEase.h"
#include "CTimer.h"

class CScene
{
private:
	// マップデータに関連する変数群
	// 全てのシーンで共有するため、staticを使用する
	// マップデータを受け取る2次元可変長配列
	static std::vector<std::vector<int>> map_data;
	// マップオブジェクト用の頂点バッファ
	static ID3D11Buffer* vertexBufferMap;

public:
	/* メンバ変数 */
	// マップオブジェクト用のリスト
	static std::list<CGameObject*> map_object;

	/* メソッド */

	// コンストラクタ
	CScene();
	// デスストラクタ
	virtual ~CScene();

	// 読み込んだ地形情報でステージを生成する
	void CreateStage(TERRAIN_ID _id, CCamera* _useCamera);

	// ステージの後片付け(各オブジェクトの解放など)
	static void DestroyStage();

	// ステージの描画のみを行う
	void DrawTerrain();

	// オーバーライドする用の関数
	// シーンの更新処理
	virtual void Update() = 0;
	// 描画
	virtual void Draw() = 0;
};

